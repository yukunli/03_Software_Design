
#include "ConstData_Table.h"
#include <math.h>

void SINCOS_TAB(float * Sin_tab,float *Cos_tab,unsigned int cycle_point)
{
	unsigned int i;
	float theta;
	for(i = 0; i < cycle_point; i++)
	{
		theta = i* 6.283185/cycle_point;   //2pi = 6.283185, 
		Sin_tab[i] = sin(theta)+1.0;
		Cos_tab[i] = cos(theta)+1.0;
	}
}
/*
//测量通道5.2KHZ待测信号的参考正余弦信号，采样频率135kHZ  
float sin_wave1[390]=
{
	0.000000,0.238941,0.464039,0.662255,0.822106,0.934330,0.992427,0.993031,0.936107,0.824953,0.666007,0.468479,0.243811,0.005018,-0.234065,-0.459588,-0.658487,-0.819238,-0.932530,-0.991798,-0.993610,-0.937860,-0.827779,-0.669742,-0.472907,-0.248675,-0.010037,0.229183,0.455125,0.654702,0.816350,0.930706,0.991144,0.994164,0.939590,0.830584,0.673461,0.477323,0.253533,0.015055,-0.224295,-0.450651,-0.650900,-0.813441,-0.928858,-0.990465,-0.994693,-0.941296,-0.833368,-0.677162,-0.481727,-0.258384,-0.020073,0.219401,0.446165,0.647082,0.810512,0.926988,0.989761,0.995197,0.942978,0.836131,0.680846,0.486118,0.263229,0.025090,-0.214502,-0.441668,-0.643248,-0.807562,-0.925094,-0.989033,-0.995675,-0.944637,-0.838874,-0.684513,-0.490498,-0.268067,-0.030107,0.209598,0.437160,0.639397,0.804592,0.923176,0.988279,0.996129,0.946272,0.841595,0.688163,0.494865,0.272898,0.035122,-0.204688,-0.432641,-0.635530,-0.801602,-0.921236,-0.987500,-0.996558,-0.947882,-0.844295,-0.691796,-0.499220,-0.277723,-0.040137,0.199774,0.428111,0.631648,0.798592,0.919272,0.986697,0.996961,0.949470,0.846974,0.695411,0.503562,0.282541,0.045151,-0.194854,-0.423570,-0.627749,-0.795561,-0.917285,-0.985869,-0.997339,-0.951033,-0.849631,-0.699008,-0.507891,-0.287351,-0.050164,0.189929,0.419019,0.623835,0.792510,0.915275,0.985016,0.997693,0.952572,0.852267,0.702588,0.512208,0.292154,0.055176,-0.184999,-0.414457,-0.619905,-0.789440,-0.913242,-0.984138,-0.998021,-0.954087,-0.854881,-0.706151,-0.516512,-0.296950,-0.060186,0.180065,0.409885,0.615959,0.786349,0.911186,0.983235,0.998324,0.955578,0.857474,0.709695,0.520802,0.301739,0.065194,-0.175126,-0.405302,-0.611998,-0.783239,-0.909106,-0.982307,-0.998602,-0.957045,-0.860046,-0.713222,-0.525080,-0.306519,-0.070201,0.170183,0.400709,0.608021,0.780109,0.907004,0.981355,0.998855,0.958488,0.862595,0.716731,0.529344,0.311292,0.075207,-0.165236,-0.396106,-0.604029,-0.776960,-0.904880,-0.980378,-0.999082,-0.959907,-0.865123,-0.720221,-0.533595,-0.316058,-0.080210,0.160284,0.391493,0.600022,0.773790,0.902732,0.979377,0.999284,0.961302,0.867629,0.723694,0.537833,0.320815,0.085211,-0.155329,-0.386870,-0.596000,-0.770602,-0.900562,-0.978350,-0.999462,-0.962672,-0.870114,-0.727148,-0.542057,-0.325564,-0.090211,0.150369,0.382238,0.591962,0.767394,0.898369,0.977300,0.999614,0.964019,0.872576,0.730584,0.546268,0.330305,0.095207,-0.145406,-0.377595,-0.587910,-0.764166,-0.896153,-0.976224,-0.999741,-0.965341,-0.875017,-0.734001,-0.550464,-0.335038,-0.100202,0.140439,0.372944,0.583843,0.760920,0.893915,0.975124,0.999842,0.966638,0.877435,0.737400,0.554647,0.339762,0.105194,-0.135468,-0.368282,-0.579761,-0.757654,-0.891654,-0.973999,-0.999919,-0.967911,-0.879831,-0.740781,-0.558816,-0.344478,-0.110183,0.130494,0.363612,0.575665,0.754369,0.889371,0.972850,0.999970,0.969160,0.882205,0.744143,0.562971,0.349185,0.115170,-0.125517,-0.358933,-0.571554,-0.751065,-0.887065,-0.971676,-0.999996,-0.970385,-0.884557,-0.747486,-0.567111,-0.353883,-0.120153,0.120537,0.354244,0.567429,0.747742,0.884737,0.970478,0.999997,0.971585,0.886887,0.750810,0.571238,0.358572,0.125134,-0.115553,-0.349546,-0.563290,-0.744401,-0.882387,-0.969255,-0.999973,-0.972761,-0.889194,-0.754116,-0.575349,-0.363252,-0.130112,0.110567,0.344840,0.559136,0.741040,0.880015,0.968008,0.999924,0.973912,0.891479,0.757402,0.579447,0.367924,0.135086,-0.105578,-0.340125,-0.554968,-0.737661,-0.877620,-0.966737,-0.999849,-0.975038,-0.893742,-0.760669,-0.583530,-0.372585,-0.140057,0.100586,0.335401,0.550787,0.734264,0.875203,0.965441,0.999749,0.976140,0.895982,0.763917,0.587598,0.377238,0.145024,-0.095592,-0.330669,-0.546591,-0.730847,-0.872765,-0.964121,-0.999624,-0.977218,-0.898199,-0.767146,-0.591651,-0.381881,
};
float cos_wave1[390]=
{
	1.000000,0.971034,0.885815,0.749278,0.569335,0.356409,0.122836,-0.117854,-0.351716,-0.565202,-0.745945,-0.883475,-0.969823,-0.999987,-0.972221,-0.888132,-0.752592,-0.573453,-0.361093,-0.127815,0.112869,0.347013,0.561055,0.742594,0.881112,0.968587,0.999950,0.973383,0.890427,0.755887,0.577558,0.365769,0.132790,-0.107881,-0.342302,-0.556894,-0.739223,-0.878728,-0.967327,-0.999887,-0.974521,-0.892700,-0.759164,-0.581647,-0.370435,-0.137763,0.102890,0.337583,0.552718,0.735834,0.876322,0.966042,0.999799,0.975635,0.894951,0.762421,0.585722,0.375092,0.142732,-0.097897,-0.332854,-0.548529,-0.732426,-0.873893,-0.964733,-0.999685,-0.976723,-0.897178,-0.765658,-0.589782,-0.379739,-0.147697,0.092901,0.328118,0.544326,0.729000,0.871442,0.963400,0.999547,0.977788,0.899384,0.768877,0.593828,0.384377,0.152659,-0.087903,-0.323373,-0.540109,-0.725556,-0.868970,-0.962043,-0.999383,-0.978827,-0.901566,-0.772076,-0.597858,-0.389005,-0.157616,0.082903,0.318620,0.535879,0.722093,0.866475,0.960661,0.999194,0.979842,0.903726,0.775256,0.601873,0.393623,0.162570,-0.077901,-0.313859,-0.531635,-0.718612,-0.863959,-0.959255,-0.998980,-0.980832,-0.905863,-0.778416,-0.605873,-0.398232,-0.167520,0.072897,0.309090,0.527378,0.715113,0.861421,0.957825,0.998741,0.981798,0.907977,0.781556,0.609858,0.402830,0.172465,-0.067891,-0.304314,-0.523107,-0.711596,-0.858861,-0.956371,-0.998477,-0.982739,-0.910069,-0.784677,-0.613828,-0.407418,-0.177406,0.062883,0.299529,0.518824,0.708062,0.856280,0.954893,0.998187,0.983655,0.912137,0.787778,0.617782,0.411996,0.182343,-0.057874,-0.294738,-0.514527,-0.704509,-0.853677,-0.953391,-0.997873,-0.984546,-0.914183,-0.790860,-0.621720,-0.416564,-0.187275,0.052863,0.289938,0.510217,0.700938,0.851053,0.951864,0.997533,0.985412,0.916205,0.793921,0.625643,0.421121,0.192202,-0.047851,-0.285132,-0.505895,-0.697350,-0.848407,-0.950314,-0.997168,-0.986254,-0.918205,-0.796962,-0.629550,-0.425668,-0.197125,0.042837,0.280318,0.501559,0.693745,0.845740,0.948740,0.996778,0.987071,0.920181,0.799984,0.633442,0.430203,0.202043,-0.037823,-0.275497,-0.497211,-0.690121,-0.843051,-0.947142,-0.996363,-0.987863,-0.922134,-0.802985,-0.637317,-0.434728,-0.206955,0.032808,0.270669,0.492851,0.686481,0.840342,0.945520,0.995923,0.988630,0.924064,0.805966,0.641176,0.439242,0.211862,-0.027791,-0.265835,-0.488478,-0.682823,-0.837611,-0.943874,-0.995457,-0.989372,-0.925971,-0.808926,-0.645019,-0.443745,-0.216764,0.022774,0.260994,0.484093,0.679148,0.834859,0.942205,0.994967,0.990089,0.927854,0.811866,0.648846,0.448237,0.221661,-0.017757,-0.256146,-0.479696,-0.675456,-0.832086,-0.940511,-0.994452,-0.990782,-0.929714,-0.814786,-0.652657,-0.452717,-0.226551,0.012739,0.251291,0.475286,0.671747,0.829292,0.938795,0.993911,0.991449,0.931550,0.817686,0.656451,0.457186,0.231437,-0.007721,-0.246431,-0.470865,-0.668021,-0.826477,-0.937054,-0.993346,-0.992091,-0.933364,-0.820564,-0.660228,-0.461644,-0.236316,0.002702,0.241564,0.466431,0.664278,0.823641,0.935290,0.992755,0.992709,0.935153,0.823422,0.663989,0.466090,0.241189,0.002316,-0.236691,-0.461986,-0.660518,-0.820785,-0.933502,-0.992140,-0.993301,-0.936919,-0.826259,-0.667733,-0.470524,-0.246057,-0.007335,0.231812,0.457530,0.656742,0.817908,0.931691,0.991499,0.993869,0.938661,0.829076,0.671461,0.474946,0.250918,0.012353,-0.226927,-0.453062,-0.652949,-0.815010,-0.929856,-0.990834,-0.994411,-0.940380,-0.831872,-0.675171,-0.479357,-0.255773,-0.017371,0.222037,0.448582,0.649140,0.812092,0.927998,0.990144,0.994928,0.942075,0.834646,0.678865,0.483755,0.260621,0.022388,-0.217141,-0.444091,-0.645314,-0.809153,-0.926116,-0.989428,-0.995421,-0.943747,-0.837400,-0.682541,-0.488141,-0.265463,-0.027405,0.212239,0.439589,0.641472,0.806194,0.924212,
};

float sin_wave2[423]=
{
	0.000000,0.292431,0.559296,0.777263,0.927277,0.996222,0.978070,0.874409,0.694300,0.453492,0.173036,-0.122548,-0.407418,-0.656669,-0.848509,-0.966167,-0.999356,-0.945174,-0.808358,-0.600871,-0.340851,-0.051032,0.243249,0.516264,0.744143,0.906964,0.990492,0.987424,0.898029,0.730122,0.498383,0.223072,-0.071742,-0.360283,-0.617326,-0.820399,-0.951746,-0.999885,-0.960608,-0.837347,-0.640880,-0.388383,-0.101930,0.193434,0.471886,0.709083,0.884287,0.982181,0.994205,0.919310,0.764042,0.541976,0.272527,-0.020748,-0.312209,-0.576375,-0.790150,-0.934845,-0.997809,-0.973538,-0.864154,-0.679219,-0.434902,-0.152563,0.143114,0.426279,0.672175,0.859306,0.971310,0.998396,0.938195,0.795970,0.584157,0.321272,0.030299,-0.263322,-0.533922,-0.757843,-0.915508,-0.993133,-0.983932,-0.888708,-0.715788,-0.480288,-0.202799,0.092421,0.379561,0.633516,0.832086,0.957908,0.999984,0.954635,0.825824,0.624815,0.369180,0.081268,-0.213748,-0.490077,-0.723560,-0.893785,-0.985869,-0.991761,-0.910947,-0.750491,-0.524423,-0.252506,0.041487,0.331853,0.593206,0.802697,0.942011,0.998967,0.968587,0.853526,0.663845,0.416125,0.132025,-0.163618,-0.444956,-0.687393,-0.869733,-0.976035,-0.997006,-0.930812,-0.783239,-0.567191,-0.301555,-0.009554,0.283281,0.551350,0.771217,0.923658,0.995347,0.980015,0.879004,0.701145,0.461986,0.182438,-0.113060,-0.398674,-0.649433,-0.843414,-0.963659,-0.999653,-0.948251,-0.813946,-0.608481,-0.349818,-0.060571,0.233971,0.508058,0.737726,0.902898,0.989132,0.988890,0.902192,0.736618,0.506644,0.232375,-0.062209,-0.351354,-0.609782,-0.814898,-0.948770,-0.999695,-0.963219,-0.842532,-0.648185,-0.397169,-0.111430,0.184051,0.463441,0.702314,0.879785,0.980340,0.995187,0.923028,0.770171,0.549981,0.281707,-0.011195,-0.303118,-0.568541,-0.784258,-0.931410,-0.997132,-0.975677,-0.868922,-0.686200,-0.443486,-0.161999,0.133651,0.417616,0.665071,0.854380,0.968994,0.998891,0.941459,0.801717,0.591885,0.330305,0.039848,-0.254093,-0.525819,-0.751575,-0.911622,-0.991970,-0.985593,-0.893048,-0.722427,-0.488647,-0.212145,0.082903,0.370704,0.626095,0.826748,0.955122,0.999992,0.957436,0.831175,0.632246,0.378042,0.090787,-0.204405,-0.481727,-0.716932,-0.889459,-0.984223,-0.992940,-0.914847,-0.756771,-0.532534,-0.261739,0.031939,0.322825,0.585487,0.796962,0.938761,0.998487,0.970919,0.858466,0.670960,0.424794,0.141490,-0.154184,-0.436379,-0.680422,-0.864978,-0.973912,-0.997699,-0.934261,-0.789144,-0.575034,-0.310650,-0.019108,0.274105,0.543354,0.765099,0.919954,0.994380,0.981871,0.883520,0.707925,0.470439,0.191824,-0.103562,-0.389894,-0.642138,-0.838243,-0.961062,-0.999859,-0.951241,-0.819459,-0.616035,-0.358752,-0.070105,0.224671,0.499805,0.731243,0.898750,0.987682,0.990265,0.906272,0.743046,0.514858,0.241658,-0.052670,-0.342393,-0.602182,-0.809323,-0.945708,-0.999413,-0.965742,-0.847640,-0.655431,-0.405919,-0.120920,0.174651,0.454953,0.695480,0.875203,0.978410,0.996078,0.926662,0.776230,0.557935,0.290862,-0.001641,-0.294000,-0.560655,-0.778295,-0.927890,-0.996363,-0.977727,-0.873611,-0.693119,-0.452029,-0.171419,0.124177,0.408916,0.657906,0.849376,0.966589,0.999295,0.944637,0.807392,0.599559,0.339308,0.049393,-0.244840,-0.517668,-0.745238,-0.907654,-0.990716,-0.987164,-0.897306,-0.729000,-0.496960,-0.221472,0.073378,0.361813,0.618616,0.821336,0.952248,0.999909,0.960150,0.836449,0.639620,0.386870,0.100298,-0.195043,-0.473332,-0.710239,-0.885052,-0.982488,-0.994028,-0.918663,-0.762982,-0.540597,-0.270948,0.022388,0.313768,0.577715,0.791155,0.935426,0.997916,0.973162,0.863327,0.678014,0.433424,0.150942,-0.144737,-0.427762,-0.673389,-0.860144,-0.971699,-0.998302,-0.937626,-0.794976,-0.582824,-0.319718,-0.028660,0.264904,0.535308,0.758912,0.916167,0.993324,0.983637,0.887955,0.714641,0.478849,0.201192,-0.094055,-0.381078,-0.634785,-0.832995,-0.958378,-0.999974,-0.954145,-0.824898,-0.623533,-0.367654,-0.079633,0.215351,0.491507,0.724692,0.894520,0.986142,0.991550,0.910269,0.749406,0.523025,0.250918,-0.043127,-0.333400,-0.594526,-0.803674,-0.942560,-0.999040,-0.968178,-0.852670,-0.662617,-0.414633,
};
float cos_wave2[423]=
{
	1.000000,0.956287,0.828968,0.629175,0.374376,0.086846,-0.208277,-0.485190,-0.719685,-0.891261,-0.984916,-0.992463,-0.913242,-0.754179,-0.529181,-0.257918,0.035894,0.326568,0.588691,0.799346,0.940117,0.998697,0.969964,0.856430,0.668021,0.421209,0.137572,-0.158093,-0.439936,-0.683316,-0.866957,-0.974802,-0.997423,-0.932843,-0.786707,-0.571792,-0.306887,-0.015151,0.277908,0.546672,0.767641,0.921498,0.994792,0.981113,0.881660,0.705125,0.466944,0.187939,-0.107497,-0.393535,-0.645167,-0.840394,-0.962148,-0.999785,-0.950013,-0.817185,-0.612913,-0.355056,-0.066157,0.228525,0.503228,0.733936,0.900478,0.988294,0.989706,0.904592,0.740392,0.511462,0.237816,-0.056621,-0.346108,-0.605336,-0.811641,-0.946987,-0.999541,-0.964708,-0.845534,-0.652437,-0.402300,-0.116991,0.178546,0.458473,0.698318,0.877111,0.979220,0.995720,0.925167,0.773729,0.554647,0.287074,-0.005598,-0.297779,-0.563927,-0.780773,-0.929358,-0.996692,-0.976889,-0.871679,-0.690261,-0.448496,-0.167520,0.128102,0.412524,0.660880,0.851458,0.967595,0.999139,0.943331,0.805051,0.596387,0.335583,0.045441,-0.248675,-0.521050,-0.747870,-0.909307,-0.991246,-0.986524,-0.895553,-0.726286,-0.493523,-0.217612,0.077324,0.365499,0.621720,0.823586,0.953449,0.999954,0.959037,0.834274,0.636573,0.383218,0.096360,-0.198922,-0.476814,-0.713019,-0.886887,-0.983217,-0.993588,-0.917093,-0.760419,-0.537263,-0.267137,0.026344,0.317522,0.580940,0.793569,0.936818,0.998164,0.972244,0.861323,0.675100,0.429855,0.147029,-0.148651,-0.431336,-0.676309,-0.862156,-0.972626,-0.998063,-0.936243,-0.792569,-0.579604,-0.315966,-0.024704,0.268718,0.538646,0.761483,0.917745,0.993772,0.982917,0.886128,0.711868,0.475371,0.197314,-0.097993,-0.384733,-0.637837,-0.835177,-0.959500,-0.999937,-0.952953,-0.822655,-0.620435,-0.363972,-0.075688,0.219213,0.494949,0.727413,0.896281,0.986791,0.991028,0.908623,0.746780,0.519648,0.247085,-0.047079,-0.337128,-0.597703,-0.806023,-0.943874,-0.999206,-0.967180,-0.850596,-0.659648,-0.411029,-0.126474,0.169137,0.449962,0.691447,0.872482,0.977238,0.996558,0.928751,0.779747,0.562572,0.296213,0.003957,-0.288645,-0.556012,-0.774768,-0.925788,-0.995870,-0.978886,-0.876322,-0.697143,-0.457015,-0.176931,0.118620,0.403802,0.653680,0.846409,0.965139,0.999490,0.946459,0.810682,0.604029,0.344568,0.054983,-0.239409,-0.512871,-0.741494,-0.905290,-0.989940,-0.988042,-0.899763,-0.732821,-0.501810,-0.226927,0.067794,0.356589,0.614209,0.818130,0.950524,0.999817,0.961700,0.839504,0.643912,0.392026,0.105866,-0.189550,-0.468394,-0.706287,-0.882433,-0.981429,-0.994623,-0.920860,-0.766589,-0.545297,-0.276332,0.016792,0.308448,0.573137,0.787719,0.933433,0.997540,0.974435,0.866138,0.682118,0.438462,0.156473,-0.139196,-0.422696,-0.669241,-0.857276,-0.970362,-0.998612,-0.939557,-0.798359,-0.587364,-0.325017,-0.034254,0.259503,0.530572,0.755255,0.913909,0.992662,0.984630,0.890515,0.718545,0.483755,0.206672,-0.088480,-0.375897,-0.630450,-0.829885,-0.956765,-0.999999,-0.955806,-0.828049,-0.627899,-0.372854,-0.085211,0.209881,0.486624,0.720823,0.892003,0.985198,0.992260,0.912572,0.753100,0.527788,0.256332,-0.037534,-0.328118,-0.590016,-0.800331,-0.940675,-0.998779,-0.969563,-0.855581,-0.666799,-0.419720,-0.135946,0.159713,0.441408,0.684513,0.867773,0.975167,0.997304,0.932251,0.785693,0.570445,0.305325,0.013511,-0.279484,-0.548045,-0.768692,-0.922134,-0.994957,-0.980795,-0.880884,-0.703961,-0.465492,-0.186327,0.109128,0.395042,0.646419,0.841282,0.962594,0.999749,0.949500,0.816238,0.611616,0.353522,0.064520,-0.230122,-0.504645,-0.735049,-0.901190,-0.988543,-0.989470,-0.903891,-0.739288,-0.510051,-0.236222,0.058259,0.347647,0.606641,0.812598,0.947513,0.999589,0.964275,0.844657,0.651193,0.400797,0.115362,-0.180160,-0.459931,-0.699491,-0.877898,-0.979552,-0.995567,-0.924543,-0.772689,-0.553281,-0.285502,0.007238,0.299345,0.565282,0.781797,0.929963,0.996824,0.976537,0.870874,0.689073,0.447029,0.165902,-0.129729,-0.414018,-0.662111,-0.852317,-0.968008,-0.999070,-0.942785,-0.804076,-0.595069,-0.334037,-0.043802,0.250264,0.522449,0.748959,0.909989,
};
float sin_wave3[368]=
{
	0.000000,0.334128,0.629850,0.853174,0.978430,0.991221,0.890076,0.686621,0.404243,0.075399,-0.262111,-0.569494,-0.811415,-0.960069,-0.998368,-0.921910,-0.739483,-0.472056,-0.150369,0.188602,0.505895,0.765037,0.936243,0.999832,0.948496,0.788135,0.537182,0.224483,-0.114019,-0.439416,-0.714303,-0.907086,-0.995603,-0.969681,-0.832300,-0.599250,-0.297319,0.038787,0.370435,0.659503,0.872765,0.985707,0.985347,0.871726,0.657906,0.368462,0.036666,-0.299345,-0.600948,-0.833475,-0.970198,-0.995402,-0.906190,-0.712816,-0.437507,-0.111910,0.226551,0.538972,0.789440,0.949166,0.999791,0.935495,0.763668,0.504062,0.186517,-0.152468,-0.473927,-0.740911,-0.922730,-0.998487,-0.959473,-0.810173,-0.567747,-0.260062,0.077516,0.406184,0.688163,0.891042,0.991499,0.977989,0.852065,0.628200,0.332126,-0.002123,-0.336129,-0.631498,-0.854280,-0.978867,-0.990938,-0.889106,-0.685076,-0.402300,-0.073282,0.264160,0.571238,0.812655,0.960661,0.998245,0.921085,0.738052,0.470183,0.148270,-0.190687,-0.507725,-0.766403,-0.936987,-0.999869,-0.947821,-0.786826,-0.535390,-0.222413,0.116128,0.441322,0.715788,0.907977,0.995800,0.969160,0.831121,0.597548,0.295291,-0.040909,-0.372406,-0.661098,-0.873799,-0.986062,-0.984982,-0.870684,-0.656305,-0.366487,-0.034544,0.301370,0.602644,0.834646,0.970710,0.995197,0.905290,0.711325,0.435597,0.109800,-0.228619,-0.540759,-0.790741,-0.949832,-0.999745,-0.934742,-0.762296,-0.502227,-0.184430,0.154566,0.475795,0.742335,0.923547,0.998602,0.958873,0.808926,0.565998,0.258011,-0.079633,-0.408123,-0.689702,-0.892003,-0.991773,-0.977544,-0.850951,-0.626546,-0.330123,0.004246,0.338128,0.633143,0.855382,0.979299,0.990650,0.888132,0.683528,0.400355,0.071164,-0.266207,-0.572979,-0.813890,-0.961249,-0.998117,-0.920257,-0.736618,-0.468308,-0.146170,0.192771,0.509553,0.767765,0.937726,0.999901,0.947142,0.785514,0.533595,0.220343,-0.118237,-0.443226,-0.717269,-0.908865,-0.995992,-0.968635,-0.829938,-0.595845,-0.293262,0.043030,0.374376,0.662689,0.874830,0.986413,0.984613,0.869638,0.654702,0.364511,0.032422,-0.303394,-0.604337,-0.835814,-0.971218,-0.994986,-0.904386,-0.709831,-0.433685,-0.107689,0.230685,0.542544,0.792039,0.950494,0.999695,0.933986,0.760920,0.500390,0.182343,-0.156663,-0.477662,-0.743756,-0.924359,-0.998712,-0.958268,-0.807676,-0.564246,-0.255959,0.081749,0.410061,0.691238,0.892961,0.992043,0.977095,0.849834,0.624890,0.328118,-0.006370,-0.340125,-0.634785,-0.856479,-0.979726,-0.990359,-0.887154,-0.681976,-0.398409,-0.069046,0.268253,0.574718,0.815122,0.961832,0.997984,0.919424,0.735180,0.466431,0.144069,-0.194854,-0.511379,-0.769124,-0.938462,-0.999928,-0.946459,-0.784198,-0.531799,-0.218271,0.120345,0.445128,0.718747,0.909749,0.996180,0.968105,0.828752,0.594138,0.291231,-0.045151,-0.376344,-0.664278,-0.875856,-0.986760,-0.984240,-0.868588,-0.653095,-0.362533,-0.030299,0.305417,0.606027,0.836978,0.971722,0.994772,0.903478,0.708334,0.431771,0.105578,-0.232751,-0.544326,-0.793334,-0.951152,-0.999640,-0.933225,-0.759540,-0.498551,-0.180255,0.158760,0.479526,0.745173,0.925167,0.998817,0.957659,0.806422,0.562492,0.253906,-0.083865,-0.411996,-0.692771,-0.893915,-0.992308,-0.976641,-0.848713,-0.623231,-0.326112,0.008493,0.342121,0.636424,0.857574,0.980149,0.990062,0.886173,0.680422,0.396460,0.066928,-0.270298,-0.576454,-0.816350,-0.962411,-0.997847,-0.918587,-0.733739,-0.464552,-0.141967,0.196936,0.513202,0.770479,0.939193,0.999952,0.945771,0.782879,0.529999,0.216199,-0.122453,-0.447029,-0.720221,-0.910628,-0.996363,-0.967571,-0.827562,-0.592429,
};
float cos_wave3[368]=
{
	1.000000,0.942528,0.776717,0.521626,0.206577,-0.132216,-0.455813,-0.727015,-0.914652,-0.997153,-0.965038,-0.821996,-0.584470,-0.279762,0.057103,0.387404,0.673175,0.881568,0.988630,0.982054,0.862595,0.643986,0.351354,0.018336,-0.316790,-0.615503,-0.843466,-0.974478,-0.993479,-0.898284,-0.699836,-0.420946,-0.093670,0.244372,0.554326,0.800562,0.954778,0.999247,0.928858,0.751702,0.488141,0.168471,-0.170564,-0.489993,-0.753100,-0.929643,-0.999328,-0.954145,-0.799288,-0.552557,-0.242313,0.095784,0.422871,0.701351,0.899215,0.993718,0.973999,0.842324,0.613828,0.314775,-0.020459,-0.353341,-0.645609,-0.863667,-0.982452,-0.988308,-0.880564,-0.671604,-0.385446,-0.054983,0.281800,0.586191,0.823203,0.965592,0.996991,0.913791,0.725556,0.453922,0.130112,-0.208654,-0.523436,-0.778052,-0.943235,-0.999998,-0.941816,-0.775378,-0.519813,-0.204499,0.134321,0.457701,0.728472,0.915508,0.997311,0.964479,0.820785,0.582746,0.277723,-0.059222,-0.389361,-0.674744,-0.882569,-0.988947,-0.981651,-0.861519,-0.642360,-0.349366,-0.016213,0.318803,0.617175,0.844605,0.974952,0.993234,0.897349,0.698318,0.419019,0.091556,-0.246431,-0.556092,-0.801833,-0.955407,-0.999163,-0.928070,-0.750300,-0.486287,-0.166378,0.172655,0.491843,0.754496,0.930423,0.999403,0.953507,0.798010,0.550787,0.240253,-0.097897,-0.424794,-0.702863,-0.900142,-0.993954,-0.973516,-0.841178,-0.612150,-0.312759,0.022581,0.355327,0.647229,0.864736,0.982846,0.987982,0.879556,0.670029,0.383486,0.052863,-0.283836,-0.587910,-0.824407,-0.966142,-0.996824,-0.912927,-0.724093,-0.452029,-0.128006,0.210730,0.525244,0.779384,0.943938,0.999991,0.941100,0.774035,0.517998,0.202421,-0.136424,-0.459588,-0.729925,-0.916360,-0.997465,-0.963916,-0.819570,-0.581019,-0.275683,0.061342,0.391315,0.676309,0.883565,0.989260,0.981244,0.860439,0.640732,0.347375,0.014090,-0.320815,-0.618844,-0.845740,-0.975422,-0.992985,-0.896410,-0.696797,-0.417090,-0.089442,0.248488,0.557855,0.803100,0.956032,0.999074,0.927277,0.748895,0.484431,0.164284,-0.174746,-0.493690,-0.755887,-0.931199,-0.999474,-0.952865,-0.796729,-0.549013,-0.238191,0.100010,0.426715,0.704372,0.901065,0.994185,0.973028,0.840028,0.610470,0.310742,-0.024704,-0.357311,-0.648846,-0.865800,-0.983235,-0.987652,-0.878544,-0.668451,-0.381524,-0.050742,0.285872,0.589626,0.825607,0.966688,0.996653,0.912058,0.722627,0.450134,0.125900,-0.212805,-0.527050,-0.780713,-0.944637,-0.999980,-0.940380,-0.772689,-0.516181,-0.200341,0.138527,0.461473,0.731374,0.917208,0.997613,0.963349,0.818352,0.579290,0.273641,-0.063461,-0.393268,-0.677872,-0.884557,-0.989568,-0.980832,-0.859355,-0.639100,-0.345384,-0.011967,0.322825,0.620510,0.846871,0.975888,0.992732,0.895467,0.695272,0.415160,0.087327,-0.250544,-0.559616,-0.804363,-0.956653,-0.998980,-0.926480,-0.747486,-0.482572,-0.162189,0.176837,0.495536,0.757276,0.931971,0.999541,0.952219,0.795444,0.547237,0.236128,-0.102122,-0.428634,-0.705877,-0.901983,-0.994411,-0.972536,-0.838874,-0.608787,-0.308723,0.026827,0.359293,0.650460,0.866861,0.983620,0.987317,0.877528,0.666871,0.379561,0.048622,-0.287906,-0.591340,-0.826803,-0.967229,-0.996477,-0.911186,-0.721158,-0.448237,-0.123793,0.214879,0.528853,0.782038,0.945331,0.999964,0.939656,0.771339,0.514361,0.198260,-0.140630,-0.463355,-0.732821,-0.918052,-0.997758,-0.962777,-0.817130,-0.577558,-0.271598,0.065580,0.395220,0.679431,0.885546,0.989871,0.980416,0.858268,0.637466,0.343390,0.009844,-0.324834,-0.622174,-0.847998,-0.976349,-0.992474,-0.894520,-0.693745,-0.413227,-0.085211,0.252599,0.561374,0.805623,
};

*/
// 41阶低通滤波器 135khz
float Low_Filter1[41] = {
    0.02749768910522,  0.00950250911255,  0.01102724896363,  0.01261233847252,
    0.01424198265405,  0.01593883406118,  0.01760686400124,  0.01930416268076,
     0.0209849322636,  0.02261713357687,  0.02418703433836,  0.02567286240089,
    0.02707101323325,  0.02835445086015,  0.02949383586346,  0.03048484167503,
    0.03131223384648,  0.03197740774778,  0.03246068281561,  0.03275278230481,
    0.03285133852076,  0.03275278230481,  0.03246068281561,  0.03197740774778,
    0.03131223384648,  0.03048484167503,  0.02949383586346,  0.02835445086015,
    0.02707101323325,  0.02567286240089,  0.02418703433836,  0.02261713357687,
     0.0209849322636,  0.01930416268076,  0.01760686400124,  0.01593883406118,
    0.01424198265405,  0.01261233847252,  0.01102724896363,  0.00950250911255,
    0.02749768910522
};

float Low_Filter2[37] = {
       0.02181138285, -0.02011265047, -0.01731494814, -0.01684645377, -0.01684641652,
   -0.01605831832, -0.01367643289,-0.009039154276,-0.002036049496, 0.007444297429,
    0.01911091246,  0.03240166605,  0.04661503807,  0.06088255346,  0.07430711389,
    0.08590719849,  0.09485333413,   0.1005149111,   0.1024425626,   0.1005149111,
    0.09485333413,  0.08590719849,  0.07430711389,  0.06088255346,  0.04661503807,
    0.03240166605,  0.01911091246, 0.007444297429,-0.002036049496,-0.009039154276,
   -0.01367643289, -0.01605831832, -0.01684641652, -0.01684645377, -0.01731494814,
   -0.02011265047,  0.02181138285
};

