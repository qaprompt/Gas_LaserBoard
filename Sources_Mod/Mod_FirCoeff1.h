/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 *
 * Generated by MATLAB(R) 7.6 and the Signal Processing Toolbox 6.9.
 *
 * Generated on: 22-Mar-2019 11:11:08
 *
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 1091
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * D:\Program Files\MATLAB\R2008a\extern\include\tmwtypes.h 
 */
/*
 * Warning - Filter coefficients were truncated to fit specified data type.  
 *   The resulting response may not match generated theoretical response.
 *   Use the Filter Design & Analysis Tool to design accurate
 *   single-precision filter coefficients.
 */
const int BL1 = 1091;
real32_T B1[1091] = {
  -1.616501868e-005,-1.954992285e-006,-2.072839152e-006,-2.193836053e-006,
  -2.320050726e-006,-2.449644626e-006,-2.584760068e-006,-2.723553962e-006,
  -2.868157708e-006,-3.016652954e-006,-3.171162234e-006,-3.329718083e-006,
  -3.494399607e-006,-3.66309132e-006,-3.837974873e-006,-4.016851562e-006,
  -4.202042874e-006,-4.391333732e-006,-4.587271633e-006,-4.787603302e-006,
  -4.995137715e-006,-5.207467439e-006,-5.427548786e-006,-5.652596428e-006,
  -5.88560215e-006,-6.123173534e-006,-6.368393315e-006,-6.617340659e-006,
  -6.873672646e-006,-7.133397958e-006,-7.401674338e-006,-7.674514563e-006,
  -7.958607966e-006,-8.248282029e-006,-8.549976883e-006,-8.852388419e-006,
  -9.162669812e-006,-9.46702221e-006,-9.799778127e-006,-1.014083955e-005,
  -1.046641955e-005,-1.082070412e-005,-1.117017109e-005,-1.153421999e-005,
  -1.190060539e-005,-1.227878965e-005,-1.266125582e-005,-1.305451133e-005,
  -1.345297096e-005,-1.386161057e-005,-1.427597635e-005,-1.470004008e-005,
  -1.513008556e-005,-1.556955976e-005,-1.601531767e-005,-1.64705034e-005,
  -1.693242302e-005,-1.740392327e-005,-1.788251211e-005,-1.837067066e-005,
  -1.886589052e-005,-1.93703363e-005,-1.988161239e-005,-2.040193431e-005,
  -2.092927389e-005,-2.146609586e-005,-2.20104539e-005,-2.256448533e-005,
  -2.312567813e-005,-2.369572758e-005,-2.427201071e-005,-2.485733967e-005,
  -2.54502047e-005,-2.60540146e-005,-2.666453838e-005,-2.728267646e-005,-2.79045089e-005,
  -2.85428996e-005,-2.918259815e-005,-2.983125887e-005,-3.048905091e-005,
  -3.115291111e-005,-3.182546061e-005,-3.250485679e-005,-3.319223833e-005,
  -3.38866339e-005,-3.458853462e-005,-3.529729292e-005,-3.601318167e-005,
  -3.673582614e-005,-3.746533548e-005,-3.820153506e-005,-3.89444067e-005,
  -3.969377576e-005,-4.044945672e-005,-4.121124948e-005,-4.197887392e-005,
  -4.275227911e-005,-4.353127588e-005,-4.431593698e-005,-4.510600775e-005,
  -4.590139724e-005,-4.670154522e-005,-4.750625885e-005,-4.831509432e-005,
  -4.912822988e-005,-4.994554183e-005,-5.076722664e-005,-5.159250213e-005,
  -5.242088446e-005,-5.325171151e-005,-5.408573998e-005,-5.492306082e-005,
  -5.576301555e-005,-5.660324678e-005,-5.744548253e-005,-5.829161819e-005,
  -5.913554196e-005,-5.9982729e-005,-6.082932305e-005,-6.167659012e-005,-6.252346793e-005,
  -6.336998194e-005,-6.421552825e-005,-6.505999772e-005,-6.590287376e-005,
  -6.674391625e-005,-6.758265226e-005,-6.8418718e-005,-6.925158232e-005,-7.008088869e-005,
  -7.090615691e-005,-7.172711776e-005,-7.254335651e-005,-7.335450937e-005,
  -7.416004519e-005,-7.495945465e-005,-7.575211202e-005,-7.653760258e-005,
  -7.731548249e-005,-7.80854607e-005,-7.88469697e-005,-7.959950744e-005,-8.034225903e-005,
  -8.107475151e-005,-8.179651195e-005,-8.250746032e-005,-8.320673078e-005,
  -8.3893603e-005,-8.456697833e-005,-8.52272351e-005,-8.587381308e-005,-8.650591917e-005,
  -8.712138515e-005,-8.772241563e-005,-8.830666775e-005,-8.887286822e-005,
  -8.942248678e-005,-8.995268581e-005,-9.046460036e-005,-9.095628775e-005,
  -9.142805357e-005,-9.187837713e-005,-9.230725846e-005,-9.271329327e-005,
  -9.309640882e-005,-9.345540457e-005,-9.379008407e-005,-9.409929044e-005,
  -9.438269626e-005,-9.463906463e-005,-9.486802446e-005,-9.506843344e-005,
  -9.523995686e-005,-9.538152517e-005,-9.549272363e-005,-9.557232261e-005,
  -9.561980551e-005,-9.563400818e-005,-9.561453044e-005,-9.556033183e-005,
  -9.547094669e-005,-9.534501442e-005,-9.518191655e-005,-9.49805908e-005,
  -9.474083345e-005,-9.446139302e-005,-9.414145461e-005,-9.377958486e-005,
  -9.337582742e-005,-9.292901086e-005,-9.243802924e-005,-9.190134006e-005,
  -9.132020932e-005,-9.069115185e-005,-9.001512808e-005,-8.929036267e-005,
  -8.851610619e-005,-8.769148553e-005,-8.681550389e-005,-8.588729543e-005,
  -8.49059943e-005,-8.387062553e-005,-8.278024325e-005,-8.163385792e-005,
  -8.043052367e-005,-7.916925097e-005,-7.784923946e-005,-7.646944869e-005,
  -7.502903463e-005,-7.352691318e-005,-7.196216757e-005,-7.033372094e-005,
  -6.864080933e-005,-6.688236317e-005,-6.505754573e-005,-6.316519284e-005,
  -6.120438775e-005,-5.917403541e-005,-5.707347373e-005,-5.490165859e-005,
  -5.265764048e-005,-5.034012065e-005,-4.794838605e-005,-4.548148718e-005,
  -4.293863094e-005,-4.031836579e-005,-3.761993139e-005,-3.484259651e-005,
  -3.198555714e-005,-2.90469543e-005,-2.602662244e-005,-2.292372483e-005,
  -1.973631333e-005,-1.646473174e-005,-1.310703465e-005,-9.662952834e-006,
  -6.13115526e-006,-2.510890226e-006,1.198937753e-006,4.999089469e-006,8.890571735e-006,
  1.287421128e-005,1.695093124e-005,2.112168659e-005,2.538735498e-005,2.974883137e-005,
  3.420696157e-005,3.876258415e-005,4.341655949e-005,4.81698371e-005,5.302326826e-005,
  5.797770064e-005,6.303389819e-005,6.819263945e-005,7.345475751e-005,7.882119098e-005,
  8.429275476e-005,8.98701328e-005,9.555402357e-005,0.0001013452784,0.0001072447849,
  0.0001132531761,0.0001193710559,0.0001255991665,0.0001319385774,0.0001383897907,
   0.000144953272,0.0001516298216,0.0001584205747,0.0001653252548,0.0001723452297,
  0.0001794809941,0.0001867328392,   0.0001941019,0.0002015881764,0.0002091926872,
   0.000216915636,0.0002247579105,0.0002327196999,0.0002408018627,0.0002490045154,
  0.0002573284146,0.0002657737641,0.0002743412915,0.0002830312005,0.0002918441314,
  0.0003007801715,0.0003098399029,0.0003190234711,0.0003283314581,0.0003377640678,
  0.0003473217075,0.0003570044355,0.0003668126592,0.0003767465241, 0.000386806496,
  0.0003969924583,0.0004073047021, 0.000417743373,0.0004283088201,0.0004390009562,
  0.0004498198396,0.0004607655283,0.0004718384298,0.0004830381658,0.0004943648237,
  0.0005058185779, 0.000517399516, 0.000529106881,0.0005409415462, 0.000552902522,
  0.0005649903906,0.0005772046279,0.0005895451759,0.0006020118017,0.0006146043306,
  0.0006273224717,0.0006401660503,0.0006531347171,0.0006662282394,0.0006794461515,
  0.0006927882205,0.0007062539225,0.0007198429666,0.0007335549453,0.0007473893929,
  0.0007613457274, 0.000775423483,0.0007896221359,0.0008039412787,0.0008183801547,
  0.0008329381817,0.0008476146613,0.0008624091861,0.0008773209411,0.0008923492278,
  0.0009074931149,0.0009227520786,0.0009381253622,0.0009536120924,0.0009692112217,
  0.0009849222843, 0.001000744174,  0.00101667596, 0.001032716478, 0.001048865495,
   0.001065121382, 0.001081483206, 0.001097950269, 0.001114520943,  0.00113119476,
   0.001147970092, 0.001164846122, 0.001181821572, 0.001198895276, 0.001216065953,
   0.001233332441, 0.001250693458, 0.001268147607, 0.001285693841, 0.001303330529,
   0.001321056508, 0.001338870265, 0.001356770401,  0.00137475552,  0.00139282411,
   0.001410974772, 0.001429205993, 0.001447516144, 0.001465903828, 0.001484367298,
   0.001502904925, 0.001521515311,  0.00154019671, 0.001558947377, 0.001577765681,
   0.001596649759, 0.001615598216, 0.001634609071, 0.001653680461, 0.001672810758,
   0.001691998099,  0.00171124062, 0.001730536344, 0.001749883755,  0.00176928041,
   0.001788724912, 0.001808214933, 0.001827748725, 0.001847324311, 0.001866939478,
   0.001886592479, 0.001906281104,  0.00192600349, 0.001945757307, 0.001965540694,
   0.001985351322, 0.002005187562, 0.002025046619,  0.00204492663, 0.002064825501,
   0.002084741136, 0.002104670973, 0.002124613151,  0.00214456534, 0.002164525213,
    0.00218449044, 0.002204459161, 0.002224428812, 0.002244397299, 0.002264361829,
   0.002284320537, 0.002304271096, 0.002324211178, 0.002344137989, 0.002364049666,
    0.00238394388, 0.002403817838, 0.002423669444, 0.002443496371, 0.002463296056,
   0.002483066171, 0.002502804389, 0.002522508148,  0.00254217512, 0.002561802743,
    0.00258138869, 0.002600930864, 0.002620426007, 0.002639872488,  0.00265926728,
   0.002678608522, 0.002697893186, 0.002717119176, 0.002736283699, 0.002755384892,
   0.002774419729,  0.00279338588, 0.002812281018, 0.002831102815, 0.002849848475,
   0.002868515672, 0.002887102077, 0.002905605361,  0.00292402273, 0.002942351857,
   0.002960590646, 0.002978736302, 0.002996786265, 0.003014738671, 0.003032590495,
   0.003050339874, 0.003067984013, 0.003085520817, 0.003102947725, 0.003120262641,
    0.00313746254,  0.00315454579,  0.00317150983, 0.003188352101, 0.003205070505,
   0.003221662715, 0.003238126403, 0.003254459472,  0.00327065913, 0.003286723746,
   0.003302650759, 0.003318437841, 0.003334082896, 0.003349583829, 0.003364938311,
   0.003380144248, 0.003395199776, 0.003410102101, 0.003424849594, 0.003439440159,
   0.003453871468, 0.003468141658, 0.003482248634,   0.0034961903, 0.003509964794,
    0.00352357002, 0.003537004348, 0.003550265217, 0.003563351231, 0.003576260293,
   0.003588990541, 0.003601540346, 0.003613907611, 0.003626090707, 0.003638087539,
   0.003649896942, 0.003661516588,  0.00367294508, 0.003684180789, 0.003695222083,
   0.003706067102, 0.003716714447,  0.00372716249, 0.003737409832, 0.003747454844,
   0.003757295897, 0.003766931826, 0.003776360769, 0.003785581794, 0.003794593504,
   0.003803394269, 0.003811982926,  0.00382035831, 0.003828519024, 0.003836463904,
   0.003844192019, 0.003851701505, 0.003858991899, 0.003866062034, 0.003872910514,
   0.003879536875, 0.003885939484, 0.003892117646, 0.003898070659, 0.003903797362,
   0.003909297287, 0.003914569039, 0.003919611685, 0.003924425691,  0.00392900873,
   0.003933361266, 0.003937482368, 0.003941371106, 0.003945027478, 0.003948450089,
   0.003951638937, 0.003954594024, 0.003957313951,  0.00395979872, 0.003962047864,
   0.003964061383, 0.003965838812, 0.003967379685, 0.003968684003, 0.003969751298,
   0.003970581573, 0.003971174825,  0.00397153059, 0.003971649334,  0.00397153059,
   0.003971174825, 0.003970581573, 0.003969751298, 0.003968684003, 0.003967379685,
   0.003965838812, 0.003964061383, 0.003962047864,  0.00395979872, 0.003957313951,
   0.003954594024, 0.003951638937, 0.003948450089, 0.003945027478, 0.003941371106,
   0.003937482368, 0.003933361266,  0.00392900873, 0.003924425691, 0.003919611685,
   0.003914569039, 0.003909297287, 0.003903797362, 0.003898070659, 0.003892117646,
   0.003885939484, 0.003879536875, 0.003872910514, 0.003866062034, 0.003858991899,
   0.003851701505, 0.003844192019, 0.003836463904, 0.003828519024,  0.00382035831,
   0.003811982926, 0.003803394269, 0.003794593504, 0.003785581794, 0.003776360769,
   0.003766931826, 0.003757295897, 0.003747454844, 0.003737409832,  0.00372716249,
   0.003716714447, 0.003706067102, 0.003695222083, 0.003684180789,  0.00367294508,
   0.003661516588, 0.003649896942, 0.003638087539, 0.003626090707, 0.003613907611,
   0.003601540346, 0.003588990541, 0.003576260293, 0.003563351231, 0.003550265217,
   0.003537004348,  0.00352357002, 0.003509964794,   0.0034961903, 0.003482248634,
   0.003468141658, 0.003453871468, 0.003439440159, 0.003424849594, 0.003410102101,
   0.003395199776, 0.003380144248, 0.003364938311, 0.003349583829, 0.003334082896,
   0.003318437841, 0.003302650759, 0.003286723746,  0.00327065913, 0.003254459472,
   0.003238126403, 0.003221662715, 0.003205070505, 0.003188352101,  0.00317150983,
    0.00315454579,  0.00313746254, 0.003120262641, 0.003102947725, 0.003085520817,
   0.003067984013, 0.003050339874, 0.003032590495, 0.003014738671, 0.002996786265,
   0.002978736302, 0.002960590646, 0.002942351857,  0.00292402273, 0.002905605361,
   0.002887102077, 0.002868515672, 0.002849848475, 0.002831102815, 0.002812281018,
    0.00279338588, 0.002774419729, 0.002755384892, 0.002736283699, 0.002717119176,
   0.002697893186, 0.002678608522,  0.00265926728, 0.002639872488, 0.002620426007,
   0.002600930864,  0.00258138869, 0.002561802743,  0.00254217512, 0.002522508148,
   0.002502804389, 0.002483066171, 0.002463296056, 0.002443496371, 0.002423669444,
   0.002403817838,  0.00238394388, 0.002364049666, 0.002344137989, 0.002324211178,
   0.002304271096, 0.002284320537, 0.002264361829, 0.002244397299, 0.002224428812,
   0.002204459161,  0.00218449044, 0.002164525213,  0.00214456534, 0.002124613151,
   0.002104670973, 0.002084741136, 0.002064825501,  0.00204492663, 0.002025046619,
   0.002005187562, 0.001985351322, 0.001965540694, 0.001945757307,  0.00192600349,
   0.001906281104, 0.001886592479, 0.001866939478, 0.001847324311, 0.001827748725,
   0.001808214933, 0.001788724912,  0.00176928041, 0.001749883755, 0.001730536344,
    0.00171124062, 0.001691998099, 0.001672810758, 0.001653680461, 0.001634609071,
   0.001615598216, 0.001596649759, 0.001577765681, 0.001558947377,  0.00154019671,
   0.001521515311, 0.001502904925, 0.001484367298, 0.001465903828, 0.001447516144,
   0.001429205993, 0.001410974772,  0.00139282411,  0.00137475552, 0.001356770401,
   0.001338870265, 0.001321056508, 0.001303330529, 0.001285693841, 0.001268147607,
   0.001250693458, 0.001233332441, 0.001216065953, 0.001198895276, 0.001181821572,
   0.001164846122, 0.001147970092,  0.00113119476, 0.001114520943, 0.001097950269,
   0.001081483206, 0.001065121382, 0.001048865495, 0.001032716478,  0.00101667596,
   0.001000744174,0.0009849222843,0.0009692112217,0.0009536120924,0.0009381253622,
  0.0009227520786,0.0009074931149,0.0008923492278,0.0008773209411,0.0008624091861,
  0.0008476146613,0.0008329381817,0.0008183801547,0.0008039412787,0.0007896221359,
   0.000775423483,0.0007613457274,0.0007473893929,0.0007335549453,0.0007198429666,
  0.0007062539225,0.0006927882205,0.0006794461515,0.0006662282394,0.0006531347171,
  0.0006401660503,0.0006273224717,0.0006146043306,0.0006020118017,0.0005895451759,
  0.0005772046279,0.0005649903906, 0.000552902522,0.0005409415462, 0.000529106881,
   0.000517399516,0.0005058185779,0.0004943648237,0.0004830381658,0.0004718384298,
  0.0004607655283,0.0004498198396,0.0004390009562,0.0004283088201, 0.000417743373,
  0.0004073047021,0.0003969924583, 0.000386806496,0.0003767465241,0.0003668126592,
  0.0003570044355,0.0003473217075,0.0003377640678,0.0003283314581,0.0003190234711,
  0.0003098399029,0.0003007801715,0.0002918441314,0.0002830312005,0.0002743412915,
  0.0002657737641,0.0002573284146,0.0002490045154,0.0002408018627,0.0002327196999,
  0.0002247579105, 0.000216915636,0.0002091926872,0.0002015881764,   0.0001941019,
  0.0001867328392,0.0001794809941,0.0001723452297,0.0001653252548,0.0001584205747,
  0.0001516298216, 0.000144953272,0.0001383897907,0.0001319385774,0.0001255991665,
  0.0001193710559,0.0001132531761,0.0001072447849,0.0001013452784,9.555402357e-005,
  8.98701328e-005,8.429275476e-005,7.882119098e-005,7.345475751e-005,6.819263945e-005,
  6.303389819e-005,5.797770064e-005,5.302326826e-005,4.81698371e-005,4.341655949e-005,
  3.876258415e-005,3.420696157e-005,2.974883137e-005,2.538735498e-005,2.112168659e-005,
  1.695093124e-005,1.287421128e-005,8.890571735e-006,4.999089469e-006,1.198937753e-006,
  -2.510890226e-006,-6.13115526e-006,-9.662952834e-006,-1.310703465e-005,
  -1.646473174e-005,-1.973631333e-005,-2.292372483e-005,-2.602662244e-005,
  -2.90469543e-005,-3.198555714e-005,-3.484259651e-005,-3.761993139e-005,
  -4.031836579e-005,-4.293863094e-005,-4.548148718e-005,-4.794838605e-005,
  -5.034012065e-005,-5.265764048e-005,-5.490165859e-005,-5.707347373e-005,
  -5.917403541e-005,-6.120438775e-005,-6.316519284e-005,-6.505754573e-005,
  -6.688236317e-005,-6.864080933e-005,-7.033372094e-005,-7.196216757e-005,
  -7.352691318e-005,-7.502903463e-005,-7.646944869e-005,-7.784923946e-005,
  -7.916925097e-005,-8.043052367e-005,-8.163385792e-005,-8.278024325e-005,
  -8.387062553e-005,-8.49059943e-005,-8.588729543e-005,-8.681550389e-005,
  -8.769148553e-005,-8.851610619e-005,-8.929036267e-005,-9.001512808e-005,
  -9.069115185e-005,-9.132020932e-005,-9.190134006e-005,-9.243802924e-005,
  -9.292901086e-005,-9.337582742e-005,-9.377958486e-005,-9.414145461e-005,
  -9.446139302e-005,-9.474083345e-005,-9.49805908e-005,-9.518191655e-005,
  -9.534501442e-005,-9.547094669e-005,-9.556033183e-005,-9.561453044e-005,
  -9.563400818e-005,-9.561980551e-005,-9.557232261e-005,-9.549272363e-005,
  -9.538152517e-005,-9.523995686e-005,-9.506843344e-005,-9.486802446e-005,
  -9.463906463e-005,-9.438269626e-005,-9.409929044e-005,-9.379008407e-005,
  -9.345540457e-005,-9.309640882e-005,-9.271329327e-005,-9.230725846e-005,
  -9.187837713e-005,-9.142805357e-005,-9.095628775e-005,-9.046460036e-005,
  -8.995268581e-005,-8.942248678e-005,-8.887286822e-005,-8.830666775e-005,
  -8.772241563e-005,-8.712138515e-005,-8.650591917e-005,-8.587381308e-005,
  -8.52272351e-005,-8.456697833e-005,-8.3893603e-005,-8.320673078e-005,-8.250746032e-005,
  -8.179651195e-005,-8.107475151e-005,-8.034225903e-005,-7.959950744e-005,
  -7.88469697e-005,-7.80854607e-005,-7.731548249e-005,-7.653760258e-005,-7.575211202e-005,
  -7.495945465e-005,-7.416004519e-005,-7.335450937e-005,-7.254335651e-005,
  -7.172711776e-005,-7.090615691e-005,-7.008088869e-005,-6.925158232e-005,
  -6.8418718e-005,-6.758265226e-005,-6.674391625e-005,-6.590287376e-005,-6.505999772e-005,
  -6.421552825e-005,-6.336998194e-005,-6.252346793e-005,-6.167659012e-005,
  -6.082932305e-005,-5.9982729e-005,-5.913554196e-005,-5.829161819e-005,-5.744548253e-005,
  -5.660324678e-005,-5.576301555e-005,-5.492306082e-005,-5.408573998e-005,
  -5.325171151e-005,-5.242088446e-005,-5.159250213e-005,-5.076722664e-005,
  -4.994554183e-005,-4.912822988e-005,-4.831509432e-005,-4.750625885e-005,
  -4.670154522e-005,-4.590139724e-005,-4.510600775e-005,-4.431593698e-005,
  -4.353127588e-005,-4.275227911e-005,-4.197887392e-005,-4.121124948e-005,
  -4.044945672e-005,-3.969377576e-005,-3.89444067e-005,-3.820153506e-005,
  -3.746533548e-005,-3.673582614e-005,-3.601318167e-005,-3.529729292e-005,
  -3.458853462e-005,-3.38866339e-005,-3.319223833e-005,-3.250485679e-005,
  -3.182546061e-005,-3.115291111e-005,-3.048905091e-005,-2.983125887e-005,
  -2.918259815e-005,-2.85428996e-005,-2.79045089e-005,-2.728267646e-005,-2.666453838e-005,
  -2.60540146e-005,-2.54502047e-005,-2.485733967e-005,-2.427201071e-005,-2.369572758e-005,
  -2.312567813e-005,-2.256448533e-005,-2.20104539e-005,-2.146609586e-005,
  -2.092927389e-005,-2.040193431e-005,-1.988161239e-005,-1.93703363e-005,
  -1.886589052e-005,-1.837067066e-005,-1.788251211e-005,-1.740392327e-005,
  -1.693242302e-005,-1.64705034e-005,-1.601531767e-005,-1.556955976e-005,
  -1.513008556e-005,-1.470004008e-005,-1.427597635e-005,-1.386161057e-005,
  -1.345297096e-005,-1.305451133e-005,-1.266125582e-005,-1.227878965e-005,
  -1.190060539e-005,-1.153421999e-005,-1.117017109e-005,-1.082070412e-005,
  -1.046641955e-005,-1.014083955e-005,-9.799778127e-006,-9.46702221e-006,
  -9.162669812e-006,-8.852388419e-006,-8.549976883e-006,-8.248282029e-006,
  -7.958607966e-006,-7.674514563e-006,-7.401674338e-006,-7.133397958e-006,
  -6.873672646e-006,-6.617340659e-006,-6.368393315e-006,-6.123173534e-006,
  -5.88560215e-006,-5.652596428e-006,-5.427548786e-006,-5.207467439e-006,
  -4.995137715e-006,-4.787603302e-006,-4.587271633e-006,-4.391333732e-006,
  -4.202042874e-006,-4.016851562e-006,-3.837974873e-006,-3.66309132e-006,
  -3.494399607e-006,-3.329718083e-006,-3.171162234e-006,-3.016652954e-006,
  -2.868157708e-006,-2.723553962e-006,-2.584760068e-006,-2.449644626e-006,
  -2.320050726e-006,-2.193836053e-006,-2.072839152e-006,-1.954992285e-006,
  -1.616501868e-005
};
