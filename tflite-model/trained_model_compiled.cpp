/* Generated by Edge Impulse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
// Generated on: 11.01.2023 05:45:51

#include <stdio.h>
#include <stdlib.h>
#include "edge-impulse-sdk/tensorflow/lite/c/builtin_op_data.h"
#include "edge-impulse-sdk/tensorflow/lite/c/common.h"
#include "edge-impulse-sdk/tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

#if EI_CLASSIFIER_PRINT_STATE
#if defined(__cplusplus) && EI_C_LINKAGE == 1
extern "C" {
    extern void ei_printf(const char *format, ...);
}
#else
extern void ei_printf(const char *format, ...);
#endif
#endif

#if defined __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#elif defined _MSC_VER
#define ALIGN(X) __declspec(align(X))
#elif defined __TASKING__
#define ALIGN(X) __align(X)
#endif

#ifndef EI_MAX_SCRATCH_BUFFER_COUNT
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#endif // EI_MAX_SCRATCH_BUFFER_COUNT

#ifndef EI_MAX_OVERFLOW_BUFFER_COUNT
#define EI_MAX_OVERFLOW_BUFFER_COUNT 10
#endif // EI_MAX_OVERFLOW_BUFFER_COUNT

using namespace tflite;
using namespace tflite::ops;
using namespace tflite::ops::micro;

namespace {

constexpr int kTensorArenaSize = 368;

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX)
#pragma Bss(".tensor_arena")
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#pragma Bss()
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16) __attribute__((section(".tensor_arena")));
#else
#define EI_CLASSIFIER_ALLOCATION_HEAP 1
uint8_t* tensor_arena = NULL;
#endif

static uint8_t* tensor_boundary;
static uint8_t* current_location;

template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};
enum used_operators_e {
  OP_FULLY_CONNECTED, OP_SOFTMAX,  OP_LAST
};
struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  TfLiteAllocationType allocation_type;
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
};
struct NodeInfo_t { // subset of TfLiteNode used for initialization from constant memory
  struct TfLiteIntArray* inputs;
  struct TfLiteIntArray* outputs;
  void* builtin_data;
  used_operators_e used_op_index;
};

TfLiteContext ctx{};
TfLiteTensor tflTensors[14];
TfLiteEvalTensor tflEvalTensors[14];
TfLiteRegistration registrations[OP_LAST];
TfLiteNode tflNodes[5];

const TfArray<2, int> tensor_dimension0 = { 2, { 1,14 } };
const ALIGN(8) float tensor_data1[2] = { -0.032982535660266876, 0.032982535660266876, };
const TfArray<1, int> tensor_dimension1 = { 1, { 2 } };
const ALIGN(16) float tensor_data2[5] = { -0.021181240677833557, -0.069288797676563263, -0.03831559419631958, 0.033785000443458557, 0.041523877531290054, };
const TfArray<1, int> tensor_dimension2 = { 1, { 5 } };
const ALIGN(16) float tensor_data3[10] = { -0.035277143120765686, 0, 0.094149433076381683, 0.024514298886060715, -0.011073833331465721, -0.19710724055767059, 0.037656329572200775, -0.04459863156080246, 0.048595208674669266, -0.026071412488818169, };
const TfArray<1, int> tensor_dimension3 = { 1, { 10 } };
const ALIGN(16) float tensor_data4[20] = { 0.027077719569206238, -0.016056308522820473, 0.0059488988481462002, -0.0026435598265379667, 0.040907539427280426, -0.025962049141526222, 0.02408946305513382, 0.027830438688397408, 0.077431082725524902, 0.052030310034751892, 0, -0.15709348022937775, -0.13785706460475922, -0.0045436583459377289, 0.03815024346113205, 0.0040713022463023663, -0.014252535067498684, -0.003766586072742939, 0.018318990245461464, -0.10652206838130951, };
const TfArray<1, int> tensor_dimension4 = { 1, { 20 } };
const ALIGN(16) float tensor_data5[20*14] = { 
  -0.33486753702163696, -0.31504234671592712, -0.27701506018638611, 0.078162938356399536, -0.066130682826042175, 0.0085132410749793053, -0.37847545742988586, -0.32966595888137817, -0.3588733971118927, 0.035205092281103134, 0.34865063428878784, -0.23345634341239929, -0.30988121032714844, 0.33787325024604797, 
  0.0015675174072384834, 0.038480300456285477, -0.050189416855573654, -0.16994750499725342, 0.08908245712518692, 0.40665671229362488, 0.28147399425506592, 0.35759088397026062, -0.31802642345428467, 0.28966584801673889, 0.23654019832611084, -0.17979402840137482, -0.070850849151611328, -0.33800777792930603, 
  -0.0083566326647996902, -0.4140181839466095, -0.33235979080200195, 0.1865038275718689, -0.0032497264910489321, 0.08746366947889328, -0.40111640095710754, -0.10315763205289841, -0.26463645696640015, 0.037102125585079193, -0.14379054307937622, -0.10572304576635361, -0.31043586134910583, -0.095070436596870422, 
  -0.40302345156669617, -0.10959547013044357, -0.3271910548210144, 0.171370729804039, 0.10242615640163422, 0.12377651035785675, -0.286844402551651, 0.066072061657905579, 0.065751679241657257, 0.35869017243385315, 0.0050603561103343964, -0.35767912864685059, 0.069308966398239136, 0.18928651511669159, 
  -0.036706361919641495, 0.19289366900920868, -0.29013925790786743, 0.30643320083618164, 0.13435767590999603, 0.3295866847038269, -0.35701519250869751, -0.2013414204120636, 0.039290118962526321, 0.088221997022628784, 0.097769096493721008, -0.025027433410286903, -0.066724762320518494, -0.12569646537303925, 
  0.23501940071582794, -0.20915557444095612, -0.052133757621049881, -0.09446321427822113, -0.0049844803288578987, 0.1811320036649704, 0.12653747200965881, 0.1650494784116745, 0.017509885132312775, -0.32076084613800049, -0.17825844883918762, -0.22990159690380096, 0.40769514441490173, -0.16925287246704102, 
  -0.36326515674591064, 0.32103845477104187, -0.10489016026258469, -0.11853870004415512, -0.16397075355052948, 0.098453260958194733, 0.10023467987775803, -0.11548545211553574, -0.21525561809539795, 0.20162731409072876, -0.36615902185440063, -0.33585795760154724, -0.43525391817092896, -0.3188689649105072, 
  -0.16584526002407074, 0.37656503915786743, -0.3077189028263092, -0.066208705306053162, -0.33836621046066284, 0.3549778163433075, 0.033367972820997238, -0.41293144226074219, 0.3044532835483551, -0.35065007209777832, 0.23441506922245026, -0.251180499792099, -0.32651561498641968, -0.20888990163803101, 
  -0.027528628706932068, 0.013019835576415062, -0.0022139584179967642, -0.30720788240432739, 0.25413253903388977, 0.11404895037412643, -0.20823834836483002, -0.15670417249202728, 0.099646300077438354, -0.39981934428215027, -0.48322215676307678, 0.32156997919082642, -0.041214000433683395, -0.23029293119907379, 
  -0.07031964510679245, 0.02982419915497303, -0.011874466203153133, 0.26129421591758728, -0.35060971975326538, -0.07126309722661972, -0.083543688058853149, -0.20797835290431976, 0.15886127948760986, -0.12414336204528809, -0.036844935268163681, -0.18373548984527588, -0.24911828339099884, -0.06712457537651062, 
  -0.33281353116035461, -0.34421068429946899, -0.39495661854743958, -0.31177571415901184, 0.39097866415977478, -0.1405317485332489, 0.13369390368461609, -0.013444632291793823, 0.05752861499786377, 0.2803020179271698, 0.0311737060546875, 0.35332533717155457, 0.078355610370635986, 0.34949091076850891, 
  0.17973034083843231, 0.060967940837144852, -0.18424929678440094, -0.2400229275226593, 0.034478496760129929, 0.56766676902770996, 0.22939455509185791, 0.40970197319984436, 0.43825444579124451, 0.5075451135635376, 0.030987244099378586, 0.46676146984100342, 0.1814093142747879, -0.14841806888580322, 
  -0.0018192975549027324, 0.12389153987169266, -0.087310910224914551, -0.35457378625869751, 0.30248633027076721, 0.010362611152231693, 0.21566128730773926, -0.081579230725765228, 0.037620630115270615, 0.48098450899124146, 0.068503953516483307, -0.10294988751411438, -0.19414970278739929, 0.44779136776924133, 
  0.03419751301407814, 0.08966449648141861, -0.13178339600563049, 0.27734139561653137, 0.053697314113378525, -0.095599815249443054, 0.21154262125492096, -0.074347779154777527, 0.13383010029792786, 0.31777670979499817, 0.40894761681556702, 0.36948826909065247, 0.20713871717453003, -0.16415384411811829, 
  -0.28361809253692627, -0.45071312785148621, 0.37536802887916565, -0.15542420744895935, 0.20413960516452789, -0.18044000864028931, 0.17482250928878784, 0.22028322517871857, 0.0032903044484555721, -0.18974357843399048, -0.38746532797813416, -0.10840494930744171, -0.37827286124229431, -0.14850850403308868, 
  -0.26249384880065918, 0.39168915152549744, -0.13523171842098236, 0.1477348804473877, -0.099835760891437531, 0.35725048184394836, -0.25454249978065491, -0.20946194231510162, -0.061385348439216614, 0.3307015597820282, -0.24765586853027344, 0.18772079050540924, -0.16975037753582001, -0.12047115713357925, 
  -0.41523450613021851, 0.25334146618843079, 0.14515727758407593, 0.058324892073869705, -0.020340241491794586, 0.011815492995083332, -0.031425513327121735, -0.18417002260684967, -0.035992741584777832, 0.14318780601024628, 0.030118003487586975, -0.32136827707290649, -0.22051994502544403, -0.35621634125709534, 
  -0.17950540781021118, 0.026362480595707893, -0.39027723670005798, -0.35920062661170959, 0.36434748768806458, -0.17064966261386871, 0.073118530213832855, 0.29946568608283997, -0.23503932356834412, 0.036988750100135803, 0.040658015757799149, 0.18251705169677734, 0.09143577516078949, -0.12208224087953568, 
  -0.29847970604896545, -0.10611175000667572, 0.3159203827381134, 0.38057142496109009, 0.25545015931129456, 0.13919559121131897, -0.027714280411601067, -0.30069774389266968, -0.13098767399787903, -0.12236784398555756, -0.37103748321533203, -0.2981802225112915, 0.28962287306785583, -0.059892762452363968, 
  -0.2385336309671402, 0.070548973977565765, 0.16780440509319305, 0.13361509144306183, 0.10072273015975952, 0.097265489399433136, 0.1154462993144989, -0.24718526005744934, 0.47664237022399902, 0.4855029284954071, 0.010038477368652821, 0.42734009027481079, 0.0851435586810112, -0.0095251379534602165, 
};
const TfArray<2, int> tensor_dimension5 = { 2, { 20,14 } };
const ALIGN(16) float tensor_data6[10*20] = { 
  -0.27318322658538818, -0.014016687870025635, 0.12290698289871216, 0.074745476245880127, 0.3609311580657959, -0.26030060648918152, -0.11589732766151428, 0.075009346008300781, -0.36281353235244751, -0.39379656314849854, -0.13624599575996399, -0.279366135597229, 0.34541714191436768, 0.34937173128128052, -0.12032896280288696, 0.0040909647941589355, -0.37547299265861511, 0.060225605964660645, -0.12740728259086609, 0.05368572473526001, 
  -0.28059786558151245, 0.062615931034088135, -0.2165655642747879, 0.1667969822883606, 0.10580015182495117, 0.03812822699546814, 0.3000338077545166, -0.18902638554573059, -0.15555453300476074, -0.3112604022026062, 0.068653404712677002, -0.33239167928695679, -0.1014312207698822, -0.13121494650840759, -0.33105406165122986, -0.3712192177772522, -0.17653581500053406, 0.2822265625, 0.20760005712509155, -0.36843103170394897, 
  -0.2382078617811203, 0.28145408630371094, 0.19754019379615784, -0.11015227437019348, 0.38067111372947693, 0.037017416208982468, 0.27475696802139282, -0.097845815122127533, 0.4511389434337616, 0.42826509475708008, -0.25146210193634033, -0.28707566857337952, 0.043315358459949493, -0.41617923974990845, 0.22911542654037476, -0.049943156540393829, -0.012670396827161312, 0.42737090587615967, -0.28669199347496033, -0.19335916638374329, 
  -0.2567063570022583, -0.091913297772407532, -0.2374739944934845, -0.32720217108726501, -0.025373747572302818, 0.21036872267723083, 0.29652446508407593, 0.35111206769943237, 0.40674883127212524, -0.28528106212615967, 0.33046531677246094, 0.030591525137424469, -0.12671223282814026, -0.28482222557067871, -0.072861425578594208, 0.44598937034606934, 0.11215563118457794, 0.12640662491321564, 0.13840413093566895, -0.36562511324882507, 
  0.053293339908123016, 0.02722698450088501, -0.24271287024021149, -0.33568859100341797, -0.43803542852401733, 0.35867464542388916, -0.16179646551609039, -0.036653399467468262, -0.26555997133255005, 0.41123011708259583, 0.021470248699188232, -0.42019453644752502, -0.37079283595085144, 0.15604168176651001, -0.078091681003570557, 0.070091113448143005, 0.068069323897361755, -0.38482159376144409, 0.40687280893325806, 0.10166460275650024, 
  0.25995397567749023, 0.3079967200756073, -0.34178513288497925, 0.037643402814865112, -0.29656919836997986, -0.08388867974281311, -0.012781940400600433, -0.09672313928604126, 0.347330242395401, -0.43508940935134888, -0.44195234775543213, 0.31645175814628601, -0.40949481725692749, 0.19077777862548828, -0.21736885607242584, 0.33017933368682861, -0.4356415867805481, -0.034634679555892944, -0.36985573172569275, 0.24572697281837463, 
  0.38132452964782715, -0.12746201455593109, 0.085620954632759094, 0.37772831320762634, 0.31659144163131714, -0.098261363804340363, 0.089344106614589691, 0.23962560296058655, 0.23107056319713593, 0.41318324208259583, -0.20815537869930267, 0.17202819883823395, -0.51212054491043091, -0.044503562152385712, 0.01348991971462965, -0.00044784194324165583, 0.20450481772422791, -0.082514628767967224, 0.1954762190580368, -0.25186848640441895, 
  -0.23455004394054413, 0.35152742266654968, -0.23938150703907013, -0.40966156125068665, -0.087713092565536499, -0.069684982299804688, -0.14983321726322174, -0.347726970911026, 0.2871149480342865, 0.25775033235549927, 0.27529001235961914, 0.31142982840538025, -0.16346448659896851, -0.030826220288872719, -0.096387922763824463, -0.17410942912101746, -0.35173949599266052, 0.069599449634552002, -0.17828625440597534, 0.12636436522006989, 
  -0.29330170154571533, 0.23992277681827545, 0.030253827571868896, 0.19904410839080811, 0.39974832534790039, -0.013660132884979248, 0.21821290254592896, -0.4124426543712616, -0.15349559485912323, -0.34022313356399536, 0.17745882272720337, 0.27848878502845764, 0.33419236540794373, 0.41852393746376038, -0.070620715618133545, 0.19627732038497925, -0.40590512752532959, 0.38830500841140747, -0.0054910182952880859, -0.050237160176038742, 
  -0.14405067265033722, 0.12738215923309326, 0.065549463033676147, 0.30919507145881653, -0.34823423624038696, 0.23773956298828125, 0.27708393335342407, -0.26550573110580444, 0.29078215360641479, -0.18153855204582214, -0.084425866603851318, -0.0036798762157559395, -0.49513232707977295, -0.150003582239151, -0.37820950150489807, 0.066883936524391174, 0.39568477869033813, 0.39590194821357727, -0.1701444685459137, 0.29852166771888733, 
};
const TfArray<2, int> tensor_dimension6 = { 2, { 10,20 } };
const ALIGN(16) float tensor_data7[5*10] = { 
  -0.18565642833709717, -0.058617472648620605, -0.42007988691329956, -0.050037052482366562, -0.14946219325065613, 0.41020101308822632, -0.11158698797225952, -0.64076697826385498, 0.17559322714805603, -0.24699203670024872, 
  0.36462777853012085, -0.55896604061126709, 0.29640495777130127, -0.070597298443317413, 0.18961507081985474, 0.078049682080745697, -0.60615622997283936, 0.10825877636671066, -0.57266366481781006, 0.094597876071929932, 
  -0.61057466268539429, 0.51904040575027466, 0.13289529085159302, 0.10547201335430145, 0.23484702408313751, -0.086546346545219421, 0.055243488401174545, 0.56870764493942261, 0.68161845207214355, -0.37584465742111206, 
  -0.56155037879943848, 0.037237703800201416, 0.43944349884986877, 0.27108493447303772, -0.046821564435958862, 0.064260482788085938, 0.39674171805381775, -0.51308482885360718, -0.42368271946907043, -0.366768479347229, 
  -0.055258631706237793, 0.50776225328445435, 0.53170311450958252, 0.029440002515912056, -0.44962489604949951, -0.30646568536758423, 0.22423116862773895, 0.52904552221298218, -0.20034612715244293, -0.48513540625572205, 
};
const TfArray<2, int> tensor_dimension7 = { 2, { 5,10 } };
const ALIGN(16) float tensor_data8[2*5] = { 
  0.26767244935035706, -0.47080358862876892, 0.5415496826171875, -0.37257826328277588, -0.82301867008209229, 
  -0.32594281435012817, 0.33484113216400146, -0.69228506088256836, 0.77083671092987061, 0.14462804794311523, 
};
const TfArray<2, int> tensor_dimension8 = { 2, { 2,5 } };
const TfArray<2, int> tensor_dimension9 = { 2, { 1,20 } };
const TfArray<2, int> tensor_dimension10 = { 2, { 1,10 } };
const TfArray<2, int> tensor_dimension11 = { 2, { 1,5 } };
const TfArray<2, int> tensor_dimension12 = { 2, { 1,2 } };
const TfArray<2, int> tensor_dimension13 = { 2, { 1,2 } };
const TfLiteFullyConnectedParams opdata0 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs0 = { 3, { 0,5,4 } };
const TfArray<1, int> outputs0 = { 1, { 9 } };
const TfLiteFullyConnectedParams opdata1 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs1 = { 3, { 9,6,3 } };
const TfArray<1, int> outputs1 = { 1, { 10 } };
const TfLiteFullyConnectedParams opdata2 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs2 = { 3, { 10,7,2 } };
const TfArray<1, int> outputs2 = { 1, { 11 } };
const TfLiteFullyConnectedParams opdata3 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs3 = { 3, { 11,8,1 } };
const TfArray<1, int> outputs3 = { 1, { 12 } };
const TfLiteSoftmaxParams opdata4 = { 1 };
const TfArray<1, int> inputs4 = { 1, { 12 } };
const TfArray<1, int> outputs4 = { 1, { 13 } };
const TensorInfo_t tensorData[] = {
  { kTfLiteArenaRw, tensor_arena + 80, (TfLiteIntArray*)&tensor_dimension0, 56, },
  { kTfLiteMmapRo, (void*)tensor_data1, (TfLiteIntArray*)&tensor_dimension1, 8, },
  { kTfLiteMmapRo, (void*)tensor_data2, (TfLiteIntArray*)&tensor_dimension2, 20, },
  { kTfLiteMmapRo, (void*)tensor_data3, (TfLiteIntArray*)&tensor_dimension3, 40, },
  { kTfLiteMmapRo, (void*)tensor_data4, (TfLiteIntArray*)&tensor_dimension4, 80, },
  { kTfLiteMmapRo, (void*)tensor_data5, (TfLiteIntArray*)&tensor_dimension5, 1120, },
  { kTfLiteMmapRo, (void*)tensor_data6, (TfLiteIntArray*)&tensor_dimension6, 800, },
  { kTfLiteMmapRo, (void*)tensor_data7, (TfLiteIntArray*)&tensor_dimension7, 200, },
  { kTfLiteMmapRo, (void*)tensor_data8, (TfLiteIntArray*)&tensor_dimension8, 40, },
  { kTfLiteArenaRw, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension9, 80, },
  { kTfLiteArenaRw, tensor_arena + 80, (TfLiteIntArray*)&tensor_dimension10, 40, },
  { kTfLiteArenaRw, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension11, 20, },
  { kTfLiteArenaRw, tensor_arena + 32, (TfLiteIntArray*)&tensor_dimension12, 8, },
  { kTfLiteArenaRw, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension13, 8, },
};const NodeInfo_t nodeData[] = {
  { (TfLiteIntArray*)&inputs0, (TfLiteIntArray*)&outputs0, const_cast<void*>(static_cast<const void*>(&opdata0)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs1, (TfLiteIntArray*)&outputs1, const_cast<void*>(static_cast<const void*>(&opdata1)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs2, (TfLiteIntArray*)&outputs2, const_cast<void*>(static_cast<const void*>(&opdata2)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs3, (TfLiteIntArray*)&outputs3, const_cast<void*>(static_cast<const void*>(&opdata3)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs4, (TfLiteIntArray*)&outputs4, const_cast<void*>(static_cast<const void*>(&opdata4)), OP_SOFTMAX, },
};
static void* overflow_buffers[EI_MAX_OVERFLOW_BUFFER_COUNT];
static size_t overflow_buffers_ix = 0;
static void * AllocatePersistentBuffer(struct TfLiteContext* ctx,
                                       size_t bytes) {
  void *ptr;
  if (current_location - bytes < tensor_boundary) {
    if (overflow_buffers_ix > EI_MAX_OVERFLOW_BUFFER_COUNT - 1) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d, does not fit in tensor arena and reached EI_MAX_OVERFLOW_BUFFER_COUNT\n",
        (int)bytes);
      return NULL;
    }

    // OK, this will look super weird, but.... we have CMSIS-NN buffers which
    // we cannot calculate beforehand easily.
    ptr = ei_calloc(bytes, 1);
    if (ptr == NULL) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d\n", (int)bytes);
      return NULL;
    }
    overflow_buffers[overflow_buffers_ix++] = ptr;
    return ptr;
  }

  current_location -= bytes;

  ptr = current_location;
  memset(ptr, 0, bytes);

  return ptr;
}
typedef struct {
  size_t bytes;
  void *ptr;
} scratch_buffer_t;
static scratch_buffer_t scratch_buffers[EI_MAX_SCRATCH_BUFFER_COUNT];
static size_t scratch_buffers_ix = 0;

static TfLiteStatus RequestScratchBufferInArena(struct TfLiteContext* ctx, size_t bytes,
                                                int* buffer_idx) {
  if (scratch_buffers_ix > EI_MAX_SCRATCH_BUFFER_COUNT - 1) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d, reached EI_MAX_SCRATCH_BUFFER_COUNT\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffer_t b;
  b.bytes = bytes;

  b.ptr = AllocatePersistentBuffer(ctx, b.bytes);
  if (!b.ptr) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffers[scratch_buffers_ix] = b;
  *buffer_idx = scratch_buffers_ix;

  scratch_buffers_ix++;

  return kTfLiteOk;
}

static void* GetScratchBuffer(struct TfLiteContext* ctx, int buffer_idx) {
  if (buffer_idx > (int)scratch_buffers_ix) {
    return NULL;
  }
  return scratch_buffers[buffer_idx].ptr;
}

static TfLiteTensor* GetTensor(const struct TfLiteContext* context,
                               int tensor_idx) {
  return &tflTensors[tensor_idx];
}

static TfLiteEvalTensor* GetEvalTensor(const struct TfLiteContext* context,
                                       int tensor_idx) {
  return &tflEvalTensors[tensor_idx];
}

} // namespace

TfLiteStatus trained_model_init( void*(*alloc_fnc)(size_t,size_t) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  tensor_arena = (uint8_t*) alloc_fnc(16, kTensorArenaSize);
  if (!tensor_arena) {
    ei_printf("ERR: failed to allocate tensor arena\n");
    return kTfLiteError;
  }
#else
  memset(tensor_arena, 0, kTensorArenaSize);
#endif
  tensor_boundary = tensor_arena;
  current_location = tensor_arena + kTensorArenaSize;
  ctx.AllocatePersistentBuffer = &AllocatePersistentBuffer;
  ctx.RequestScratchBufferInArena = &RequestScratchBufferInArena;
  ctx.GetScratchBuffer = &GetScratchBuffer;
  ctx.GetTensor = &GetTensor;
  ctx.GetEvalTensor = &GetEvalTensor;
  ctx.tensors = tflTensors;
  ctx.tensors_size = 14;
  for (size_t i = 0; i < 14; ++i) {
    tflTensors[i].type = kTfLiteFloat32;
    tflEvalTensors[i].type = kTfLiteFloat32;
    tflTensors[i].is_variable = 0;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
    tflTensors[i].allocation_type = tensorData[i].allocation_type;
#else
    tflTensors[i].allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
#endif
    tflTensors[i].bytes = tensorData[i].bytes;
    tflTensors[i].dims = tensorData[i].dims;
    tflEvalTensors[i].dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
    if(tflTensors[i].allocation_type == kTfLiteArenaRw){
      uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

     tflTensors[i].data.data =  start;
     tflEvalTensors[i].data.data =  start;
    }
    else {
       tflTensors[i].data.data = tensorData[i].data;
       tflEvalTensors[i].data.data = tensorData[i].data;
    }
#else
    tflTensors[i].data.data = tensorData[i].data;
    tflEvalTensors[i].data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
    tflTensors[i].quantization.type = kTfLiteNoQuantization;
    if (tflTensors[i].allocation_type == kTfLiteArenaRw) {
      auto data_end_ptr = (uint8_t*)tflTensors[i].data.data + tensorData[i].bytes;
      if (data_end_ptr > tensor_boundary) {
        tensor_boundary = data_end_ptr;
      }
    }
  }
  if (tensor_boundary > current_location /* end of arena size */) {
    ei_printf("ERR: tensor arena is too small, does not fit model - even without scratch buffers\n");
    return kTfLiteError;
  }
  registrations[OP_FULLY_CONNECTED] = Register_FULLY_CONNECTED();
  registrations[OP_SOFTMAX] = Register_SOFTMAX();

  for (size_t i = 0; i < 5; ++i) {
    tflNodes[i].inputs = nodeData[i].inputs;
    tflNodes[i].outputs = nodeData[i].outputs;
    tflNodes[i].builtin_data = nodeData[i].builtin_data;
tflNodes[i].custom_initial_data = nullptr;
      tflNodes[i].custom_initial_data_size = 0;
if (registrations[nodeData[i].used_op_index].init) {
      tflNodes[i].user_data = registrations[nodeData[i].used_op_index].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
    }
  }
  for (size_t i = 0; i < 5; ++i) {
    if (registrations[nodeData[i].used_op_index].prepare) {
      TfLiteStatus status = registrations[nodeData[i].used_op_index].prepare(&ctx, &tflNodes[i]);
      if (status != kTfLiteOk) {
        return status;
      }
    }
  }
  return kTfLiteOk;
}

static const int inTensorIndices[] = {
  0, 
};
TfLiteTensor* trained_model_input(int index) {
  return &ctx.tensors[inTensorIndices[index]];
}

static const int outTensorIndices[] = {
  13, 
};
TfLiteTensor* trained_model_output(int index) {
  return &ctx.tensors[outTensorIndices[index]];
}

TfLiteStatus trained_model_invoke() {
  for (size_t i = 0; i < 5; ++i) {
    TfLiteStatus status = registrations[nodeData[i].used_op_index].invoke(&ctx, &tflNodes[i]);

#if EI_CLASSIFIER_PRINT_STATE
    ei_printf("layer %lu\n", i);
    ei_printf("    inputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].inputs->size; ix++) {
      auto d = tensorData[tflNodes[i].inputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");

    ei_printf("    outputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].outputs->size; ix++) {
      auto d = tensorData[tflNodes[i].outputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");
#endif // EI_CLASSIFIER_PRINT_STATE

    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}

TfLiteStatus trained_model_reset( void (*free_fnc)(void* ptr) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  free_fnc(tensor_arena);
#endif

  // scratch buffers are allocated within the arena, so just reset the counter so memory can be reused
  scratch_buffers_ix = 0;

  // overflow buffers are on the heap, so free them first
  for (size_t ix = 0; ix < overflow_buffers_ix; ix++) {
    ei_free(overflow_buffers[ix]);
  }
  overflow_buffers_ix = 0;
  return kTfLiteOk;
}