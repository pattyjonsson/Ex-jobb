/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 8.5 and the Signal Processing Toolbox 7.0.
 * Generated on: 07-Jun-2017 19:56:07
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 29
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 */



# define M 646
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\MATLAB Production Server\R2015a\extern\include\tmwtypes.h 
 */

static float b[M+1] = {
   4.011308894654e-09,4.188299076913e-09,4.587189264154e-09,4.832892738699e-09,
   4.103775396614e-09,2.100677866109e-09,-3.241455830016e-11,-5.482254534755e-10,
   5.514819634591e-10,7.369836286386e-10,-2.130262595922e-09,-6.327687420004e-09,
   -7.83574022536e-09,-6.310336910583e-09,-6.957339545163e-09,-1.355632309081e-08,
   -2.152690228429e-08,-2.315694524913e-08,-2.008093351665e-08,-2.35619853506e-08,
   -3.798028812322e-08,-5.110584180266e-08,-5.051132448823e-08,-4.543213341819e-08,
   -5.7174608736e-08,-8.543088708957e-08,-1.027552286854e-07,-9.519707861567e-08,
   -9.070899982518e-08,-1.218073370461e-07,-1.70030569841e-07,-1.850232402272e-07,
   -1.646596770648e-07,-1.713956753642e-07,-2.395855302066e-07,-3.08724975136e-07,
   -3.062915071508e-07,-2.718779081878e-07,-3.151055905363e-07,-4.411491189247e-07,
   -5.17964082511e-07,-4.755864937155e-07,-4.424676949141e-07,-5.663920195154e-07,
   -7.620537938566e-07,-8.095141966413e-07,-7.083391369595e-07,-7.253287528517e-07,
   -9.876170797099e-07,-1.23391957824e-06,-1.189386374256e-06,-1.040159141562e-06,
   -1.203355748183e-06,-1.650928511458e-06,-1.872504511975e-06,-1.666568261021e-06,
   -1.548697082714e-06,-1.996416552523e-06,-2.618218482487e-06,-2.670601048171e-06,
   -2.278294748632e-06,-2.377010291129e-06,-3.246165989115e-06,-3.91262584866e-06,
   -3.609238408425e-06,-3.132956009104e-06,-3.743189491289e-06,-5.07542264865e-06,
   -5.496322927078e-06,-4.701297120206e-06,-4.459078447548e-06,-5.915399613353e-06,
   -7.527214603992e-06,-7.280487151476e-06,-6.071696779164e-06,-6.632176808469e-06,
   -9.136461716592e-06,-1.050952076721e-05,-9.195686791907e-06,-8.055295561358e-06,
   -1.013973865571e-05,-1.350386941996e-05,-1.379318998018e-05,-1.133434010618e-05,
   -1.1262833378e-05,-1.545153659744e-05,-1.88487157805e-05,-1.711706194054e-05,
   -1.413680498171e-05,-1.654239495035e-05,-2.279900674483e-05,-2.469686025361e-05,
   -2.042834691117e-05,-1.853768247372e-05,-2.477198874915e-05,-3.193245959735e-05,
   -3.041149066401e-05,-2.42192130332e-05,-2.594527934472e-05,-3.647738948311e-05,
   -4.199633992246e-05,-3.55780000238e-05,-2.982571356652e-05,-3.793350594502e-05,
   -5.137791525703e-05,-5.169737863109e-05,-4.058410411871e-05,-3.947496519687e-05,
   -5.561514938266e-05,-6.808675037252e-05,-5.98881938548e-05,-4.718995951831e-05,
   -5.586385101027e-05,-7.884037366646e-05,-8.426260613631e-05,-6.652155369189e-05,
   -5.874074764518e-05,-8.118345030194e-05,-0.0001055724071528,-9.744443842413e-05,
   -7.367500544454e-05,-7.964795151949e-05,-0.0001157759346409,-0.0001319262094883,
   -0.0001065513385135,-8.610185138662e-05,-0.0001139472879455,-0.0001569493772727,
   -0.0001532858810267,-0.0001136296972482,-0.0001106877362833,-0.0001631519088718,
   -0.0001987182041936,-0.0001665584079068,-0.0001250258766607,-0.0001544300529892,
   -0.000224154175428,-0.000233181738315,-0.0001730140829599,-0.000150989747063,
   -0.0002211558750208,-0.0002883487210127,-0.0002537600086037,-0.000180515811159,
   -0.0002030042489325,-0.0003080134243719,-0.0003431482782584,-0.0002596117091101,
   -0.0002035970118196, -0.00028897916425,-0.0004034694329088,-0.0003764141020068,
   -0.0002595505836977,-0.0002601667697616,-0.0004076666701952,-0.0004886672101828,
   -0.0003830455257292,-0.0002731524537468,-0.0003647670388638,-0.0005447739496556,
   -0.0005431874822732,-0.0003714494577187,-0.0003270395198382,-0.0005200697378146,
   -0.0006736077193032,-0.0005544854654316,-0.0003665417977267,-0.0004458290374718,
   -0.0007100334519724,-0.0007621316187584,-0.0005280415706334,-0.0004061017982707,
   -0.0006397098252546,-0.0008989098769147,-0.0007859456995616,-0.0004935211090291,
   -0.0005291835956409,-0.0008932093631143,-0.001039264794827,-0.0007435081873318,
   -0.0005021133781264,-0.0007586671092906,-0.001161148367753,-0.001089104264013,
   -0.0006671977947646,-0.0006124701445532,-0.001083814770864,-0.001376825653225,
   -0.001033775649833,-0.0006231347320639,-0.0008671342386335, -0.00145114964834,
   -0.001473637213455,-0.0009042162461157,-0.0006952037138785,-0.001266698598496,
   -0.001771334470584,-0.001415377575812,-0.0007815066392563,-0.000954453314353,
   -0.00175286719621,-0.001945136871162,-0.001224512042713,-0.0007802825506398,
   -0.001422392478149,-0.002211657862514,-0.001903776071728,-0.0009946314737083,
   -0.001010654796304,-0.002042712329092,-0.002502765379343,-0.001650551308998,
   -0.0008756056052,-0.001528086017159,-0.002677299047169, -0.00251122710517,
   -0.001285420757899,-0.001028397362573,-0.002289477764779,-0.003136859631975,
   -0.002206069424083,-0.0009956365996182,-0.001559184398542,-0.003137105467358,
   -0.003244381203686,-0.001682356541348,-0.001005132426445, -0.00245486505863,
   -0.003826724452676,-0.002914467650652,-0.001162793343725,-0.001491260906209,
   -0.00354847040986,-0.004101908009967,-0.002219279944982,-0.0009452793048445,
   -0.002494420511541,-0.004538792547762,-0.003797221238292,-0.001408683789738,
   -0.001302053814623,-0.003856864747827,-0.005072500437334,-0.002935307429758,
   -0.0008622331138951,-0.002358364241627, -0.00522514077175,   -0.004872920709,
   -0.001775521758713,-0.0009729670293229,-0.003995087092039,-0.006133631648022,
   -0.003875777527041,-0.0007801927051806,-0.001991268371798,-0.005821932634312,
   -0.006157994062913,-0.002318690351313,-0.0004892671897306,-0.003880754586934,
   -0.007251393050973,-0.005096110381247,-0.0007362051626571,-0.001328514777407,
   -0.006246454379705,-0.007671013968252,-0.003112807172426, 0.000162355754243,
   -0.003408656603676, -0.00838163174634,-0.006672712857483,-0.0007837911178018,
   -0.0002850400902607,-0.006389267008722,-0.009444654223674,-0.004267120288366,
   0.001001591913764,-0.002429665445437,-0.009472441869008,-0.008731223068118,
   -0.001002086583796, 0.001275033462819,-0.006091974518949, -0.01155590598539,
   -0.005966421824757, 0.002074893207706,-0.0006925289979768, -0.01046786862313,
   -0.01152264162233,-0.001522747572266, 0.003623099068162,-0.005080336360606,
   -0.01420904295077,-0.008591620680327, 0.003513028218031, 0.002334668220996,
   -0.01131248796524, -0.01566126484083,-0.002621530595221, 0.007444733860862,
   -0.002729111355536, -0.01801820507903, -0.01315816002184, 0.005738900968763,
   0.0081598810816, -0.01195636360721, -0.02311935535921, -0.00513086704852,
   0.01512102683283, 0.003097784642185, -0.02545033043093, -0.02373681702357,
   0.01068029575112,  0.02372741157375, -0.01235978758099, -0.04492647865803,
   -0.01406122833532,  0.04352523595222,   0.0297723459538, -0.06168787620649,
   -0.09346166337636,  0.05562412699548,   0.3067346221198,   0.4319472421149,
   0.3067346221198,  0.05562412699548, -0.09346166337636, -0.06168787620649,
   0.0297723459538,  0.04352523595222, -0.01406122833532, -0.04492647865803,
   -0.01235978758099,  0.02372741157375,  0.01068029575112, -0.02373681702357,
   -0.02545033043093, 0.003097784642185,  0.01512102683283, -0.00513086704852,
   -0.02311935535921, -0.01195636360721,   0.0081598810816, 0.005738900968763,
   -0.01315816002184, -0.01801820507903,-0.002729111355536, 0.007444733860862,
   -0.002621530595221, -0.01566126484083, -0.01131248796524, 0.002334668220996,
   0.003513028218031,-0.008591620680327, -0.01420904295077,-0.005080336360606,
   0.003623099068162,-0.001522747572266, -0.01152264162233, -0.01046786862313,
   -0.0006925289979768, 0.002074893207706,-0.005966421824757, -0.01155590598539,
   -0.006091974518949, 0.001275033462819,-0.001002086583796,-0.008731223068118,
   -0.009472441869008,-0.002429665445437, 0.001001591913764,-0.004267120288366,
   -0.009444654223674,-0.006389267008722,-0.0002850400902607,-0.0007837911178018,
   -0.006672712857483, -0.00838163174634,-0.003408656603676, 0.000162355754243,
   -0.003112807172426,-0.007671013968252,-0.006246454379705,-0.001328514777407,
   -0.0007362051626571,-0.005096110381247,-0.007251393050973,-0.003880754586934,
   -0.0004892671897306,-0.002318690351313,-0.006157994062913,-0.005821932634312,
   -0.001991268371798,-0.0007801927051806,-0.003875777527041,-0.006133631648022,
   -0.003995087092039,-0.0009729670293229,-0.001775521758713,   -0.004872920709,
   -0.00522514077175,-0.002358364241627,-0.0008622331138951,-0.002935307429758,
   -0.005072500437334,-0.003856864747827,-0.001302053814623,-0.001408683789738,
   -0.003797221238292,-0.004538792547762,-0.002494420511541,-0.0009452793048445,
   -0.002219279944982,-0.004101908009967, -0.00354847040986,-0.001491260906209,
   -0.001162793343725,-0.002914467650652,-0.003826724452676, -0.00245486505863,
   -0.001005132426445,-0.001682356541348,-0.003244381203686,-0.003137105467358,
   -0.001559184398542,-0.0009956365996182,-0.002206069424083,-0.003136859631975,
   -0.002289477764779,-0.001028397362573,-0.001285420757899, -0.00251122710517,
   -0.002677299047169,-0.001528086017159,  -0.0008756056052,-0.001650551308998,
   -0.002502765379343,-0.002042712329092,-0.001010654796304,-0.0009946314737083,
   -0.001903776071728,-0.002211657862514,-0.001422392478149,-0.0007802825506398,
   -0.001224512042713,-0.001945136871162, -0.00175286719621,-0.000954453314353,
   -0.0007815066392563,-0.001415377575812,-0.001771334470584,-0.001266698598496,
   -0.0006952037138785,-0.0009042162461157,-0.001473637213455, -0.00145114964834,
   -0.0008671342386335,-0.0006231347320639,-0.001033775649833,-0.001376825653225,
   -0.001083814770864,-0.0006124701445532,-0.0006671977947646,-0.001089104264013,
   -0.001161148367753,-0.0007586671092906,-0.0005021133781264,-0.0007435081873318,
   -0.001039264794827,-0.0008932093631143,-0.0005291835956409,-0.0004935211090291,
   -0.0007859456995616,-0.0008989098769147,-0.0006397098252546,-0.0004061017982707,
   -0.0005280415706334,-0.0007621316187584,-0.0007100334519724,-0.0004458290374718,
   -0.0003665417977267,-0.0005544854654316,-0.0006736077193032,-0.0005200697378146,
   -0.0003270395198382,-0.0003714494577187,-0.0005431874822732,-0.0005447739496556,
   -0.0003647670388638,-0.0002731524537468,-0.0003830455257292,-0.0004886672101828,
   -0.0004076666701952,-0.0002601667697616,-0.0002595505836977,-0.0003764141020068,
   -0.0004034694329088, -0.00028897916425,-0.0002035970118196,-0.0002596117091101,
   -0.0003431482782584,-0.0003080134243719,-0.0002030042489325,-0.000180515811159,
   -0.0002537600086037,-0.0002883487210127,-0.0002211558750208,-0.000150989747063,
   -0.0001730140829599,-0.000233181738315,-0.000224154175428,-0.0001544300529892,
   -0.0001250258766607,-0.0001665584079068,-0.0001987182041936,-0.0001631519088718,
   -0.0001106877362833,-0.0001136296972482,-0.0001532858810267,-0.0001569493772727,
   -0.0001139472879455,-8.610185138662e-05,-0.0001065513385135,-0.0001319262094883,
   -0.0001157759346409,-7.964795151949e-05,-7.367500544454e-05,-9.744443842413e-05,
   -0.0001055724071528,-8.118345030194e-05,-5.874074764518e-05,-6.652155369189e-05,
   -8.426260613631e-05,-7.884037366646e-05,-5.586385101027e-05,-4.718995951831e-05,
   -5.98881938548e-05,-6.808675037252e-05,-5.561514938266e-05,-3.947496519687e-05,
   -4.058410411871e-05,-5.169737863109e-05,-5.137791525703e-05,-3.793350594502e-05,
   -2.982571356652e-05,-3.55780000238e-05,-4.199633992246e-05,-3.647738948311e-05,
   -2.594527934472e-05,-2.42192130332e-05,-3.041149066401e-05,-3.193245959735e-05,
   -2.477198874915e-05,-1.853768247372e-05,-2.042834691117e-05,-2.469686025361e-05,
   -2.279900674483e-05,-1.654239495035e-05,-1.413680498171e-05,-1.711706194054e-05,
   -1.88487157805e-05,-1.545153659744e-05, -1.1262833378e-05,-1.133434010618e-05,
   -1.379318998018e-05,-1.350386941996e-05,-1.013973865571e-05,-8.055295561358e-06,
   -9.195686791907e-06,-1.050952076721e-05,-9.136461716592e-06,-6.632176808469e-06,
   -6.071696779164e-06,-7.280487151476e-06,-7.527214603992e-06,-5.915399613353e-06,
   -4.459078447548e-06,-4.701297120206e-06,-5.496322927078e-06,-5.07542264865e-06,
   -3.743189491289e-06,-3.132956009104e-06,-3.609238408425e-06,-3.91262584866e-06,
   -3.246165989115e-06,-2.377010291129e-06,-2.278294748632e-06,-2.670601048171e-06,
   -2.618218482487e-06,-1.996416552523e-06,-1.548697082714e-06,-1.666568261021e-06,
   -1.872504511975e-06,-1.650928511458e-06,-1.203355748183e-06,-1.040159141562e-06,
   -1.189386374256e-06,-1.23391957824e-06,-9.876170797099e-07,-7.253287528517e-07,
   -7.083391369595e-07,-8.095141966413e-07,-7.620537938566e-07,-5.663920195154e-07,
   -4.424676949141e-07,-4.755864937155e-07,-5.17964082511e-07,-4.411491189247e-07,
   -3.151055905363e-07,-2.718779081878e-07,-3.062915071508e-07,-3.08724975136e-07,
   -2.395855302066e-07,-1.713956753642e-07,-1.646596770648e-07,-1.850232402272e-07,
   -1.70030569841e-07,-1.218073370461e-07,-9.070899982518e-08,-9.519707861567e-08,
   -1.027552286854e-07,-8.543088708957e-08, -5.7174608736e-08,-4.543213341819e-08,
   -5.051132448823e-08,-5.110584180266e-08,-3.798028812322e-08,-2.35619853506e-08,
   -2.008093351665e-08,-2.315694524913e-08,-2.152690228429e-08,-1.355632309081e-08,
   -6.957339545163e-09,-6.310336910583e-09,-7.83574022536e-09,-6.327687420004e-09,
   -2.130262595922e-09,7.369836286386e-10,5.514819634591e-10,-5.482254534755e-10,
   -3.241455830016e-11,2.100677866109e-09,4.103775396614e-09,4.832892738699e-09,
   4.587189264154e-09,4.188299076913e-09,4.011308894654e-09
};
