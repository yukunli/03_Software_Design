### -*- coding: utf-8 -*-  
  
import re
import os
import string
from scipy import signal  
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib


global datalist
datalist=[]

global inum
inum = 0

Filter1 = [-0.001638296875, 0.001976465574, 0.002134647453, 0.002753725043, 0.003676692024,
   0.004842206836, 0.006222689059, 0.007803681307, 0.009575296193,  0.01152345072,
    0.01362994872,  0.01586939767,  0.01821359247,  0.02062819339,   0.0230763685,
    0.02551575191,  0.02790359221,  0.03019426391,  0.03234416991,   0.0343089737,
    0.03604891896,  0.03752631322,   0.0387105532,  0.03957502544,  0.04010182992,
     0.0402783975,  0.04010182992,  0.03957502544,   0.0387105532,  0.03752631322,
    0.03604891896,   0.0343089737,  0.03234416991,  0.03019426391,  0.02790359221,
    0.02551575191,   0.0230763685,  0.02062819339,  0.01821359247,  0.01586939767,
    0.01362994872,  0.01152345072, 0.009575296193, 0.007803681307, 0.006222689059,
   0.004842206836, 0.003676692024, 0.002753725043, 0.002134647453, 0.001976465574,
  -0.001638296875]

Filter = [
         -6.278696674e-05,-3.094174872e-06,-2.044103212e-06,-1.840480337e-07, 2.50182984e-06,
  6.035544629e-06,1.040167172e-05,1.558321128e-05,2.151943045e-05,2.814332402e-05,
  3.534229108e-05, 4.29978063e-05,5.094855442e-05, 5.90311538e-05,6.704354018e-05,
   7.47839731e-05,8.201303717e-05,8.849070582e-05, 9.39407546e-05,9.809580661e-05,
  0.0001009098851,0.0001019394258,0.0001011015411,9.821768617e-05, 9.31532195e-05,
  8.583578165e-05,7.622599514e-05,6.435653631e-05,5.030104148e-05,3.421036308e-05,
  1.627999518e-05,-3.216239975e-06,-2.396012133e-05,-4.555998385e-05,-6.75895426e-05,
  -8.956657985e-05,-0.0001109965888,-0.0001313507964,-0.0001500946382,-0.0001666402968,
  -0.0001805337815,-0.0001912303414,-0.0001983009861,-0.0002013438789,-0.0002000438399,
  -0.0001941554801,-0.0001835408329,-0.0001681533759,-0.0001480708452,-0.0001234758383,
  -9.468132339e-05,-6.210562424e-05,-2.629073424e-05,1.212586358e-05,5.239701568e-05,
  9.369754844e-05,0.0001351225947,0.0001757340942,0.0002145626204, 0.000250599609,
  0.0002828930446,0.0003105038195,0.0003325616708,0.0003482889733,0.0003570117406,
  0.0003581959754,0.0003514521813,0.0003365652228,0.0003134935105,0.0002823914983,
  0.0002436031355,0.0001976746571,0.0001453385485,8.751275163e-05,2.527552897e-05,
  -4.014060687e-05,-0.000107376407,-0.0001749700168,-0.0002414127521,-0.0003051296808,
  -0.0003645745746,-0.000418224954,-0.0004646411398,-0.0005024933489,-0.0005306027597,
  -0.0005479709362,-0.0005538139376,-0.0005475862999,-0.0005290043773,-0.0004980596132,
  -0.0004550291051,-0.0004004783113,-0.0003352596541,-0.0002605018963,-0.0001775895071,
  -8.813699969e-05,6.037222647e-06,0.0001029413033,0.0002004776907, 0.000296452723,
  0.0003886556369, 0.000474892644,0.0005530476337,0.0006211298169,0.0006773279165,
  0.0007200532127,0.0007479869528,0.0007601138786,0.0007557595382,0.0007346104248,
  0.0006967348163,0.0006425839383,0.0005729964469,0.0004891845747,0.0003927201033,
  0.0002854951308,0.0001696918771,4.774365152e-05,-7.773286052e-05,-0.0002039804676,
  -0.0003281701065,-0.0004474665329,-0.0005590894143,-0.0006603861111,-0.0007488898118,
  -0.000822388276,-0.0008789729327,-0.0009170957492,-0.0009356039809,-0.0009337816737,
  -0.0009113670094,-0.0008685722714,-0.0008060767432,-0.0007250263589,-0.0006270084996,
  -0.0005140255671,-0.0003884400066,-0.0002529457852,-0.0001104844996,  3.5800771e-05,
  0.0001826515072,0.0003267596767,0.0004648535105, 0.000593767094,0.0007105233381,
  0.0008123989101,0.0008969980991,0.0009623056976, 0.001006743289, 0.001029202831,
   0.001029083272, 0.001006302191, 0.000961305399, 0.000895051402,0.0008089995827,
  0.0007050738204,0.0005856140051,0.0004533290339,0.0003112267877,0.0001625445875,
  1.067366975e-05,-0.0001409251563,-0.000288801326,-0.0004296013212,-0.0005601458251,
  -0.0006775091169,-0.0007790862001,-0.0008626584313,-0.0009264436667,-0.0009691395098,
  -0.0009899501456,-0.000988607062,-0.0009653714369,-0.0009210230783,-0.0008568366757,
  -0.0007745536859,-0.0006763247657,-0.0005646635545,-0.0004423737701,-0.0003124797076,
  -0.0001781469764,-4.26020888e-05,9.094936831e-05,0.0002194040135,0.0003398377448,
  0.0004495785688,0.0005462699337,0.0006279278896,0.0006929860101, 0.000740331132,
  0.0007693211082,0.0007797963335,0.0007720750291,0.0007469368284,0.0007055880851,
  0.0006496306742,0.0005809994182, 0.000501912029,0.0004147956497,0.0003222199448,
  0.0002268182288,0.0001312156965,3.795147859e-05,-5.058799798e-05,-0.0001322384778,
  -0.0002051122719,-0.0002676511067,-0.0003186598478,-0.0003573384602,-0.0003832941002,
  -0.0003965470823,-0.0003975153959,-0.0003869987559,-0.0003661411174,-0.0003363868454,
  -0.0002994294919,-0.0002571500954,-0.0002115499956,-0.0001646841702,-0.0001185864603,
  -7.520399231e-05,-3.632526204e-05,-3.523097121e-06,2.190471423e-05,3.897591523e-05,
  4.706446998e-05,4.592007463e-05,3.568354441e-05,1.687963049e-05,-9.59188128e-06,
  -4.248788173e-05,-8.02583163e-05,-0.0001211009148,-0.000163013683,-0.0002038724197,
  -0.0002414941409,-0.0002737220784,-0.0002984973835,-0.0003139409237,-0.0003184216912,
  -0.0003106273361,-0.0002896186197,-0.0002548811899,-0.0002063579595,-0.0001444740483,
  -7.014048606e-05, 1.52497505e-05,0.0001098477442, 0.000211385297,0.0003172304423,
  0.0004244496231,0.0005298888427,0.0006302599213,0.0007222332642,0.0008025396965,
  0.0008680695901,0.0009159729234,0.0009437559056,0.0009493682301,0.0009312839247,
  0.0008885662537, 0.000820920628,0.0007287285407, 0.000613066135,0.0004757017596,
   0.000319073908,0.0001462498476,-3.91335343e-05,-0.0002329483541,-0.0004306706542,
  -0.0006274871994,-0.0008184147882,-0.0009984301869,-0.001162599423,-0.001306214952,
  -0.001424926217,-0.001514866133,-0.001572768437,-0.001596070128,-0.001583001111,
  -0.001532652183,-0.001445024856,-0.001321053947,-0.001162611647,-0.0009724820266,
  -0.0007543154643,-0.000512553961,-0.0002523401636,2.059895996e-05,0.0003000827273,
  0.0005796258338,0.0008525911835,  0.00111236074, 0.001352496329,    0.001566911,
   0.001750023803, 0.001896913629, 0.002003450412, 0.002066415735, 0.002083594678,
   0.002053850098, 0.001977164531, 0.001854659291, 0.001688579097, 0.001482254243,
   0.001240027836,0.0009671622538,0.0006697151111,0.0003544007777,2.842572394e-05,
  -0.0003006838087,-0.0006252674502,-0.0009377197712,-0.001230681315,-0.001497221645,
  -0.001731016906,-0.001926507684,-0.002079044236,-0.002185003599,-0.002241885522,
  -0.002248374745,-0.002204380464,-0.002111035399,-0.001970671583,-0.001786758774,
  -0.001563818427,-0.001307305647,-0.001023471472,-0.0007191998884,-0.0004018342588,
  -7.898353215e-05,0.0002416671487,0.0005525587476,0.0008464466082, 0.001116588362,
   0.001356910449, 0.001562162768, 0.001728043775, 0.001851306646, 0.001929830294,
   0.001962663839, 0.001950036502, 0.001893337118, 0.001795061398, 0.001658729278,
     0.0014887742, 0.001290410524, 0.001069476479,0.0008322646609,0.0005853404873,
  0.0003353530774,8.884813724e-05,-0.0001479161292,-0.0003691415477,-0.0005696481676,
  -0.0007450121921,-0.0008916809456,-0.001007059589,-0.001089569065, -0.00113867328,
  -0.001154874102,-0.001139673288,-0.001095506479,-0.001025646925,-0.0009340842953,
  -0.0008253813139,-0.0007045147358,-0.0005767011316,-0.0004472177534,-0.0003212214506,
  -0.0002035713987,-9.866186883e-05,-1.027068447e-05,5.857364522e-05,0.0001056977344,
  0.0001298641728,  0.00013081824,0.0001093050596,6.704850239e-05,6.701648999e-06,
  -6.824021693e-05,-0.0001535525516,-0.0002444266574,-0.0003356316302,-0.0004217013193,
  -0.000497128116,-0.0005565682659,-0.0005950420164,-0.0006081351312,-0.0005921784323,
  -0.000544418057,-0.0004631520133,-0.0003478449944,-0.0001992015168,-1.920835894e-05,
  0.0001888704719,0.0004205328878,0.0006701257662,0.0009309667512, 0.001195509336,
   0.001455536229, 0.001702387352, 0.001927207457, 0.002121214056, 0.002275970066,
   0.002383664483, 0.002437379211, 0.002431348432, 0.002361188643, 0.002224102151,
   0.002019042149, 0.001746833092, 0.001410242636, 0.001014002948,0.0005647727521,
  7.104830729e-05,-0.0004569870653,-0.001007660409,-0.001568062464,-0.002124340739,
  -0.002662035404, -0.00316643808,-0.003622981487,-0.004017631523,-0.004337286577,
  -0.004570161924,-0.004706159234, -0.00473719975,-0.004657519516,-0.004463912919,
  -0.004155918024,-0.003735934617,-0.003209276358,-0.002584141912,-0.001871516462,
   -0.00108499371,-0.0002405262494,0.0006438943674, 0.001548618195, 0.002452774439,
   0.003334753448, 0.004172720481, 0.004945155233, 0.005631394684, 0.006212176289,
   0.006670155562, 0.006990397815, 0.007160814479,  0.00717255054, 0.007020294666,
   0.006702511571,  0.00622158777, 0.005583884194, 0.004799688701, 0.003883073106,
   0.002851653611, 0.001726254821,0.0005304884398,-0.0007097448688,-0.001966825221,
  -0.003212036099,-0.004416229203,-0.005550513044,-0.006586954929,-0.007499267813,
   -0.00826348085,-0.008858558722, -0.00926697161,-0.009475179948,-0.009474050254,
  -0.009259151295,-0.008830962703,-0.008194951341,-0.007361546159, -0.00634597661,
   -0.00516800629,-0.003851545276,-0.002424160019,-0.000916483812,0.0006384498556,
   0.002205949975, 0.003750453936, 0.005236354657, 0.006628832314, 0.007894690149,
   0.009003151208, 0.009926622733,  0.01064138394,  0.01112819742,  0.01137281954,
     0.0113664018,  0.01110576559,  0.01059354935, 0.009838215075, 0.008853926323,
   0.007660278585,  0.00628190767, 0.004747967701, 0.003091502236, 0.001348715043,
  -0.0004418406461,-0.002240136964,-0.004005586263,-0.005697981454,-0.007278431207,
  -0.008710275404,-0.009959952906, -0.01099780854, -0.01179880369, -0.01234313753,
   -0.01261673588, -0.01261162292, -0.01232613716, -0.01176501531,  -0.0109393131,
  -0.009866191074,-0.008568543941,-0.007074504625,-0.005416812375,-0.003632080741,
  -0.001759966719,0.0001577349758, 0.002078049118, 0.003957806621,  0.00575464312,
   0.007427974604, 0.008939942345,  0.01025628671,  0.01134714577,  0.01218775101,
    0.01275900286,  0.01304791309,  0.01304791309,  0.01275900286,  0.01218775101,
    0.01134714577,  0.01025628671, 0.008939942345, 0.007427974604,  0.00575464312,
   0.003957806621, 0.002078049118,0.0001577349758,-0.001759966719,-0.003632080741,
  -0.005416812375,-0.007074504625,-0.008568543941,-0.009866191074,  -0.0109393131,
   -0.01176501531, -0.01232613716, -0.01261162292, -0.01261673588, -0.01234313753,
   -0.01179880369, -0.01099780854,-0.009959952906,-0.008710275404,-0.007278431207,
  -0.005697981454,-0.004005586263,-0.002240136964,-0.0004418406461, 0.001348715043,
   0.003091502236, 0.004747967701,  0.00628190767, 0.007660278585, 0.008853926323,
   0.009838215075,  0.01059354935,  0.01110576559,   0.0113664018,  0.01137281954,
    0.01112819742,  0.01064138394, 0.009926622733, 0.009003151208, 0.007894690149,
   0.006628832314, 0.005236354657, 0.003750453936, 0.002205949975,0.0006384498556,
  -0.000916483812,-0.002424160019,-0.003851545276, -0.00516800629, -0.00634597661,
  -0.007361546159,-0.008194951341,-0.008830962703,-0.009259151295,-0.009474050254,
  -0.009475179948, -0.00926697161,-0.008858558722, -0.00826348085,-0.007499267813,
  -0.006586954929,-0.005550513044,-0.004416229203,-0.003212036099,-0.001966825221,
  -0.0007097448688,0.0005304884398, 0.001726254821, 0.002851653611, 0.003883073106,
   0.004799688701, 0.005583884194,  0.00622158777, 0.006702511571, 0.007020294666,
    0.00717255054, 0.007160814479, 0.006990397815, 0.006670155562, 0.006212176289,
   0.005631394684, 0.004945155233, 0.004172720481, 0.003334753448, 0.002452774439,
   0.001548618195,0.0006438943674,-0.0002405262494, -0.00108499371,-0.001871516462,
  -0.002584141912,-0.003209276358,-0.003735934617,-0.004155918024,-0.004463912919,
  -0.004657519516, -0.00473719975,-0.004706159234,-0.004570161924,-0.004337286577,
  -0.004017631523,-0.003622981487, -0.00316643808,-0.002662035404,-0.002124340739,
  -0.001568062464,-0.001007660409,-0.0004569870653,7.104830729e-05,0.0005647727521,
   0.001014002948, 0.001410242636, 0.001746833092, 0.002019042149, 0.002224102151,
   0.002361188643, 0.002431348432, 0.002437379211, 0.002383664483, 0.002275970066,
   0.002121214056, 0.001927207457, 0.001702387352, 0.001455536229, 0.001195509336,
  0.0009309667512,0.0006701257662,0.0004205328878,0.0001888704719,-1.920835894e-05,
  -0.0001992015168,-0.0003478449944,-0.0004631520133,-0.000544418057,-0.0005921784323,
  -0.0006081351312,-0.0005950420164,-0.0005565682659,-0.000497128116,-0.0004217013193,
  -0.0003356316302,-0.0002444266574,-0.0001535525516,-6.824021693e-05,6.701648999e-06,
  6.704850239e-05,0.0001093050596,  0.00013081824,0.0001298641728,0.0001056977344,
  5.857364522e-05,-1.027068447e-05,-9.866186883e-05,-0.0002035713987,-0.0003212214506,
  -0.0004472177534,-0.0005767011316,-0.0007045147358,-0.0008253813139,-0.0009340842953,
  -0.001025646925,-0.001095506479,-0.001139673288,-0.001154874102, -0.00113867328,
  -0.001089569065,-0.001007059589,-0.0008916809456,-0.0007450121921,-0.0005696481676,
  -0.0003691415477,-0.0001479161292,8.884813724e-05,0.0003353530774,0.0005853404873,
  0.0008322646609, 0.001069476479, 0.001290410524,   0.0014887742, 0.001658729278,
   0.001795061398, 0.001893337118, 0.001950036502, 0.001962663839, 0.001929830294,
   0.001851306646, 0.001728043775, 0.001562162768, 0.001356910449, 0.001116588362,
  0.0008464466082,0.0005525587476,0.0002416671487,-7.898353215e-05,-0.0004018342588,
  -0.0007191998884,-0.001023471472,-0.001307305647,-0.001563818427,-0.001786758774,
  -0.001970671583,-0.002111035399,-0.002204380464,-0.002248374745,-0.002241885522,
  -0.002185003599,-0.002079044236,-0.001926507684,-0.001731016906,-0.001497221645,
  -0.001230681315,-0.0009377197712,-0.0006252674502,-0.0003006838087,2.842572394e-05,
  0.0003544007777,0.0006697151111,0.0009671622538, 0.001240027836, 0.001482254243,
   0.001688579097, 0.001854659291, 0.001977164531, 0.002053850098, 0.002083594678,
   0.002066415735, 0.002003450412, 0.001896913629, 0.001750023803,    0.001566911,
   0.001352496329,  0.00111236074,0.0008525911835,0.0005796258338,0.0003000827273,
  2.059895996e-05,-0.0002523401636,-0.000512553961,-0.0007543154643,-0.0009724820266,
  -0.001162611647,-0.001321053947,-0.001445024856,-0.001532652183,-0.001583001111,
  -0.001596070128,-0.001572768437,-0.001514866133,-0.001424926217,-0.001306214952,
  -0.001162599423,-0.0009984301869,-0.0008184147882,-0.0006274871994,-0.0004306706542,
  -0.0002329483541,-3.91335343e-05,0.0001462498476, 0.000319073908,0.0004757017596,
   0.000613066135,0.0007287285407, 0.000820920628,0.0008885662537,0.0009312839247,
  0.0009493682301,0.0009437559056,0.0009159729234,0.0008680695901,0.0008025396965,
  0.0007222332642,0.0006302599213,0.0005298888427,0.0004244496231,0.0003172304423,
   0.000211385297,0.0001098477442, 1.52497505e-05,-7.014048606e-05,-0.0001444740483,
  -0.0002063579595,-0.0002548811899,-0.0002896186197,-0.0003106273361,-0.0003184216912,
  -0.0003139409237,-0.0002984973835,-0.0002737220784,-0.0002414941409,-0.0002038724197,
  -0.000163013683,-0.0001211009148,-8.02583163e-05,-4.248788173e-05,-9.59188128e-06,
  1.687963049e-05,3.568354441e-05,4.592007463e-05,4.706446998e-05,3.897591523e-05,
  2.190471423e-05,-3.523097121e-06,-3.632526204e-05,-7.520399231e-05,-0.0001185864603,
  -0.0001646841702,-0.0002115499956,-0.0002571500954,-0.0002994294919,-0.0003363868454,
  -0.0003661411174,-0.0003869987559,-0.0003975153959,-0.0003965470823,-0.0003832941002,
  -0.0003573384602,-0.0003186598478,-0.0002676511067,-0.0002051122719,-0.0001322384778,
  -5.058799798e-05,3.795147859e-05,0.0001312156965,0.0002268182288,0.0003222199448,
  0.0004147956497, 0.000501912029,0.0005809994182,0.0006496306742,0.0007055880851,
  0.0007469368284,0.0007720750291,0.0007797963335,0.0007693211082, 0.000740331132,
  0.0006929860101,0.0006279278896,0.0005462699337,0.0004495785688,0.0003398377448,
  0.0002194040135,9.094936831e-05,-4.26020888e-05,-0.0001781469764,-0.0003124797076,
  -0.0004423737701,-0.0005646635545,-0.0006763247657,-0.0007745536859,-0.0008568366757,
  -0.0009210230783,-0.0009653714369,-0.000988607062,-0.0009899501456,-0.0009691395098,
  -0.0009264436667,-0.0008626584313,-0.0007790862001,-0.0006775091169,-0.0005601458251,
  -0.0004296013212,-0.000288801326,-0.0001409251563,1.067366975e-05,0.0001625445875,
  0.0003112267877,0.0004533290339,0.0005856140051,0.0007050738204,0.0008089995827,
   0.000895051402, 0.000961305399, 0.001006302191, 0.001029083272, 0.001029202831,
   0.001006743289,0.0009623056976,0.0008969980991,0.0008123989101,0.0007105233381,
   0.000593767094,0.0004648535105,0.0003267596767,0.0001826515072,  3.5800771e-05,
  -0.0001104844996,-0.0002529457852,-0.0003884400066,-0.0005140255671,-0.0006270084996,
  -0.0007250263589,-0.0008060767432,-0.0008685722714,-0.0009113670094,-0.0009337816737,
  -0.0009356039809,-0.0009170957492,-0.0008789729327,-0.000822388276,-0.0007488898118,
  -0.0006603861111,-0.0005590894143,-0.0004474665329,-0.0003281701065,-0.0002039804676,
  -7.773286052e-05,4.774365152e-05,0.0001696918771,0.0002854951308,0.0003927201033,
  0.0004891845747,0.0005729964469,0.0006425839383,0.0006967348163,0.0007346104248,
  0.0007557595382,0.0007601138786,0.0007479869528,0.0007200532127,0.0006773279165,
  0.0006211298169,0.0005530476337, 0.000474892644,0.0003886556369, 0.000296452723,
  0.0002004776907,0.0001029413033,6.037222647e-06,-8.813699969e-05,-0.0001775895071,
  -0.0002605018963,-0.0003352596541,-0.0004004783113,-0.0004550291051,-0.0004980596132,
  -0.0005290043773,-0.0005475862999,-0.0005538139376,-0.0005479709362,-0.0005306027597,
  -0.0005024933489,-0.0004646411398,-0.000418224954,-0.0003645745746,-0.0003051296808,
  -0.0002414127521,-0.0001749700168,-0.000107376407,-4.014060687e-05,2.527552897e-05,
  8.751275163e-05,0.0001453385485,0.0001976746571,0.0002436031355,0.0002823914983,
  0.0003134935105,0.0003365652228,0.0003514521813,0.0003581959754,0.0003570117406,
  0.0003482889733,0.0003325616708,0.0003105038195,0.0002828930446, 0.000250599609,
  0.0002145626204,0.0001757340942,0.0001351225947,9.369754844e-05,5.239701568e-05,
  1.212586358e-05,-2.629073424e-05,-6.210562424e-05,-9.468132339e-05,-0.0001234758383,
  -0.0001480708452,-0.0001681533759,-0.0001835408329,-0.0001941554801,-0.0002000438399,
  -0.0002013438789,-0.0001983009861,-0.0001912303414,-0.0001805337815,-0.0001666402968,
  -0.0001500946382,-0.0001313507964,-0.0001109965888,-8.956657985e-05,-6.75895426e-05,
  -4.555998385e-05,-2.396012133e-05,-3.216239975e-06,1.627999518e-05,3.421036308e-05,
  5.030104148e-05,6.435653631e-05,7.622599514e-05,8.583578165e-05, 9.31532195e-05,
  9.821768617e-05,0.0001011015411,0.0001019394258,0.0001009098851,9.809580661e-05,
   9.39407546e-05,8.849070582e-05,8.201303717e-05, 7.47839731e-05,6.704354018e-05,
   5.90311538e-05,5.094855442e-05, 4.29978063e-05,3.534229108e-05,2.814332402e-05,
  2.151943045e-05,1.558321128e-05,1.040167172e-05,6.035544629e-06, 2.50182984e-06,
  -1.840480337e-07,-2.044103212e-06,-3.094174872e-06,-6.278696674e-05]
global Filter_Size
Filter_Size = 1064

#正交锁相放大器
sinwave = []
coswave = []
longsinwave = []
longcoswave = []
global Frehz
global Buf_size

global Filter_SampleBuffer1
Filter_SampleBuffer1 = []

global Filter_SampleBuffer2
Filter_SampleBuffer2 = []
global DAL_OutPut
DAL_OutPut = []


#设置字体文件，否则不能显示中文  
myfont = matplotlib.font_manager.FontProperties(fname='c:\\windows\\fonts\\fzshjw_0.ttf')
def drawpicture(listdate,bufsize = None):
	global Buf_size
	lenth2 = len(listdate)
	print "listdate is "+ str(lenth2)
	if bufsize == None:
		figure3 = plt.plot(range(0,lenth2), listdate, '--bo')
	else:
		figure3 = plt.plot(range(0,bufsize), listdate, '--bo')
	plt.ylabel('value(mv)')
	plt.title('listdate')
	plt.show()

def read_singledata(filestr):
        global datalist
        datalist=[]
        file_data = open('.\\'+filestr+'.txt','r')   ##sample_table3 sample_Value2  DAL_OutPut3
        lines = file_data.readlines()
        file_data.close()
        inum = 0
        for item in lines:

                pattern = re.match(r'.*\[.*\] = (-?\d.*)\n',item)
               
                if pattern:
                        inum += 1
                        datalist.append(string.atof(''.join(list(pattern.groups(1)))))
##                        if(inum == 460):
##                                break                            
        ##print datalist
        lenth = len(datalist)
        print lenth
        print datalist[lenth-1]        
def OccureDate():

    global datalist
    global Buf_size
    global Frehz
    global fz1
    global fz2
    global Fs
    f = Frehz        #信号频率Hz
    A = 2000         #信号的幅值（mv）
    fs=Fs           #采样频率 hz
    
    N = Buf_size    #采样点数
    xx = []  
    n = [2*math.pi*f*t/fs for t in range(N)]  
    x = [A*math.sin(i+1.0) for i in n]
    print"原始信号x[]：\n"
##    drawpicture(x,N)
    x1 = [500*math.sin(i*10)-30 for i in n]
    
    #另一路正弦信号
    n2 = [2*math.pi*fz1*t/fs for t in range(N)]  
    x2 = [500*math.sin(i) for i in n2]
    #另一路正弦信号
    n3 = [2*math.pi*fz2*t/fs for t in range(N)]  
    x3 = [300*math.sin(i) for i in n3]
##    drawpicture(x1,N)
    for i in range(len(x)):
        xx.append(x[i] )   ##+ x1[i]+ x2[i]+ x3[i]
    print "加噪声后的待测信号xx[]:\n"
    datalist = xx


def drawsamplevalue(listdate):
    global Buf_size
    templist = []
    lenth2 = len(listdate)
    print "listdate is "+ str(lenth2)
    for i in range(0,Buf_size):
        templist.append(listdate[i])
    
    figure3 = plt.plot(range(0,Buf_size), templist, '--bo')
    
    plt.ylabel('value(v)')
    plt.title('listdate')
    plt.show()   
	
def drawCross_OutPut():
	lenth2 = len(Cross_OutPut)
	print "lenth2 is "+ str(lenth2)
	#Cross_OutPut[300] = 0
	figure2 = plt.plot(range(0,lenth2), Cross_OutPut, '--bo')
	plt.ylabel('value(v)')
	plt.title('Cross_OutPut')
	plt.show()
	


#数字低通滤波器		
def LinearConvolution(CrossDate,LOWFILT_SIZE,filter_xishu,Outputdata):
    
    Output = []  #输出序列
    h = []       #滤波器系数序列
    Input = []   #输入序列
    
    hn = LOWFILT_SIZE
    
    h = filter_xishu
    hn = len(filter_xishu)
    Input = CrossDate
    xn = len(CrossDate)
    yn = xn+hn-1    #以xn = 420, hn = 62为例，yn = 481
    m = 0

    Output = [initial_value for i in range(yn)] #初始化y
    m = yn-1
    for i in range(1,hn):   # 1-> hn-1
        LL = m
        for j in range(1,xn):  # 1-> xn-1
            Output[LL] += h[i]* Input[j]  
            #print LL    #LL 第一次从480 -》62，第二次从479-》61，最后一次从420-》
            LL -= 1
        Output[LL] += Input[0]*h[i]   #Input[0]*h[]
##        print LL
        m -= 1 
    ##Output 计算了从61->1
    LL = m   #此时，m 为yn-hn, 即419
    print 'LL='+str(LL)
    for j in range(1,xn-1):
        Output[LL] +=  h[0]*Input[j]
        LL -=1
    Output[LL] += Input[0]*h[0]
 
    drawpicture(Output)
    return Output

def Dal_vpp(samplist):
        global datalist
        MAXvalue = []
        MINvalue = []
        index = 0
        Winlist = [0,0,0,0,0]
        sumvalue2 = 0
        sumvalue1 = 0
        for i in range(0,len(samplist)-5):
                Winlist[0] = samplist[i]
                Winlist[1] = samplist[i+1]
                Winlist[2] = samplist[i+2]
                Winlist[3] = samplist[i+3]
                Winlist[4] = samplist[i+4]

                ##比较[2]是不是最大的
                if Winlist[2]> Winlist[0] and Winlist[2]> Winlist[1] and Winlist[2]> Winlist[3] and Winlist[2]> Winlist[4]:
                      MAXvalue.append(Winlist[2])
                elif Winlist[2]< Winlist[0] and Winlist[2]< Winlist[1] and Winlist[2]< Winlist[3] and Winlist[2]< Winlist[4]:
                        MINvalue.append(Winlist[2])
        ##处理MAXvalue MINvalue，排序比较，去掉最大值和最小值
        MAXlen = len(MAXvalue)
        for k in range(MAXlen):
                for j in range(k+1,MAXlen):
                        if MAXvalue[k]< MAXvalue[j]:
                                tt = MAXvalue[j]
                                MAXvalue[j] = MAXvalue[k]
                                MAXvalue[k] = tt

        print MAXvalue
        for i in range(1,MAXlen-1):
                sumvalue1 += MAXvalue[i]
        print"MAXvalue: \n"
        Vtop = sumvalue1/(MAXlen-2)
        print Vtop
        print '\n'
        MINlen = len(MINvalue)
        
        for k in range(MINlen):
                for j in range(k+1,MINlen):
                        if MINvalue[k]< MINvalue[j]:
                                tt = MINvalue[j]
                                MINvalue[j] = MINvalue[k]
                                MINvalue[k] = tt
        print MINvalue
        for i in range(1,MINlen-1):
                sumvalue2 += MINvalue[i]
        print"MINvalue: \n"
        Vbottom = sumvalue2/(MINlen-2)
        print Vbottom
        print '\n'
        ##计算幅值
        print  (Vtop-Vbottom)/2
	
if __name__ == '__main__' :
	
	
        global Frehz
        global Buf_size
        global fz1
        global fz2
        global Fs
        sumnum = 0
        Buf_size = 520
        Frehz = 5000
        fz1 = 500
        fz2 = 50000
        Fs = 210000
        initial_value = 0

    
##------------------------------
##        OccureDate()
##------------------------------    
        read_singledata('sample3')
##------------------------------
        drawsamplevalue(datalist)	

        DAL_OutPut = LinearConvolution(datalist,Filter_Size,Filter,DAL_OutPut)

        Dal_vpp(datalist)

        #频谱绘制
        scrdatalist = datalist
        N = len(scrdatalist)
        xf = np.fft.fft(scrdatalist)
        xf_abs = np.fft.fftshift(abs(xf))
        axis_xf = np.linspace(-N/2,N/2-1,num=N)
        
        plt.title(u'频率为5Hz的正弦频谱图')
        plt.plot(axis_xf,xf_abs)
        plt.axis('tight')
        plt.show() 

        #频谱绘制
        scrdatalist = DAL_OutPut
        N = len(scrdatalist)
        xf = np.fft.fft(scrdatalist)
        xf_abs = np.fft.fftshift(abs(xf))
        axis_xf = np.linspace(-N/2,N/2-1,num=N)
        
        plt.title(u'频率为5Hz的正弦频谱图')
        plt.plot(axis_xf,xf_abs)
        plt.axis('tight')
        plt.show() 















	
	
	