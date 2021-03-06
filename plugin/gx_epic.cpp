/*
 * Copyright (C) 2014 Guitarix project MOD project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 */


#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <unistd.h>

///////////////////////// MACRO SUPPORT ////////////////////////////////

#define __rt_func __attribute__((section(".rt.text")))
#define __rt_data __attribute__((section(".rt.data")))

///////////////////////// FAUST SUPPORT ////////////////////////////////

#define FAUSTFLOAT float
#ifndef N_
#define N_(String) (String)
#endif
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define always_inline inline __attribute__((always_inline))

template <int32_t N> inline float faustpower(float x)
{
  return powf(x, N);
}
template <int32_t N> inline double faustpower(double x)
{
  return pow(x, N);
}
template <int32_t N> inline int32_t faustpower(int32_t x)
{
  return faustpower<N/2>(x) * faustpower<N-N/2>(x);
}
template <>      inline int32_t faustpower<0>(int32_t x)
{
  return 1;
}
template <>      inline int32_t faustpower<1>(int32_t x)
{
  return x;
}

////////////////////////////// LOCAL INCLUDES //////////////////////////

#include "gx_epic.h"        // define struct PortIndex
#include "gx_pluginlv2.h"   // define struct PluginLV2
#include "epic.cc"    // dsp class generated by faust -> dsp2cc
#include "epicbooster.cc"    // dsp class generated by faust -> dsp2cc

////////////////////////////// PLUG-IN CLASS ///////////////////////////

namespace epic {

class Gx_epic_
{
private:
  // pointer to buffer
  float*          output;
  float*          input;
  // pointer to dsp class
  PluginLV2*      epic;
  PluginLV2*      epicbooster;

  // bypass ramping
  float*          bypass;
  uint32_t        bypass_;
  // booster
  float*          boost;
  uint32_t        boost_;
 
  bool            needs_ramp_down;
  bool            needs_ramp_up;
  float           ramp_down;
  float           ramp_up;
  float           ramp_up_step;
  float           ramp_down_step;
  bool            bypassed;

  bool            needs_boost_down;
  bool            needs_boost_up;
  float           boost_down;
  float           boost_up;
  bool            boosted;

  // private functions
  inline void run_dsp_(uint32_t n_samples);
  inline void connect_(uint32_t port,void* data);
  inline void init_dsp_(uint32_t rate);
  inline void connect_all__ports(uint32_t port, void* data);
  inline void activate_f();
  inline void clean_up();
  inline void deactivate_f();

public:
  // LV2 Descriptor
  static const LV2_Descriptor descriptor;
  // static wrapper to private functions
  static void deactivate(LV2_Handle instance);
  static void cleanup(LV2_Handle instance);
  static void run(LV2_Handle instance, uint32_t n_samples);
  static void activate(LV2_Handle instance);
  static void connect_port(LV2_Handle instance, uint32_t port, void* data);
  static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
  Gx_epic_();
  ~Gx_epic_();
};

// constructor
Gx_epic_::Gx_epic_() :
  output(NULL),
  input(NULL),
  epic(epic::plugin()),
  epicbooster(epicbooster::plugin()),
  bypass(0),
  bypass_(2),
  boost(0),
  boost_(2),
  needs_ramp_down(false),
  needs_ramp_up(false),
  bypassed(false),
  needs_boost_down(false),
  needs_boost_up(false),
  boosted(false) {};

// destructor
Gx_epic_::~Gx_epic_()
{
  // just to be sure the plug have given free the allocated mem
  // it didn't hurd if the mem is already given free by clean_up()
  if (epic->activate_plugin !=0)
    epic->activate_plugin(false, epic);
  // delete DSP class
  epic->delete_instance(epic);
  if (epicbooster->activate_plugin !=0)
    epicbooster->activate_plugin(false, epicbooster);
  // delete DSP class
  epicbooster->delete_instance(epicbooster);
};

///////////////////////// PRIVATE CLASS  FUNCTIONS /////////////////////

void Gx_epic_::init_dsp_(uint32_t rate)
{
  // set values for internal ramping
  ramp_down_step = 32 * (256 * rate) / 48000; 
  ramp_up_step = ramp_down_step;
  ramp_down = ramp_down_step;
  ramp_up = 0.0;
  boost_down = ramp_down_step;
  boost_up = 0.0;

  epic->set_samplerate(rate, epic); // init the DSP class
  epicbooster->set_samplerate(rate, epicbooster); // init the DSP class
}

// connect the Ports used by the plug-in class
void Gx_epic_::connect_(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case EFFECTS_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case EFFECTS_INPUT:
      input = static_cast<float*>(data);
      break;
    case BYPASS: 
      bypass = static_cast<float*>(data); // , 0.0, 0.0, 1.0, 1.0 
      break;
    case BOOST: 
      boost = static_cast<float*>(data); // , 0.0, 0.0, 1.0, 1.0 
      break;
    default:
      break;
    }
}

void Gx_epic_::activate_f()
{
  // allocate the internal DSP mem
  if (epic->activate_plugin !=0)
    epic->activate_plugin(true, epic);
  if (epicbooster->activate_plugin !=0)
    epicbooster->activate_plugin(true, epicbooster);
}

void Gx_epic_::clean_up()
{
  // delete the internal DSP mem
  if (epic->activate_plugin !=0)
    epic->activate_plugin(false, epic);
  if (epicbooster->activate_plugin !=0)
    epicbooster->activate_plugin(false, epicbooster);
}

void Gx_epic_::deactivate_f()
{
  // delete the internal DSP mem
  if (epic->activate_plugin !=0)
    epic->activate_plugin(false, epic);
  if (epicbooster->activate_plugin !=0)
    epicbooster->activate_plugin(false, epicbooster);
}

void Gx_epic_::run_dsp_(uint32_t n_samples)
{
  FAUSTFLOAT buf[n_samples];
  FAUSTFLOAT bbuf[n_samples];
  // do inplace processing at default
  memcpy(output, input, n_samples*sizeof(float));
  // check if bypass is pressed
  if (boost_ != static_cast<uint32_t>(*(boost))) {
    boost_ = static_cast<uint32_t>(*(boost));
    if (!boost_) {
      needs_boost_down = true;
    } else {
      needs_boost_up = true;
      boosted = true;
    }
  }
  if (bypass_ != static_cast<uint32_t>(*(bypass))) {
    bypass_ = static_cast<uint32_t>(*(bypass));
    ramp_down = ramp_down_step;
    ramp_up = 0.0;    
    if (!bypass_) {
      needs_ramp_down = true;
      needs_ramp_up = false;
    } else {
      needs_ramp_down = false;
      needs_ramp_up = true;
      bypassed = false;
    }
  }

  if (needs_ramp_down || needs_ramp_up) {
       memcpy(buf, input, n_samples*sizeof(float));
  }
  // check if boost raming is needed
  if (needs_boost_down || needs_boost_up) {
    memcpy(bbuf, input, n_samples*sizeof(float));
  }
  
  if (!bypassed) {
    if (boosted) epicbooster->mono_audio(static_cast<int>(n_samples), output, output, epicbooster);

      // check if boost rammping is needed
      if (needs_boost_down) {
        for (uint32_t i=0; i<n_samples; i++) {
          if (boost_down >= 0.0) {
            --boost_down;
          }
          float fade = max(0.0,boost_down) /ramp_down_step;
          output[i] = output[i] * fade + bbuf[i] * (1.0 - fade) ;
        }

        if (boost_down <= 0.0) {
          // when ramped down, clear buffer from valvecasterbuster class
          epicbooster->clear_state(epicbooster);
          needs_boost_down = false;
          boosted = false;
          boost_down = ramp_down_step;
        } else {
          boost_up = boost_down;
        }

      } else if (needs_boost_up) {
        for (uint32_t i=0; i<n_samples; i++) {
          if (boost_up <= ramp_up_step) {
            ++boost_up;
          }
          float fade = min(8192.0,boost_up) /ramp_up_step;
          output[i] = output[i] * fade + bbuf[i] * (1.0 - fade) ;
        }
        if (boost_up >= ramp_up_step) {
          needs_boost_up = false;
          boost_up = 0.0;
        } else {
          boost_down = boost_up;
        }
      }
    
     epic->mono_audio(static_cast<int>(n_samples), output, output, epic);
  }

  // check if ramping is needed
  if (needs_ramp_down) {
    float fade = 0;
    for (uint32_t i=0; i<n_samples; i++) {
      if (ramp_down >= 0.0) {
        --ramp_down; 
      }
      fade = max(0.0,ramp_down) /ramp_down_step ;
      output[i] = output[i] * fade + buf[i] * (1.0 - fade);
    }

    if (ramp_down <= 0.0) {
      // when ramped down, clear buffer from epic class
      epic->clear_state(epic);
      epicbooster->clear_state(epicbooster);
      needs_ramp_down = false;
      bypassed = true;
      ramp_down = ramp_down_step;
      ramp_up = 0.0;
      boost_down = ramp_down_step;
      boost_up = 0.0;
    } else {
      ramp_up = ramp_down;
    }

  } else if (needs_ramp_up) {
    float fade = 0;
    for (uint32_t i=0; i<n_samples; i++) {
      if (ramp_up < ramp_up_step) {
        ++ramp_up ;
      }
      fade = min(ramp_up_step,ramp_up) /ramp_up_step ;
      output[i] = output[i] * fade + buf[i] * (1.0 - fade);
    }

    if (ramp_up >= ramp_up_step) {
      needs_ramp_up = false;
      ramp_up = 0.0;
      ramp_down = ramp_down_step;
    } else {
      ramp_down = ramp_up;
    }
  }

}

void Gx_epic_::connect_all__ports(uint32_t port, void* data)
{
  // connect the Ports used by the plug-in class
  connect_(port,data); 
  // connect the Ports used by the DSP class
  epic->connect_ports(port,  data, epic);
  epicbooster->connect_ports(port,  data, epicbooster);
}

////////////////////// STATIC CLASS  FUNCTIONS  ////////////////////////

LV2_Handle 
Gx_epic_::instantiate(const LV2_Descriptor* descriptor,
                            double rate, const char* bundle_path,
                            const LV2_Feature* const* features)
{
  // init the plug-in class
  Gx_epic_ *self = new Gx_epic_();
  if (!self) {
    return NULL;
  }

  self->init_dsp_((uint32_t)rate);

  return (LV2_Handle)self;
}

void Gx_epic_::connect_port(LV2_Handle instance, 
                                   uint32_t port, void* data)
{
  // connect all ports
  static_cast<Gx_epic_*>(instance)->connect_all__ports(port, data);
}

void Gx_epic_::activate(LV2_Handle instance)
{
  // allocate needed mem
  static_cast<Gx_epic_*>(instance)->activate_f();
}

void Gx_epic_::run(LV2_Handle instance, uint32_t n_samples)
{
  // run dsp
  static_cast<Gx_epic_*>(instance)->run_dsp_(n_samples);
}

void Gx_epic_::deactivate(LV2_Handle instance)
{
  // free allocated mem
  static_cast<Gx_epic_*>(instance)->deactivate_f();
}

void Gx_epic_::cleanup(LV2_Handle instance)
{
  // well, clean up after us
  Gx_epic_* self = static_cast<Gx_epic_*>(instance);
  self->clean_up();
  delete self;
}

const LV2_Descriptor Gx_epic_::descriptor =
{
  GXPLUGIN_URI "#_epic_",
  Gx_epic_::instantiate,
  Gx_epic_::connect_port,
  Gx_epic_::activate,
  Gx_epic_::run,
  Gx_epic_::deactivate,
  Gx_epic_::cleanup,
  NULL
};


} // end namespace epic

////////////////////////// LV2 SYMBOL EXPORT ///////////////////////////

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index)
    {
    case 0:
      return &epic::Gx_epic_::descriptor;
    default:
      return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
