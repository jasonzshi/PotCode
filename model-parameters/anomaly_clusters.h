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

#ifndef _EI_CLASSIFIER_ANOMALY_CLUSTERS_H_
#define _EI_CLASSIFIER_ANOMALY_CLUSTERS_H_

#include "edge-impulse-sdk/anomaly/anomaly.h"

// (before - mean) / scale
const float ei_classifier_anom_scale[EI_CLASSIFIER_ANOM_AXIS_SIZE] = { 0.060750337251110655, 0.5000009090694911, 1.3733660482504455e-7 };
const float ei_classifier_anom_mean[EI_CLASSIFIER_ANOM_AXIS_SIZE] = { 0.07384978617557277, -0.030368049410621704, -1.5 };

const ei_classifier_anom_cluster_t ei_classifier_anom_clusters[EI_CLASSIFIER_ANOM_CLUSTER_COUNT] = { { { 0.5160946846008301, -0.9681451916694641, -1.7360162734985352 }, 0.8715205765444328 }
, { { -0.6769430041313171, -0.9712003469467163, -1.7360163927078247 }, 0.5547602466097359 }
, { { -0.5206522345542908, -1.1813030242919922, -0.8680080771446228 }, 0.5952927379594335 }
, { { -0.44154810905456543, 1.1280829906463623, 0.8680080771446228 }, 0.7497729846211494 }
, { { -0.5615562796592712, -1.2428518533706665, 9.313225746154785e-9 }, 0.5026692899502361 }
, { { -0.47741061449050903, -0.1908896565437317, -0.868008017539978 }, 0.6486315808890762 }
, { { 2.790743589401245, -0.3361985981464386, 1.041609764099121 }, 1.5886485671879573 }
, { { -0.4828066825866699, 0.007545549422502518, 1.814926266670227 }, 0.9011233267448708 }
, { { -0.190362811088562, -1.1353501081466675, -2.85202693939209 }, 0.8968610936256755 }
, { { -0.6226441264152527, -1.036746859550476, 0.868008017539978 }, 0.6920903411700869 }
, { { -0.3043227791786194, 1.1755343675613403, -1.790266990661621 }, 1.0215621350726591 }
, { { -0.6594150066375732, 1.2120920419692993, 7.450580596923828e-9 }, 0.7828667831558334 }
, { { 0.41599342226982117, -1.0532344579696655, 0.8680080771446228 }, 1.009015665502105 }
, { { -0.34265223145484924, 0.052898045629262924, -1.7360163927078247 }, 0.7255687924292762 }
, { { -0.19346481561660767, 1.2896043062210083, 1.7980166673660278 }, 1.0718647589343089 }
, { { 0.9151615500450134, -0.2147546112537384, 0.4340040385723114 }, 1.1622707418501912 }
, { { 0.13185760378837585, -1.1385318040847778, 9.313225746154785e-9 }, 0.6039367751873234 }
, { { 0.830039918422699, -0.5065506100654602, 1.7360163927078247 }, 1.0311133990616386 }
, { { 0.1816566288471222, 1.2777069807052612, -0.8680081367492676 }, 0.6746660434916489 }
, { { -0.4304393529891968, 0.11793056130409241, 0.868008017539978 }, 0.6741738889810827 }
, { { -0.7849939465522766, -0.5715585350990295, 7.450580596923828e-9 }, 0.46652979243259374 }
, { { -0.26841917634010315, 0.10450100898742676, 9.313225746154785e-9 }, 0.6212316052865234 }
, { { -0.6452764868736267, 0.9658965468406677, -0.8680080771446228 }, 0.7411802449249688 }
, { { 0.5979871153831482, 1.2496745586395264, 9.313225746154785e-9 }, 1.0375544542866109 }
, { { -0.5632875561714172, -1.1452417373657227, 1.7980166673660278 }, 1.0202233620782781 }
, { { 0.25743675231933594, -0.9129895567893982, -0.868008017539978 }, 0.7889800738423649 }
, { { 2.9572911262512207, 1.2845152616500854, -0.10850100219249725 }, 1.100503014738509 }
, { { 1.0504330396652222, 1.2795974016189575, 0.9701266288757324 }, 1.4024606628266678 }
, { { 2.244338274002075, -1.0989301204681396, -0.9920094013214111 }, 1.5201458686146487 }
, { { 0.7150675058364868, 0.46482381224632263, -0.8680082559585571 }, 0.9994438510727763 }
, { { 5.493378162384033, -1.3534406423568726, 0 }, 0 }
, { { 5.418651103973389, 1.3947557210922241, 0.8680081367492676 }, 0 }
};

#endif // _EI_CLASSIFIER_ANOMALY_CLUSTERS_H_