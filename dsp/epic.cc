// generated from file '../dkbuild/epic//epic.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)

#include "epic_table.h"

namespace epic {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec1[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec3[2];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fRec4[3];
	double 	fRec2[4];
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec5[2];
	double 	fRec0[11];
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;

	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "epic";
	name = N_("Epiphone");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<4; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<11; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (5.99165054431605e-48 * fConst0);
	fConst2 = (5.98247960327493e-16 + (fConst0 * ((fConst0 * (9.24890398994427e-18 + (fConst0 * ((fConst0 * (1.70561336817518e-23 + (fConst0 * ((fConst0 * (1.00907394223877e-30 + (fConst0 * ((fConst0 * (6.49379095501319e-39 + (fConst0 * (fConst1 - 2.62868525686115e-43)))) - 9.95591450689114e-35)))) - 6.13054612415728e-27)))) - 1.5501659604586e-20)))) - 1.20111649936669e-15)));
	fConst3 = (5.99165054431605e-47 * fConst0);
	fConst4 = faustpower<2>(fConst0);
	fConst5 = (5.98247960327493e-15 + (fConst0 * ((fConst0 * (5.54934239396656e-17 + (fConst0 * ((fConst0 * (3.41122673635035e-23 + (fConst4 * ((fConst0 * (3.98236580275646e-34 + (fConst0 * ((fConst0 * (2.10294820548892e-42 - fConst3)) - 3.89627457300792e-38)))) - 2.01814788447754e-30)))) - 6.20066384183438e-20)))) - 9.60893199493352e-15)));
	fConst6 = (2.69624274494222e-46 * fConst0);
	fConst7 = (2.69211582147372e-14 + (fConst0 * ((fConst0 * (1.20235751869276e-16 + (fConst0 * ((fConst0 * ((fConst0 * (3.06527306207864e-26 + (fConst0 * ((fConst0 * ((fConst0 * (8.44192824151715e-38 + (fConst0 * (fConst6 - 7.09745019352511e-42)))) - 2.98677435206734e-34)) - 3.02722182671631e-30)))) - 5.11684010452553e-23)) - 4.65049788137579e-20)))) - 3.24301454829006e-14)));
	fConst8 = (7.18998065317926e-46 * fConst0);
	fConst9 = (7.17897552392991e-14 + (fConst0 * ((fConst0 * (7.39912319195542e-17 + (fConst0 * (1.24013276836688e-19 + (fConst0 * ((fConst4 * (8.07259153791017e-30 + (fConst0 * ((fConst0 * ((fConst0 * (1.26176892329335e-41 - fConst8)) - 5.19503276401056e-38)) - 7.96473160551291e-34)))) - 1.36449069454014e-22)))))) - 5.76535919696011e-14)));
	fConst10 = (1.25824661430637e-45 * fConst0);
	fConst11 = (1.25632071668773e-13 + (fConst0 * ((fConst0 * ((fConst0 * (2.17023234464203e-19 + (fConst0 * (3.41122673635035e-23 + (fConst0 * ((fConst0 * (2.01814788447754e-30 + (fConst0 * (1.39382803096476e-33 + (fConst0 * ((fConst0 * (fConst10 - 1.10404780788168e-41)) - 9.09130733701847e-38)))))) - 6.13054612415728e-26)))))) - 1.2948465585922e-16)) - 5.0446892973401e-14)));
	fConst12 = (1.50758486002528e-13 + (fConst4 * ((fConst4 * (2.04673604181021e-22 + (fConst4 * ((fConst4 * (1.81826146740369e-37 - (1.50989593716764e-45 * fConst4))) - 1.21088873068653e-29)))) - 2.5896931171844e-16)));
	fConst13 = (1.25632071668773e-13 + (fConst0 * (5.0446892973401e-14 + (fConst0 * ((fConst0 * ((fConst0 * (3.41122673635035e-23 + (fConst0 * (6.13054612415728e-26 + (fConst0 * (2.01814788447754e-30 + (fConst0 * ((fConst0 * ((fConst0 * (1.10404780788168e-41 + fConst10)) - 9.09130733701847e-38)) - 1.39382803096476e-33)))))))) - 2.17023234464203e-19)) - 1.2948465585922e-16)))));
	fConst14 = (7.17897552392991e-14 + (fConst0 * (5.76535919696011e-14 + (fConst0 * (7.39912319195542e-17 + (fConst0 * ((fConst0 * ((fConst4 * (8.07259153791017e-30 + (fConst0 * (7.96473160551291e-34 + (fConst0 * ((fConst0 * (0 - (1.26176892329335e-41 + fConst8))) - 5.19503276401056e-38)))))) - 1.36449069454014e-22)) - 1.24013276836688e-19)))))));
	fConst15 = (2.69211582147372e-14 + (fConst0 * (3.24301454829006e-14 + (fConst0 * (1.20235751869276e-16 + (fConst0 * (4.65049788137579e-20 + (fConst0 * ((fConst0 * ((fConst0 * ((fConst0 * (2.98677435206734e-34 + (fConst0 * (8.44192824151715e-38 + (fConst0 * (7.09745019352511e-42 + fConst6)))))) - 3.02722182671631e-30)) - 3.06527306207864e-26)) - 5.11684010452553e-23)))))))));
	fConst16 = (5.98247960327493e-15 + (fConst0 * (9.60893199493352e-15 + (fConst0 * (5.54934239396656e-17 + (fConst0 * (6.20066384183438e-20 + (fConst0 * (3.41122673635035e-23 + (fConst4 * ((fConst0 * ((fConst0 * ((fConst0 * (0 - (2.10294820548892e-42 + fConst3))) - 3.89627457300792e-38)) - 3.98236580275646e-34)) - 2.01814788447754e-30)))))))))));
	fConst17 = (5.98247960327493e-16 + (fConst0 * (1.20111649936669e-15 + (fConst0 * (9.24890398994427e-18 + (fConst0 * (1.5501659604586e-20 + (fConst0 * (1.70561336817518e-23 + (fConst0 * (6.13054612415728e-27 + (fConst0 * (1.00907394223877e-30 + (fConst0 * (9.95591450689114e-35 + (fConst0 * (6.49379095501319e-39 + (fConst0 * (2.62868525686115e-43 + fConst1)))))))))))))))))));
	fConst18 = (1.0 / fConst17);
	fConst19 = (1.75575379672823e-16 * fConst0);
	fConst20 = ((fConst0 * (0 - (1.86381864076869e-14 + fConst19))) - 1.49347061016142e-13);
	fConst21 = (1.75636706304418e-16 * fConst0);
	fConst22 = ((fConst0 * (fConst21 - 1.68121475890895e-13)) - 1.96785108195018e-11);
	fConst23 = (8.78183531522092e-15 * fConst0);
	fConst24 = (8.10287245938644e-09 + (fConst0 * (1.01871220761924e-09 + (fConst0 * (1.04590056454411e-11 + fConst23)))));
	fConst25 = (1.04718061969763e-14 * fConst0);
	fConst26 = (fConst25 - 1.08151526492492e-12);
	fConst27 = (1.49347061016142e-13 + (fConst0 * (fConst19 - 1.86381864076869e-14)));
	fConst28 = (1.96785108195018e-11 + (fConst0 * (0 - (1.68121475890895e-13 + fConst21))));
	fConst29 = (8.10287245938644e-09 + (fConst0 * ((fConst0 * (1.04590056454411e-11 - fConst23)) - 1.01871220761924e-09)));
	fConst30 = (5.26726139018469e-16 * fConst0);
	fConst31 = (1.49347061016142e-13 + (fConst0 * (1.86381864076869e-14 - fConst30)));
	fConst32 = (5.26910118913255e-16 * fConst0);
	fConst33 = (1.96785108195018e-11 + (fConst0 * (1.68121475890895e-13 + fConst32)));
	fConst34 = (2.63455059456628e-14 * fConst0);
	fConst35 = (2.43086173781593e-08 + (fConst0 * ((fConst0 * (fConst34 - 1.04590056454411e-11)) - 1.01871220761924e-09)));
	fConst36 = ((fConst0 * (1.86381864076869e-14 + fConst30)) - 1.49347061016142e-13);
	fConst37 = ((fConst0 * (1.68121475890895e-13 - fConst32)) - 1.96785108195018e-11);
	fConst38 = (2.43086173781593e-08 + (fConst0 * (1.01871220761924e-09 + (fConst0 * (0 - (1.04590056454411e-11 + fConst34))))));
	fConst39 = (1.09867843155018e-24 * fConst0);
	fConst40 = ((fConst0 * (0 - (2.15695136744491e-23 + fConst39))) - 4.56823883901493e-23);
	fConst41 = (1.65586876023392e-24 * fConst0);
	fConst42 = (9.13647767802987e-23 + (fConst0 * (3.38160909427453e-23 + fConst41)));
	fConst43 = (4.33843373719161e-10 * fConst0);
	fConst44 = (2.37823472375625e-08 + (fConst0 * (8.85089934800159e-09 + fConst43)));
	fConst45 = ((fConst0 * (2.15695136744491e-23 - fConst39)) - 4.56823883901493e-23);
	fConst46 = (9.13647767802987e-23 + (fConst0 * (fConst41 - 3.38160909427453e-23)));
	fConst47 = (2.37823472375625e-08 + (fConst0 * (fConst43 - 8.85089934800159e-09)));
	fConst48 = ((2.19735686310035e-24 * fConst4) - 9.13647767802987e-23);
	fConst49 = (1.82729553560597e-22 - (3.31173752046785e-24 * fConst4));
	fConst50 = (4.7564694475125e-08 - (8.67686747438322e-10 * fConst4));
	fConst51 = (3.14154185909289e-14 * fConst0);
	fConst52 = (1.08151526492492e-12 - fConst51);
	fConst53 = (1.08151526492492e-12 + fConst51);
	fConst54 = (0 - (1.08151526492492e-12 + fConst25));
	fConst55 = (3.24388245742757e-26 * fConst0);
	fConst56 = (1.07364025155065e-19 + (fConst0 * (2.34392421378708e-23 - fConst55)));
	fConst57 = ((fConst0 * (2.34392421378708e-23 + fConst55)) - 1.07364025155065e-19);
	fConst58 = (9.37569685514831e-23 * fConst0);
	fConst59 = (0 - (6.13508715171799e-20 + fConst58));
	fConst60 = (1.62194122871379e-26 * fConst0);
	fConst61 = (2.30065768189425e-20 + (fConst0 * (0 - (3.51588632068062e-23 + fConst60))));
	fConst62 = (2.34392421378708e-23 * fConst0);
	fConst63 = (3.067543575859e-20 + fConst62);
	fConst64 = (3.24388245742758e-27 * fConst0);
	fConst65 = (7.66885893964749e-21 + (fConst0 * (1.17196210689354e-23 + fConst64)));
	fConst66 = (6.13508715171799e-20 - fConst58);
	fConst67 = ((fConst0 * (fConst60 - 3.51588632068062e-23)) - 2.30065768189425e-20);
	fConst68 = (fConst62 - 3.067543575859e-20);
	fConst69 = ((fConst0 * (1.17196210689354e-23 - fConst64)) - 7.66885893964749e-21);
	fConst70 = (1.40635452827225e-22 * fConst0);
	fConst71 = (faustpower<3>(fConst0) / fConst17);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.00036676987543879196 * (exp((3 * double(fslider1))) - 1));
	double 	fSlow2 = (0.0010956234992476606 * (exp((2 * double(fslider2))) - 1));
	for (int i=0; i<count; i++) {
		fRec1[0] = (fSlow0 + (0.993 * fRec1[1]));
		double fTemp0 = (fConst24 + (fRec1[0] * ((fConst0 * (fConst22 + (fConst20 * fRec1[0]))) - 1.58879852144832e-10)));
		fRec3[0] = (fSlow1 + (0.993 * fRec3[1]));
		double fTemp1 = (fConst44 + (fRec3[0] * (fConst42 + (fConst40 * fRec3[0]))));
		fRec4[0] = ((double)input0[i] - (((fRec4[1] * (fConst50 + (fRec3[0] * (fConst49 + (fConst48 * fRec3[0]))))) + (fRec4[2] * (fConst47 + (fRec3[0] * (fConst46 + (fConst45 * fRec3[0])))))) / fTemp1));
		fRec2[0] = (circclip((fConst4 * (((fRec4[1] * (0 - (2.80697849952188e-09 + (1.37541946476572e-07 * fRec3[0])))) + ((1.40348924976094e-09 + (6.8770973238286e-08 * fRec3[0])) * (fRec4[2] + fRec4[0]))) / fTemp1))) - ((((fRec2[1] * (fConst38 + (fRec1[0] * ((fConst0 * (fConst37 + (fConst36 * fRec1[0]))) - 4.76639556434497e-10)))) + (fRec2[2] * (fConst35 + (fRec1[0] * ((fConst0 * (fConst33 + (fConst31 * fRec1[0]))) - 4.76639556434497e-10))))) + (fRec2[3] * (fConst29 + (fRec1[0] * ((fConst0 * (fConst28 + (fConst27 * fRec1[0]))) - 1.58879852144832e-10))))) / fTemp0));
		fRec5[0] = (fSlow2 + (0.993 * fRec5[1]));
		fRec0[0] = ((fConst0 * ((fRec5[0] * ((((fRec2[0] * ((fConst0 * ((fConst54 * fRec1[0]) - 1.11402193584854e-11)) - 1.15054815417545e-09)) + (fRec2[1] * ((fConst0 * (1.11402193584854e-11 + (fConst53 * fRec1[0]))) - 1.15054815417545e-09))) + (fRec2[2] * (1.15054815417545e-09 + (fConst0 * (1.11402193584854e-11 + (fConst52 * fRec1[0])))))) + (fRec2[3] * (1.15054815417545e-09 + (fConst0 * ((fConst26 * fRec1[0]) - 1.11402193584854e-11)))))) / fTemp0)) - (fConst18 * ((((((((((fConst16 * fRec0[1]) + (fConst15 * fRec0[2])) + (fConst14 * fRec0[3])) + (fConst13 * fRec0[4])) + (fConst12 * fRec0[5])) + (fConst11 * fRec0[6])) + (fConst9 * fRec0[7])) + (fConst7 * fRec0[8])) + (fConst5 * fRec0[9])) + (fConst2 * fRec0[10]))));
		output0[i] = (FAUSTFLOAT)(fConst71 * ((fConst70 * fRec0[5]) + ((fConst69 * fRec0[10]) + ((fConst68 * fRec0[9]) + ((fConst67 * fRec0[8]) + ((fConst66 * fRec0[7]) + ((((((fConst65 * fRec0[0]) + (fConst63 * fRec0[1])) + (fConst61 * fRec0[2])) + (fConst59 * fRec0[3])) + (fConst57 * fRec0[4])) + (fConst56 * fRec0[6]))))))));
		// post processing
		for (int i=10; i>0; i--) fRec0[i] = fRec0[i-1];
		fRec5[1] = fRec5[0];
		for (int i=3; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case GAIN: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TONE: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   GAIN, 
   TONE, 
   VOLUME, 
} PortIndex;
*/

} // end namespace epic
