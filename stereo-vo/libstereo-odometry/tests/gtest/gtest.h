// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file defines the public API for Google Test.  It should be
// included by any test program that uses Google Test.
//
// IMPORTANT NOTE: Due to limitation of the C++ language, we have to
// leave some internal implementation details in this header file.
// They are clearly marked by comments like this:
//
//   // INTERNAL IMPLEMENTATION - DO NOT USE IN A USER PROGRAM.
//
// Such code is NOT meant to be used by a user directly, and is subject
// to CHANGE WITHOUT NOTICE.  Therefore DO NOT DEPEND ON IT in a user
// program!
//
// Acknowledgment: Google Test borrowed the idea of automatic test
// registration from Barthelemy Dagenais' (barthelemy@prologique.com)
// easyUnit framework.

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#define GTEST_INCLUDE_GTEST_GTEST_H_

#include <limits>
#include <vector>

// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan), eefacm@gmail.com (Sean Mcafee)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file declares functions and macros used internally by
// Google Test.  They are subject to change without notice.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_INTERNAL_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_INTERNAL_H_

// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan)
//
// Low-level types and utilities for porting Google Test to various
// platforms.  They are subject to change without notice.  DO NOT USE
// THEM IN USER CODE.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_

// The user can define the following macros in the build script to
// control Google Test's behavior.  If the user doesn't define a macro
// in this list, Google Test will define it.
//
//   GTEST_HAS_CLONE          - Define it to 1/0 to indicate that clone(2)
//                              is/isn't available.
//   GTEST_HAS_EXCEPTIONS     - Define it to 1/0 to indicate that exceptions
//                              are enabled.
//   GTEST_HAS_GLOBAL_STRING  - Define it to 1/0 to indicate that ::string
//                              is/isn't available (some systems define
//                              ::string, which is different to std::string).
//   GTEST_HAS_GLOBAL_WSTRING - Define it to 1/0 to indicate that ::string
//                              is/isn't available (some systems define
//                              ::wstring, which is different to std::wstring).
//   GTEST_HAS_PTHREAD        - Define it to 1/0 to indicate that <pthread.h>
//                              is/isn't available.
//   GTEST_HAS_RTTI           - Define it to 1/0 to indicate that RTTI is/isn't
//                              enabled.
//   GTEST_HAS_STD_WSTRING    - Define it to 1/0 to indicate that
//                              std::wstring does/doesn't work (Google Test can
//                              be used where std::wstring is unavailable).
//   GTEST_HAS_TR1_TUPLE      - Define it to 1/0 to indicate tr1::tuple
//                              is/isn't available.
//   GTEST_HAS_SEH            - Define it to 1/0 to indicate whether the
//                              compiler supports Microsoft's "Structured
//                              Exception Handling".
//   GTEST_USE_OWN_TR1_TUPLE  - Define it to 1/0 to indicate whether Google
//                              Test's own tr1 tuple implementation should be
//                              used.  Unused when the user sets
//               S.�v�z�&/��;�gu���q���9��?$�.�����?(�_��V	��*_v�!�>�=JӦ�1��,�����
�6;�~7.���n���ڜrqr{��w�k�๳Hp��7Ҵ��ׅ
��(�t	�$�����MwB�o�Wp�B��<�=i9���ؠ�q���	�5���YF�6|���|{��T�ut��k���R��OiRb��[ irB�[��z� ��a��c��EAx� ����f6�!�&�p�s�к��\�{�h�������q;��|����L�H����h�z��A|9�����@c�{6��G�l�qMp�ȹӘ�!\�],�Wm� ��`(k���C�%�5���R ���޺�`r�j��+fJ[��HԐ;�������{�:�M���lVq"N�f�pV~X܅*���;ΐ���
{�wF��m��Y�YѮ-%uX}�;\[&u�?�]}TW��B��[��5�Q�Dt[ec+�j�͚h�{�c�ʈ�Buԉd�nV�tz��8���L&;�sf�9�l�	I�Y���1FG4j6մ��I���~TИ9�]�֫��{��}����v�J�����O�?�&���b�?j���z�NQ�Wf�0�wC�"�>I+����K���l�G.�<�v
͂��AOdp:�/����k���6j���f�������Mf�<#�sRe*-� y��Xk���4����=Q�*&i4#��4�i�F��R��R	��m��E���;��j�Tn��ZzA��n;�"�K�a�,A�Jl���W5�?��J;�/J�.9�%�J|G	wP�� �.��v
F����o��%��Ac�]��{��P���]%y�!9	���#��y$g�WJ�M�AN���Я�]���2ϥ>mjM#c�٥�fQ'�Z��F���̋%e���t��Q��$E9�.j�*�����}����U��Ғ�@��gҴ�&�_b�+H�d�9�Ȱ��굏~��0�u~��_�K�|ܩBԬI���٧d�Jݣv�?�_XfT{�؉-�G���zt�������S�/� 1�j�m�l������_�F�����c�J�Ҽ����BY����n�x�����K��`�����t��gj�����k�B�}���z1�
�mz��~�_:�.H~�?ɏ;�R�o�z�ˀ����y̗����$yƢ<3d�ٞ'N��9.�K@�����Lf�&��qO[���B��,N�yg&s7 �f�>3=���<��<��#�HSCO���
X�x����s�G&cr>�1K�W�z+a>��ԃ�����?>��L|̭��^�{�#�G�pYV�ubʢ5`ĵ��g�~���`o� {;�ʶ�g�r��M�l{�p��퀣�����k�UlZ��O�r¥v�n)���@-h��T��7���@��`���,�X�q�J���1异����a�S�Ͳ��r��!pki =O�j��]mGg�~�����0>*6���b���ݳ﫻*�0��ek�l�Ӫգ�"=�a��E�V�H#���/<�'����'� e;�6�>W�v�l;Xyp�G�&���o������wou���[MN�X=�[��l'��b���/�l�b�
��%$*6�"�#��y*�-���jG�S&��2�,�ɋ�o�Έ�-��\ཕ��Ӌ֌���\��/�@�R��R�b�a�8��� <�#�u�oзW������!��!9A���@�_�o8�e�U6+�S�t��5�5!]���F����Y���IN��_Ep2�L����xV�W����^e��p��2�p^�v�.﷾L�_�ӆ￟����� ��~ٯ���%�������AM��`�K�엹���6�{椐�i3U��T����\c���Bg"��8��D�_W��<��?3���:�p����S�����n��������9��W1�Հ"`\Z��mvx�D�D���Gĵ�6����C�{��]����N+�&�`��M��;�A��;�3.�-10Sx��r��X���N��$�Cʏ�cV��B�q�3B5��j�'�ֱ���F�»=W����{��K���B��<�L}s���բ�0u�kzf�N+I�0M�z�|,ˠ�>OV�x$�����h���>.����>vZO�H��,��F�o�~Ob�����,޵�Ԫ����.�(�6��XS���B�8�{�V�A��k�x{���7�ek��1�rN;C{Y�X>�p�_�R�VA��EW�Yȟ��;�l
�:�z�#���]�s�5F�$6�q�Q*u�B<�:�"¢h?�N6�bf�B��f��,������.3��x����{1S&������O��A���>���lj����Kˡ��7Sj��V�lŽ0�e�i�|��z��Z�K��K+r�)Pɬ<�v��k��~ʩ>���a�I��Xu�9���M����M;�-}Rb��������������S�Mߎt�T2~��L�B�?#y)��g���QH�F�̩�=n\-͎����/ ��$�6�;Øk����c��\�mS�C��u�8�ݤ��Rr$����Q���=0p|�`6$�t�����"6��H�mRΪ=��Ȼ롔��#�����C�w����;q�%���m� �{-���E��{�e]_������gy�,��Z��4&�q�Iz\h���ǅ&�q��9��8'6XT�d=%6EF���>�
[�Q�`�t+�Q����q
e��Z����"]�g�g��%�g14홏ɪ� �w�3��K״y4��\1��&�8�Q������EιTR��U~�}/���I�~"��T�E���t�
�r]�BT���\AW��+WЕ+��t�
�r�D�
Q�U��{)W�)W�҂��ds����l�/w�@�6\Xט������,$��i�`��O=��t޿�LI�oY��؋N�e
�]���U?
�y=[�6r�<bgʤE�q��Δ��۸�z"�2�����ƿ5�"��hFU0oD�R�F��;���.�T��iߟ��S&
N��<#Ceo�*���z�����>��[���R"����i�F�xZl� ��70�rI���W���XL��TJ[F�~8�Q�',����Qԭ��/�=5.�eB�\u�G��H�7�}�/��%�+]�������a��1���<#;�귺{�3�&l������G��>���B$.��=w��8a�n�&L��M;�qaX�(��+�x[d�\Bs����6�ی�@�+Z`Y�wH�6~S�X����7@�:$�Ql�Wz����s	��D��D�oq��@�v]���گ�����d#%/�`�`��e��#�Q���b
բ=���q~��5���&�9tm��;���^G������G�4�;4��r|�*�y^��u���롱��8H ����P�z'��Ӡ���BMvuS����4�;��[m���1�|fZ��8h�<a0O� rW%�2�ڮI�}e����@˼���bs����o;���1����������3�מ�xv��ƣ�x�B@���`z��j���x=����{I�?�.�k;"�M��<'ġ�3�i���<X��ǣy~pqдW�͋S}m�	����EsQ�,��Fx<J��#j=4f�x>�8��������'W{k�~S��GG���	�յ�ډ�?�5�N��}̽������pU�.u��V��xg�8B���G�WFm��=bs�*",(���.�n�e�8:^ɡ֟��V��~��{zz��a��gp� ��y|����!6�}'�덷<Y��D��%T/����0/'fO��s|ka�y%��9PkԮrW�27#�[�r���޸���O���=��� ���9���e����u��	��!�����,�X�`��p�{��O�֐+�k����~����e<Fl��09��88�&`�#�ߟ��	^�._�sz��X^�d�cG��{��=�[�\l��.�(��s�>��5�>�;��ѷ��0�y.Rv�0]8�#�Ϧ7�\����'�o�L�%�s�0w�)ч'�9�0�\�0�;��,}� @��� ���P�������Ю��L�5�x��(��!ΨDl��h����Yؒ�X�����/��q�Sl-5B��h�-2{��L&�"1�S݅
�$W���Dm�s�F_9B�qK����~$[?l�$�u�^F9��<�ޙLC܋WF����:.���7�S_�8�;�b%+^�{R���z>��-��Q��&�~�`�B��2h(�e�1&��K����u��7<�~S��:-|��E�zکu�_������kĜ�gFp��E��1j�N��h�������=�`*��
d�~.�i��^��S���w�������`���#I���x�O���L�R@�Өڅ��kOå�kߓ>����g����`���f�d�G�O�	�a!I��:c6��J��qlh^�=/۠yNbo(�3� �|��{o ���qX�P�\���*8���!�n��f'��\5L��V|ǎ���VZ4U+.#�/����<K��q,>p�s��9}(��gcpߘ������9��[I��wŪ>�7��C�B鈛��.g��3��m@1���Ia��_d�G؉�j��R�-�oϦu@�o���|)֜���s����:N�P�q����ɉ��jm��*��RY5��P��UVo0��}���ז�����Sk�K�*w��SﮛQ^S��r�����m����6�<뮫��p6��I�+�{��0O�ͩϕ�kI��2Eʩ�/*⭯���6�9��:wY+�$�̓��5����\E��uW�n.���K��ϖUy�����vo�u�+�
�ֽYz���|S"�.�5��F�]{sUe�"UT���n�P���[m���n��\S�r���AUCe5HRY!�m����NʍSf.=�n������q�J�7�\���_\QRE������
2�W�K��e������g@��ɣczx��|��]/���67�ǺM]�U�Vi���97k�ȶl)�%U��?�e鱥F�T�H�۲�t��Aw1PX�
����n�.�|�
xP ����\�.�+����9���<��������+�[���9��9�����Me�5�{�m�[��B͛-�do-_ns�R��U9��˹[$���v�[,gr�Ҵw��ke�)M�k�B�wgM��,�\�����Z��M����
�g�r�V�DsH�W(��9A�N�r)3#��=U(���t�\�sP��e�T�ިʺA_�D�R!�5��j�|M�7��\�o��V�����c���)��;k�{s�T�Qd��2#I�_6Șɲ�T�<�V����wi�.!IN���r�^�ζ�OW��a�4��.�'Qº~�_�Tk�5������i9-��&��?Q��]����Y���(Ǜ��F�GG�V,�kVZ�T�����ˈ	�J��.Nf�'t¤��f���P)�*2�l>��׫���KD�����V� �r�r�0�J[�D��L�����]9�)6��WO�ׁ�x�|h(O'��tb, ����٘���'d���9�YSz
���\��庅m���Z�Z�M�TI��<G��<;�^>!��£ԥ���5�L���.�M[�m�M�I�j��2*@�T����
�B-oM����2�58|u��މ�N*ݨ6H�)���6��������&}��޽)���]�H4
G��I��ņ�QI�GG��@�h0�E�c�d8!V{ >=N�p$�JT�EdRz�Q�jMb },S���	�Y�\�K^o8r�;U�`����JF#�t�ht`DJ�J������!�T����O�9���Xx\*tL��'�40:L�I��J�G�Iw!l:\*�c�T����	�?E�9"T"�)B�$�ȥ��jT��Afw"F�Ϟ�t���X	T*�B�BE���ԬTɫj��rM�<�EA��4,�s�iH���H�F�LE��X�Xb,�|����V�0"�J�@h�.�#�@z�L5����ljFƵ�e�r��/��?��.�ɾ'�hX)�8�&�d��o�p�(��lV� 	Ӥ�`���*�QαG�=^ɱ�e�u�{Ԅ���h�V�J�<�P�=ªA
�H,����g��&)��
*2���EP���`��YtiU<��TO�/Z����Oz(�9��tY���\$-q&d9ϔr�$EfMpX.Q���Q�_X-�_E��V$iP���R������m�5�̤\<�E�e�53�Rc*��,��U"��� �b!S�4f&� ����8�a����ұx4��)��ht8Iǃ���4��F+OS���~P0��D2�G����ӑ`pP��[JG#�G������ďǒ�t4���1�XLȦ>�F����x2�$�j�j0j :�np4z�LF����f2�eM���B�Ȱs�A� ��A����n��Q�4E'5@�eAT��D��EMR�%�s�\�c�It�c��>T�e2�N����m�|��;���hdh;�w6��*Tg�h�g����{��Ƕ��Uz�DPɩ�S��́F5����h�Z`�1�k���PQCD��e��`�hx Ȉ!�0�ѤP��Q�K��(F;�Y���5��֓�ć�aP>Y���j�\%	R6&g��pfFi񆡆�T1�͢<fVZ�iЋS'p�#����4|���h_�	ѣ�8# �C�_M��`�c����t,���"�m&�}���<P0�F�X�J�����b�z� Vʨ8�j7YB�h�F����x�hx�(�	��0�JGG Q��x���|�`�t��d5S��Ԝ[4�.�+�$�����^Y	��z�"�����)D�	�~�+��*I����1�䵉�@�2�Q1��	�:Ӵ�2�P�kfԯ,h��v]��Ve,�6��Ol�4����SP��gz0���<��X�P�ԄuCx�r�"z-���wM�&��L�M��y1�{�s\d�tJ�_U1J<t1M��L�}�H��&������Q}�M�؄6�i��鴩A��ڴ\<�����t����L|KX_�R8��=�|�=}��֟iI���
A{6.
��1�����	�C~�w��Z&�f�}��|��ˉ���>c�v�_oߎ�7/����|K7aK߆|k�"���T,|c��@�\���Zr�[�2�s|���E�5>Ӳǉ���t7y��L|ꕌ���E�����I�aE%��v��ة;ɫK*'}�1�&��%�;��b�k~;�:S�;���u��!�j�ՇL���<|�tu���#��:ܩ���\�0>�����2��H�֘�35kw��rQ��+i{Y���I��)����Nn�%��3�r.=9�h&��G
�Xָ�C^�ܝ��M�����<ŝ/���hm(O����s��+5��]�\�L���j�'�1j}�"��b��璜�v曍"{�4!.T`��4n�jz�^.�%=%���(�a8O9�-�_6l!i�U7���e��T��9�1�X�b�.����Q��)��&�}B���s�JM?e�_��K3{T���6�W/�j�\-�g�TK�j�V�Wʘ
�J���*�)k*E�P���˦�ao��6&(�)>K��jNԤ��\ԣ(�U������:i*S(Jj�l��&ݥm�I�F�D�|���	 %�,۞��S"Z�C����M6��Eö"�%N�b䤏�-���ʉlm���Kw����֨U�aM/�mi!v=Ѥ�H���Q��<dm
 ��؛Ϝ��Nʨ�T���*W����M��>�ݘ�Լ�ed��ؼ觼z���ҩ�}Ν5�1x�Q*QĐӷ*EڽZsgsAծ��m`�xR.�}��*Wʅ��U��A�^V7Z-�I�#�S�2�+�2��Rx���������f�����~������.���Y])�`4�P��.m���G��þ����I0�N�փ 9���@ԫ�<��*K������la㥶�7�m�$���FMl(�΋6�E!��k��ݵ�j9�Cɝ�V��u^Z��|sA�Sz��k�T哅r�7�Rٔ�T��^<���Z�g�uSr��m)3Y��ym3U�I9�i�dS�<�t�d�'�|ˢ��b�C�gB��э�d�7u �F����L����f�)3�/���LBt�j�@�ޔ��f�I/[CFh�۔�<���栆z-�*�>&k5�QN4<����>��i���O�!�zt��֠7H���#۪6�-T���Ř �P�"��-fJ����0W̟2�M�����Հ���v�B?e�F���� �q���f{Q��w�'Z��o�g���\.�Z�|k���_��;����!k�4��	f����(���pQ̂���;��T~�y��ʷ*W0�ۓ�zm���g��
�v"V}n�����H-_qċ�>|}�6�X��r5m:?��>���zٹ]Y��	�k��x�́������!d�<��Nk+":h�WXK?z����G;���Q������BM�K�t�ɫ�sEZ��ޏ���a��«�ڀZy��f�_�[�f�#b*�ٮq%�[�SتN��l:���F�X�٤R�`3����9!���2Ř�M;5?ꗃ鼾��6H+o�ԥ����g�A�3��Y);�\45���y�H��k�F5+@:�~4R�@��#���{=�=��p�响�)�mhᛞY�q9�F���XC��7�_�򍒚�V�M1�%"�?���d���v�Q�)��k���*��f��^2��O����l3�����`���%͖vY�bp8q]����_ʣ��;��QP�Sb����4��:�"~1Z��n���<����N�h*vߛ]�q	g�*i���E���v�T�ێ��ߥ�3���&$��,��gl�͔�2yN�r�¥ZQ![@/�a�I���X&Q�.�!�鐅E!_LA�{\2����Ԙ��1oG&�%�&�{��eBL�m�B�^&�Bi�OȳD�)ԘO �w�ȥ4��Ԩ���uf��F�*�$�9��<���O⭂S|�Z��I�p��� i�3��ɜ`�b&�m!�өr��ڏ�#$#ʏ��ϓ�h�����Wk�Uz3YrY�s�@�s<Pbnc��^i�!՚���ʂ�!M�0���V���e���7��BH��4�Q>����SE�fX�eJ��,��rǲ.�� F����)Y��+�.)�w�;qU�V��Թ���A�;�ce$����5�>G�/�k�9�i6Q��Np���-��R�@%�����U�$�+k�&y5�Pwre�fx-��h�$� D��t	���Dx��l�ZUPj)o��-�jzD��f=T�,�J�A%������6,u�׺�E��ɭfl��M(=u�B�_t5Z��V�R����,u,�H��/l�O/�\�$3���	���'���YK��k���ch%j���/u8w��/ 3�h���R۫�w��C��)W��C�r"v>�`C��>���]�Q���h��z�����
X|��+O�����M��&3L�ݠ:d��$g,� r��Am�9!�#�E���;��IK&�j����:[��,M�,�Xk؈l�RUou]�������i��i3���FW-�4�^s����u����p]j=Ve�C��O/I��24h�%�:$��8e�y�o;���7��6���<�V�f'9����;o�����
�.�i�[f�*�)F����ʍ�<�Yt/dYZ�Q�K��-`�]��z�6FEӸLVp�dH���Zml�If[����Q6��N�2��:�>���ʪw]Y�g��M|R���P�՛�E|�or����D���S?}��g�W~�?p��<R��/SWSȧ�}�x�Y�v᳈�<>M|R7��tύWn���W������G�&>)|���\���`�����,�M|R��ݰqx���r��v�*��#l����C8>��_�����<>M|R��]�.��]�@>���{.��C6幊����5�Uƿ����|���2�<�7�BG
a����m����Aޫ>�j%맭���vg�;2ury���hNˎ��Kk�?=q�&mu�;�<����3�:%���F�/���5�Je����H1������<.W˘��K�5r�Z�,��(���(&b|�̈́��;s"�&��L�5M�Ť�Ny��'���o�H��������?��ɻ�,��ad�A�O��gd}�f83���ރ�����r��h�y�!��&�~2�h���oH�Ox}�Q]�_h�%N�i�K/%Bn�Yv�Dh5�+8�t��+u�^��k�.)�Y��X΢�����=�}ZMf���&�]�BE6��d�/ר��M�j�/s���(��l�P��y�zg	W]��γ�t�:Sr��f�ܜ����Q����n�,���Tj�Q�z9[.J��aB������=s:��s�/ȜS�B��b+7R�d<嬰\�T5n�+�����T���<gr<�Q+�v�C�Զ�&��a~'�Ս���7�@fgΰ����r���B)�˓���,�+�T�c�.-�p�h� ��<3C��b�$��YQ�A���Z��J����W�^(�ҙ��I~�K���<f�|��iQ���/���^�����-]�����gmP��t�I��A|��Y����М?�Χf��2�{�������ZSp	���N��Ufy&)�L���=�[ �'Π�e�e���F�Ҩ�ʢo<֦����,$�	���@?j�_;5�JF�RcF�V�T�K2��2��6��1`RC�㱁�@`t4�ǣq�{��9H�u7��k���\7F	�f��Z�vR��jH�Z��I���N��I0���%"з�,�O����	࿩��	�4�D�@�?b�?�!*)`��_�n���lQ�\_�${��Zn���]�[fo�%�Ǖ�?y����+?{��W�q���\e���̿�U�_�*���^{O�.yc�Yv<��&S�im��!ø��^�`Wy=I��G�u`Vy�5p_k%�˱}T�E��2��f��9bK745
���������sЙώ�4���D�L����c��q��'inv�{��Y��R`�ƽ�;�'
7}:�M����	N53{E����./<-�ڊ~����o`�{y���۠<uv��k��m�	���f�U��_7�G�7���W���O9�E��7Ϧ��IV�H[��c����]�X`�-L�D�ްЧNm
�΋�мS<��"쯤�W��S|!fx���v�Q����kz��2��of�l���y�cY܄��,���q	ñ/[���\����ju�H��&Û�?�`�0����3����(fx��l���~��3H3_�� �UfUV.e�����6�fx�܉�_�v�i�7��Ku1�E�ıV.�k�,C���k�Mo�ۥɣc����%��3M��ڮ��2ih�i�ڭ]�a����5� ^k7����U�8\�>!�z�,dn	�M{W�S�0��V+��v�~��ca���5\�]k����U/.v�����n��w]���U�ΰ�,o�q���+�V��iߏ硲�,k����G�w�uM�e�]���uvB[�G����c�k�'W�Y��'{����U�;Mǔm�m��?�!->v��K���n�y��<�� �:6b��jy��D��(�F^n�^]�-df���R�f��[�,}�l`���Q=��7�l�6����A�t�Z̍�ih0����i$0�q���9�M���c���O���]�k>�Lɫ�R�l��=���-�	,���z�����:b�Ɋ�x�
]����l9�7j�7�л'xӢ���,�=���h�[I�Ԣ~ġ}9�m�r_:��_��Z;ۤA�&;+�ց�):�G��ZfFV�����y,>H�Ñ�X�?<G�������t�Yt :�?����/vzہ�������̬�f=���]������.����w�?����8���������5��߿Ɵ��_k��~?���x?�^�����w���=��~7N��wӞ-��������&�����������w�n3>�9L��'����8-7��/g���Ie�?���\"�����Lt�g���]�Ⴓ�����Lt�g�������>w���<#���I���8#��?3>;�'���\�oO����߿�>�[���|_���#��>?#�M޽<���3�R���,�k�:��6�����w�/�=��}��������}����7h}6�����;�bk���~Bu<q���0^8n*���u�u5�S��.Q1]m�$�g�~�߳��l���~����C�-���+��Fw;���ĪZ?Y�������oS��S&>���TY'珛�h#������/nw5�.x�z�ё�����g�#����>&��C�qEϵ�d]�vo�����v����-���.�������ss��m��a�C���88��7�*6��Æ����u��u�(�Q-q�[X.d����S�ik�PǬ�n{4�>j�}��6�]"�Z�:�kmQ�
o��좷o�m����z�x�[���=��㶇9S�6:���c�&YN�hgX�i�P�fN-�5�e/�y6\FV�P�n����4;��ޖ�Az23Ig�5�f��5B�O�z�����3'd�-�B=q��$h��n�-5TgG��������g�^~��)�_�PT�;��s�s8�'���)�My�]�4��7�e�Ҫ!��n�7�x�i�����`"�$��yۘ0X��nS����T��6��ݚ�~?;/����A��̉��V��+��*�Ӕ�sHz9�mm/7+�L�����k*K����+���\W��[��.�+���������r]y�#���?�+�W�J�ſ[W��������O����f]ً�a�������u���d�_@�}m]y>G�v]�>���u�|�����^|�����ϿXWj�������O�;�s��#����_�+|�����5|~����ٝ����|�.��+O�����d�~��e�*6�4ެ�������㛭���z�yc_�H��^�l���z�}=��z���î�����ƈ�Y�����+�G��3��sƺ�g�
/�d���cc��{~��?3Dؖ?�!���7���?�q�彫�������u�/��iG���]{������������������~�f�#���OqZ�1��n�3��T�>���m���������!}��C���q����?����������6Tl�-�s�u�������������z�<�������M���޹]s�5����0��N�n��ooV��{��T?'A@��j*�4�"�����o��l��;)���毆�'��~����~ʌ~��$�m3~��E:N��:�f��Oign7�*K=�~T�����-��
L��$�:�{���.�L����?�{�������/�rf8��~��ss<�ֲyyF��4j���y��Ι��z�i���VX�]i촐�NCf2�����GOgJ��c�Z�q�Ts��@��`ph8>22:���'��G���?ػg��~����W���٥U�^A~�aA6�%X���׮A���Dr�B���-��ȑ�^��du�S�������w(J/>^|z��vEy�]��>���>/��
>E|��4*^ھ:A�g�J��k��jk?�/n�	1
��
8�^#[w��-�9~�S@� 椿@]�.@G5s�~�̺�����u�\>�ȝo�ߕ����ն�$/���Y;z��ӛ�W��4�@�»�3�ٴ��>�������6�2�ٻ�I����������U�g�A�҆�o�߁��o����֖`onk�&ڗ�BV�����F?w��i�'S���P6H���45U`�T�laJ�Y��6�?��7�w�8-]5�cDz���nл���H��#�7��9:->�[���5�K�M�*5N�mZD��o��3%3y���h,w������Kr�k0/���Mbe�6��}�v�sd����kw��
%��
����0��_T�4��^� ���;���.c8W�2��������â�˥�� *�G��Ͽg�W�ɯ�ņ׷��K�Eܤ?G���K������͝�{���ݻ%�� ���}H�>b��.vzA�`����!���U�>��Ҩ
�v3!~k�dz�7��t8��"|-O�uv���
]��'���W�o�����Ɯ���CC�xz(�N��������~�7~0Ha��޽�U�Kc��>C��)���0�UU����߽4?�<t����~"Cr�7J����gM��̩���2���_;���0���g�<{7�K�=��_���o��u?����F�f�W�&<�[�F���D M�`�����������4Q�W2���f�����=�<��RS���0r�O߈>6�W>���Wc�F�37
��ٵ|f��ǂc�{���BX=�39�%��$�Z$լ��1=K�������=��k��߷�9�Xs�8IKl� �Hس�QMY�Ը�1%���C���.��J�>W�r̿�$���{IΤIڿ�q�FM^��$�t����Ã6���d����{�Yv汓F)d��M�
϶���o�I�6�{��d�l�1ƥ��1>��,q���x��ƸUYc��l|`/+VK�{YahU��@?���I�6�?�h�ɬFp�L�D#��x`T����E�.T�AU*BN����o�k?�y��&��k&��DWm'ٮ~'����,h�͂g�Y�`6�h3x{��Z����g�
��-��LfT5�U��h�>������gL�>S
ǆ4���)���K62�j#������Ȩd#��6�T�F�k�Q��lT�s9�?���yj��~#�O%���IgM��tV��pD��64�(4,���T-*ה\4^i���s���U����4�{�g��u}:GӨK�[�:,꣡e�d���R��,�7m��S\{���2���`k�KHX��ּB�):Pc��f����Ry�Se���ϊ������6jVyFͪ�U3ze�9�nU3��F�*ϨY�1��@"���L�nn��e-�8ZK&��A�րIDk���7`��G�5`�0u2��3ٶ�f�>ͺ}&����ۧ��d�>���m�g2r���&+ج<�Yy�d���4+��<`�򀣕LV�����0y@���1|0���}�0|�������lWx0�+���2�%�G��Q�8FU�cT2�QU�T�f��5Y�jd&�Z5Y��@:����蘰�-��y42H#����`:�pX���;�:?ݤ��җmh��$���K��p$�S8g�H��F�x�媃�`*��ţc,%�M��ɦ�dZ*��}�X�Vԉ$�jv�j�}�JUF��e��1ȋ�7b7N�)���T�� $K)�b���ł��KDX�p�фS�T��n��`_�Xs3�QYGa\���-��#�7O�e?��}�مY���l~�E�v����Mr��$��"�"u����.M㫳<��vy5��i$���X� ����+��$�+�)f����2�H�
���Mj�Ml�������}� �|IZ>��N��5�:�3I��5��5����`�-_��d{�l�$��Y��4�4��j�&����{���{uY,y ����=�L�s�X?ws����!��ʹ*����R�oڬ�K?q�گK�w̹9���]��Ő�&��H��4�b��㑑���?�/ΖN��	p�e�	�0�in���D:��35�0���H8v$00���'
�G3��.^��p���&�A]��4	�Q�e���:MB_��:�YG�}{M���$�4I�9h��3	�����:��I���f��8�� ���tɪ\��6E	Z�v'�\��1S�D=Se��P4�>�` ����XL��3?���3r����V��шV蓙z�d*q�GqSw��(l�oѸ�ԙ�	�y�zHTsȁ�x�Fe�oh�U?
~-ߘ�*�>�r���98`�}��\�!�$gB2�(A]��	�Q���cns�@t�+��Lb�2�W���$o�K�Y�O��x�a��y�Q*T,=�*#�E1��*!�_�0��&!�@1��*���*c,	U���*�����P �����35>�	|y�// |y�// F�at�^���X|z�^����X|z���cC�DHo��B-on���I�v%�EM*��6�)P��?�ďǒ|N/�~qI�>�W=�6iJ���>G��\��sT��Y������'�3����;�i�enUro�?�eۡ�Ȋ�
����`��-XC�����@p�}E�Q�Ə���h4��hZ�&�������Տp��������	����r��\�C����� ������0�a� ~�gvS�،"����ЁK��j�8������K�	�2�	�J�`
��/���0�Gה�� ��y�ܱ5e8�����a0�=� ?���%`��An|��W�DO���M�с���`~��h�����\��&8����y`����
�S2�vM�>�Ӑúl����]y�}����y�p�* =Q�z�+���Q�8<\.�N�.`
��q� .CE����/ =3H?p�� �}�8�r���p�<�Q��<�'���S�f� �D.�C�$>�+�y��"?�!�i�2�<p�����ºt��c@O����<0�@��#�g��A���$���9��,�s
v������(�����.���KD�E8`�s�c@�������Q����K!>�a`�	�l�+�%`��8�bm���>�x�!�i����KD���=�>`�9�p��p	x��$��!�� �>�r���"�p��?��y�z�}O����y�*�"������S���!��./�>;�v }�%`
���?px�\���~L�W>��C�h@ߏ#��'0����͟����9���yԏ�'P?�M�y���#����E�L�2�8<\^.�
��"�(O��W/p���5�� �瀇��0�눟��`?px��s�/b|��!��+���y`�<G�/!?�y�*�	�B�}���2�I�_A<�%��Ţ靖g��=��Y�]���t �]y��5�C�
0̿�r.�?h������!\:9��� ���wQ~��G~<���}��)���џ��|6��N@��� �W����?A���W�N,*���\�3�旑3��.��S�!����By`���k��u��+߂�2��;����| .��W�W`���(7��?������Hp�;��t	� ��WEz�D~��� \�w���p�����������ǚ<����
��u�+��oYW����֕E���J�I�f]I維+@ϵ��*p��J��ѽ��C=��
p�]�J_�{]��߳�,�޷����K]��4	oXW��7"���|�.z?�s��(ͻ?p�V��܆��~;�t��݁�����`/�z�!~��~��q��C�J�ط����+�'�>�����G`p9 �N#}����Dx`s��sh]��$�YWN�Fa�'i�	>p%���a/p.��\.E�'�'�x�]B/p�!��)��#�J�I�+g�����"�.y]� ������Gו	��4px�����%�֕ß��u�̧i��Pv�!u�.��^`�	�?�xG|�ŏ�>`�c�J��z��>	:���?��_���?B<�e�`���� ��?C�������;�/�
�40�"��.��y`��Y�;���
��y����W�=?\Dz���Dy�����"��k��3�?���S���W��O�ϣ����s�����]_�~`p�.��U�<��#�_��W�)`�+��>�<0\��I�
\z~r�@x`����E���Һ�]���p�䁞g!�.S�����@p�.���E�*p��<�����)`��<��\.��!<0\�=���������L�s�E�p�\v�	�����M`
� l���?F�h�'9�2p�
\z�a���S���M�<p�\$��!<��z~vC��\ �!:p�[F8`
���4��>����s���`
�� ��s�e�Y�
p�
� ��&�+��~� =�>`/0S�	`��｜�~��5��p��\v=���^�
��
����z���>�<�x.S���<p���������?E�*�\V�K�9�2�,p�\^ v�%�� ��F�@�O�����!`
8���&�p� ��. ����K�%�͛/ ~����c��א~�x�����!��h�����U`�s�}�y�a�0\V�+�9`�_!�@��0�p��H?�J?=@p�\��+�	`���<L~��-H?�.��(��g�o�~��c�<0��. �K�s���s�p�U
��9�������`
��-���S���&p8�@�+�e��<��-��{�!`�N �M�"�p�@���p�e
�l�~�z���>`��H?��恧I8Or�s@��#���"�W�s��_�<���G�����E�%���Q�^������p��.W�����?�^�*0�|���y��%��/A���W����_��&���7�/瀞_F|�^��M�/0l����"с�H����ߐ���	\� }����;��
�����]��\"�P߯�<VQ&�]��2O��e�
���`�E	���зUQ��ү���)�������+�0<Kt�"p�����R�9��.��U�0�MQ. 灗Hn���~����e�9`�����E��V���?�(M�p�
\�ޥ(]_"���W�}��Ap�=��|/���� ��]�C�^�y9���A����o�9`ח������ WnP�%z^�v@�+�@px�w#����Wȿ
��<\.ބ�_�/��nF� ��
�w�}���H�"��!�2��H�XEY ��=��*p����v݁p�e���N�.�Q~���(������E�S{?p�l�C9�W�~����g���#>p���KD?�t������Z�ǥ�fO�׾��L�$�
��=��Z�ٷ�Kw�P����l?�uZ���?|Ǿ[oQ��!
߾�2A�Σ�=���y���@g{��;ݞ'�v{�����	tw���).L��s�������.I磉I�]�d�+�\ �m��:
�:>K���� �;��j@�oEz���[�;��|����tw{Kj2��Q���o)�5=�m�]����'���_�m)�6�G��@_ �{� }a�S�ρ~	���|
�w�� Gy�r�}K�(�w�|�����-���g��}O�-����ۏtOt~}[w/(�n/$ ٯ m�^ۉ�>�R�o��ä糤�3[��}ϐ�����{���g;������`��}C�D_K)l�T�p���-�/��{�N��R��ä/����w��ڴ��Ҷz�z�o)�s�7h�w�Ѻ��Aw�Y;�!?W��|��D�ٞd���62j@�8�G�B��#-���{d�Px/>/�?�)QN�!��قR}���ɷ�>ױ��:����l���pK�-��K���L�aX��|"�[Q~}�-�$�3$�4��'�v�x�mm>	�%ȿ�*�fߠf_����~���{�����D5}��[�����n_�����dO��P!E)F{��K@m���yrg!��h�<���|
V#�D�L"	���:t �����S�����)}Œ��^Q�I�_n)�S~(��c[ދzN����C��#�E=9�M�������?������m)��[t���~�u��F��m};��Zʇ��������"\��:�mT9dC>B�3�����u����jn�}�k���i)?�N�,oԞ��W�/� �+��M�4�Nl�*����i���1ɍX�󋿋>�����B���ch������F�'���7��;��z��ز��Rq�����K���;���?`�6�||�Bɖ�͎6�ً[�;\z2ѿ\��/���Ϲ�C��T���I��;�R~ښ_�Μֿ���� ��@��t��~	�zR-e�s��;J=�c��R�}�5��`K	��{����������Ex�C����n᾽�8t��2����t�
}�GZʊ�^;ےQ4��n����DP�O�|b��t��ˌ����ӓn)�:�(�3[�9�OH���2�R�z��w����������O��ʛ�ߋ�=�+��?|��-e���Af�眞#j���/���r��z����7h�oǵ�N��x��1j__v�ׯ�w��G7ɯ5K~��z�����8�I��l�ޡZ����&��[�/�����|'�9����F>���l0o�|z�VJW�Odϫ�3-e�{P�6�w�ڍ5�co��z7������!�oq�T��}]��ξ뾇�\�u�rзr�K���i�5�Q�ڊ��lK9�y��а�T=��s��o��B��Gߺ�z�<{��k���_���b�?����[��W���鷮���^��?������Q�����W_�^�^:�s��߂�ާߺ�}7���~��=}=?���{�N��[��^,/��[׮�����\}�xz�?�ϫ6�3䠇����؎� }?�Rn��X��;��[~���"�g�% I6�A��O���w�׮������|���R޷�J��P��~��;ދ��ϵ����F�b�}�s�yR�.�BK�mK{��o�y�K�w�Z�_u����W� ��\�>Կ/�����Q�||���G呄��/���[6*�0�t^r*�Φ(�-����?�{~��t�Yo~�9�a�����_k)/��t})ډ����P���:�X`� oR��A��o�<��n2>�}~����f��&�{��z�wZ�B;�-�����U�3�w�m0��Kvl���?��Ρ������u���a����UzY�7���M�r���{o�>6�C_���R&6�g~�Cw7����Ė޺t�ހ���o������u�ހ��_��ݻ�o��W�lO��_ڏy���aKj������Ŏ#x���:D<�ާHb�M�3w���n��4&�S�BG�t_�<���(�%���m�%����C$d		"!��H�K���Ֆ���-O�a>e�q��-V�o��o����OB"���oJ~�{�������qm[hP�+B��g-�����ݡ�����s��A�N���ܦj��������/����DF��}����]6�R�7A��6"S��t1��M��1�t}�%1�}mP��x��zNC�ގ��nh^����0�P�z�*�l)��hc��p�k��%��q0�\����t�������r�gP����]пl)D��y?�sz���a�!�h��y�Kg�Zʗ�I7�ٞ�4.�	}��R���������"՛�n����R��-�꣬��Q�'\����������f�!�� �������v\�6�7�|~�� ��n~C*��-~�a=}�ނ��[-e@kO���¤�G�������ҏ���4�������QN[��c��J�s�w��[ʜ��ȣ��('x�aY7�~e��5����_l�����������(�o�s$����v5�Q�+�g�s�?ek�i{{g釾���R�t��FyN��㼆�g�m�3����6C�;�=`||����G��]�[�]�7Z��t�c���3Lf,���3� 5xeh;����w���:y�w���6뺝� &{"?ހދ�i)ݰ|�9����#��x�N�ǥ��v��ʖ��f�Sз��Z��΍�ؒu�φ�~��9�o-%Ӟ]ގMέ�� y�M��nj�5�9oG!��]�9v���ﶧ��@~�kN�ůj_�*�u�����m���Q~v�w��P,��������M';��ʹ�K򣐿 ��N�4w�$��'V[ʒ��'��_���-�6n��G��F,��A��_jg�|�,�iܼˇ��-eO�ӹ���W��؏�3O9�[�?-�km��x�e��y�q���������JK�N����h���z�ڿ�kM�s��_�i�ЏNU������U��>=��s�Ov�?l�~Ϻ���h/�����9�ތ�1%����������|�uλ���{�iM��á�~�P3�ŀl>/Fv<Ew_t�i�
�x��=|\;34���e�_�����ӝ�:הk�һ�^�_qϟÝ�p:e'��~˚�F{��;��&~��xۚ�V_dv�0�M�0���;�������s�l���6V�M���Vt>s�XS����c=;��9���y�7���=]k�ߵ��x�:��q���[�⿕k֔���s7��k+&t�mk�Ύ��׶Y7,��������U�{�\Ǻ��pg\�>Ew�l_Sޣ�k�t��y�����K�O�n<�L��U!﷝W�>�2��-~ġ�0tc	C�E��ߍ��po��3
z�Bg�?���`{���p�뼄�y��]S�����ρ~�!��f�]��c��{ޤ;o ���?��Nڦ��#�lv��nzGbM�K��迶���wb�K�x|(���һ��P�y�пj:�9�z��^���U�c�F��	j���)Փ[{������e��a��}���1�K�z�'���T���Y��|�ݢ}���������[�P�ٺ�����-�P���wA��:s�S�Aл��<|r�����)�C�_[���	w���U�K�gM���>� }�~"<���l݋����ye���#�Ofx{�/�GT������{��c���@����3l�����y�����7�Z�_�e��§z�:�K�?o�'(Ns���_��gM�l>o��X�lV9���zs��	�',t��Y������ː���\�)�_�,蟐68��������@�x��Q}��
���;e�����r�����Z��?��dO߃��?�+˚��@?��6J߄{�Z����Qw�)zӥ�{ĥ�E��7��;��9�C78�O���s7��d�s������x�,vP~����<��:���{}<��.�2�����*;���)��;گ/�w�������������!��s~���ȸ���%.t�}�+����t>�37���"��W`�w�F{���G�@���[��}�\?�������"�'>`o�O������˗��y7X�?��_���`��ɬ�ҽt�M�;w�)c��<��e�y�go���ˠ/�t���z��&{�� ]�^�އ>��_���2���{��@?�ݼ�yr+^����ūH߽���f{������~���;"o���9�O߼y�^�����~�5��_��R��b�����uK�z���b��E�������?{�=�_}�2�{SܥiM��a>pz�|��z�t7�/��ŝ���z�����z�/|О_o��|��Jw��j��^н�^�}O |�V�}ς޼�}�^����rx���ڏ࿝�����Q�!��P�A�����gw���A_�
�[�X�;@�n����c����AO]��~�A�+���
�ג#�v��[A�����>e�K��O�>��K��3Ǻ+��n�w����J��EF�W�wzw�����`o�\j�tw/���6:?G��]��(�{�1?��s4�$�M��KJ���{}���a�ob���Hw����*�s��Oߎ��.�c�_�/�.c�y�.{���]����|~��y�
��F�?>�!�� ��ޱ�����3�������x�y=��������6��t�5m���������Շ��'�;spM�l��Suh��m�AG���й�남?}k���˾�Ƿ�w��-gB�+f����]��)����![YK���#���d?�?�iߧ������#�~�C�??�������6�>�]�_ �ڹ��L��&�=}��Xwvnt>���Ϲ{��?����v���������~�_$�{���L-�π�_�b��/�c���7=/�I�}��|s��N�?k��ތ������������v��m(d�?�}>���%��~�������j{��}�Q�_������v��[�\hM�e�9��ӽ �A�7����]�vكA�0²�OJ�=��~��m�u����v?������v���Ν׶}v6����G�l�P� ��[����������ӛ�i^=���|	j�x�����2�c����S���z{dM��e����?����]ϰ��Ň!xtM��v�s@q)�gh�nlMy�e|y��f����F����ž�t�>���c�}Mj���&[���<��;f�/f��3$.�1�/�' ��bW���3�˲�_��/�=.�}
�9���f{�L�2�7E������m���ojQ�Ț�%{y:գ�иz���?��Q����/�1�;���%��4�t{��yV��7�����I�y[S�7:��i�|b���5�9��:F9�t��C���k�v�Rͩ�<K�������1�1y����h�|]��7��CP�����9��b\;�tw;_�)
����3��,����S��h��U���ה�;�Jj�GT�g�7&��)�(m.�ֿ�[�֔o���b��u��R�����5�N�sP��&��#���`�~ciM�:��;LG��=q�G��YSn5�ςJ�y6���j����]����>e��_�Wo \oF�����A�9L6����5�g7�������LO�~�#����U�a�蹔[S�V��}���;��*���Å��Vڥ֊��~c�i����*�**�*�*��%&*nVVnYY�F�[�YٮmV�.��y�ϙ��˝�3�߮���G��s�3g��9��9�97��s@}��(�ni���d�	��"3)�D�m��d�<{}���;d�W����3�e��>�/� ��j�U�#�{�8����Wq~���q�ߢ_�~1�z����;ū�*��^����������+�^��8�ח3r���̦�Oq^b���;�y	;��N�]��|G������IY����Z��9�[�2�Q��d�n�W�R/��fr��Cg�W����F�:{�س'T�������^�
����ƞA�����_�������^C����y����=���^�;� t���^vq��5��cCg/U��8t��B�+	������v?oO��������?�7���]���Ui��5�4��
��k?��-���������/�[:{q��}~0t��F�=CCg���m^��=��<��/#s��^mI���,��&t�[5��^���$����1d�2t����>���Q}9*��{ԫ��h�>��K�>���[���%d/�q�v�G�^U�g9s?�^zOx�+�w�s8����ʻ�����+�6y�m���.��{V{����\c��P��{>:{�d/~s��E�#����%�z�G����U���:{MbOȭ^mC�ڃ��ƞ���d�/#�>�3�i�*�^��е�G�{J~�2^F�w���#��{_��j[��=}���Ss�WKb��!m�huX�MvV�)�]��.��?yaa�{����6�	
��5�x�\9�>�E��5�)WD�p����\��C�e�qH��'~.�s��l�8z�?���W��h��S��>���`�:�&.��a�Eq��?�W�Nw�}@v��(�����2�O/��K��������o�w�U����@�����9�tz�3J��M����u�~�ҥ����d/�m������X��q#04�����_ n%��G�Uδ7Yboك^�Mޞ[%B	8�Co�'���ZX�����=}��$c��'��5����������y�[�����^��)�}��q��&��������h�je��\OE��������٫=��q?�<�S��W{�W���?����P}V��Ԯ�s�k��o�^�'^��Z��th�<+b6����oL]xj̾��1z(t�O���W���|6"���|ļ���O�g^�#�|V��SSI�T����71�i*���{�nN�KS��5ӿ���/����}���	� z�3J_���ؗ�ڷ�������G��z�CQ��A�!Nϯ[u2�M#�����[O��:{��^Ʊ���9���7��WN�b����d��x��]s'շ�Bg���%�:{������kwտ���4��������?���&�5����Ԯ�H���j��z����ɫ�w��|O�c��_�{�O;�Q��x��c?K_�O��.���~t?s�}�k�X�3�S���'�Xм/�����D�kD@��>���\�K�ɭ�ML�|���*�A*��T������N����A��C�%R~eh�'�����K�*��v����8(�#�'��j���g��2>����i����bY�O'#��ԙ�~v�O�����O>w��QNv�N'!�È&�Y=S�����s_q��̏�7 f���Q�\Jw'���0]�L_�=S�1�'�U�,���O�f�����}�R�����O��I���*j�_���U�x>)�~e"���+YM�1�n�ss�5A\�����ѧ�4�'0��9t�>���P�T���������_H�G��n���w��D{5�P���i?�Z�T�Lx=��5}�;�_|�O��2��h�ؓէ݄�t��t���H�_�~�g��Z}Z��ۼE}���W����H�Lrk<�B��_�n���ʫ����?�א\���h���ó�z�v�n�e?��v�0��1��E۞L�I!R��u7�������	m�W���m�vL��SMqΪI��,�gԷt�W���>��/(^�I�璼����	�K����e���Mb�Y�����
y&}��~�g�+���L�ZF� ��~�$�����.��ͥ��O"}��N5���\���Pw_�������������79_�F������g蝮_�;ބ�Z��6����O���4���٤����Ps��wJ_K�|��H_J���Qn�ީ|qԑT��D��.�,�׹�/$����?�r}j�w��@�c.ק��Q=��q�����r�I��E�E�t����w�W����~-�+{8����O�:�qEt\�'A�X~�r����[�I�ӥ���w�7��������z��������O"}�K�,җ��/$}��������O�:��H�E�D�n�'G;�fg}黹�H��~o!��~�_?V��H�'��Ĝ��Ԙ(=�q57ÿA=\�tdao?q��'.���=���Q�z��ҧ;���?��&�u��4�g��K`�*_O�d�[�>�:��[�GQ���}b��`y\1=?6�kH�`#O%y��<�ظ�Vy!ɣl��$��W������$o$y�E�@�c6��$?b#�\h�����m�I$?`#D�}6�<���ȋ��*� �f�V�W������F~��+m�M$/�����ޟl��ϫUޓ�6�,���ȧ�<�F^��h/���$ϰ�ג<�F~���6򣋌��*?I�Dy�b��6�kH�`#O]l��Vy�cm�$�����@�6���F{m��%y������l��I~�FYb�A����6�$���"�>y^��_�����+J��/�����F����O��?�W�țJ��9��/��o#oO�6�$/��g-1����O�\y�����$ϰ�ג<��/h��A��ط�O�|η�����[��,5�k�7u�q}.�����׳p���,�}k����oͷa�q��y|�Q.���eF}��i�̨�m���Q����eF����[f<_��/Zf<���Xf<�V�[�ϻU���>X�^f�'V�i���X�uV��^Y�/5�7k�z��U�Uj��V;�J���*/)5�����F�b�ז�WP�/5�;�u>Zj�V;'K���j'��诃��ѿ��2���s����oa��X��2ß�ʫ���*�[f�KV�e�?T���-��/7�C+�n��OZ�I���*���o��?��m�E$/��W���F���56��$?`#?L�#$�a��$��ŧu�������̷'y�ߓ乷_�,���ȧ���"�c��|.�K�⃼�0̖���^���������H^L�~��O�:�_`��$�gc'�U���E$�'����#r�-�5R�I�����"^�O���^�G $��������������a�i���_A��������H���q��������4�{>0:���c� �2-���J�4s?���'��4��6�'�Iȍ�O5�'��8M�����	s#�r�'H_(�P���P����]�y�#/���+'��������#��G��������Taň㳟�H>IƯm�#s������S�~o��{k� =ߔ�w���iZ���naaA����$ղB!�˧t]-����+I>�l��N1�g��?�5�q��4���)؉\I��`;�V��3>#~��N�q=_@|�5�Y�̀��2ZOs�{JWI�v��k�������un�/j����tD7��>^�>��JĿ�is⮊���ة�u#��?)��c��E\�L���<a�OK���͗O�+_%�������'�y�W��͊��"x�����Ao��D����\M��m��+;&9b��i��~��N�P�_"(.u��-��z�Jw��٤��I�y>���.!�����O(]>�������Y����.���E�l���p�E�i��>��y
���t͵R�7�)݉,����{�_.�����a��xRY��Z��>q�A��̘������C�������A�
&��\�ft@����g[�)}�e�I~b�?��8�b��������i��\F ����u$.�_�"S����;ם.1���$�G��-�^���$og3]��A��/��3��M3���lW�c��(]l��O��߬�h|�|��N��j������l����fF���W�G<�GI�O��N����{��_��|��_���i��6Ξ�S�H_E�a��X�_MsXV�j�T��ߑ�ƑA~՛qA�&����ǎ�i]��o��/-��g������Y�G$���z�;J_0ڧ��_�4�@}Op�I��<��tiw�KZKv�s|��2��`�=�,���@��18�����2�H��A������A�7�ɩ6�a_:٧��)�<��^�X�v?�Ϗ��_�I~@9q���d�K��ן��.�%��O�
r}�f�G����� ��/��w�O�s�O�~G)��5�xH>�Q������q��3߸��?J�K�'[���n�/(>�z���y?t�r�����o��'�����������$���ü2���T��?i"���Z���Տ<̏l��=���8�?����~�O�<�DO��4��ߔ��{?L�x�˶p�y'{�|�1k����f�A��?ѧEZ���$�%yF���I����y���R>m4�cv�<-���~�D��d�7��O��R��t{I_?�2��5��ɳ�#�k"}�I>-���c=�$?�����$�%��
��Īӈ��"������g�E2��:���}ڋz��"�@����[����<on��n?���F�F���u\�Az�dc81w����)>�����Oٷ3��xz;D��wx1�u|aֿ�=F�}�O����$?D��A�U����ڿ����1���p��Y�*�C����E��t=��� ��C/���9<ȓֿP������?H��"�oɫ
�۳���8��w����7�I^G��v� �������=Nv�g��c���� ���K=n�~[�]�/ʒJ��f���a��{pLc�x�1m0����m�Om\؂����$/ ���yOƊE�1�s����|kE��}��y��-/0��7�������,�s$|�*��I�]�;Yn�����\><���(���>�)L�{�n�e����6/�];*�3��g��?�I>K�QSb�����f�=�`q}r����x�I"}���A$����wao��G�{��0-������<c���8㘌���m��OE���~��;�c�=x�q�ϫ���[���(�է�1�caG�k�﷐W0�2�r1�G����XČh�>z��\c���b_�a�B���ql�ؽ�R~�%�-g����mRřf�L/�\�䠗s�>���'򉁾-��f9?�gԥЧX�r�~�E��Y�M��~��r��ˣ��o��e�;ʾ|q����r���{`B?Ģ�c%���_��������+�쏀>G9F���/��6X�_��0S���+\�p}.���ϵؿ�ǐ>�r�d���A� �Q����9�/�d#Z�ۿ������}����O��%�+���`_���km�|ȵ!�[�ן+��p~r�3�\��s5��'��,r8�k��!�렏q�_�]>�"�	�;A�Lk����_p8��п�O��Z���@�����1���7B�����m���ݡ��A�)8���E�5�́�z�S���ϳؿ���/�����ЗZ�r��.���?��h����=��v��h�Z�����h�Z�����h�Z�����h�Z��������v�"]�E�?q�r��a�;/���u`x�o$����R�n$�Kd"�9/��pk^�+��^dx鿼�k����	p����ҿ�י᥿3 \�K�'�T����=��bx��n�Kh�7��y�`�ʟ�����`����3�?1����M9��rw^��ׂ���?n���a!��/���0�l���;���ܹ+�������r�G�1�*�_��1|�����dx���/�kp�dx����� �>�?��	�p]��i��1|,�q�f0����?���'�_~����=���	�G�����
�]�~{�����/��\����y�`�N�;�Ke��g����OW��I�>�[��]�?n3�w�����cp�>���<+��|p��G>��c�T�7���i�ǀ���3�����3��W��C�?n7���#��^:����������=���i?�_�ß�jp��7�S�g����`�K�����/�
�f�O�"��������o �#���L� ��.��pC�7�q��>�C�g�L�O����C��
�/��;p'~x�9�����\g�/ ����~$��?�lp+^�`o �Ç��A����\ܣ�?	�K�?0�#�� wv�O�����'���\�9�0�o����\����_�؏���?�k�>A�/pM	x��ok����V0��2��we��n8�_>�=��\%�w_���o _n?�w�!�O\�w���Z��� �ç��n ���n��?��O_nç�
�n�� �����'pm�1��k�`�;��[��y�׃{��'�������\L%ӟ��\
������g�/�,���z̝��s�=�n�?��{؝��jp�_~����}�V1�J�O�������ï�opm��-��\w�� ?�d�_#����
�6p�3����;�o�pg1��&����������f�'�OW��O�_n+�?�%p0�f�_�����z�'�w��n�o�e_�Qp[~���>d�z�߂;�i�>�����O໽bp����>���|.엾��~3�z���Kp����C�4��^p��S�ǀ�W�Np������8�>�jp�>���r>�]�1��W��f�V�w�{������3|����3��<p�3|4�4p#>�dp�\�����	ස;����?��w���������J������~(�	��,pK�+���md�d�ρ���)�?����wp?1|�������~�bp�~���r>�tp~�lO�U3�xٞ�{����	�o>�����ȼ���u_ ��t�/�	n�/���<�_~!���p��3�^b�%���ï�8ï�&���ļ\
�?$��q/'�L�����?
���=����G��\�j� %����
^N Z�Q���7��3p'^�/��<�6_B���"/�^������y9�/M����F(�r��TE^�������~�y9��IE�?_N�����y����}����>E�?삧�x9��jE^ί����u�y9�n�"�,�#*�r�܃�|�[�L_S�p<�����E~<�1O��w�z�����C����m��D�*�p��������/c1.R�?�JE� ���8�W��xD�_���U�ܬ�W�x�"��[����Q�7��G����A������v�*�;d����~o���}��w��gE~7��(�u8vS<�}үyF��v�|��Ρ��� E��l�/p,R��q�"�(�%���O�)�����������}9?��"/�k�����Y5^��Q,��~��}9?|�"������)��W�ha��N�;��ꕊ��|�]����}@���u�G(�{�T�_ ���|1��-�� �+�U�^U���U��|�"/_�'+�����m9��k�����-[N�������>>����S�>�:����i>�ح��#w����۪�>��[�ևv�i����e-���g�byf�+W,�p{OSy>��O���ྪR+���G=�V���O~Qm}��=ϩ��m��sj�E���֋v�����W�[^~��7��e��1�&2���1\!�����-bx�c�U/�w����e<�-�v0����>���>��O/�|
�k���@�����A4pQϻ�2^����{^m}���x^m}���z0|f���cp�ϟ��m4��^�־M ?�y��������>�`�i���;����C�������݆����Q�{�����nζ������gr��Q~�b_^{A�����mj����2����6��'��ԨŷH ��K����M5j��7����=
\>�g��	��F�y����ep�1|^��C��	�F�? ޳�!���<?]�O�v��/���=?��/P{~r�Oܮ��MW�]Ϳ+���j��j�U��b��
�/ı�YL�"�;>�c�|ך�_"�Tp2�/w�/��[��w���p�~<c��9��0|������/�1�v3����O�^�OE�@��j�C� �y�Z�����w��� ��v��!#�wۥ?d�;������[�_.��_z&���70���o�e/3��v�1������o�po2�Y����oP�Ǣ���U��r>�+^~߾\�Z�x,}�eժ�cnv�Z<�%��U�ǲ��Z�x,��{�� �!�/�����d����܉��;��+�_�;�7:������c�Z<���rw�œ�n�:�x23%�S-��Bp/�;6��������6Ï� .�io� ����<�>��f�O���:1�D��e3��n���pk~��_��R��R�]j�^>��.�x/'���V���\��j�"2���V�Qn�n�x�6�V[?�\�n��S�����p_1����I����U��:Ɵ��=��a>Ò��c�b����c��P�	n1�/��ܦ:��kσ{����׃;�����/f���]����GJ��7�U�a�#��p�>���o�g�������Q��r��{Ծ�� ��j�_.��j�_����/��-f��ׂ{���� �e����O~�����'���8�o��I��ue�|���r>�\p�?|�?0�P���e�,��w]ļ��m?�xp�0��������k����#��=Ï�����������9�s��a�1���{��ǂ��.�����~b�\���x9�=�|Op�~'���
>��{��=���e�������������j߻��3}�xp^	���Z�>(=/4�k��|�>#�^3�1�Ƽ�Y��㲟�����}U����S~���C�{c��� #�|	��C�{�E��X�/�$V���/�R$"��/�g2��x��_�8���?�ʜ_.�O<M��¾��?�ʜ_1��v��/B����vd}�����g� ���Cx��}pg�7	�Жr(b�PNJR�J��B�ږ){:3:�I��@r��#un����h����A�G+�v2h;xVZ��Um����H��Wg�Qb��{Ҽk8���8��f�_��}�������>XV�׼+'�0���]�j��{�ر̼n�o}Gy�����_iȿa����c�������7I�������S�ZC�y���=W�����o�w}>�M�����)��� ��!�>�6����l�[�O��!�W�9�c��G8�(����\�����o%t_ܐ������/��!�-���L�@���k�?~;��l���;��;	�6�_��w��/���!���3��	�����;\��hB�e�?c��M���|�$t��?kȟ��O�|���IC����~7����=C�o�O�O't����!�o��Y�����������]�����?g����K�4~������s	���/1�����o%}��<��'N���?��}A�W�O����R������㷓�/��!�9����}.~ې���O�%u_�!���s��Iݗ����J�=��?���>n�߀��K�>����4����'u_�!���w��/�?lȿC>�𧓺���d��-��y�'u_Ԑ?��w�g���ÿՐ7���%}���^������sI�g�א���~+��B�������C<�S�/��!�O��S����������S�/��!������t��?m��{y���t_������w��}��!������M�(�g�?�?�?��}.��!�r�?�?��}Y�'�?��~�߻���(�C�����)���?c��<~&����s������{J���3�_J���{)���
��W���ϥ|���>n���~�m�^��������_)�1���_����8�/u? �;�JGx��
gl������C�c�s���b1c���e�od"�3�
Ʌ�i���Dq:�I��2����sj�V��) N������g�!�2��ת�[��K�?�˝]6��}�G?���x��X�`\#�v�n�{a�pS ��`��k`v�.�{`/��p ��i�a��5p��N��a�}��AX���V��F`'�ݰ��>�� ,~/~X�`\#�v�n�{a�pO��`����2�s���9zH�^�=����b|�b�EwO����>E{q�q�Պ����� ���b�����X�2�'���}���*�d^G�w*f�2��((�d눯����a;����b�F�O�?ͼ�@��������?Hg:9/
�m��3����_f��_�x�1~������~�qv�5�_�xl�z0�
߄W�V\ �������;���ƅ�c�Q��Q�0����1��)�JCоA1���C��BŰ��E�C���+���R1�%x`����2_hWs|h/��`�F���9>��}�x��b�?��`�a7q<��L/���p|Z��`���}����J�o�:��*�yq�d;tW�)������H~x�r\�$x=׏<qg����'9�$��K~8�A��%o`��1��&/�0D~x0N~�:���G���� y��Q��"/��!?r0F~ȋ4tȋ,���A�"�#c�M^d`���`��pȏtɏ�a�Y'?��M^da�v���8�Y���N�.Z�pcsG�b/}�{~Kk����������e������dJ_*u�r�繮�ຝ�>M����k����b��o�3�~I��=��/g�N	�
��e��r�&�oܿ\�~����<������3����/�9��,��.��3���=����(�?�c�?���A<���t���0�1�8�g��<��G������~��S�#�q_���p]����O:m��a��W.���g-���w,��҇+��җ*��ҧ)��ҷ(����'�t�}mP����J����H���G�b�?E�D�_C�&�A�d=_��e}{t�Y����:��ʺ����:��ɺ����:��'H]_��un(u_��JTꑣuA�s�Ǌ��G���Eo ��_��]��!ȿ��|鏗>u���m韖>f�'��^鯕>W�7��O鿔>H�G��@�ϓ>9�W��1�ߒ>��~����#}6��"}'��!}�!}	� ���^.�ֲ~,븲�*뚲�(�|��&�^��$�@�#�"�>!�R����ԯ��<Z��;~~8�U!n��q�T�;��J����Z�^7|�T�k:�ѷ;/��|��Q��O�ju��I_�q5����ph�`�yP4Zwh\�`WD"K�#UK�U,�TV.^�P�i�l�Z�dqeE���q}yC��-F�ܮ�x�*ooj�h�[o���v4�oh�R�~K󦆅��Ȩ����*o��Ҿm�bG������>���놷�5n���#?E7uX��-�����|C���[��~wx�ֆ��:���i]��ns㺦���G*t]][[�6!?�U?�ۅ��ᣌL�nss�u��������G&�n��75�l�o}Ϻ�گ<�d�N8Ϸ��������V��z��K�^����3�B_�[�����pL�ԡm�]諟�^�_'�W5�k��z�p{�>�BWP���Å�1׭h��c̹������~r�k���W�J�����?��kR�[�μ����ŧ����^/l�Ň�G
}v�����/>J�p��y�
w��e}G8���U���'�}V��>_���:>A�ޙ�����S4nO�~)־�|�Y�]ǽ^�����M/�]+�a��_�k��%���_|��0�������}�o�ǝ]���O����|~w�sT|�E�/������T�^a���|�R��������cI|�B�7T������o\d�@�+����ڹ�y�"��K��;�Хx���	|SU� �g+P��la�X��)��^ d�Ŷ�-TJ[ۄE�-��>c��3:#Ό�82�v ���H�Q\*�P�R���ι�佴ՙ���������)'��s�s�=���^�)N�NP)�
�V<��T� !�(f�� .^��W�	m���Ϡ<9T(�,��*�؊5\��%jy9-����J�E�L�"B--��u
�r��p�i{~ߚN��V����r]��GG�t�^g|ɧ��R���d���Sf)�<t�v���.���i$��[SV�tI��P�t���t:-�<M�;�o�u���6jϪ�ܢU���
���uKT�(�i�cUO̍x�;����l+�vwY#�{/��}����o �?���8,��w��=�����O!v~$�=Hӣ%4����>	�7����qT��ß���_����$I���SPp^(~��f�ͅ��h��Kq}��~\�����s�`��=o�S]�彻��5���֙�_��u@�]ߧ��|n�?+{�k����{������p6�==��/�����e�z���~}�����WwOW�o�ᵿ-�U����`ƿ�|��I���sSyӡ����V�����p_�|*���p�����09�����%o����]}��{��y6":c�c�Lc�,���[����k,?�|��{Wd���u&����ݥ��M��?��e��/���|��?�a�/��SY^����o�y�ϯ�l]֛�?s9�ᱹ�����O�z����5�ڴS���Ҩs����'�Z���mM�AB���q}A�o뀶o@C�?�U��u�_�	^�Y���gx'��N�k;���ݑ�୒�%�� ���P!�@�>v�����OQ���t�QE�Z��L�b[�j��9B:��Kh���tw�����Ņk���{%��CH����A���Sz�wS�8��uC�� ъ�v�iq�_ۥ�n�?@��Ң8���7q��m�!�]��F��O��\ ���zJB��B�[A�I�>v��~�⿦�-T����F��*����폇�A��t�S�|{��M������u1~ޥ��20�+��@�YAtzZ��-���>?%�ۣr9�/���~@����h���F�e���ߏ�ۘ(�����dZO,���D�A{%�y���l�_2����0K��h?u&!]I��"?gi�O�ҏ��(���r<��C�|y����)=C��'�ǁr?�J�H� �E8ŋT��GE�2�Q?P����h:.]^��?m�\�鸶�q���"?�B���ߦ�XA�Ѵ�˴?���z ?e��B["��?��w��~$��3E>�"q�C��l����Eʷ8:�Ɛ�r���U�B�3����n�4*������e0�3��mb�鼌���E{A�y�6`���������h�B��6��d�\nQ/��MV���^D�+(B��C��@h�(@��������쩩�Ԭ��lE�efJjFfA���B{f�̔����̙�r2���sRm+ӱ���� 9iy�tJ���^X�Y��[�85?}qf��̂��� �k��udfQ��$2���鹎��|)�0� ;='7/����i��L�P��^���,ն$ӶT���L/PddfJ���bYzNN�M��Ȅ/y�$���
ˠ3vY��噶�\$H�2���W!X9RJ��ٹR\V��pI;0:'G^tqf��������U�6ap����@R:D!?�1L.rdeeJ�W��3�I�@af�R2�e�,) Iy�-�ʖ�f�g��t0�!HR��ݎr����]���n
3�� #0�ʶg��B���(`��J�P�G�-�L�K��%i��(O�B\��HHRFB���_:�P�Ɓ�r��bRs��$|��H"N�H��g,fI�=N�'뎼+��8y^�ܢUvAK	�l{a�R�7^���&�	.'{�mDaވъ�̌t{:,�E����TnR@A��UL�Z�'��7*�5�m�z�";E�U���?a?�Vd��N^���]��/R\���8��h�1 �+��0����w��9�(:�%r��>^,�.��H�4J��</�GH��|	�U�����#�o��gA	^%��I�J��=�q	�~�x%�����u��J��J�+�륎Gqo����H�y������5�A��.�GK�wI��	>^�+�'J���^V���wN���s%x�\�I�Z�y�#��K�]%���x	�D��&��K�V	�B��.�o��H�[$�>�V	~�T�%��R���o�ʿ/]Gu��R���-��r��e]a�l���/U"r����<�L�A��Y����0��l-���iL��5��S��%��t�Q������FQ�m!�E�F�U��<L���JHz:��۾|���i	_I��4N�oI?�i�R_"I��4N�/����4�*����aU�OG�0I��$}�Q%���0��:2~�Va�'?I_τ�md�$}	ӽ��I�,�{���IL�!�'�0ݗ���b�?I�Ŵ�����0ݟ���wbz ?I����I�mL"�'�?cz0?I��C��I�yL%㿅�g0m �'�1};?I?��ad�$]��;��I�	LG��C�u�m����bcZY�4�l�\�ZX�i���B#�Ч��$��V5�U�޳�Xe{��A
�J
��,W�?��K��H��n�96�͂���5V)~,��_�-�	k�0(�����3�ZJ��ؕ�P�~t��B�̂�,4��oX�0CK�"�߃�+XW8S����G�a�F%�̒����TgU�1ݏ�߃���z�l�:��=��[�k��Wm�+T7�M
��Z:>R?�:��~�#�"�PϮuޓzBݎ�������}(=�Y^�CLeр2�}@��8OEɚ��nV�${Yg��x�����8O�?@�a��̋��ǫ�㢬Β��`�v���a�S7@�\�B*GHE��!�R�d��vn�Ŕ�ES�R�bʜ�7�c!w ����[�4��w�[�T��ΓJtc~E5�ךp$�+�k��,nb�ؿi���׆�R���vO�1�yV�YM/VԨ�H��M>
JE\=��<UNm�-E��ߦYV�y��Y8h����L��0ӵ���tLL�>�&S�g@Aߘ2|�����'alm���X�(�g�g���a9Xd{w��:�%,�n>Y\v��L�����S��S��X�wVBߐY�������	�60C2>2�O���~ ���L�L�
�)}�#���������km��y�M�#b�[("��_���� ��W~:�"� �8��|��RX�qk�◚�~����ꚨ��X]LJ������preo��.΃z������*�-.X��Zg5Vq͎��%�Y=T�ǲ���9:(�"��(*~����ԗu1@v^��u��O��d�I+�֟�7�|ͱpWM�-\�i�wdHY4�EDY9s��O����y�j�l�
gF�{�Rv�ٸ��ڔ�z��U��z�'9���/|��V�$=!X�B��A�u֘/���̳�58=��>#�8j�xv���^=�io�)�{,ޛᖘ��9
ֲ9JgqM�[\�u���lL(}7[ǔ�*-���DZ�֘��h�\v��+k�Y���<�Gb��0�i�!��z�u?��5^b�),w��fF��ZQ�A�O�������j��,���~��_\�no��������e�3�t���Ŗ��{�Al�=�%"��������\E�nu��K�"��`& ��زsEc��PB�zOk,��u�iQ?bq=dq���k���[q�E]��/X�"��븃���)�	�)nk�r;�{�;aZԳ�-��
@�j6�±p���LZ�u�oe�Ί����p:�ʳ��z8���QL�e] l㹈�M�4�n=���.b�����\_ߕ�3!
Z�o��T�>_)<���N4w\P9��M�������=��Q���7�o?�$�P;֑w
���'�Y���?�
�{+h�?�R��rͬk
��D���b]�A����iwbM�L(}ѷ_o��d����ӡ�����\h`��5������I��L9\v��`JgA����H.kaJ��C�Af��.(�q-�5��d0��M�������.&g��8�8��Ym5V�79γ��3��0�%�k��F͆�4��^��lv'�Vwć���;�
�[CmҴ��ϨI�	���j�f)��+�I=��r'�L��#f�;B��9��Ϙe⎹^�����ƃ���b�"���]2�ήu��̂�h�g�<|ӕϘ+|ӗ�xL�f(�1O�]>c>|�x��!�,,���u�����-��8�i�
)��t�.�lo�2�X�u��] Fi�{�~�Xv��Iʂ�-V ��ց%�<�32�Q���哟`J��6Xܓ�Zݣ6Y�M�5�r/k<ƼPe����8[f�����,��A���&������c\N��{F��2�����U�o�e��y�!��ɐŤ�d1�_@*cSls�F������ː�D���A��,����=�݄Y�1U�����:$��÷z��
�a����%� �B~�$�2Sl�{���l��ŴUA�0��,�hP�50O'�7�+��9�)<��!LcB#$�fFE��QL)��e�Mvt�ޔb�/�9fSyPy�䞭��q��A ��
I���D�$$C: � IF�dh$aHb
�: �$C$�w@�$7"ɰH�Hr<@rG$]��� IT$ݐ�� ɝ�t76
�wu��3��;���
��dGBv_�vi6A*���{A�G��.�.5�N�[b�Lr�~�����X��
3��A%���Z9���uVni<v�n\I�@{7��͟�A�+���p�?�`4�2��HP����#�o�)��������]����X���:v�5T�գ�_ң�q-�m�q	�%zY`����	Fឦ���X�%� І��<���SH�A�����W��[���8!��{C�L�R�7j�����DN$L��s��Y>�{~b�M;��������k���#�i;�����5��l�OmL;��Ǵs���w`OIw	�}7۰�__��}��N�Md^<��`"ˉ����AM侲z��)�Y��r�D��C`�=7�d=[[%��B���3h���G��J�b��*���k-����`�d]�'�X�Wc2VW��c"���O�y�T0�	���7�/��̝��/XL���B���Hb �IO�(5bs��z����� _�	_���|�tŗ�X(ZGo�����������X��J�oo%W>b%A�����������o|���ݾ������$��;���:��b'��}�NA��ר�'�5��v]<�1}"�_�u遫�^rXL0��Ĵ���h7���ݬ v�����|�:��x�I��k��P�D���s�	~�`6�ۤ��hɯ�	��<`�>"��WĭWr�	���ax�s�)�7�$��[v����1�y�;>����A�+�P���S�8)�,Y=S���P����K��l�����������y]�<�	�0��7X�Ga3��VW��=`�Ϧ�"��d<T�Ѻ�͔>��bJ�����=} 6ku�+�����Թ�.
�l�������}k�[k]N�yI�e���Li	ٷ֙�'������$ط��7]y�\᛾<�1ᛡ<i��-�<	��u�5ط�����<	��Na��-O�|,�d��^���N�"_�<,r+Xd,�vb�]%b�EX6h�'�hX��`yX��r���_�`�#6X��`�����5�2/xLZ/S�-�u�ȏ�|Lj��G�|-΃�{qߺ���2{�Af�7�����=��L�����A{�����Ib����U]�D���j��6�=v�!	�(u@�2V1�(R�B��E�!Ph��1�bhaH�Ha耢R�)n�").+(Ű(�Hq@�����H�H�E7�p�wv@��XU�Gr�� 7r%�ww��r ���FBnv���h��-�n\F-���~A����k�N������?�x5��w}O-pE�	�@�]6���⹓�琿�=G�2Xe��,}�w��6X�L%�)j�{R����3�R��K@������=�bS���=!�gM�����	������Dӆ�� _
�N�1tq�j��*Q�Xݓ����:��OK��X�hf�~"f����o�p�7�l��)m�q[;��	1����Pn2�(�G�XChSZ�ʡ�Khs�`@��&5�G��9��c�	e�x��-�#�q�W���-��i�QіzÄi�T&�[m�[��/nkW��t�+b"�fp�`[�Y����3��9�Xm^������In�)�Qe�^��i��%jR���ЬJM� ѤƵ�xa`Q���3�AMmXZ�iPY�*��D��BJnP!C�H�����A�7�Ca�K�.b%[\ ��:�dY=�D�w�Y��u�XʺGm`����A0����4�50�s�A���ԗ�@.���Z�'�����c����S�_4�v4���f���$��zP�݉�q�W��?���A�	TF/��B$ܞ@�y"���$�"mO�����]� B$��=A84)(���Z$�+�ў�+�%D�'��"���	��EKI�]�3# s
ɼ�}fȌ#���3#!�7��Yb?k��3�~��T��|��χ��2��W���g&��3���'�~&�6tT�h?Ye��
M������&�>Ǘ�р�D-^f��t܉�Ȟ~K��C��`OO�*M\=��#�>���S�U,���{���d��;��$�-��ZM����E5m'&u1����!�//�O���ӱ7����=m�=V���(K�iF��&���q]0���f0��<���sʗ���
L>�+4t��:�������yA��>��oy�N�R���<��������>��'�j�@� �V�D+�/�O�}��ǄI�tL�>�k���:4؞��k���8�Y[��5#�Ӱ����܌���X��]�0y3�A6�+I��nf��ڑ"����j���X�<?�8yvoO`95�Te����� %�0�7g��������v�Xr��X��/���c��w@�m�vĬ�<k������4�6|?��\z?�J���X�u�ٵX���4wF�����<f׊>Wl`��b۝s�U�I�����r%���f���q?G����>0�TÔ��<����m@�!����?����ͣ�焻w�2y�{�@�v�b<�fk�Z��W/�'S9��@e��Q<�WrI��J� �����z�/�Oב+�omr_��?Zݙ}Y��(��Z�CԲJ��k�0:  // NOLINT
#endif

// Use this annotation at the end of a struct/class definition to
// prevent the compiler from optimizing away instances that are never
// used.  This is useful when all interesting logic happens inside the
// c'tor and / or d'tor.  Example:
//
//   struct Foo {
//     Foo() { ... }
//   } GTEST_ATTRIBUTE_UNUSED_;
//
// Also use it after a variable or parameter declaration to tell the
// compiler the variable/parameter does not have to be used.
#if defined(__GNUC__) && !defined(COMPILER_ICC)
#define GTEST_ATTRIBUTE_UNUSED_ __attribute__ ((unused))
#else
#define GTEST_ATTRIBUTE_UNUSED_
#endif

// A macro to disallow operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_ASSIGN_(type)\
  void operator=(type const &)

// A macro to disallow copy constructor and operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_COPY_AND_ASSIGN_(type)\
  type(type const &);\
  GTEST_DISALLOW_ASSIGN_(type)

// Tell the compiler to warn about unused return values for functions declared
// with this macro.  The macro should be used on function declarations
// following the argument list:
//
//   Sprocket* AllocateSprocket() GTEST_MUST_USE_RESULT_;
#if defined(__GNUC__) && (GTEST_GCC_VER_ >= 30400) && !defined(COMPILER_ICC)
#define GTEST_MUST_USE_RESULT_ __attribute__ ((warn_unused_result))
#else
#define GTEST_MUST_USE_RESULT_
#endif  // __GNUC__ && (GTEST_GCC_VER_ >= 30400) && !COMPILER_ICC

// Determine whether the compiler supports Microsoft's Structured Exception
// Handling.  This is supported by several Windows compilers but generally
// does not exist on any other system.
#ifndef GTEST_HAS_SEH
// The user didn't tell us, so we need to figure it out.

#if defined(_MSC_VER) || defined(__BORLANDC__)
// These two compilers are known to support SEH.
#define GTEST_HAS_SEH 1
#else
// Assume no SEH.
#define GTEST_HAS_SEH 0
#endif

#endif  // GTEST_HAS_SEH

#ifdef _MSC_VER

#if GTEST_LINKED_AS_SHARED_LIBRARY
#define GTEST_API_ __declspec(dllimport)
#elif GTEST_CREATE_SHARED_LIBRARY
#define GTEST_API_ __declspec(dllexport)
#endif

#endif  // _MSC_VER

#ifndef GTEST_API_
#define GTEST_API_
#endif

namespace testing {

class Message;

namespace internal {

class String;

typedef ::std::stringstream StrStream;

// A helper for suppressing warnings on constant condition.  It just
// returns 'condition'.
GTEST_API_ bool IsTrue(bool condition);

// Defines scoped_ptr.

// This implementation of scoped_ptr is PARTIAL - it only contains
// enough stuff to satisfy Google Test's need.
template <typename T>
class scoped_ptr {
 public:
  typedef T element_type;

  explicit scoped_ptr(T* p = NULL) : ptr_(p) {}
  ~scoped_ptr() { reset(); }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  T* get() const { return ptr_; }

  T* release() {
    T* const ptr = ptr_;
    ptr_ = NULL;
    return ptr;
  }

  void reset(T* p = NULL) {
    if (p != ptr_) {
      if (IsTrue(sizeof(T) > 0)) {  // Makes sure T is a complete type.
        delete ptr_;
      }
      ptr_ = p;
    }
  }
 private:
  T* ptr_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(scoped_ptr);
};

// Defines RE.

// A simple C++ wrapper for <regex.h>.  It uses the POSIX Extended
// Regular Expression syntax.
class GTEST_API_ RE {
 public:
  // A copy constructor is required by the Standard to initialize object
  // references from r-values.
  RE(const RE& other) { Init(other.pattern()); }

  // Constructs an RE from a string.
  RE(const ::std::string& regex) { Init(regex.c_str()); }  // NOLINT

#if GTEST_HAS_GLOBAL_STRING
  RE(const ::string& regex) { Init(regex.c_str()); }  // NOLINT
#endif  // GTEST_HAS_GLOBAL_STRING

  RE(const char* regex) { Init(regex); }  // NOLINT
  ~RE();

  // Returns the string representation of the regex.
  const char* pattern() const { return pattern_; }

  // FullMatch(str, re) returns true iff regular expression re matches
  // the entire str.
  // PartialMatch(str, re) returns true iff regular expression re
  // matches a substring of str (including str itself).
  //
  // TODO(wan@google.com): make FullMatch() and PartialMatch() work
  // when str contains NUL characters.
  static bool FullMatch(const ::std::string& str, const RE& re) {
    return FullMatch(str.c_str(), re);
  }
  static bool PartialMatch(const ::std::string& str, const RE& re) {
    return PartialMatch(str.c_str(), re);
  }

#if GTEST_HAS_GLOBAL_STRING
  static bool FullMatch(const ::string& str, const RE& re) {
    return FullMatch(str.c_str(), re);
  }
  static bool PartialMatch(const ::string& str, const RE& re) {
    return PartialMatch(str.c_str(), re);
  }
#endif  // GTEST_HAS_GLOBAL_STRING

  static bool FullMatch(const char* str, const RE& re);
  static bool PartialMatch(const char* str, const RE& re);

 private:
  void Init(const char* regex);

  // We use a const char* instead of a string, as Google Test may be used
  // where string is not available.  We also do not use Google Test's own
  // String type here, in order to simplify dependencies between the
  // files.
  const char* pattern_;
  bool is_valid_;
#if GTEST_USES_POSIX_RE
  regex_t full_regex_;     // For FullMatch().
  regex_t partial_regex_;  // For PartialMatch().
#else  // GTEST_USES_SIMPLE_RE
  const char* full_pattern_;  // For FullMatch();
#endif

  GTEST_DISALLOW_ASSIGN_(RE);
};

// Defines logging utilities:
//   GTEST_LOG_(severity) - logs messages at the specified severity level. The
//                          message itself is streamed into the macro.
//   LogToStderr()  - directs all log messages to stderr.
//   FlushInfoLog() - flushes informational log messages.

enum GTestLogSeverity {
  GTEST_INFO,
  GTEST_WARNING,
  GTEST_ERROR,
  GTEST_FATAL
};

// Formats log entry severity, provides a stream object for streaming the
// log message, and terminates the message with a newline when going out of
// scope.
class GTEST_API_ GTestLog {
 public:
  GTestLog(GTestLogSeverity severity, const char* file, int line);

  // Flushes the buffers and, if severity is GTEST_FATAL, aborts the program.
  ~GTestLog();

  ::std::ostream& GetStream() { return ::std::cerr; }

 private:
  const GTestLogSeverity severity_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(GTestLog);
};

#define GTEST_LOG_(severity) \
    ::testing::internal::GTestLog(::testing::internal::GTEST_##severity, \
                                  __FILE__, __LINE__).GetStream()

inline void LogToStderr() {}
inline void FlushInfoLog() { fflush(NULL); }

// INTERNAL IMPLEMENTATION - DO NOT USE.
//
// GTEST_CHECK_ is an all-mode assert. It aborts the program if the condition
// is not satisfied.
//  Synopsys:
//    GTEST_CHECK_(boolean_condition);
//     or
//    GTEST_CHECK_(boolean_condition) << "Additional message";
//
//    This checks the condition and if the condition is not satisfied
//    it prints message about the condition violation, including the
//    condition itself, plus additional message streamed into it, if any,
//    and then it aborts the program. It aborts the program irrespective of
//    whether it is built in the debug mode or not.
#define GTEST_CHECK_(condition) \
    GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
    if (::testing::internal::IsTrue(condition)) \
      ; \
    else \
      GTEST_LOG_(FATAL) << "Condition " #condition " failed. "

// An all-mode assert to verify that the given POSIX-style function
// call returns 0 (indicating success).  Known limitation: this
// doesn't expand to a balanced 'if' statement, so enclose the macro
// in {} if you need to use it as the only statement in an 'if'
// branch.
#define GTEST_CHECK_POSIX_SUCCESS_(posix_call) \
  if (const int gtest_error = (posix_call)) \
    GTEST_LOG_(FATAL) << #posix_call << "failed with error " \
                      << gtest_error

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Downcasts the pointer of type Base to Derived.
// Derived must be a subclass of Base. The parameter MUST
// point to a class of type Derived, not any subclass of it.
// When RTTI is available, the function performs a runtime
// check to enforce this.
template <class Derived, class Base>
Derived* CheckedDowncastToActualType(Base* base) {
#if GTEST_HAS_RTTI
  GTEST_CHECK_(typeid(*base) == typeid(Derived));
  return dynamic_cast<Derived*>(base);  // NOLINT
#else
  return static_cast<Derived*>(base);  // Poor man's downcast.
#endif
}

#if GTEST_HAS_STREAM_REDIRECTION_

// Defines the stderr capturer:
//   CaptureStdout     - starts capturing stdout.
//   GetCapturedStdout - stops capturing stdout and returns the captured string.
//   CaptureStderr     - starts capturing stderr.
//   GetCapturedStderr - stops capturing stderr and returns the captured string.
//
GTEST_API_ void CaptureStdout();
GTEST_API_ String GetCapturedStdout();
GTEST_API_ void CaptureStderr();
GTEST_API_ String GetCapturedStderr();

#endif  // GTEST_HAS_STREAM_REDIRECTION_


#if GTEST_HAS_DEATH_TEST

// A copy of all command line arguments.  Set by InitGoogleTest().
extern ::std::vector<String> g_argvs;

// GTEST_HAS_DEATH_TEST implies we have ::std::string.
const ::std::vector<String>& GetArgvs();

#endif  // GTEST_HAS_DEATH_TEST

// Defines synchronization primitives.

#if GTEST_HAS_PTHREAD

// Sleeps for (roughly) n milli-seconds.  This function is only for
// testing Google Test's own constructs.  Don't use it in user tests,
// either directly or indirectly.
inline void SleepMilliseconds(int n) {
  const timespec time = {
    0,                  // 0 seconds.
    n * 1000L * 1000L,  // And n ms.
  };
  nanosleep(&time, NULL);
}

// Allows a controller thread to pause execution of newly created
// threads until notified.  Instances of this class must be created
// and destroyed in the controller thread.
//
// This class is only for testing Google Test's own constructs. Do not
// use it in user tests, either directly or indirectly.
class Notification {
 public:
  Notification() : notified_(false) {}

  // Notifies all threads created with this notification to start. Must
  // be called from the controller thread.
  void Notify() { notified_ = true; }

  // Blocks until the controller thread notifies. Must be called from a test
  // thread.
  void WaitForNotification() {
    while(!notified_) {
      SleepMilliseconds(10);
    }
  }

 private:
  volatile bool notified_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(Notification);
};

// As a C-function, ThreadFuncWithCLinkage cannot be templated itself.
// Consequently, it cannot select a correct instantiation of ThreadWithParam
// in order to call its Run(). Introducing ThreadWithParamBase as a
// non-templated base class for ThreadWithParam allows us to bypass this
// problem.
class ThreadWithParamBase {
 public:
  virtual ~ThreadWithParamBase() {}
  virtual void Run() = 0;
};

// pthread_create() accepts a pointer to a function type with the C linkage.
// According to the Standard (7.5/1), function types with different linkages
// are different even if they are otherwise identical.  Some compilers (for
// example, SunStudio) treat them as different types.  Since class methods
// cannot be defined with C-linkage we need to define a free C-function to
// pass into pthread_create().
extern "C" inline void* ThreadFuncWithCLinkage(void* thread) {
  static_cast<ThreadWithParamBase*>(thread)->Run();
  return NULL;
}

// Helper class for testing Google Test's multi-threading constructs.
// To use it, write:
//
//   void ThreadFunc(int param) { /* Do things with param */ }
//   Notification thread_can_start;
//   ...
//   // The thread_can_start parameter is optional; you can supply NULL.
//   ThreadWithParam<int> thread(&ThreadFunc, 5, &thread_can_start);
//   thread_can_start.Notify();
//
// These classes are only for testing Google Test's own constructs. Do
// not use them in user tests, either directly or indirectly.
template <typename T>
class ThreadWithParam : public ThreadWithParamBase {
 public:
  typedef void (*UserThreadFunc)(T);

  ThreadWithParam(
      UserThreadFunc func, T param, Notification* thread_can_start)
      : func_(func),
        param_(param),
        thread_can_start_(thread_can_start),
        finished_(false) {
    ThreadWithParamBase* const base = this;
    // The thread can be created only after all fields except thread_
    // have been initialized.
    GTEST_CHECK_POSIX_SUCCESS_(
        pthread_create(&thread_, 0, &ThreadFuncWithCLinkage, base));
  }
  ~ThreadWithParam() { Join(); }

  void Join() {
    if (!finished_) {
      GTEST_CHECK_POSIX_SUCCESS_(pthread_join(thread_, 0));
      finished_ = true;
    }
  }

  virtual void Run() {
    if (thread_can_start_ != NULL)
      thread_can_start_->WaitForNotification();
    func_(param_);
  }

 private:
  const UserThreadFunc func_;  // User-supplied thread function.
  const T param_;  // User-supplied parameter to the thread function.
  // When non-NULL, used to block execution until the controller thread
  // notifies.
  Notification* const thread_can_start_;
  bool finished_;  // true iff we know that the thread function has finished.
  pthread_t thread_;  // The native thread object.

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ThreadWithParam);
};

// gtest-port.h guarantees to #include <pthread.h> when GTEST_HAS_PTHREAD is
// true.
#include <pthread.h>

// MutexBase and Mutex implement mutex on pthreads-based platforms. They
// are used in conjunction with class MutexLock:
//
//   Mutex mutex;
//   ...
//   MutexLock lock(&mutex);  // Acquires the mutex and releases it at the end
//                            // of the current scope.
//
// MutexBase implements behavior for both statically and dynamically
// allocated mutexes.  Do not use MutexBase directly.  Instead, write
// the following to define a static mutex:
//
//   GTEST_DEFINE_STATIC_MUTEX_(g_some_mutex);
//
// You can forward declare a static mutex like this:
//
//   GTEST_DECLARE_STATIC_MUTEX_(g_some_mutex);
//
// To create a dynamic mutex, just define an object of type Mutex.
class MutexBase {
 public:
  // Acquires this mutex.
  void Lock() {
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_lock(&mutex_));
    owner_ = pthread_self();
  }

  // Releases this mutex.
  void Unlock() {
    // We don't protect writing to owner_ here, as it's the caller's
    // responsibility to ensure that the current thread holds the
    // mutex when this is called.
    owner_ = 0;
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_unlock(&mutex_));
  }

  // Does nothing if the current thread holds the mutex. Otherwise, crashes
  // with high probability.
  void AssertHeld() const {
    GTEST_CHECK_(owner_ == pthread_self())
        << "The current thread is not holding the mutex @" << this;
  }

  // A static mutex may be used before main() is entered.  It may even
  // be used before the dynamic initialization stage.  Therefore we
  // must be able to initialize a static mutex object at link time.
  // This means MutexBase has to be a POD and its member variables
  // have to be public.
 public:
  pthread_mutex_t mutex_;  // The underlying pthread mutex.
  pthread_t owner_;  // The thread holding the mutex; 0 means no one holds it.
};

// Forward-declares a static mutex.
#define GTEST_DECLARE_STATIC_MUTEX_(mutex) \
    extern ::testing::internal::MutexBase mutex

// Defines and statically (i.e. at link time) initializes a static mutex.
#define GTEST_DEFINE_STATIC_MUTEX_(mutex) \
    ::testing::internal::MutexBase mutex = { PTHREAD_MUTEX_INITIALIZER, 0 }

// The Mutex class can only be used for mutexes created at runtime. It
// shares its API with MutexBase otherwise.
class Mutex : public MutexBase {
 public:
  Mutex() {
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_init(&mutex_, NULL));
    owner_ = 0;
  }
  ~Mutex() {
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_destroy(&mutex_));
  }

 private:
  GTEST_DISALLOW_COPY_AND_ASSIGN_(Mutex);
};

// We cannot name this class MutexLock as the ctor declaration would
// conflict with a macro named MutexLock, which is defined on some
// platforms.  Hence the typedef trick below.
class GTestMutexLock {
 public:
  explicit GTestMutexLock(MutexBase* mutex)
      : mutex_(mutex) { mutex_->Lock(); }

  ~GTestMutexLock() { mutex_->Unlock(); }

 private:
  MutexBase* const mutex_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(GTestMutexLock);
};

typedef GTestMutexLock MutexLock;

//���]<��O�?t��fJ�yEE5����Hߌċ�A���B��9��k��O�$;��)x\�!RgY��d��� �wR���g�
��]�b+�T��	����\���U\������7(��,,1\�ڝ%�Q��{{&�Q)l� �G`b�v|N�?ޝ��Gg�W��RC�F5+�*�dP��2S��v�g�����{��<�Ĝ����U��(<�G�$�K�u��8�.>T�,\��G�P�4�e�tN�i;�Ķ��� ��q5_d瓠?g�����`���굣ʡ�L�.��5\�z���~���F�7
�Gc�Y\��{&��^.�G�e&�O�|�O���#ޏk�G~%��{�۶1��}L~&ʫ.v��O�7���삉؄���!�%�x��"�$L]Xd�7k�����BK�Eۯt�����P2_���6q��nڔ�4~}��^�8'?Ϭ-.F��i5��<��>]l�>UX��P�g&���Ҳ�	�<k�E0[JM%y�(-�/v?KN!E#�d���jME��yl%9(�ūGx�ƴ{�-�))�hٵB�M2�̓����n�>_t����XJ��}r�l�b�-7�RB1��,���h�
-�R˂K�U�X$O:�b1�J���z҄�Ʌ(9�[ ~^��Rq������.�?+��CA��K-���2Ȥx[iI|~�����a�Òb��
me�
m�<ђ}�\�K|~�)���"�p�S�,��X~qwZ��H����	�X*���M��ؖ	Jv�g�@�yشh�[����0hT�]
�;T�>�@�^����aЍ~t�k�,��V�[�� ���@[`���]ka��U�
"~V>L��j��S�W��t�^�а/A/L�� Mz(�=�M��:��@G~�``8���ё'Ah>P���
���S_�s����@�m���a"�E9�����@_����	��P[���:��@���q��}��0�$�Wϸݯ �p��@�;�=@���9�ga!|�Ӏ.�t�灶 �t�y�[n�}���a�H�#�N���7�^��W.�~�:h�eH�-@�:�;�=��W�ⷱ7ï,C�Rl��W��_���8�KKG��1���ˀ�I*���)=���/߲@O	M�i)��e�I������-�DD����]-5�|����c�W�^�����*gy@��C�P:��"~%b�T
7��Kg�Y�
�A�!��.�|C�xuoįL�!!���:�n+�'?M!� �Q��)���������-���F^N�������3��L��=�߄�)홐4,ȟ*��� ��k�L�0�0�<�L>�Zw��byl�A��tP^<3���Y�� �����"�x����v�%��Jg-��*��H!��%]"b�2<R����1��|���3M�����}�r��FO�� }Zh��7�C��Ū�� ��Y�`�tc�����1�N�b~`F�_��>u������5'�g����O ~�B�nZ����';~B���#>���L�S_�Mlw��	��A��TBF�C���.X6t�� �{�;�����BB�a��&5h�_
� O�M��1Oլ谙���Xe6����
�׷;	���e8����ڣ�J���q��,J9���qa�įD<���8����Յ� H�S;�	��|W `��_y��ѤP��`R�/D������'h����ю����Wz���R?SJ���YA.�{��l�$ՓW@���~A¯,��׎1~�_����/��e�N#��-�~�����}�߰�~x�x-����$Ļ��������R�ŷ��K���W��%�b�7�� v����X����-���N�Q�{��L��	�� ��T��W}$��ƙ�G۷+8N���oЮ~5�7.�7����?ȭi��*�H�|��[��w��w5����;=p�g�>V�v�7�x��|�z�q�_�R�h����~�G?��4o�����k�K���M����G��6�k���_y��<�WF_���yA�I_\K,���=�xO�p�X�IB��~���'z���ߘ�7�|z� ���~����ʙ~�4֛O8O)�x'��dDd)�����Mv6��>�`���{��C����`�x&�>���PF���~,B����������מ�Q�������ka������Z��<2��cx����y�������'=���Ч=����z��
���q���HvO���|�A�?�,��b�4u[dW8��1�� �"i�B��r������|����t.�G	c��I��t"9�#B�;�;�;�;�;�;�;�;�;�;�;�;�;�;�;�[�Ix�_�����$��[�~�p�$̇���0$|�@x��ǭ��s	#��kH���;��.��!ar4��@x�Q]|���}�������m�������x�����?/�a���t���.�t�/p���8��t?�'9�(�(sC��iN�q:����r���U����[�nⴖ������b���8�?3dH�#I����?t�ْ0?a�#�LI����S����Grr�}�K~Є��׽����5��7�ו�U{ý|]���he�����ו�������u��F���|�|]���hc�����U���m���
����H���u�}i�_��_�V��#:�/���u��Q������x_�������?�n ��@����M�a7�_׋�ٱ���u��®[����7ܢ|]/^����*��4��U��������� �����J�i��D_y�Q@@|]�?I�q�_w$��s�u[9�U�����G�׽Z����5�R|�]��
�>4��V��O��m�����D)|�H���O�����n�|�����_Zv���=��W[�竰ވ>E]Q"/S5ϛ��!��Uv�F+B�
���k�X���zŊ�cV���;�EJؙ�S��G '6�����D��WN� o���T�WN��7S&�Ձ?�g��S֯��?����q��e���������B�������^��^���}��	���kS���������O�}���~�}_���?k?_�q��	��Ȟ�ļ�1ڮ����[d7��7�hR̪?�Żo&�_����7���_�ݨ�8��c�F�1�j <�� �A�� �v ��@x�����CƳ
���Qu�''@�y��+��c�o�������gU =��� ��?���c _�1^ ���7*@<�(��_@�� ��nt =��T�nw:<@�����Q����b�\�pu��#�l �� �S������� z���� �y�x��N������P9�	�=��/�A��`Ư�xԯ�|���x縜���=�t-��tj.��>ח��O�]W��㓩�]o;�d|-碌����zR��0��\~^s���OI����O<>�P�&��S<���y������g�2�4|~������x<�)����˗�	x=ׯ�����d�x�ż\�2�����|������^>?�,�wp~�(����7��҂@�4��廞Wi�{���<~���7�o��}ׅ�x<Sy�fs����&��}^0[xz%\t�پ�+���l�8b�"(yQ�)�j)�fӒ���j.��XϷ1���BsQ�W�|- L��<�Ci�,��)Y`�"�9$)7ǖo�����YP�����W\R��$�@
*;ז�/����Jr�v�z�)Ei��#�s���%%yV�P�4dL�Pb)(Zli�}ه\Z�c�&��Gt�l,'�S���ܜ��s"��R���O{�λiXR����KN���/��y�<|��A=9%��"���e���YL6kQ	�o�/1�۳
ڳ@1d�ZG�P�raG����y�"�\���ȏY�c#.�@�|��en~Q���K�"܎]j-�3�%��V�=��V�˷��s���e!�,��A�d�f�/��K(&��v��*^��X��1#+be�ꋊ�~ȋH*ɝc6g�L6J��w�E����TT����󢴣��Suל=��
3�3�t�&)`��T�k.�p�k��/������B��[u�~��m�$$��؏ST���,��çVi1�7wX�mAA^q�`���/2	�E�ye��h�
� �(y[�a��,�M>z3�(soTJ��E����A;�>/-�K@w>�'��	e0�^�q���c����yN�<�K��hL��#+���K�y+�{��*=n� �J�y���ؼE!��w����a�
��5*�`�R���pL�W���U$O�P�ѭ���;I�g�}�z������%wǻ��Q齌/���I�H�e|��j��?L�o��G��|}V��%_���W�12�|�>AƗ�&�����T_�=�AƗ�-g���=�,?L>����e��2�|+�XƗM(���{-�2�|=g��/�U��w��d|��F�e�����/���=������/?#P-����w���%������}�v+��+�[���ne���v+��̗y����	d|�|6R�Pn�2�|oW+�˿������E%��1r�����_Ɨ�k���ۿ�?Hn�2~���e�8�����r�����/��ۿ�?Dn�2�|��JƗ��������e�d����)r�����_Ɨo�V�����/�?*��1yy�U�AoN��u�A��*~�?g3�}x������#���w�W^4��]t�-@�~݄�@�B�{	����#�s��2ד�7覛-���,���u���tc�]��.A76�t���ߓ��&ՕI���ƮɕJ�Y��.��������Z����эM�+�ܣэM�K �ptc��j����莤��{ ��R��� ��Q��}7�������S����=(��V��'��ܗ�����܈��0��O���ݛ�O�c辛�O�辇�O���C�'�nt�K�'�6t�����#t�G鿆��ѭ����]t�O�'���~��O��� ���ϡ;��O�ߠ����Ϣ�?���Ϡ�!J?�K�C�'���@�'�|t���{����{
�Q��=ݱ�~r�Fw�����O�J��J?��;��O��=��O��=��O�n�N������R�ɭD�0J?�/O�#�~枬r������Q��t���x���;��-bq��['�j�y������n���+}��}�����k����F|̠�5칎SA���2��__���A�`{�`� ����>!5�b�@Ļ���% Cq�}|��P�c�-����^1gPg�U��R��l�=U��X�W��/+�zCe��Z6�~Ym��_�-28C!�Oa�Bb����P�V\{� 4fK��!�Щ^9�)0������A�&��*�JC)�V��zgɭ�7z91��y�5W�����v9�Ҥ�i�f@B�ZP�]��sg��	�&R2�d��S�&$����4�����s����0q�5��x���,�:�e�X@�����Ľ�sc��L5�>��9ͬq�U�8��}����XO�>#�`���JW�����Z6#���:#WE"����?��ᵉ�j\ceP}"�ʛ�$�=�[�ɰ��E�v���h���T��6�_֨0I7��%�\ФY�5
n \Ў�4c���~j^���o�����$�%0S��G�aA�AV�n��(�-������`ǁ���$�y�M�����O	��.y�uzq�%v���N\J�G;�^����Q4@�'�����)JmQ�eJ��[y�J��9���nH�ֱ/��DPHQ�B�2[��2�	]��  �+n�(7r�iVπ2_q�-���#��b6	���T�5�+v`��V�h����ŚKtwm�����;�'J���Y�������g��ˁt���]3x��b��Y��5T�����w0]��w⹼nzbu���̓Kp�q��"$�ap̝�Y]�ḋڰzi*V�AK����p�
Vn��7$=�Y�ٚ���o~b�~o2 Ϫ�a<@�gX!f��W��GU��q���\�s\�3�Hison¹:��EN�H���֬Vr=㹞��z>�j�Y�cD|ȏX;���\�,���8S���6A��^`h��vk�x�8nq?�D���Ӈ4��|�Z�ԢXY��j�IM��?�����+��8��>�n�\қ��&o�E�'�ݟ�m��] �S<�7Œ��I�b,��?H��.����=��V����LK�5�� �_#?���_��E~�?|�nt�3f��&{<���?��� H�����.�|��f<R���Z�7�sj�����#5��ˊ.<t�����������Ѕ��k��]a�/qS ��+�t�2��<���Q|�q@$xk���a��k��0H�-k��6#dن�rj�?���>Myo�Oa�=O�����t�E�a����z��&��I��G�$ʙ�,&�?	���HfV?	(8q�E�Ҷ�+q��$�9ZT�GN«�j�m�X'�M�S���C�W(��*��4;�њ�'��0��m�q�3h�8�>��<U����x�<k��2�}<��Չo�c�)D�{������O�#�D��i�4�F��oL�ZʏA�������Y��2:��\?��hJw�>�\� q��)��sX�!'_��7_���/ǼE=�Pя�ѫ=/)�y�5�HS����IO7:��NB[�8jQ[��Q��,O�U�ڢ��(�P�/R���BE�\�o"�V��?�W����W�E�lK�T�~d�7�d��W[Y�w���t-��%M-��kdm�@�s�����j��x��A�k��}��ů@�k�5>�@�������V��2��_
q�����y�㩿Wb��KV����P��?��*^�a�`(���C��q���h�����=�}���,I�`(�_ow1�י�އ��۷���!TP���!�V�c�KH|�Ø1�~�R�V�#�EuJ|�,��:�'������
��ڍj|�'�� ;-�V�íT#?�.���S�#��V�IQ="6�a=V[�g���frigHMsV�O��x���{�?��=��a�_�Wf#�Y���3h�z#��T���,�����f8��|a
#�{�� ��H�HL�����O�zq�4��OKU~/<�h����wJ�o��/d��U�(ꨇn��$~@�%�qM'��x���H�j�3A��ⲇ+ǺVDe~'�. /��,�oW��F�3���]y�Ӿ<L���$0�H���a��5���B4*�W����CU_Ë0SJ�q�ϼ,�6�]����t�A���s�9���� BI��/�CW��c�4ۣ|!�1��|�E��y���HpT��37��I�z�_|;7�{%�#D���b�ª~�-o�-�RD��@�k�<(���8S�G�)�>��Z�0;)�o%�	�݃vCZ��cX������緥��k-Тe�x��[<U�-΃�N<D�����/��1_4�kq �\���2�ꗥYWҙ���h��9B��ś�x-���|�=�IC�*Y�9�wHJ�h����zḞ }z�u�"���q��ɞc�=~ g|R�d���J<$�na��p�`�|�1�EM��E�
D��f������ͽ_þC�n�Yf���ٯ�jVW �߯w	��:g�a{�B����6%�����m����^�����	�҃��7����`�ʁX=O�g]nwsL�+�5x>0��f�� |}<�4&!��ÀLQ9�Ù����~Mkۃ�1�JK*��3�.���bsQ�b��������i'4�#�Z�������F+���:���4g��8 %�w���x�!�$��KE�u<ڔ�4I\G,_?��lH��MV$�N/����'s�>�KQ���l�1�:K���A��Ӑ>Wr;v0$�u���f�,��� Nי�d&2:��#��}�,pb4��զ���ɕTkD[�8
�m;��t����-�sQ���c�QP`�� �!�8_=Fg~c*%o�7�^|
��j@��j@갇��?L���.�/�^�WP:5+�M��X�=��'?o�G��o@�旔�4��E)�����`�\����t�#��Ue�);����A���r��R�.^�NAG��0F��I�Bڢ��y����Cʦ<<�yx�s��9�1��K�-b~̤l<#�,z��C�Fl�\�d)���������]�ؔHHkN��v
1�{�Q�G��z�!���T,� C�v�$˞T�ǁ�����2cJ���7?~��<[�'$#:�4��´ċ�-�/�7��t��4gT��e��Ƨ;��8���GĀg�Ķ��v�/�'Q������)6|�EB�!Dh:��c'o̮�m/�!F��+���`��	�N`�J�\�rta�,�u9Jc��O�git2V���^$'��QqkC��ue)�	i�Ni�˚ӝ�а���33�Y�:[�$*� �y[����3B��[Ob@�Q�����3�}:h�*���@54���3)��9g�霋Cҝ����9Ko&:�$�S�m)�at��H\��	�	�-#&��b�-�$۶ׅ`^���Z�
HyZ���&�wܰ�
=�v�́Z(��|��*6�"�OH(K��,�6k*^X��8�$Q���Y�i�bt���ߍw��}�R������e����ZM�`���P����Hܘ��qx���ʅ�p��B�l/Ng8���$е���}�|��92�#��.fG,�j�4�YǤۗ����Q��$��Պ�ˎ@IZ�;;Q$qo2��B;�f�્���r��1)ǋܲ��]�`@!�!���ȵqӪҝ��0���l��ٸ]�jxѠR�/+���%���~9DS1�Z������.�XT�����
B���L�xC���_g+B�O��<�k%��'�:��X���X6���D�J�V߇��ޤ�W��h�U�Z����W!8�r���b�c4�O��J�@�J��bH��/x�=�p��1,����&�	Z&���!�@��1�
�&��ݡ!���4}d�$���P�Q0��m�1 T|^B4+;�Y
��Y�G�r���ͦ{O�Wm��+�J��C�<��j���h]�h�����^j*�Q��3-����k���u�Q�>�s��@��l][�#P��3��9����E�d�28D�����M���L�-��S�}�]jWv�J����)U��\�"��%lJ��T)��7A�5}��1)&���,�.�tB�G;�o��|�0<��gF{F�p���l��@$�7��;��*|V�܊��Ӛ���{����Q��`�돶�|ᜠ����ʟ�
o^KC�Q��Wn���x��"Y�>�kC�:��׿�XA��7���GX�:�T���ڗ���{��?
N�b�dWt&��^��k��9�������j_x;%�NX <��a�����tN�ެ+�RԬ�Gb��ސ�iX�۝6,�]=YqR��ұa�� ���	wa���c鴡e��cӯ�}@��x�q ��nG���@E�J��'[w�+������i�xK�V�G3���e)���`�o	"�5+=�K����Ȓ�r +�==(�:�&�m�d��J�ʱ(]]�r��S������es�0���Oug�:���S�B��K�q�=l7�I�L!-)$����}F�]l%!SZR�bK
��3i9a�ʳ���^(���CȖ ���a�������ޤ�Ѭf%��a���U8{����k>!<ͤ��΁��h��"�W�}�C�|� ����z��Dj�A5M����������%H~]7�ެ��Z�#��m���]"�����'�ly�aT��e"p����i���h3:��Qi��p	ì�|���`�Y�k[:{��kCtv7Lj�-���>�Lr]0��N�X��m0GW$��n�C�(�	&���G��Gr��Mc���k$�|
�t���k��M��|�|]|r�5��`-�F��ZM J�B.��|���"-N���d���19����0���TZ�${���8�Ju
T�9D+HX�b�ACZ���y7�1�kq�j-����q�������95����Dhԕw�+�`kN�Az�w�5�V����_�����n�qR�WS��scew��C��X)�?j�J^�a��d7R�iȏ�R�f�8�+��^�ǚH���<�`c���`���t�+�9?:d�s� �̓�ӂ��|��`N�U\:`p��U!����:�-��S���0��%��^_�JO��5�P���h�Y�f`�Y��r515'k��%U�p����|׎�G���C�_|=�?�Rar��G��<�����Ao1b���y�#����|?B�*����G��8�L5������0Z���re*�"]iq��|�����e�xY�������G0T�k���l�����%���uT~�����pʩ"|�nN��O#��a(�C��I��$����!z��w��I~���O$��������|w��
���o��8ıM��(m��Y���v�@P{�4����p�g ۿ�v?MU	g{6���l�D�=����(����>��xm�g�g�>f�����0v��y?[�vVt��Ӳ�w�'�|�톫b��[�͟�,Z�}|��ws���=4�	O��wD��=�垃���#���!����n��Y��o�y=�"*~���u�0/FB����l��pO/|���/��^����_q/&���πM��m�M��mT���mT��R:���%��Յkl>�����t��ǽ�Tz�w�;r���o��K�;(������ȿ��"Hh��{�����U����~��}��v�gc��ӧRJW>��:��2���&�!"�Ȋ�;�u���V��xD�(���qj+^"�b;��ڏc{yܑ�HkMS���y5⬬8�74:�ka�"�MYiM����:�U,� �<^vg"�Y<�G���U��K���W�i6�18Ҡ�����=�W4�N�b;���xj��1W�i�h��a.��>�&{��Q�=T�]���/M3��,�q�u/�:Z��Y�r�k]CI���]Vx �/�r��w�Q^g��Jk_�e��m����ySxakv.�^qq�	��S"_�pNqN��l����tY�Q�-�>���'/G-��$�]����a���b�V �vʘ��ǡ�O�U��7?WU��V9ۓ�3<p�N5?o��/��C�=j��Y�HK<��w>��U$�F�,Z2L����+�������88T��a�c[?�{y9؃P�i�6�z�s�ΑvU�R�|N��)�����:�+3�àc�ݡ�ǜ�;M!�1<��`�gT=XQ�,�]x;�"��B����Y M:�S��|��9�Z����b���R�o�r��_����� �B���4�Yw6�q!zgQ������G{�3`�cCh4��L�T�3D:�VqZ��;���8et�_9Hۜ��Fd�\���8����zE�A�i�X��ݷ�UslI�`��k���DCq`rV�5,Z<��2��E[�!�giS$��S�h�A��}�m1oh^)�d�c��ů�Km��՚M���,�B��|���P���_��92$��F�eG���C�a 7��$���i�j�5d�5�{��`Y�?�<�S���C�Q̕�G�]���G뺐������$�Qe��|�Qe�����x��{i�q�����yO�T�V!��������.�1��75�f�+��z�֞�Ey�޾���Q��hk�C=IÊҌ�qaF�}�F��q��{/fTU
h�t)m��ʟF�oR/��q�9��'s��\ЩO���`ߦHWЧ�]ZUm[��tS�2�Qј�bg�4/d���ߴ��K[)���'�;�B���m���x�����\���aަ^�_Ji�mdh�{�����ʡ�d�_�d1^��j���4t<�{^�bﲘ��`oӂ�>�S��Z�������j��5c݆����`���Aީ���oa�-M[�G���ȭʫG�8���C�G����Eg5�:=�kT�Y�`cO\E��?���aCx�D���:1��s~�q�P�����;�fpiEh�q���n�M�-I��I!��5�$�}\��0b�''E����H�AЍd����3�mݚGI�-�0b|�5
4��v��j��y�����`���28�u	u+W��[�K���^�s8�?�>��4���gC�b�E���ӆ��n��#f'�}�<S�9S6]3p�s-i�^xy �rd����@�4�Y����e]�W��4��S���5��{k�bit����]�O�nt�d8�a�=.�����y�Y�f �̪o^��7xL7@��(���N8D�Ɲ��a��-�A�� �v�w(���������]o?�h���e����=e�ȋ����X������V�&--�wd��?V���\�E+]׾����Ѝ5�۫��{��йƛ��@̊��i8+�)k�|<ƽ4:�D���
�B��x��N�e'	F��vŻ=�H��k>�u����A��0�%.���߄�~	��'hs
��_�มmڔ)��VKAq����Я4���G7 /�ܸ"�+s^)�̶���y��g�kr�pm��.�a�ɤ�������5K[�
E�DZ�b�bF����i�i������Pd�����+9%ZT�y�h�dϠR�{VbM�j�D�Ȫ]h)��y�X����`.*�hKl��y��V+B��-�~��V!����9�.B�ͪ-�ղ�=H�4������G�@��$3�3�IL0#[�c2	���"��`��(����� Rm�t�2��b�+F7]������+-���=��jGj1�E�1,s��
��c���!}�o&p{�`~n.���Mf�i��b�%hXK�������'fkbSrbs����5<�!��D�&cӵ`�9%�4Ik���[�<,vX�6v�6oH�0mll	�%��b������rzi�������LW6V�lυ �,x�.�Ev���o���;���U$vpBB�!񠖜�`��y�����6K���X��9%���@b�0�`p��m�LE%�؜dp��]��~��_<J*n��E2d0Z��l�T�����3ӭ�O��t�?{̸i�c�%$$d�K�KL�L��� ������0�w��A� ��`����{c�K�C�`��K��v\����&�I-���w�R���Y�QCE�tx^i��/Y�7L�797��G�}��^!����H?�&�������I,����\~uj����bՎ�M@���A�:i�h-]lť�9V-�i,�a������TR���A������rv�B�c<-���'���rHo�ҹ\A�F�(?	�b"d��_�������
��c�e�]w��$u�\'�:Ah�?�Z�M�f��n��W;�r���G5�i��ԭnw*<7ms��Ɔ�`8�h��W����{����R2!vm@Sq)L� ��#e�u����o����k���	@�!�(����[��C�돹ݑA���b��@�>�H<�4�4�>�,��"�C9�5@�g��F��������,��i�9x4�z�U@?�h����(/�)>�vGMţB@3����Hw�(��"(�"��u
�R�;U𲄶-0���ȱQ�5�KBʅ��1pH�ҽ�x�dq�۽� �W����ǅΣg�;[��Ż���/P&_{�"�Ou��4 �pNB�4{�j��xo�{E���^"�Wx���H/�r�O����~<���j�" ��ryDc��M��Ձ�,���:�󀦃{w��L?ytgs� ��w�ֹݛT7�ߴ��N�:��!T�I�"��)�d�.�@?�yZ����_��'Hx��V������7Fh�"�tۡTj=(�(?Å:D�	X�1]�Ÿ�]������׃<���oZ�Q�TM�T+�E4(���Q�J�����/~=����햷�h�ݡ\Z���o-��㙏�(V�D�eD�+�E��"�gw!p/�?�Wt�7+:�,��ѡx7���?������G%⁯E<�U�nփ
��5���*еF���.�	:3��������'�gDT�TB>� �U���3Ku�|ƃ����3��@ ��ߪ�5{|����
V�
i�*��5Ó�`?z��d*�FOgm^wȟV	'�p�3}p���p?{2_�x��?3��;��:(O=����o��UZ�5A�*�d�ާ,�!^<�WQ(;�y;/�tЮ�z������n�Ә�A�������i�Y��To��|Y�ۭ���(~�)�� ��y�7 ?���:п�����?|��~�w��>��z�.ޞ"2US ��.�.Jz��/�>9�O?����������������������~�O�����/_��m���5?�;�-������^�4v7s��.]��@8�ҽѷ�C���P��Wi��=�X����j������v��Gu��g b	g�û<�E�p%���|r�K���O������[��*N_��-N7qZ��~NOrz��`n=9���0N�r:��\Ns���8}��M��r��ӓ�^�4�^ON�s:�ӱ���4��Ŝ���N��t������$�9�B��?��8��Ns9]��*N_��-N7qZ��~N���Sr��&�������!�R�)�܄�9)�d��$N�<24���|i\���c�dxdHǿ�2�Q���*|۵��'K�D?�{+��R�+��;�O��?~���I�#�v�f��R;*�yB��~���R�-�[�O��HT�7�O����R?)���OμۗV�:޹	���t�/��K�Ͽ%~�%�W��$�9�_�������]��?.��K����VN?���Y��'?��s}�N7ο�
���^�֎���_�ei��p��?|1����[�_-��/{�t}ۡ@��%~�KxE�����%Z/���&��{������E���F�����o
���~�:�o���\���%������ܫ�x��w|TE���		�",�Hр��z��R�"E#IH6ɒ�lI�.�����1b��A1B�[��G#X6��ޙs�MfN���~��?~�~�ٜ�=w�3g�̝;�,�o�8??��_ӽ&.E�ĵ��L`���nj������֝���ډ�ҧ��˯kȎ�i��M���i�ZM�u�x]�:�uݤO��I�«�(CS�gW���������qy��mڙ�O���uM��f����3�K�p���'Է���4~��MZW6c��}�|ԥ}c�k����~Z�6㠡�l����o��(����iX���|[N����R� ��
����E!�k?>ri��i�i���{�_u�V!�M�ē�̖s��[�M����T�eb��4�u�S��ܰ���ҵ��]�"J&S%��-�6����bj�Z��bÎ�M!�fS~�ɔ3�eG��9 d�c+^ZֱKY����6ͱ���4�ϟ��<�dz♵L˖7i�0�-35�<����
ه%(8��3��:5`������Ҳema\t�щm�wn��߲��-�����z��anm����oyK��b�dn<��4����-M�V�Ҁ�`s@�kD�XK�9�e���.bmh*l���*Ȓ�b:k�@�9���������lnl������(!]�W�7��捄��k�64��;.�dz�+"�d��p�b�mV�z�9��%�p���)��ڗ�L�����G�=Xֵ�����ϯaE�Q��h����f�����/��J@@#&-Z��-;ne�m������x[h�Յ}veGwv�Ŏ���͎����4��1���c(;��c;�e�Hv�f�v�e�x,��>'�c2;"�1�t��;��>c�acG;�agG;Rؑ�z����>�ّY��L�ߋر�^v,g�J�|�;��=�>�`�zv<Ŏgر�����g!;��M� {�}�Ǝ"vla�V�o�g1~ng�;��;v��Cv�a�>v@�C��0�}�}c�GB}?fƎrv|Ύ/��%;�a�	v|ǎ��.v����Wv��QŎ������q���q���
;�f�uv��Ӓ�?;�#���є����lk�ن��q+;��q;:���	a�w��;��#�=�ѓ���l����ˎ0d��� v�s�&e�0v�ˎ��Îq�ȎI�̎)�����~���c&�Y��Q�;�}F��1�s.��>m�Hd�<v$#w�O';\�HgG;�c!;�c	;��XΎlv���V�ϵ�x���x�ر�ϱ�yv���ٱ�/�u���"v�Ύ-�x�o⹷�g1;v����ر��c;��0;���#v|̎r����%�������/~<uT�����c�{nI�P>��;M'��54���^[����{��V��懍[t��)�-���=�1��4�;4��d�os�<���E����3x�?6v�r��o�����¦��������䭼�%ڼ����J��ﶛr2�ь�������?�������>�>���&S�d|?��g᭧�o�7����c�Y��񣭆}ٶ��N��.v��ҿS�_�i�����X���aO{P�m�1������;[����~z�R���{?���62�����<�����W4�yn��.L��kw�m�dF�3���٭濻��];�]�q���}��1zv�W{�u���?�T��}��洷��Ȝ�2�Y�:����W��:�k�ȵ=l噶��ۗ濝��J��=~.wm���z���l7:��}������������s�O4}�p���>����w��٭~�O�(X�5�侯w�5�{߳�b=�Ԝyc�z�O���쥓[[�ޑ���闣
�~��B���{.���t��kA-�_��=/q��[[��-|�Ŷ��&o��0��v���6�K:��L���m?�?l�<�c]Y_�|��+C/�?�䤝�/tݺ޿ō���B?;p,����9�$�U���?���ޟ/n���Ϯ���鳏�4�{q�{Nl�ʓE���<��c�ow�ù�s�ON]�h�-���P`EV��{��m���]�&?3�p�]=g���{��O6�z��s��=���a��1[����Q^�q��f���1{�����У�o/�z����7~֚�p��+רR{�H�ٍ!N��#�_It��z_��k�>lǼ��[|�V�O}�W|����ׯ~���?�x�˯<��y;c�^��}qSν���^��y~�W:s�{�?�~CK�&���Ƽa��a���p�0��&E�o���#�_z���;6�|x�k둜����ڽ�x�ĜO�?n����B/�[�;����f����w��ԭO�ج�v>�锣c���ِM�����K�,������n�"��W��̻���_�n}�i�)ӵN�۾�?����O��++������o_�2x؊���W�����?y��~w�-|���s��П��Oˮ'?��^/�Ю���9�>u^9p����_95��O߼�m|˗�~1���/)��ܰ���{��_X�e��M��_k�'�1o�~eܚ�=æ�q��S�Bg�4��/�wH�;.��C��5�9�v]��s�<�fܓ��m�yoH�K�c�}zo��c�K�mXv,vެ�}����|���eϼs���}W^�ئA��acV\�ss���M
�^4�Aށs{��7�f�o׎w�{6�u����rē�~X�{���1?��{~���Ϭ�ծdQ��C;_�b�﫶=�d��k3wm���o]�/*��=�`�)͇u�����>+<8s��=;B�����鲰O,]����o��=���[���|௾~�.�����^5��=�Ф�C.&|z����1��nKF7�/S�o����cw�����{��5}�u���Cw�y��/���[7�?~y���������7���m���ͦ�{6n��'�^��=���e�$|v˙O�\�d�/3n�Oȩ��?u�튯G��Gƛ��*nF�߷|����>�i�N�}=�ݣ=nlL��&��[����eM���[���.��U�w�:?��Y�/�;��i�����Ѧ�|�O3,���;�謉׷�9�����_���eˋ��}yP��V�Sz��e����VxN����Ӗ~�hg*Hz�a�{��}��>���'�_��MϽ���=\�ӕO������-�
��rs+�����}���c�c]�7�~�m[�oyy�S7�w����$��KO]���u���G'$���b{8 �{�}u�.�,�o{�[�WV_{�݉>t�s�1������6oj�ckg�]����!;��1���{sM�=������U����-�3�����z��#�k��.�Oټ"��]�C"��eO��4��;w���;t�g��i��'���]+��Ցj��mj~ @�Wܡ�۫���jkPϾc�|�A�׻�y��j>;\�ݩ����[���I�+F����j���̵+�ݙZ*�۠���y'?52h�+�j~ޠ�w��x��?lP�=��|�A<�`�^�74(� ~�Sep_{O5Oh�����05�g���vU��k�rW?5om?3C��s����4��ď�����P�Qq�� O�j�W��Àj����;7U���m��_R�U�jx5à�o:�;H�W����j�� �t�� �[����������{�M��	0�w�A{y��� ���?�`)4�w��Ӗq�� ��6h���8�؏~�a��[���A>|��A>i����|�A�z٠�l��C{C��N�~�� �56����a�w7��Ĺ� ��d�.����AYb���@������/3���3��gkc5�3���k'o����F���5���c�w��q���O�m����� �<a�~�n��4�M3(?Π|��ʠ?>h���-� �a�O��W�s�A���w�A�ke0o�aЏ0觡qr� ��a�A������}�V~xҠ]�2�O���� _�1�k�1Š�?�̫�kWc���<s���BW���:�1�A_o���`�-3���n��e�.���@��0�/�<_�`Џ3�#�=e�6���7�O�vof0�=c��b��ޠ�<o���J��}� �d��N�oW�z�1��G����d��O��0��|iP�������8�cP�e�_�=���t���o6(�n�v�nϹ��n���L�v�fon��C��?5h���43�'��Q��{�A;�6��P���l�~��A��� �u6�[������]���D�xm��f��A=g�à��g*�}�onP϶��� N�ܭ���/��H���֋b;r��T�Y�����[��[��?i|��n0\��[hy
����Z���v0������q��K�h|��~;���G��f����
��]f�s��-5����j����R=ǎָ��|��C���x�n�����������m�?A�Ÿ/dc���40�y-�?C�ow,�nX�Sr��c}.�I��@��j��/�R�A?/��J=��z���s�<@�i`����Kㅸa&\��P�_����i6�����#��z:k|�!��a�����-oo��v�'���>�`�[��q+��y�o�u�v�h��P?ׂ�'��>�����8l&�yA���'4�vh﫭Ю=Z�1nû���b�w�?��o���W�qw��u;a}�����}P�?U}��+��쏅��~~�M��jW��:�|�.X�L�c�0Ub?��H+?�9
�o�Mk��;`|>����o_b?
����f�3��r�]����'�;��%]�7�r�i�G!��!�!�p&�'���m���ƭe��3�u{�����#П{�<f��|�V�7���q^�Nη�c���]�%��>X���Z������ho��c�����Un��Ѯ���|�Jk�3�5�A�cد��������/��n��&9ox0?W��|a�۽����v�~!��z~�+��8�{�<N�a=�h��z�x�߫�/�����������~(='�� ֳ��Z�o�^)��q����c=K���]��q�ʴK��5���9ު�co"���o�u�~C�[ �J;��w�ޯq�El��wh�Ͱ��|X�Q�����oG�̗�$6����K��C���7�|��o�����¥r|n�|XH�as�/����_��<����8�(�y�s�}� _���.����8����M,�r���=��P�񭬟���������_�����?C0��N�����D����x;�~�>��w������7�<PJ�%8�M�B���`�~y����]ӵr��~���=�L7�n�o��@/}����O���c�{1���<����v�ļ]~N�Q�E�*/�vU`?-���8����Ǘ��'+{��p"���Q�?w��#��31o����x�E��o��,B��8��/�8����Q^ү�b<����W����
��}�����|�����4E'��.�?�~�x�{c��d����4O�W۰���|���o
E��,�u�������%'�!�SQ����Կ.��� 9n?���I׿C��ǈ�rR�uK�i�Ɵ��9�������w�<�/ƼQI�_���G��&�=2恰7�r�����R>���9��+w����2}��y[n��<�;9_U��i,��%c�X�yc���+����B��|R��?�����sh4>�V/�ǋ��K5�U�w���������8�D��chW�xٮ�X��W5�@,�c�sD�<������[?�G���G�x�>�G��7�-�Uo�]��~��0N_/����]�<�
�w���x,Η,d<��)�y�P}<��f:*�SY����1�	��y�Y�3?k��yD���s�>.�@�E��@���W������/��5����1T�o��q��]y�ǵ�D�?��eǸ�(��6����ذ��臈���B}y���u�Y�_7�������y�ߘ�
'ky�?���~Inߵz���)A�?�b?m���C������ܾǰ�Ӹ���B|��n+��՘����_#?���M�4
۫|����>_m��,?�=���9�¸��"����|�C��Ѯ�#2��O�z�����qIjP�^������|��������{Ļr<_�<\>N�K^l߈����j/�9Tηb����i#�9���<m����KWlo9/��R/�g��zE1N��b���<DSl���[o2N=����;2�G?����+�Q�de7a9=���`}\r�^�R��8NM��?_��cG�G��>��g�y~�>�V�s�'X�",�r�<����;����zܒ��F_����_�o��X���W�s���ӟ�1?X���9{q�mi$Ϸ�����ߵ�y]y����B�k4�y��8�(^!�7��;d��;�?���k��@���SI�ϓ�[�D^���{�2y�x!���Z+�v�����r>�ya��N��́��1~Vb�+l��?�u ,�{�\�S��o�����s.���]�]�"�&�M���_�?���C"&��3a{����q=hv�ԟ�����n�����/����[��G8o��ػ??m�����w=�`��u��?���߳��~�O�����B�n��)��_��<�O���kS[y��a��$y�{�=By<��N4�?���-�s1�/K�ܿ������y�����S�ûp����&�����F�G^&��������{1����sl���$n��xZm��Ӧ�_Ӵ��㯞g6����q^�A�χ'a�r����%h�q2��C���~q�/��y��O�O',����;��0�
1��yŽX��EZ���o�o�G��"����Ld�i	��{��߾��E�x�Go����܀�Y��? ��a�>b �]����ј����}�U�0Y?�Kѻ����z~���"���9���zl�2y��1|/�?\���c�<�3���2�"T��d>������*}��F+��j�o���q���H�����^�ii�!�)ǭr�z�]�=5������,~E~���:@)YH��]�췟�u�!�����<߶���@n���'�r:p�&��1�˿��|���O>���k!c�����^�^��~dA�g%�w^\~y?}��vi�+�7l�ܾ�ݫ���ү�8�<���㩙��>�����w���_�_���x}�n��9؏L�X�3��yf!�[e;9�>A��a��g����G�9}(�k�.��������xߐ���nџ_�zi#�3�$����"H���)�>��r���#'�p]����7���5�^>��D@?��&���n��{�ϧ���/�ۋ�g���u�=�.��xލ�*��$�߆������z�����-1oW��?�8\��[������[���n�o�rM?A��c7� ����y�����q<D���~�?�{��8��k ��M]��_���u��W�<����Ծǂ�d��?D��<�=&�{+�_s���`�3b�'�7������M�)�>�]��#�^�9̇�$��p�`yH.?F��$?�m�����l��b����D�"���$@/G+��N���;r޸��Y���`�+�'?���׽�v������O�G�	�L';����o՟��ra9��<����s�r���a_��Z���<9Yߟ%?�v��՜l ��;9\��h|��W���k�cX_�y�y��~��������}&���d�<WoK������܎v��C�z]�'�V~_�����pX���ב��}�_���ԅXN!Y'y��h����c>Y/����%���m�����s�����V>N�M�_TΕ�W���`��r�M���m����g$ϳ���Vd<��<=�����U�r������d�s�	�����9E~^��KѸ�f��^꧿���� }�D�n��1�k���~�qh!q�����*��'KI��K�M�ϟ�:��m�}5#p>��1�sGTTBJZj���tGE��&L *��%�]n�s�c��Rm�c�&۴s�3Q��1Q��Ԙd�&NL���zc�c\.���H��kw��m�qQ�i��{j��iOs��Y�zv�ؤ��Ĥ��{���LK���zR�gZ���;�]鴧&����T[F��J��p�R���S��u�esG���$�i�RrZ�����)���H���?ӣ�m�	�D�f���K�:	�4�Cef�9bZ�k���șx{2k'���I�#�<����U7v;cR]1�n;�����*�S�o�qI�vKE;����X�Q�-)�㴥��1q�<.7���-*->��N�J���2(�Ƹ�]�_W�ǺHL�eq�٢x,�`����p;�b�Θ,^�vz^�=�XwJsPz�i��d;3���M�;���Rc���1ܴ�t{\�YV�=���"�.O2T��ә�4P�M�y��x{\2�:m�<[�;ʓ��K����]��XM�'�k�FUKsp)*���gA(�Ƚ��Dn2{*KC��F�j�v��i��	����0������8?�I���X�Kv�[h�'&�o0���`0&��Ym�����չ��+�a�I�%�W�U�U
N��!���r�멼�,�Q*&��^�Z�@m1�뼄��'w�⨨]��9�v��Θ�oj�bg��N9mn��#CTF�3;��䴴$ևn���(�INN��L;[UL�ʰ�����=Pl�vrZ�.
`�JKN�	�	+���|O�3��z����Ipj��vW��ΎI���f�3���`=4�`S��b�1���N��%8h��d����<[B�3�����<N�&�#=&�CRDFjLJ�iW�iZ���ygϸ�`Ϣ�
-�ի�枔�gV=e���R�����46��I���U�\���?3Kt�@cy��Wz�����c�x�i	,"\����U���ee��$䔴t!ŧ����Y|	lv��ʆ �+*��b6�r��7��qBOJ�%; /�9إ�<$'�pM.zTI�'$m���L ������Y�e���S G�;Qg,A������8�>˫�i]_�к�c�Yc
�0@��q�H[�=S�o���l�,AjÖ��|�S�)��T�Kl�#L^R�X���1�9�7Qԣ�ޒ��50�V��~l�Z�O��Nڒc.�>�S��:�-Na����T��2R!���b����+�yh�$�i<�k�$	׿����Wıl��;o*�=9�	(�(Hv>ֳ��AN�j��\î������<6�v����5;W���[[H�;����Sս�3'�q���ޝ�mιi.e7�Gwi�6�V`��I�L�u�.Y�!��KR����*b�f�j�U�D?]�������$���	)3������O����4<	�?+LY��<�8>��T�i�v�7+C}.�?���*�
�go�����i��;N�A���]�3&�@G����d��Ә�k��9�S��ꝭ�H]�+@�`���E`��ks���$��͑��ܣ�:;����d��$R��u7G����G������lL\�C��>fJ�T��LBC�q�8yf���O�='5��僣���`N�Y�u��͖逜����Zė	�!Ad�ݵϛ�X���b�4V,�j9W����=�֦#�f�"H�1.N�ah�ﱱ	*���풦6������Np���8�,F�,��8��IA~dם*'��$�,d�k����
�;�邖x���q޳j�;���Rnʻ�ͮ�j�k�R�t�C����RI�-�æ-1�	77E�ȕ�<EH�)IC�:Ŵ^;��J59m1�8W����^��|*�Q��2K:���M�Q������(��ȗԃ0Gaq����8��<���u�lᒛ���wc�l�?��l��d�ǔ:FOX�t�d����+����4h�T[2{�gb6(�N*�mM���뉏�9ar������O�Q�x��Y���'�k��ŉ�+���S�:kb��	�4�f��5��:�^�g�K�P,~�>/c���ݝqq�d�\����li�,A�ޭ��C7<�G���tmw�_��U��ۖ�ף�*A�U6sq'�O�l�1��J�8=��.a�&W諿�5�������h�k����l|���z��/�]�D�`�k0�5Zÿ�tW5�5��On���7���l*k<�5���i�фV=�5��N_�&�t�j0�<�ӳݕ>8�_�qi����'�[F|�'V>Y��kaM9N{�.���]�]�*���uzyQ���{�r��h�^�cO�q)Y:��X{W���lŝ�P5^��[�A������k̺��ŗڅ5H�0���̓�V�t��+��ܖlO���1�X�f|�]=	�_i)������/x�@Z�̈́�)��|��ƘDf�CS&�����[��� ���)����^v�-c����u���tX�q� �3}��M�?�I��p����������$�������>�c��l&,��_���5�G�*-!��r��{%��GJ�z���B�x%� Q1w"K}n_�N��y�������1	��}Dc�f�f��-5s2���7����N�/R�@j�Z�6Wd�vS�Oh���L!m1�QBx#v�����>VR>��i��'�� �%�0�bд<���*���s&xh�(��Q[[d�g����4~^����3��� Y1�$v۸4����i&�+ƭ�������ʭ���Z�����]]u�=)�v#"|c�E%��%a�]In��i�5?�M��M�E�N{a����L[l���.�}4�ة�Zbq�D6"H�}م��o���,�Ra��'��洮RNg�+A��e�U�;Һ�����D<��~��lk�C �G����[�Sg2Ez�#�&�k9�)�a�«R�Y7�;���'!�'&��|�nI��`��d�V$���Cj��Z�"�Q��Fu�|R�Ξ����_��D�Sm�4gҿ����^��&��� �Hu�p��u�����tU�2��*�t>Jh#����
�|%�0��i�ں��z�
��bI<����
�0/v���:n�����m���M/B₫Ȟ�zK�7�����B�O"Ĥ��z�H��O�;����(���M�q]ċX؊)���'��k��d��.��xF�:�9r���TQ}y�Y��K�B���ؕ����:k���θl�t��������I������ʵ*&��e²���-�A�3ut�v���;-���Y��ڼH�B���ۺ�"�ޫ)F}�r�����MB]��!�u>��E�ښ��Z�Т�����õ��x:��0�3��������n�zS�)���)�jӍw�(O>�����F�E���(�^�7%��5�;��3��r�%P�M,�޾�zw��o�����I/�=3;�-&��Z��|g��V�d��	��Z^o�/���J����W�7ӏ���jA�%l`�E4�*�X�ŤH���|�d�᰼�lO՞Z�M��J,P�:8�cbmu�y�CA\sV5˿\b�T����=x�Ю�n�mԥ��j�QoY�$	Ee���]�4R;H�ᚦ�h�4�(?7_CH�SlNȉt���DwhuԾ��U?�ם6��7���ށ�5Vm#� �ei�Po<��PMOD�( ��7 ���u3RBB]	�sy�~�/��[	�,�6�TL�"��]�� ��P�wx3�s�{��QNf�Jj����&��(b`�A)j�+��ɡRE=4�5��rY�P����3ff��_��2�$�VJi�k8�e��mW��a]����m�SL��u�z���8`��럢�.� �i�B��
�h>�Nc>¥s��1�$�op�pC�Um
��R�-�I:bA���$�;Jm�B��YgK�� }�4��!S|�"�)�jз�xM����/��<�D,�'���8�b2��ހ*��7O�ͧ�9�ە���3�:8���z�=�F��37)��&S8��>�x��ݪ���2�m�B=����c���M��v7l>�Ma��m��P�p���U�vI]}F�=��
�����q�m�[�bb�]_���giN�I� ��z�q�Y��I�1�=���_�οtÞc�q���q��I�1�47�37�27�1��&�A�)���h����(���%j>�5T��Kq��1�m�ng{����$V�ܭ,��aC�-�f\W}n������G22$���&.�M�ӟ3�_�2�L1m��	��ӂ! �ڬ�$>��;��F�W�^ጼ�V���u��ɴ�,��O��n�gr�d����l�s�X�I��6f��G�_u�0w濬�<]����)�����cq�(>IM�^Q@��f6�esVg�;GqG<7���a�+:i�I|KJ_,�W�|�*���T����*LL+��u�[�/�^Lg�������	��>����u��Y{z�;$���k�X��`��a~U~��`��IF����wH�_j�X�W������hR��)����-
�k�����ψם����+��������N��:6��J2������@�	U�������:��������������g���e��1���������sYk�Mߣ�� ӯ({���^���6.�����
��M���|�]�0�#�[	�s���#	�.K㉄Ǣ~&��ȋ_y��K_��e�/G^A��A�����C	y8����i�A���o�rry�/���_A����#�-�5����g��w!&��u��>��A�D�?���/u�~B��M�`�~
�K���$��?�7��$<y�ݑ�>��O8������!���$܂�E�%����e�F^A�X��[u?>y��2y0�su�nGN��=�o�{P?��e�?	���I���!|���O���Kߥ���r�������_u�~Q������Ox�0�?ᕘϭ����&��ϑ�xΌT��A�%�����A^Axo�>�#�!|8�Gd~�`�'#%�Y���@n%<y$�/��)�ɨ�I��9��B^@��E���Kߪ���wu��S�?�u������$���'�J��Lu�	'����oE���O�-�3	o�<����p��?�P���F��g��Q�L��-h�z\&|8�7�p+�p��#��{���ɺ�	�F�L§�~&�����Gt?��7��𹺟	˯ <�}���RCx�=*�����/��O�d�'|���G�qI�:��������o��O�o�_@�k�?5���]�'���������d|DL�_�?	��Ix+�V»#�$|�D§"�$<y�ː�y�ې��r�l��0� ?�Q�G������Q�O8�t~I���y/���so����ȋ[��wG�2�!� |r��k�EE�ȃ	�CJ���ã�qe%|�>���D¿C�I�y����@�~�"�C��~�2§"� <���L�5�?�<(Z��!&|+�P��#'�;�V«�G��5��#�$|0�§ / <y�.�%��D^Fx�
��D�#������cd���3�P¯!'�U/�?ὑG>y"�3�g�<�p���#/"�-�%��G^F���+�F�#< �[�!ȃ��<y0�S����<��\�V�7#�$�C䉄G�I�o�s�����}Пs�!�?�����rj�<(�<�"&|�P�'#'��τ?�����"O$|�L�s������@^D��Kh�u���
�w�?��#����/�����u���7��C	�y8�w!����?�P?����3	��<��y�_����ǐ���9���~&�j�3�/�~�M�#&|���g�:~�	��םo4 �L�}���d�6�:^�o�~&�D�3������¿@^A�	��6�z`�M����e~R�?��8'�)�K8ᝐ[	CI�H䉄OC�Ix��S��y�O"/!�U�e�������}�W"�!�Z���u~¯��$��>$|�>'���fnF�����~;��yI�z�-#| �W~�D�^4I�f�/a�	!܁����0�^���ͨAx)�G��	�����0����>��B���_F���	��o�=c%��X���_C��7�e]�7���		y(�������[/C}+��߽%<�&�,�A�Y䙄7��Bx&��O���_Hxw�E��@^Bx�_J��/'|�
��|�o�_M�D\0�#�������C������'�𧱜pZ�\�_��'c;~G�_���~�<�|����/���_ńg�~	ዣ��^��������w��$��[�X~h�z�E8�>Է$��cDn���0I�O#��/���$��E����8I=n��|�9I����^�_���RM��k���$�<���d��V½����7��M����ޗ�I���d�~�|��~A�zK�P���^�WQ���^S
y�1����'Lx/�IQ�	#|4ꇧ���X	���)j{sw�~~���B��P�(E�O���B�/MQ�)'|'�W��������S��mL�2?��W�z�M0��OB��};a�G�~x�zߎ��ԏHU��&�%�7��>�3i��{	�@�Ox֧ U�/�������T��Ex
�W���4�Q?(M�_(��gP?$� �^��?� �����4�>�L«�|o�z?I>�c��/#܇����$�����ߛ��&�š�ge&��;���B	��a��)�3P��P�㊤�~�C�_�A�b��t�����������oA�"�z?X	�{Q�ԡ�'VNx�W8���|��G�j�z_�i��ރ�q�z�Y0�Q?d�z�*��~�>_�?�J�9��|���h��Q?q�z?[&��>���u�|£P�`�z�[�Y�_<_�/�����_6_�_����Q�r�z]5�Q�f�z]����Q��T�!��C����H��P�Nu~�~��8�����a�_�T��b�A��z�`��_n`o���cG}�Kmoᯢ~�K��0����oq��F�=�G����	����K�o�K�9�˥�X@x_�/t��nE��z�`�q�_�R�?�$|)��\�}�5�?��&�z����7P?ح��J�^�s���Z���n�~�H�ϡ~�[��A��p̫n�>��;�~�[�����0�/r����>�K�����G�~�[�o�G�������&y^��(ȣ�Lx��Q��#|3�{��c���B��z�h4១~�G=��$�W��z��r�	��<�}\E���y���[Jx_�/���V>�+=���մ}Q�ƣ�7�N�����C߈����}�ᄿ���t�>����~d��z៣~~��zῡ~�W�����t���r��݋혮�/�#�?�W���љ2�s�e���������_Fx�g���Y	/�����uфW������L����ޏ�O��S��ާWD��/�P��+%<��2���*_����P�{�&<˯�P��$��Qߜ��'Bx�f��O��2�ߒ��/A�.ԏ�T�cL$�4��L��F/�?������X@x�_���YL�%,�$S�O���H,�<S����#1d��U���MY���f½X��,�}���~X�z���rԷf��mF^���Y����a�R���!܂��Y�����;P�(K�/����/�R�-'�~l��,�>R�X~u�z){А�sQ?h�z�i0�A�1,P�G#<�����Z	OD{#���F��'.P�k�$|��]���Ox�_�@����b�/^��[Jx�-P �4���~�j�CQ�f�z_J�B�� �c^��Bx��P�/7�p�[���F^�����x	/G}�B��^/�5���P�ﷀ�0,T�.&܊�%���˨P�|�z�p%������^���E���f«Q?x��>d�<@xr�ȭ����#	/D��E�����Q?s�z�s�5���H�����H�����J��~�"�~�r�K���H���G���_�H���X�P?l��y�Bx#��b���"	w��ы��#s^������/�!�����wVHx7��b���J������S+'܇��X�����p�#�^���k3-!�������Lx4�,Q.���_b�=&�KP?b��{sфW�~����2	7�ļ�D�=�|�-�_�D���"�l��%�	��~����K��:Q?h�zQ0�Q?d��{|a��A����Z	��#��ף�	OD&.UO0��|�����o�O�9�O�R��ń����˗�/&�6������>�o��/�	����oп'Hx,�����b����%���	y�W��o�/���&�y������%�"��"/!�O�^����	o������> y�W�=t�2�OB��e���`���L���0!'�y�V·�����ф�"O$��L�A�]��^|>�W������o��x��{����!/#|"�
�g �\�^�&��W��ZN�C�����s��X~(�����&������G~H�=�O!O$�"r�r����7���`�(ᷣ~�r��bU>�+��/���P�f���he�|���l��k���������
'�qԷd� �e�wd� ����V����OQ�0[�=�b�O�~I���/e�_A��l��b*	o}��l��ej�����˘	7��<�B��J�h,?l��{7�ñ|�
��]$�s������8_���+����!���_a0_"��/_a0_"|��^+��O�!�k��V���h&���T�1�p�q�^+��s�~+�[W���Ix/ԏ^������Q���R�=���~�J��(	OG�����W���KW��wYN�K�_�R���G�Nԯ^����iY'A��U��o~�CV���Fx��W���i%�3�G�R4��!���J���L�'��w���:��Q�`����E�Gb�)^���i)�^�/[���i�E�_�J���jj�׬R_5h5�oh�y��{�!��`�����o'|�oY���k��~�j��a	y��j��d��[Q?g�����;P�p��{�ń�~�j���^�����í$��}���ϭ!�4�@��{�f���s��K�Y��1�_n�b{�̯o��99��X@x�/�Q�E1�Q�$G�;e��B����WT�D}_��w-j_���\��]�	��sտ�Jx�CX���1,������͈$��G�O�A�����k�;�[�������($���۹��@	�}Q�4W�{�ߏ��������չ���0�!y	��֨�#�����F�{ a��~���X	?��kԿM���kԿ+�I�ߨ�]����|�o��y`��wH����kԿORJx4�[���T�E��5��3�&��O����� �o�S��I�v,?4O��(ᄯD}K���R"/D��<��{�oC��<��o!��ho�ǰ�? �6(ߴ���"�����w���>y���߻ �a�V�c�G�տ/Fx�'q��?�����Y��@�O���y᧐�U�ǖ2��~�;��E^�������J���X�����ɼw���7��j�Kx�]�9�&k����8��^�@�T?J�e�>	7���-���E�v�����U�x���<Q���h��<U��_"�"��x���x���^!��^)�?�x�_�x��k��I�w���B.��2��͟0���"O���]�"�Fb�
<Hl_�7�W�M-�b������E��o.p��[<G�f1~�R�o%ƕ�[�q%�6b\	���K~��K�A�e�(Ƨ�;��)�����b|
<D���,��w��:~����U�f�wx�����/���x���!ƿ�{��/��b�����+ƿ���_�ab�����/ƿ���/p�_!�� 1�>X���_��b��1�>T���_�����1�~��)ƿ�-b�|��#ƿ�Ǌ񿾎�'ƿ�ǉ�/��b��*ƿ�'��/��b��~1�>I��? ƿ�'��/�)b�<B��?(ƿ����/�ib�|���!ƿ��_���/�H1�����)ƿ�g��/�G���l1�>G��G��/�h1�#ƿ���/�X1�'���:n�_��b�<A��'��/p���'ƿ����x��O�_�ib��!ƿ���/p��w��/p�����/�t1��!ƿ�3��x��_ ƿ���/�Eb�|��_*ƿ��b�|��_.ƿ�����
1��R����c_-ƿ�s��x��_#ƿ�����:1����\����/�'���z1��A��o�_�O��/�����b��@��?#ƿ�7��/�g���sb��y1��1����/�_�/��/��b��%1����E���*ƿ�_���:^$ƿ�_�_�[���b�|��S���%ƿ���_��b�|���.ƿ���_���/�b��}1�^"ƿ�?�_�;���.1��[��(ƿ����/�b��T����_�����1�~P���_�����1�~T�����11�����X��"ƿ�?�_����/�r1����?.ƿ���_�_��/�����b��1�^!ƿ���_�'����b���b��1������_�?��/�b�����Y���"ƿ��_࿉�/p����_�������_�g���91�~^��_�_��b��w1�~Q��_�_���/��b��/1�^#ƿ����/�b�����[���#ƿ����/�b��$�W	�O���x���T�/xC�����+$�J�7�O�M��y�7x������֫$���f���>���d]Y���i��`f7�d�nt���o�;,�/.�qU��_�\�%V��|����AU)�Ǹ�_T�����AU!�;��_T僼����@��-\��� y3��+��h�7q�/�WE����|ɿ��.���0��s�/�W�����|i������!݀<��|)���:��r���<��-�~��r���D.��A��6`?�C����?�ہ� ���`?�]���ܞ˷�� ��r{��&\� �����`?�Wә�	��"�o�A>��;���|��!`?�'����8���� ��`?�����y'���� o�rw��-\��y3�C�~�7q���z.��A^��^`?�˹��y���� ;���y�������r��L.��A����`?��< �y4��� �� ���\��ܓ�C�~��p9��=���An��`?�M�<�ٟ���~��z�<��"���A>��`�5h.[�~�Opy��q.��A>��1`?���<�y'���A���q`?�[�<�y3��`?ț�<�y=�'�� ����`?�˹<	�y� �Avry2��<.O��B�s9�y&��A���`?��<�y4���� �����\~��'��A���H���\~���g�� 7��,�d.?
��|����`?��<��4����+��\��A>�����\���|�˱`?��������6��m\��A������\N�A��e;��z.��A^��$���\N�A^���d'�S�~��q9쯁���y&��� O��y"�]`?ȣ���A�e�r.��� ��r�r.g�� ��r�r+./ �An��`?��\^��|����`?�����4����A�s���|����~��sy9��1.g�� ���
��\^	����˫�~��py5��f.�� o�r.��z.��A^��<���\^�������~��\~�y��/C�s9�y&�� �A����`?����y4�7�� ��`?�����rO.?��܅�`?����r+.o�An��g�~������U'���A������ ���`����\.�A>���~��sy3��1.������/�� ���+`?�۸�*��.������E`?ț��:��z.o�A^��7�~��sy+��.�	�����[`?���6���?���~�gr���\���<����~�Gs�]��\~��?�w�� ����`?�]�\��ܞ��� ���N��&\�������`?�W�3�C��\���|��{��K��\.�A>��}`?�ǹ������ ���A��\>����ˇ�~��p���f.��� o��Q���\>������� /���`?���	���˟�� ���g`�Eh.��� ����`?�S�|�y"�� �A��/�~��r�+���\���'���A���
���\����O�� 7��w`?��\��������A����~�Os�G��wh.W�� ���O`?�ǹ|���O�� ����`?�;����6.�
����˿�� o��y���~��s�4��.��A^��`?��|�����`?��|쯆��r5��L.���<���~�'r���h.���<���� ���e��\����k�~��s�
�r+._�An��k`?��\���j���A����`�v�������ϡ�9?���&��f]v6ߏ��8k^@7��f�]�5��~���,��,u7�����&�-���-�u�����:{��m�8�6p�;�7��D벃��Y����C{E��+�AVa�@�1�ڣƚ��5��yz[k^��xmY�����-�`O��U��"��-��AM�����]o`ͭ�����~~��
{k��]O��8��n=wY�G�f�"sq7���̸�+�H�2��>XȀߥ��y��O�H��i���՛ݿ޿�y�|6�oX��F
��5�_���KYs�w��N�>�A�$������5���\��e�>y �8�k����|ac�*2�k4/0��
������t��[��?��W�gbw;�,ʮ��~)����Zsˬ������������{źnQ��zu�]�ﰨkH�Pw�P����J�4W0O`Ws�X��Ϟ � +n\u�sm{�^�>4��X^��+7�'��~q��W�}���S�ܫ��#Ap��5o�b��@p��;��u�1j:��?�X�T_�7���w�܍r�i��!��_��;�=��뺘�#�}AY~<�b��3{�O����@6�d��o&乙�+/�;����~���߸1�k]�=�Ѫ$�t�=�v�ׯ��G��=�EX)�Y)�n�^��3�s��׈����x��ɷ��M�f0S���;�`a4!��{�5����%��}~�r��;����CA���a���e�cM'�^����ʚ} h�=�<��.�j�s�,k���`��Qs �Y���������o�S�9��ܙÚ�����������S�/������/����S��	�D5�]��CP?ױ:���'��HF���,^�i�ҿY��.8+�wӥ�5���-����Y�������!�׺��״+�C���]p�9pt�3��o��sG�Ϧ��3?'����Q��Έ�z������M����J��=�{.�������ծ״ҙ�,F�?�N�!��r@���Ӳ��_�7������W���? v(��|���o����3��mU��pg?p��b�WG�^�;-z���+<������su��<�0c�l����~�߆#u~����?<�N���X��s�xô�y�n�����/�{M���{*���j�w���w��Q����}�kU8��{�=g<?O��˷�/��̎P͎��~��~��|L�XLӬ��|㙗����lF�8��/�OV���O+�\#�Es��W�|�X}�]\Mx��w��F�ͪz���C'��=-�+"�Uf�w�;���1)�I��l���#��?�<��[m]y�Ŋjm<����}��C�weW�����Ӿ����C-V�ǎ�ߵX���Z�����ug�L����L���g.g����3��>X7Ə��5� ?��;��>�{�52��Yv������}�e�q���2����*�2�;�DXUz�|��	��R�A�����/��U-ى��]>����\5��g��Q�����lY
6�K���<������v���\6�8�Z��q_�un��}���.�p�^��]�<��&���ső�5�F��/�/�b�u��db��{��֣\�/c@���K�}y��{/�z̑�|�(ںb�H��X����z�t��v��I`{[���0hR�+dR^��w�2��P�[0��^y�MAY�ySYu�
�~pRn�/k$w�߲?����ega{������<Q�\ ���=����v�?� �����V�Vu���V����?��m�������2;�f�̄�{����mY}�^{���-q�1;�}�y��[�U�f��@
�M���ݧ�a��?���8�Wv�΄�ZiX}��?r�˳ì�Y8_�[j��}F�Ț�v�L�J�:��q�*b۫�G�X��Z�ְ��}�,Mz��7��h���.�d7d���&��6x�����+V�UGx��o�Dq�Ŋ���[������]�����I�A�t��3����E�|�n�yA��X��<X�b����k��Y�x�7�+O����`~9s0��Ʋ�jy� ��VuGp�	y��rO�amR^�r֪�i�@M�� �^
֣k�YHP��O�[b���u�젌w'�ϋZy�s�Ӓg	ZY깽�e^���h]<�U��g];�s��ݙ�Z��2�u����B����kG����uN�^+߫�^~��׈����H{��Ij�v���S����Tk�2i�o�^��%�Y-�WCV5�Q�^��륗������&��k�i��&�V�^��Kk$�m�
Y״&��"�j�m��^_�"�|	�H���_ڣ{����uV�n����Ǜ���;I{��ꬷǪk��������Z{�L��%����������jl4ל6Ek��Rs��u} ͱ�C�9��iͱ����9�cNP�{��.�\��c���Z��;��|��0�5�ߝ��8�ђs��}�?nc����j���A���� LqnY�r�<�N�*?�$|{򧯙��+#������7"g����fB�>N�6�mډ7�	xiKy�|��S�U��]�ϏE�4��q0����M�l�U�gc���ֻq����p���=��u����K ���=W���V��X�����!��3;��w���zw�����3O�2*k�X-V� �C�mͦ��@�0�@��}�|�<�`β�m����A���5����S���ھ; ���Pɡ�*Q�b�`@ 
[�`��-���r��y{���b�hlh4��ǒ��&��xwf�)�=`�����{��������γ�����kUL�=), ��H���:$�������݈o�}S�w>��P�@s�n:͇y�c̈́���U�ԫ(��h�	޵ ��O�? ��'�3#0���z��K�#�|��Q�پ�(�����ۑ����z�`֑���r��N�巰w@�9F:�-����`�\�Qa�Id��
�b}F���u��1i\����b��p/� a����<4���{vK�f�Bq_hO�����p3��TA�T�>���[��h�0>�~\}L86�!5�x&�z����e��F/P�k���b5#�[�72Q>:��MT�kR���=c����,���e�n�1N�D�|�{f &�rx7�7=6���=��6ͽ�B���Z���G$�G'�Fr�����p�I���;�����|a�{f�.��%QN���>�ο��Κ>�I��V5�-xy�k>�ug��w�q����.17��O��y�;����3K����z4��T��!m��� c{�-e�J6��m;8�^S��{�_���1��2ﲹ���l�����
?�K�{�8�e�4�z��R��s#p��J���v�'
#h�V�I,G>s�Jx�k��4�ܴ�\�ɾf[>,4�H�f����%b��u"b���6ޡ���NL����Q��]���R�hz�B6�]4i�X�mP�;h���oa[��ݦ�Y)Y�Q7��-Y�g�˙|h; p9��Oc��^�Ђ�t����@R����T(�����8�dE�o"a�ݽd~��\�a;Ao�T����))p��0WM����!�9�pbPg�)��(p�^F{��-=u3�sϮ���]6��U:���i�9(�d��9S�vW�s���,�:�� ������n��Vk-�8�Z���=�?��0���^�����4$��%��A������1ȸ�Ay�ݫo �C[S�Q�1z��9����B�8P�~����l��S>'�%[ϳ����rUK}�mK�3��������Gp_ҥX���8L���c��	�;Pu2�?Cb�?52�ek�����cOo�c�����`Că=ă?⃟xH�Fz�O�s��V�sZD�Ƀ?��>ϛ��C�y���<l��"�RDE��L��%��7����z���e'�K+�$� BE��X�C_G��˃�C�0B��=�o�+u�ݤ0������H���?AH�n���Pp��<v��n���8��u>�ʺ���`���N��v���gI�q��o>����� ��&�[���[w]o�cج8]�o�}9�R�	GY�h[�$*RF���҅���H]$҅�!Z(A�̫� �>q�5����f�0���hL����߈���&��M���K��� +E>;f��?Pk}�]�~�G;`O�
g܀mEo��5~�|A�#�Hr�'c ��z
Q> ���ؿ�y�;�'����N�fH/�"�5�_��n���}�W;E���_�mU�(���_86���ǃ�i7��G<�{������hw�5�è���͐��E��q�����q^�Լ&��Dm� �����\��y�-7����	��ٿ�gy����ڿy��l:do��;g�?��u̫�W��U��~_'��`����;{]�_�k�?�����4�v�\Q��g-��M�|ǻɆ�5Q�F��΀+R�>��N��k�[s���~��}z������S-�z}V�WO��j���j�9��~����|�_}C�U�3��J��v���_5[g_U/���܊���q^���1~xw]�8��99��D�=^�<��E�h�sr�U�OS�S�W����r�U�"�^+`/Pz��r�ZX�/�qd��0	<�V]��?Q�o���� ��t)�7̝�~	?s��Q���9\�J���S�D(�A��
����i���
��C�ؠ���סt�7��%��Z9o���ț�qM���:��Ohe}ɕĶ�&��,��x���9����N�'��ܙ�m2@H#}���/7�k�6���k��9�'�p%bb��_���r�L����#8�Љ�[<^�W��30z٧��w��K[c� ����D~�Oim-`V;��i�������Gkl �qV��A+W��3/�����A
�3���[��~�$�t��LL�1�R�����:q�l۲�XLi���۝��Jvg�.CO��7�Ed^����-1>��;�>ȿ��Bh����f��?s�P!0'^��3�7�y[��&�LQ��,�O����}!��B;~
��y�i@�q��  �k��a7����ߧ_�w�$���'X��*1�uA�Wٗ���Kb=�Kb=�6]Ĳ�t���E��{0뱏n&��t����E
[zI,V}sI,@��>U�?�n�����1���;ky�V�|�S+.8a��Hg*y!0>�.��8���'��N!Q��2^'�x=�5Ա�d���7���<JgsOH��v�c������]-JhsNإ{8�+�Jy����!xj�!H��7)L��Ѷ�D��`��9iͳ��&��H6��	Gٔ�۫��`զ+�&Y\�Y?��ߑ|ZSW�R�1�]s ��C��^('b��#f���8�1u�":\0F�{�{����A�t�sRR���F�:+���M垞�����r7�+R;>�zNd\��V�^���w��US.���?�xÎ=���5z{Z��?���!{�f9���gr��B?��c(1��:	���Pri� �y4��w��'�;�����_�%T'�f�#ɟqΛ%���r�Ra��o%�#D�1O5-�E�gZ���Eg?�;��g �����Bw�g�&�b���8M�W9�)��S�=3�(]X��0PI_�$�i�JQ֣����[�<e�֟ ٘,P����^=vM���+g��̏i)L��G�����N�'P}�j��+�j�����֒Y�T;5���Ѧq�u�{��ԥ��V��P��Az0� ��&���
'��~�w�7�ٔ��xc�5d+ܮ�?�q��Rl)�YO�<s:$�!��R�ү=�e>"�B�(�n�T_��������M;�y��-u�b������aW"���������>�"l��z���=j��qs	����gˏa�C�uvX�2�^%j�����9w%��	OB��Ys$��o��R+�Hl�N�r�B#����.J�Dx���$~
�G~.���� @��1�ƿ���[Iw�d��n�"�d�3������?G{"dڼ��i�I:��@�R�nD�Ӯ�^8��U��r�k�����Z.�kYo��{���$�9�|��������B�r����I>����th���(���Č��&v�&��h�͹���&8�A��#�������W2�U��({�)W��(��VO���9(7s�\PO��B�N��@���2x�8A:_��t"]HO:]��*�O�H��U/eҳ�I��'�� m?�����<	��rPn�L�m�r��ꀪ�h+���0��N�D�d���������j�h��T��������P�P��P�z����Y���sadUC|��gh�r�bZ����T��~��Q�*G�T0��c�w��ή�������>��\l�wо�)�'=2�;��}��H>?��w��}""]>�P�[�IxZ�(�L������ӯ��v?Li�Iq�˿D\ڒ7�u�U9 ^�_��.�_H7��g�77�91T���ǉ��_{x��u�M�O�2��'��0�EX�C�ʠRr��#V8�zB�A;�"s�o�
+޿�&\Ͳ�k���S7��h�k���[f*� �q�z"7lYcح��6a�q���Id�ٞ��1���,xv����dq�Gk�����.�ѷXˁ�Q7Vb$�����V��ƒ�U��X$�*�a��/��a�\�Y�#�/��\��;i�ͦ�G��5�_����=d7<D���â)=�=��ZR�Xq���s�1�^<��_�Ra�{�ԟ��,�o*+����4n���3� ��V�ޙmkw���(�_LOD{�
U�T��`���\�|�gj\�N�^�D̠��u>>���]>����Z'�a�����8��Iq��(ځ���"�c����w��-��}�\͞CeK�\��+���p���[l�b���D�S��8%��f2Yi����̌���z�]j�"�^�rD[p1sS��.�d�)��sp������ �ʬ�12u�QyW�c������.�+��GAlY\�q�ռ��;l1v��,E �b���l�F�Q
u�N)0����o8��s��7��;�(��0��i��6f:�9������3j�ϙr���A­뛉}e#2���2��i��M���
l�,l/&l�c?^���bK����8�)�Z�w�f��ai�q&��.l|�j��1:}��6l/�w?����ݻ�.�sX(�!��H�h�}�?�f�������H��M~�g7��Z�ir�H�K�c2�e�r���݇�/�#�A���I.ۼ��)��/�M����J��>��؄��Sf�ԇ� zo)uF���Z����5_`�ѯ���H���%՗�T��Ϲ:��}8qh�����%s8���C�f37�������ذ�..Yݝ��o����qY�BVl���r��
��{��Ƹ�j}�b.L�-g}�gw��`�s}c��(�RA��X�Cʽ���;:g�y��i5�����k~��>��h�2��]�_ ���V���.���9���>ۿ����`<���Lp��7��Z���z�[�-��,����/�%�I}�>�+��*�[��q���ً���l���_�����uP�(xӒ�:D�{�^b��D�Uu�.�
{��Y���Ou���|8���z���/�V[�-(&Y7Y�=|e"~k_��w`�C��gP����������!)o����W��jm������]?:�-�>����g���Yב�%��.�%����zEr�2M�K����K�L9m��	��.�����9aD���2�F��}�m#<�lm !g�NE��W��8�}�h[�QJb�<g";W�OSSX��^20FZx�5�~G�QX���þĨf�K��/B6*uwkuҫ$|deY;�c|E�]�������A�m��!c]o����h��F�t�E-]1�y�����+�?���ϻζs���ќ����rw�v�d	��][@����<p~���y��M&�����@V6P�j���h�=�K��m�R�P�
�O宙�!�+B�?��0�����:������x5ށ��%�'��+��u�mUBpk�b̔�9�����;�o��_�\���}H�YSo��ƽ����a���,��zf��Kw��(�E��d���hH)>s1�5��݃r;�J/��tr���E�ɍ5@@��PhU����B��!D�o��b�(����ڊD��SE��Q;������ي_C��`Y�(�RDv�(�۽�dA���L�si�U��7T�>�F���gx��4/<�߭��W�� J<���Z�9<�ޔ6�R�4i�&���f�͆xx�� 6��u�.���Jxh�U����>ڊx��3��1�C~r�	��a�fg<,�e��	#nKxh������C;���z���������	��hx ���Ψ>I����Wo*x�#��ݎ:���'r��I����k<�}�nW��f�Ո��m�|�ܘ�����x�pҼG��t��h�!�����Zݸ��.㡨�C�o$<4�F�Ê]*|�x�y�6���7�a�Fg<|��)wT<��%��=��{��5�l3�C���:m�� rc��$<xn�� �1c��0{Cx8񓂇2;e<<���|G��>㹎�^������5<����xhL|%�΍�|�[��kr�C��f��4k�3���-x��J7��-2�	<�m��Ps�����%<���p�3��5���o�ôu�x�����xh]�C�,�C����6�a�J�ܚo��P��Kxx�N�������恇=W<�&���q�#s�����@�c���ë��x�|?/<�ۤ��#��g4�!�S9_�W灇/W悇ћT<_8�h&Ͳ��pb�.|��/7�xxW�!p����k5<��"�᭵��ם����yRW;��&C<��T�sU��;���x��ô�xX�\'���2@n��j	����|�1�ozRV假�<�n��p>��SPG��py�B��֯�xxLx8�x��e������/|~�{^88�^�Au�g7�򐽣9?_p~��!����/ρ�x����i�"_ӝh&�+����-��ޜ��Q��,��N]�
p��^,U ����|�|��ӧ+%�8Vj���$燕��W����r�� -ߠ̷��������
���.�$�a�m����O*T�^�
T~�Od�fխ�S��+�7s�Y�z��cȾM��w$Ŀ�y�x_�:�E'�z�P���"����֢\�(5��e+��P��W h�P�O7���G�_[#QT��**~����5�)�t�5fԿ�]���P�pv�BḓK��M�g�Tr䅗�kT�d�B�>������偗�%��żF����
�`�����^:�1�K�E�q�Z#��C���r	/��kx)�^��_��䌗-K$�$��/�˜�ⵆ�K0�3�.���wN���[��Y�|�ԛ!^�=��'�6뒆���8cm8[��1�$w�Zm��:��\%���.���u���ck%�D��/ϖhx���2eva�D��_Cy�-V��vQnx�O�փ_��Mו*n2��=B��
�+���j��f��� 7��MK�/��ԓ�L4]���E4�rT�f�~��Z�M7�5W�%d�n\o���R\�e�	/�%^ ����%��
��P�K����Y���Šܢ�_9Gg�W|����}A����|��|� r�"ޛW⚳?(qME�u�E?���X�M��HN�cQ�w��_��j=~���<P����:9�|-�8�,���X�τU~
�T�H3{�5��ODsi�h��f����Fԣ�GK���Z�{��Th�T�������Ϛ��p�����r�� �ը/)~G���U���6��種�_�������,��?��C�7��������h�c�~�c�<)��,��?��?V��i�����<��'���y�3�=J�2��=y²�
��?H��W	4�+������+�闥(�k��ߛ��Ӕ��|� �H��|e	j2NU��b����x(���	�w��c�o�P�`'N��6?	�:PȂ:�.��@�:jVl�6?	�O���F^�^e���_F~����~~������\���bU�[�ü7i�i�c��%��{���q<�X�w_��c�I�>`����I��f�׏���g����=�s����8����}�)U�ם����%����������@�_O��i�"Y�}�s%}�����7K%}��f��E����]�KS���RY�#�Q~M���0�����L�����Ge���F�|��Z۟GG�!D�)%ڶ��5Tr�p�q��*.�Rٽ'D�'��'8cYme�����s��N-P����2F��'���4��Z�?�a�����,@8���� ���
p�-^ B7��q�%�D�ր�~��j�(wO8%|F� ��@��ה,|�
����1��DV7̶���͆~���	>S�S�<��g�A�4�?9��Ӿ�85qR�ԿM��'.���i�|�s�Wz9Ϙ��s�|ejrf�@�B�=�5�l^��;5��O��¬�}�vtC��%�� j<ʮ�@���ʱ}&a���҆���w�ݚAԑ�����9~�u9/rm��O>&���t$�d_���i���|9%���\-�K���N�e���s��_��se��g������9�;����S�i�4u��?9�П��N�D�#�?)u������O��1�'&��?���+�
O��?���?����i����ɉoRf��O��xe(������)�?9���G��B^���,՟4 ��L"�x/���7��/'��OF�R��;��jD8	�M�o�d�,�~����Β��[xL���l���s%�\��@�u�(OV�f�+�R�
�	��~�?i���OBf9��J�*x>8(���?���1�'��2g��O��ƱX:�򿉐����?�7���D�trf3d�gJ/K����t͟<���!:p"��B�º�z�?���ɟ���:���O��~��OMr�'Zj~�em域���l�?X��y��2]�W{R>��L���䗊@|�P��d�Wq[.��O��5���h�G�{�w�Q�ɿ�����PJc���f��y_��ӓ%������,	6+'#l:�f�M����Nƚ�'��oXi,nwƍ�tr<p����;�b���,?A�g�L�Ʒ\�l�j�T9���r\'��jtr<=U�? G6�.��v��ܚ��U4�	�Yǡl�M���+��`��U{Pk�b�3���/��A�����+�L�@�5���~.~����=��~�Z$v�G#�	�����ô�;r�i r�8z��p�Am����t��5>�<MWq2��gD�u���W.9q��߳��5�߿�e��8Ym�p2צ���4	'�l�����8�>A�E Fbd�&:_�S9��퀊�{$,>F�0�9����xI��t��������+Y�K��O���N�����}Fv��US�R�N�-w*q�jN������8杓���ԿrUq����8#��/��O���g����c�o������y�I�e��g��^����gD�h���Y/�9�h�#U��a��?�+����	���ty�c��5X�H��?��{���8g� 9�׿ߧ���Ni�#��_�Ӎ��٦�[�ty}ݳ3��45!��|��^xe��z�ctr�0I^�����K���k�����;�O�{��x���z�N�u���-�za�T�����?8u</�Ȧ������>�NM`�v����1��6Q�}�� ʗ���ǩ������4��w�&�����s�$������=�����P�v9��el������M4�Wv�*��6��$P�����݉���(�|���� �Æ[$�ע��ӓ��ES������I�?�ہ�]{��'�?c=�����9��\��m�q� S�	B��1mIQ�4w��h^����_,j�|��)DH���h�_d*�����\�������$���?:�������W����Ж{���#t��M����;b~�8VL۱`�M� �p,��6g�����=�棔o~�=�S����s���!��iz�V)��iz���2T�{��p�F%.���#��G��S����Ж��=>����u��Y���C�����a���8y���3F���Ѻ���9��Ef}K�����0g�4J��"?��s�b��C���.�]~���b������P��_���%f�t��o��ruutzS�wXn�_���%�ڌh'�@��9�k1��~���Zd?��G���Q���x9�;����s�'+l^���o�X����V7J��o/�����&�M�fY�Q�7E��M���'�G�������#%����9�Ή�j���s���m�](���\u�����8�E�ƹ�*٠�*Yz��@������ ��v��+��ͣ�ʚ�K�7}����&[�h��5��{�y���z�y�n��ص}�uv-a��O���g����5`��H��7��r�30�}�3 C����}��5�ه|6���P�!�B��:ɇ<�I`�	�ӝ���7T?�r��GV�±k�њ�	4�m��)߻\�?����_)rn=H'秣d��6�s������H��86z�<F�/5�!J�2[ag�w��T��\�;�<�W��ϓ�%�k�r%�?�{�ۗW�w�H��g���
��Ҝ�[	�.�{�I�ފ�r�'e T19, typename T20,
    typename T21, typename T22, typename T23, typename T24>
struct Types24 {
  typedef T1 Head;
  typedef Types23<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25>
struct Types25 {
  typedef T1 Head;
  typedef Types24<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26>
struct Types26 {
  typedef T1 Head;
  typedef Types25<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27>
struct Types27 {
  typedef T1 Head;
  typedef Types26<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28>
struct Types28 {
  typedef T1 Head;
  typedef Types27<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29>
struct Types29 {
  typedef T1 Head;
  typedef Types28<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
      T29> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30>
struct Types30 {
  typedef T1 Head;
  typedef Types29<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31>
struct Types31 {
  typedef T1 Head;
  typedef Types30<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32>
struct Types32 {
  typedef T1 Head;
  typedef Types31<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33>
struct Types33 {
  typedef T1 Head;
  typedef Types32<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34>
struct Types34 {
  typedef T1 Head;
  typedef Types33<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35>
struct Types35 {
  typedef T1 Head;
  typedef Types34<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36>
struct Types36 {
  typedef T1 Head;
  typedef Types35<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37>
struct Types37 {
  typedef T1 Head;
  typedef Types36<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38>
struct Types38 {
  typedef T1 Head;
  typedef Types37<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39>
struct Types39 {
  typedef T1 Head;
  typedef Types38<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40>
struct Types40 {
  typedef T1 Head;
  typedef Types39<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41>
struct Types41 {
  typedef T1 Head;
  typedef Types40<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42>
struct Types42 {
  typedef T1 Head;
  typedef Types41<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43>
struct Types43 {
  typedef T1 Head;
  typedef Types42<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42,
      T43> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44>
struct Types44 {
  typedef T1 Head;
  typedef Types43<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
      T44> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45>
struct Types45 {
  typedef T1 Head;
  typedef Types44<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
      T44, T45> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename
�%`:f	����ҷq����ωu {�O���4��+���s
}ם��wω���x؅�\�K�;+So���?ki�	ȫD�ٛ�J��'qZ�q&�b����
��yA@��Z�9/4����-��������D�?��̬o_%7�;~BԽ��s�
���VV�_��tN۾��D�~;�m�On_5�����QX"��������`�0�.���b%kiP�Q �<�J� �֜B��p�'�4r1 +�V�4�_�y�K�>��4��|�4�'�I�3q��<e��Z�X��vÃ���=RF���=����Ek�Bk�Skk���Z������W�@�?q����*Z���O�$���U?��S��Y1Jj��!q��L?	�R��"R��hpK���!��yC���(�Jo�\z[u�J�+W)=�5Ք��I}�!��	,=
J����7B%9�Q{;��5�����f�8`X�]D���E	���������;t��s6�^���e�ߤ����qTt <��n�����Rթ;�u�� W(�"��4��N͘}��
�jq�\�Q�o�F�pQt��{�q�l�z'���
`�z	U�g&*�H� ��F�I�M�B�Eݲ���6�W����T�Vn�M2i*7C�ݩ�
��Y����P)'��lګ���7��s��VPJY*%ݩ��;���T�H(%A-��o�
M)���ǰ�6i���� ����\t�f����)�(/�����l-�.���&�ͅ�d5K�ױ���S��
{[�ƛZ
��}X�|����H�@[�S[��%�-��aWҨ�m�2���e�M����1��Ge���ˈ�2��2FRCIJo"�L�,��4V�8yz�>��F�o�Iu�gh��V��pv�:n�ӏ��l�Ql��yCҞAC��/D�����XdE�^aos�����~Y.��b��ҀM�+��;�?/b���іQVo7��kE[����=}���	})��)"Dߐ�$�y�����	����8ڎ��t��C:m���yE	��-E��Q�_�`�ze��B�r�M�gj~���O�9q��!��h����㹚�wv�OP���Ga}��"��������l�0���e׸O|�u$_��Ö�Ҩnv��l���JZ
�%Y��]a���)���#��^��������7�돣�k�����ֿ<��W��������������{i�;����k�����ֿ��+����#������t���P7��U��gx���d���]j�:�����/��ڳ����������l�ǰ�/���2��w����w���-Q��?M���$�7[|7*o��Ha�;��N#{Դ����&6���?���o��4LK4a��eG?�F
w} �)݆N�����و</Ky?:t�u��w�\�˅/��Cě��2�	&����A�[��e�O n�w�yQ�S���[n�O85�co��!�����y��%[h&`=�m)1���v7��;�+��d7��$_�X�oƹ��<�3#����~���G�v
����X�f2��`^������<<NT����P����0#re
��d�TGe�#<Їw�t{��̦��6��)�+����xRy��B��Opq٩p�6�kr^��&�y�tK%����\A$6�Ͻ������1�mN�^���Ĺ�%���oF���Z�֗�<�77wlP��%6��M�ɀ{��m-�`*v�8A��?m�i��>�˰��U��u�D��&��q3��T^�9r3�Җ7T�9	�ڑ��ߺ�(�@��>��n��|D��fp@K�ࠐ�)���I��{�H['���J`��v֬7�F�5l��o$���b�yy�bp��OV�;�U[kX�
�|�,]g3���I�:�M��o�u�}��-�VZ�y�v��܀4�Q/^4^z�֌��)��8`l��j�#q˚d+��#��;�j���ik�Ø�M^v�$��r��k,���+�k˦q��˦	�+އ�JG_A0���*
7C�?��:�Ί�)��~��4�T�����.�o�%"�s�q�W
+ċ�OS����F�S�
3;|wV�AD��
3��i@#�z�P�#�~db���2(�w,��q�۟g�f�Qr����X���/��j�m�����[�?bZ�~��ϣ�dh�}-��b_�9�in������o��>���~^���~@�m�o�}wӗ�|����ڿS�E��#ڏ:E�Ɏ|��b!��,�ޙ����H��/g�!.���/=E���[:�������x��Ot��=��?�p���.�\'[�u6�r=���SxglwA�E�ϼ���o�8�8y��N�n�Y���o�B���qPj](�{,��pj���]x2�,Ġc��֦\�բ�`Nޅ�y������8�aY�����Z�:�q=8М�Ԝ��W�8�/q����̫��n�O��T:-4~��d�&q?�t���E�C�@y����"��)���!׹	1e�dh�����>"{a��׳�r���F�ih~h`�8�m�a�R��K:��l��~�6j��:]�/��Jċ�`S�1�J!�o�9>���\�r��~�ߕ?�C�7p�"}Vc/��F�2���o�G�+����S�����*��n��V�z�t#7h�Wl�V��l��߮��۰U/_�t+S���/s�_���G���	�۴�E��*��x����\�X�{����4����?N��\�|����^C��;���E���[<�ߟ������I�mW��
����������Y����ۮ�9$T�8(��F��o�;��V������f��۬�����v����%'��I违���]���Ng��薪�����7�o���$��5�����[��R��5Z����M��ɓ�[����O�o����c/'�"�7��z��o���6U�}O���T#��q�{��͝�[���t�o�V�m��N�o�{�����������6�e���E�n��/E����M/�V����R@��u�[��UZ��E��5�o�'���Y��~�.�o����Ǖ}�[�s�6���9./��6��z�<f�C�V���(�ce9�r(�z��lV���;,�
�i4\
��"�g6#K��t��B�c�6(��X�u9l��C%��j��#7���B̀�n��Z�9�X���#��T)�	�x�,��PJ����Y�m�RZH��s�)�|����ѾE+�{�|��������]����B>��s�x��eH� ^;�J,�T�L܄tݜ����?4t�$躋=Z#��4�]_�4�6ًC5m���J�i7(��jq��w/���[I�~��G���/�׵v�Zg�"�5~���K���@egx��2zy�)��2��S�@^/lP����	ǃ��^�P�vy��Q#�򸯵\C�STyMg߯�����H�Γ���H���4���*�����Z���(�eFa@� �5��^�Ư"�]��Un�ʭ�~�/��8^�}�V~%�"�3-B��\�*�+�����c�� ����E�R|��ڢ?N�᤭G:/���K5t�|��s:��Jկ�V!��N��j���I�	)]��:��5�R���D��|��<��_�S����V%�4��a��f�|����m�:En�N����Q�(u/�m���Y�f��j�f�z{�v���B#��Wh��=+��)QsZ���c�r(	ds�iz�,p��,>s��5�@�r��}C
��ӿ�{M�W}��GB��?>t���v�â3�|�^{$���EHã�8�p��Z��i��n���5���F�������?����Ae�[�4�[|FT�k���{D��l8��X'�;V��|�٤�AN�ݲ�敼CS�3}��J�����տ����$�}�K����|��:�<Z�5��huV�y�&fk[����Eo��{{z;�kt�6����r:��r:-��	��P+tD@&�߾�-^�������p���ޫ���������͢i��r�������K��;Wmv�hqj��w��wqٻ^�f��(=����/K�S_�@��L�_4���J\n�I`�5bS0�/�k�B��)ߋ��.�mZD��l|�n��(����%��Q����V�L��e_�%��/��RjN�r���A@��]���=9�(>87����9����\�ۿ*�W��_���2qCqꃶ��V�8�:ppKT \)#*];N�0w��(�VDA���>���O����~/\��b����h_��?���sU���`{Lb�,BJ����R��B��������c��_�7��+��+�����������u���r����J�WQ������ڸ�^��:��p;o�Y�̛��R��_Q�.|�u�Nи�T:#k`�*g��aYp����!^�-�?,W⵭���QaS��(^��"�����q�&�|�@�����ӗ�I�s�A=��)_�<���IMO��E�E�X�!�$,��-�߿����"����^�D?��~'?�t���}���B�./�L������7��b�0�����)��#�` =�����)�+��׸���Fjz	*�Ѽ�����X��Ζ<_����W�yO��T�׈��7���Pi9]�٪�=ӫ�R�^�Q���OXXy(�د��e"���k����z�]����R�׾��vP�{Pk��޿:���wU��,R��ǥn������B���ˠA1��A�AUȑ��]��k��yXG�]��#��&�Js�E.Tl*簭���D3<���������\� ]��OX�īy{Z�
� �6��:S������h-��@Hvs�0(Q5NZ,�#��w��b�M�f��`	�,[&����1�o1�Mr[&?��L���pl�	��mr��t����y�q���fhjd{Vc1���S~�oN��߀>�	��7��!a,!V]���OkR�0�/̧�זѼ�YLq�a=�ّ�q�R��)����=���sq��@�ٮ��r�r��Cw~ڿ��a��_����m�z����!���֑��B���ǩng2<���38M�Ο�����臎�/[�c��
ڐ�g�~����~(���CSa�Pؚ���7���	���F?���臍��~����#j�����PD�����_���i�\��t�)O�
Y�Ы�,�p����y:z���3�./T��d�?Tؑ�v�{z�$�v�@;�sC/�E
��/Bz}_\�5��	��<gz����S�Ϫ>m����{�I�����!W��d�|��\��3�%����J��}G�5Wīu�t���2�d�,PퟅH?K1A��3��X*�(�����T�+�_����DC�����;z��J%��F�t�t�,z�k8���+͌���G1����VKЭ?Z�::��B��"X������k~U�Qwң��GE^�=b�7���d��o���.��^�%��`PI��ϛ�=�Ӽ��<ͦ3oΤ����?����O��)v�"O}�ɾ�A񏡰�?���	t� ��܌Ǆ�
���G�e�t�Xۃ�8�����Y���I��f�q^�>���ʣ+&�-�4eW��de:��Zo���/8rپ��s�����"����:`�m�>�n)�z�ҋ�R�8����y69�3��80�v|��ߑ�K>��s�o�T�?Sͧ�dG��WE�qcu�V�ȟyO���HR�s�go|�z"�׋�?L�%�p@�>�]<��:�A���;�����œ=�%�ܖ��1�^xr����6�i򕌁O��'�?vM�c�U�ns�%vaV��U�;+�}_�I���d$�G4���|百o|N�	�����sG��}~��o��v���}7GK��d��9G��w�L�O���7�B<�
5�N�;���L����x�B�_��T �﹨���<�{�g4�J@)3�?��3u���zߜ��>�����L�e?h�yޏ2�M����;U��f�����Ǒ#��5�_�9_�>�=���֜\�}����o�<d��bͶ�x��8����d��g��8Ǚ�^����8��w�s�e2������}�}M�����(b+�h�{��a�Ї��AC[L�������*���"�_~|-٪5_�����fj��L���i���1�fa5�VY����͍`<8�	|��Ȓs���L^6��Ώyag���� mߚ+��9��g��$��L�9C	_7K�}���ZL��ar�Őj�,% �7;�E��Q�oV�D��Th*�5��:���A؉�x�����S%95r���,�o�x��ȱ7Ɉp�2m�fN���%��a�)�Y�~�H�ܷ��$f�L�im�<�Bv�����~�!*���G�n,�)�+$�i�/7��5iQ�r��t��{�}�amC4�c1�%���������j|KScam������1<Zz����ߥ��k���}�b.��pS;c�4C�[cE�1�oLN�=�HJ���C���q6<�희;��(�!�Gu����ߓ�zz*XX�kS��Z|� |B)��̧��=[A�ؼD�+�$�~�!������;�n����m)�o����^|<K��$����'^����H�i�p[Zi�߉L_7�H>�@9I��;��9��cS��1�����,��L��P�c�c��&��y��x�%�����o�R��積i+��
���_V��&~4	� ��i�������n��I9BM��$���rX���,��=+SD	{�-��~�5�3��	�
�^Ys�,�
����3R�}5���Aaբ��1�ۍp��jc
��3��3��ڿ���&;�:$1�hNL7�Ա'�Ї�T��
}۱\<�����3��+�ȍl����єy'��N��z�����Q�4-��-(�����cKf�&0P�.����:�v�rw�ye��>�
����,�ޟ�^Hܟ��ܟ�N����������q��瞣AeJ(D��>���s=��?����Pn�L��W��d���7i�� G�빇13��Cg�3:N7�BB_/���$e}��ջq�f�b� b49߆s��PA�BLթ4f-!q��כ��yQ��$T�k����L�#��}8��U��(�����\7�H+���ӱÑ���T�4Mɼ�Л,L�&q�b_�%�|Us"ρLB� _j��7�7�2�1�I����V/Zѧ���I"���������� ��{��勸lB���ȵ°~^7[���K��Rf������a�q�8|���a�'��Ͻ�c��@�*h�y]�Ĉ�f7�f�-��=����|����������&j�	����s�؏��'h�_q��������\��<Ӆ�������T�Ϟ,���t=��P�N˪�������x'�����8��z�h[��S�+�@h�����)�>Ke:������'�������o�I�t��C�ns<��wO�h�D`X1Xa���#$�"�5c�r"��H<�P��:`[�;�=@c�/"��ڇ|�?G�&��2�+Ey��aO�O>�r��i=�����I	�Ii �f��|�m�J�~6T��"JpR�i@�I2H�w>N���a��m{�a�yhrz"Z��T7��^������d�� a��5��`?��T�C�V�JW3H�. ������o�b�q4�@l�M��;��	oB�[kؕq`��B8V<F?�q)�L�x�R���=h} �0r��5����EF��
�TVs�
6�"n5��j2�K��K+��`
�Ѕ��1V��ȡ�
���?=xk;-�������������j����W���'�1v�[�����d��O��~IB#�7Yz+F�o�-��XMlY�	rlYK^�dBom�N�{S$�4�����ER���yG�:�,f��]1��`�^
��>ʺM�ǑM�s.x�x}�7��\�x}����*�����>}oY����;X�E儃u{\g[��~��GyT��ea�q���?��[�޻i'���<��F�;7��4\B�H;�F�W<��}ϋL����D���^f��@&4��3��HqZ�/�UV[�`�۾�b,�}�����篛{�L�۾�7��F'��`��L�Oú�Њ��Dў�[.�,��}ed�`8	��k)�m�L�������*�=�D��������p�저�&�*\�
��'��m��\��(���i"�������;���Ǚ`G'qswc��$�u�mI��*����kr\��ȁ	ā��/�o�t�Y��g-���ߊxtC����zx��>���r~�=�_ڷ��'�[ݽ�w�%�$�}�$�����	�����[C���t��I>U}��s����x?��{O��YEp׻�#�1�a:�1�ro��C�Ļ��q�p!3-�p^��7I��A2��$V�?��>����a�� �~f���{ƷD���w&�yw��˽�� �?���~M��7/�$�&��2��'���������!ᯖ񻃢#K^�ob{���@#�V	7g�>N+��<��!�S"���|��b~{��j��5��;�����N_�.[�Nq��4�i�����y�Cc�ݝdT�Ó�p܄Ȃ���n�[��g ���br���N.4�lIrڿ�z�tP�/>��2�<��+��_*��x8�gA$���y~Y���i6���r8��%��x�K�	ɮ�K�t@�&>&�g�j��"c�ә'��-�7�^^b��o����+���O����%�,���_my?�iO�e�7�}��z��I@���k�ː$g�+��o�'�`>���O`�b�DOx���&��10QpC[�F�+7P�pFM����u�H�A�,��D�a��H��Isd���&Sd痂"���K"I�vD����$�q��#�T� $�4$��H����W�eG�q�9M����N���~|fc�>T��
 �>\G���hi��c�����SY=��F���@=��0��uK�$eݲ�N��F�S����%�Q�Y�l���������ʿ���ߕ�_�L�9aل��-����ǫ�;�j0�?ʯ�|����c׳U�Yu��٪��=Q�?u�O@����f�0cT�M�\����xkg�h�y��f/;_�!Ri��9
~�[ j�W�G�䣙�U�z�㫆��:���Z[{�����x��b,��-yqWi)FJ��O���I�nu9�-���g3����c£U<�m%�|~��_���|��ɯ^̕�+�g#%^z������f��� =S,_�U �f��F��q�vt�g�.��5-��V��P�E�?M�<J��C��su�\G~~�.�W���T�kR~!]~I5ߋ����Ô|���]�Q��S�*� V�8?��bS��d��i��sd~��+sT~-��'�*�3�s�&L*O(�������^[y���r~{��P�uO8�䟀������Bɯ��5�����J��u���s5��J�:����7���j��R�������M��ˡ�J�k�9X��`�?[�|~�Ň��J�k�Y]������gq̷6{������tV���z�����!�qk1��?����%h�+��4�G*����'(?N���O��zJ�Y����_W����(?���o�珦�3J>�W�m��*��t��Cɕé<�Rެx]}���_���/A�-����Ͽ������P~!%?@��F����'Ct��(��R�o��LG�DGY߱�.��Đ\���Q�z�V��c$/�f���f�����I?"��5�K(��Gi�;�C�{���oH�פ[D����9����~��Ҥ�S�&H�S�^����5���n��5�(}�'kһQz��I?2�����V�~k8��M��^TN	HG�>���n�ӋhҧS9�!���jzyJ���>wi�*HOפ_���!}�&}���ӵ�PzH�IO��XH�D�>�ʯ�-5�U)�<��i��Rz!HC�~c(����tM�T�H�9Hs��-�s]
l���u��)s��=XX����\B%�#V�5?� ��aϨ�p�{�V9�^�k�A�=�T�2�������!�9��������	?'���"~;w�u4�?^���	��;��7U�}�r�	�I���u��o�Y2������	�������2�j�\��Sį���?TƏ'��L�¿u���*~n���?wX����×4��e�����?�wq����-�&��ݢ���;��v���O��t��?`w��B�_]�?�w�)�O�c������U���Gm�'������L��O�[RE��#���n�O]W����	���L����O��.����*�O����Gk�#d�}h�m�'�7��{i������͢��������7c���n��?�Ot�����_��s6��~Sw�5��d����߇�s���L��"�&|�z�������w�����u���?�_�gV'����El�?3������k��m��L{ş	3��?󹗓?����4��3?G�_�AN~����2��S>��)��O�̃\��41�2�0Ko�?�s	���_���_��5�y��'������^�?yc�;��1�?�_��*1�w��R�	�'���k�W8�hW(�/9ᬍ�	7a��+��y�~m������1�����
	�V|m ����`�Gj��t�Qh�߂�q?�Z;��h�{H�Ư��	��e^t���m�}�>u�I]���PקDR�'��v}E$u�����4]���V�?�������R�ϙ�kq� ����CУx�/٣X�S��_��ޓ?��g�?�8��	�H(�9�}^⏃�{���V�J�Ϣh<���}^�d�����}i��y���6~�~�$�TБ+�_ү(�e��/Szk�����~�����Z� �����]>P��^��AS�T���Z���&���|�Np���|Ap5��V� 5�z Y�N�����<��U}��e����?ؙ*��3������u�W�_��~CS���2�2=���s��U�/�O�0�~��Ա�S�{Ї�f�4t`b�w|��켾��ԀeT ;8��ʶ�b�{ �w�v�{��+�'	��8�����sU�PNز~��@�AHg=G
�A����N�H��[����0�6���?\�M&�sQ��o1�Ȳ>���CM�MM1�i�����9����?3�
P�-N��]�K�C�?�_��)d���O��ɓ>}�]���Ww"@��D���*�9��� :h���u?9�`w9�G�����~���b?�����џ���Y)��Y����~��9=i����2���꟠~jq��邢��_�Ow���[�O�H?�7r�����r�~�z��SE.�(�k�ͽ��Vfٟ荟�ުV�O@o�{�>_d����,�>��OE�<���������jj�,a�t��+�U�ޤO��6sFՌ���_�+�П\���P�������M'ā�H�G�!!.��"�?�!!�Q������>-�V@1`w���<���>k4���ݟ��zX��t������>���G����}T���>
ꪳ���)�)�~V���D��u��kh�����l ٻ����U#iaoe���2�����]���g��l��f��U�Q��n$��r��ܼ����'J��ga<'�U��4��uՌ��n�g���{�3B�v��8P�F8
���`�;��	�[w�����|�=\�gL>����3��?�������?��Gb��|����e�1����/}�U���u>��O^�|F�N��;�	;���6W��#Y�Sh��F֏t����_t>#_��u������3��&���'�������t>#(N�
�����I$)7GQ�SjI,��$m4$I����3�����_�|����+{����S�IY?\��N?��e�H�i��J=��F8��XN�~uR��O�~����tu�������;����CH7Hu�:��>]�S�����㝮��c�	u�/=�������2��?��זH�c���}�b3?<A��t{1�#O��x��o�;F}����Aݤс���P��߫���P��55���4R}����{�0��Y���ح�����;���j�������M{]ף�S�����v}{u}cu�����_��X�Ƴ��lW��#?�[���<Bt�����]�V
��B�<�,dK��S��]��P�é��P~L����x����co�����4>
�%쨢_*%��s;���8��a5%�r���]O4R�?tt����kX^[�k����Yo,���
�5�L�]g�%24�E#M�(��'򈪏h�Q0�`�>T�Q<������W�?Nu���$}�<V�=������-��f'���*϶3�폵�Z�cQ,N��hp�����Gc��j·!c;�`���s�
�G�������-���IP�������g�^���������!��^e"I���(^�HR���I�;����Cz�lPa}��D:7?��Y{U����Y8�B��C�:���^�a�pTި��]X�m֟��菢m��H���Qw>R��7!}�8�����=�"���C���h'k��>�u��B�H=qT�a-b0(C4	�:��5I7Q>�H�K��)�
�u!�n4Q�t��V�G�p]
�p����#6��ދZ���&�w�����oT�#`#��]��/������C���z6MWG��]E�����7�ꀏ�Q��po$�mӜnp)-��I�o*��ӷh�ZI �#��(�˷z��*pA �̻�&�E�>T��iZgңhi'[�`����1!�ׄ/*u|�BC
��z�tk�@�&���g�´�:�=k����2�֌�VW�̃�XK�_ ���C	���D�*0^�L%�J\s�������UT�%B+Fh�L�5h�
pq �D��:̔O<I.��S9��.�//<����+g,5�����ݘG�WE�?�@�bleb����ڧο��̿��`��\��+�"Z���:Ͽ�g��{�e�����}b��B̿�{��������"DX��`�7�����ʩ�r����x��}�A�T���`��G+֛~t`]�G֖~b1�k�q�K��=����Yxo�~c�����������pW���{�Y�bk/�~�us�.L�2ѯ޿+a��
�;���2Eܿ+<��[w�n�zqZ���P�WX��6����`�}���۷k�ip�}�&��`�}�y�[ٿC���:x��J������>�.������l�뾝�k���_	p�3
�J`�}�ܿ�=�5%��e%��f�q	,+�a��mY	W�m�rU�?�ب���E�����˓9S;E�_ؤ��_X��׼Ts��V/�_�܏o�is����9F��摒���8���~<���.f��9�
�x�?Qa�)
����I�O>��ú����Y��?|�(a��gpF��N�-���i1����(�Q���g{�+��<m�d�y��s��y�+��TX*,
���T����?�O�a�Dp��s ����Y �ɛ�mI-�}�j�����H�%�o�R3-���?@���z���8F�@�hO{ c�Y�������
�����P��V⍅(#��ƅ�}U؋�-Ph�h�e�\{i1Τ�fK�_�v/�5o)_+rt����E&�zI{#�x;g�:�D�  )>'`�"�O $��Lhĩ��/45)�wz�o��"M���K�"��hX.��C��:��-R@@ˁ؅�Nă��x�9�#��ĝ�����{T�PD��Q��ۜ܅��r'�qB�|��&"N"ķ�HS'D9�C؂&���F�%YLc���N�ys��_���<AK��3�$q�MhM�J'��ud���@f���Q�OGJQ��h��CɩRZ�w>̫��i ��Ǽ��������8��R��F`�Sh�J\X��(���B�<���H�70�Z�P䖛�.q�ye[��2�>��U�ƁR��.�Ur|�G��=F�*L�
;��@��M�8N���u���1��D�'\4�9���c�F�H�zŐ@Qv��Ÿ�l�>�؊�Ȁ(�@'3�vƀ�`�l�RkB�B�O�#9��T����ռ?��fά\����і�"ص��'�Q#b#�FؾP���זO��W�T�Vl���)�-�������:���g��u����-��=ӵ�k(�	�����v8WS� ����/�>#�A�ߴp�Y~7W��{��E�9ے@�hY��ٸ��Cu+���\��{�U��<[e'�,i�Ơ!�+�^��mD9M�R9K�c9h#]����̭"��
�$�C�iS���p���9J}h"_��r�FQ9������+Lh_%D��[� �*�4�W'4�-.�����ª�G��|��'J�8�����y��jV���18��P ������W��;�S����?��>(h*��p_~���
����L)�6�ׇ��X��?��h�ϸ��~j���|6��?(���Ԗ��S����S��J���������T��M��RdF�5fC�1/(?�y�i�tds ��;{2���'ir�EuM�C5^��b�\G
M�-�y�d B�xH@��qH��.[���i]�*�ќh(�?�ќh�]A���~�,��Q��_'�Ia_cv�	��/�=�4������4��j���|Ɏ���<��^2Q~��Ī?	&Jބ���躆xc�s�g�=s3Q[��^lh�9c�f��h���b}kd�f�3��"��("a�ʃӠ�x���}�������EK�;Q����^��3��`+^����_W��'$%���OL�����ɀ8/�����_��R:k��};*�
��j3Ҋ���D� ������7b$�F�_���_�t�&L6Fn� d+!͘�[�/��x��\�L�yE~�#>�E`DHn�Ň��m�I,��9����~�-�������W�͇��{�Y,��|�����UL·� �q$V ��/���I^"�Yϱς��ɳ&��]�u׭���9��œ��/�1�ދ����Б� ��H�ro��3���A.�y=�p-�@s�o�&2���f����$�n�c�/
gk#���X����Q�)M�?�̇��0���(�����!��=�5�/����A|C��6����P������l�O7�s"�Q|]|��ȕ8'�V��=K���BԞi%!�_]�".�ajwA� po������A?��H�c|�Q.���y���-^���ҡ��x��o`�6)�6���tx��l-�.*H8�Pе�HD�����v*���3m����#�W>������4�k���˓�?ߤ��@}�D}dg���2�_�/����|Iv��So���[;z�X�X4F�I'���e��%X�de鴠ok?����H�[�OrН�s>�C����Ɵ��9й�c����a=�)	�N�J& \8y}��" ��N����7iR�y�M�o=`5u��t�n ����������i
�ז֚;�֫[�V�:8�.��^іM���x��X�:��Dʱ�$�Z��T�󌢗l.���� h��[��h*{	~�7p�
��F{�n��Z�s�W+�s_�.�sfF-M��J�h*ŏP�G�30�RL(K3nt3FB791���o^Kx�y�P2H:��dJP���
=t��}�S?�N'X�G���s���]fKC��7�\�K�u����,�J-q���T}l�]�o? |��.?p�	͔ζ�a~��w���:��Ax�<KCx�'�ͨ|:}��2��,L�t��(��4��p;R�ɆFP<�����ke�����ݖ�8y#�Z�R]q�<�D'�a@��"� ����`����[�"�ș0�ڷ����]��Ǵ]YN���0=	Q�e��W��Ws��=&�bֻ���_7crV�f���،�����xٚ���r����d: nzT ���͌�����G�66���ě��|�9߯������as��op�a�L�W�&Oj�n���c<�9f���q�t ��X����]��:b-0�.Ό�@�A�8�b[Dt��2h��k�=�~�iB<]���K/��;�q��$�C����C� �-��WXd�J�1�0Lf!at�dDQ����ll �,
j�nK�э"����Rm#]�@Ǭ���ch�4m.�z5}�bR�QV���}Q �
9�o遞�r<���:
=��T��( O��:z^
U�NK��u��szU=��(�̩���n'z^��B��	z�p*�4��t�B�����@���j6�~�I���t,&�\��~���W4\�FY!���@#�
���s�{�5wC���i��I�oKu�~+�;�o^u�u~���@�ү����sG�C8r�ɧ�Χ'����{r��ZH�7!2�7=�x��9���T���U2��|W��'�e|��y7�{?��/QK�L�@a�~��������/@
Rփt�9�]�����bT�T������VUu�?��7(,}��(��������,R5��IQ�4�ZZ{���{�,���:��p�l�I'�@���)Nw�0�>�I���67�f?�-}�m�C��?���6�,�/��O�nM�>������������4~��2�ϻi����*�/2�^j�O�x&B��v{=��N�y��6�d��U%+b�EK�~��v�5ϡ���n��=��������T�^�|B�r����U��7�;�#��Uq�	�����	{	`wq�Na���8��dp)bu/�fPBY����v��q�y6���~��m�m��T_}��Ve�����u��a�W#�;Ul�#�S�\n�O�UW�O��H�f�o���1�y�<�;�|-�{?4�<"M��|����*��VuO�&���_�⦸���N;����k75�jU�BxM|�㛜�K�8U#�劑}.W����f�?C��0�X~���{�y\Bt�@(�
~��v|��w�p��>¶a�
�=�ΪU���|��A�O*Q������-�,�6�
�t#)�AϬ�^'��G��k`�����ǋ���^�������^��z����v�zL��XF��;D���cV��x
��_���g;0�=�8��8��9NCe�g�;X\M���5�=1x0!\yY���ĝf�b���d�k�:8�X�~�^~�$�.����p5�س |^#���B+#�Z7y�f��Z6[�Ro��Vr4����6�L��9:_���'����)�ϧ*����:���b��r�;����}4X��w�'����_�]��������c��0|XM�Ы��h4��G��
N�1z��tç�r�IP,�Ћ��f_���_F	(ߺ�NP���nR���U�.���9����=w���N_W�VT��n���!؊ϠoW�9G���w{ 'Bψ�P��O������ڡ����K� ���Rn̿�u���A�M�P�vz��Cz� 5鬁7i���5��j�+b,�ؠ��FJ)�n�?ڞ.���CA�
*(�(F�X"�PP�("V�Q z^�%�{��hb/�F%�5Qc�mϳ�v��̼z��L�������nw���������9�^Qh���5�{�B�������(�ER}�(Db
��w�<D�\Aب�RQ^�YHf�KX���I-�b�yX��o\�
NrD��m5�+$�K�3I� �@��{�a ������E���@�t�R�{�����J�>�8�Ao�op�iS��Y#I*Y������k\K�������	�s2�?��п�UCW��5q��T��)p7^����P��9��K���=k,Ix{�E�Ng2�1A�~���11̷J��Ȝ	���9�P���ҁc�����5t�`���ĳ<���]lB��WXf������b�Ǎ��6�!̗�R/aQ�2f�7q�������Vֽ.-T�x]��͍�Ge?���=�-(E���3�⮭��9X7R�8(U����6g�et<����]��:������3��W3_�{Q��^J��q~���ױg;]��U���ߩ�`��>lj=U�D�~P�/�Б7�Q���=�`���3�������dؖN��$?gj����Cٲ�����g��Ǐ�G��˗*�UV	�Ә�?Xd��#������ Tb�F��<��uNp���En�rXL�ԫ�(�b�����y��\�F���8���$�������K�b(|f��'���Y��(��S}&A<G��K����Թ�#���z `��ɟC��S<!X�jn�qr����h5�Ţǡ�`��ݳ�!��,�=��?����<���Ɛ_��䷒�@(�]��7�������z�~�rÔj���@��6�dW��k�\���
�9^��"��_��3�&�g `�!�X�A��@>Ӫ:��)wN��{f��#��'HRڨIi�,��(���IR�5�0Ii,��F)�u�^��Gx����w����EԪ �T�?%
���N,�V�uɠ�*d̿^&�����a�Xw>L>��]`~c���Q�7࠹��"8 �4�@S`"o���;_Ѧ,߹�~iO-�P&|ݞ/4����[��^'��h ��{|�h�� e��/�͍j�Ls��)�y��Y�ų�~4�2`��;�����:�>@7�]���K?
0D�+���M>`�Q��#�va�?a?QN��qH���� �N��Q�I\s�8����$6�s��i�Yϕ����ϑ����\D�����%.O�D2����NdD��&�C��z�i%���g\�At��LVϹ�7g�c�l�?Y�^ݤ���k�~�Ee���Te�Q2��=���TZB</�8H�'�+(�D2�LxM2�ʕ�%G�'�AO$Ѕ�gj=T��D2`-���'��VR����JHNgFo���}O_{����d�O
��,A��r�Tְ�Pq��z�^��MK� �'l���6�	(o��<�k��E��ҏ�d0��}�hn)�����Y�@�s����?{`~���㿲'��uX/�
FY�8|����դ����r�~!�А�b���[��y�2�6����ۘ��ۡ������ ����R�-7�[fZ��ȴNKɴ�����? W���,�6q?VQ����wտj��b��#m�R�ޱ�V}I����{םԓl�#Փ�!ҧ�p�~̻��F�B79.Y>��ޕG���~���x����$�<~�۬?L��u}�7������BG�+���;���4����0]:^�ڤ76�������8ԘMZ!׃���VĆ��g ���`nT� O>6�/�>�P\b�X58��Oy�P�s ��#j��������W��}���NMO?�MgTP�7�&�@����*м:�ICB��{Ir�z]U�����W������~	j����Yū�¢?�����ɵ��:�}����]�_/(����m�9���<9\>�X��z�K�45>��ca�.��H�Xag1@,D�{G�a"����'�[a�_Q,TX�;�� ��;������>_;A�p�1��@9���8G��	��f��{�\�#��H��������H'��B������A�i�(Ɠ�*�]��X��PJ�ܴ�$/
�P8P�%���/;ћ��H�j?ҙ�b% �_<Q;�����9Q�K����?�����]`��)
Ʈ"{>P><�	*̾H.<��Lf ��p��F�vE��,Y�ƺ�l�{>=�l��"p�]b}/��b/S_o�UI��w�����X�sòˊ���}W^tB��$��#%U����p�Y�9}���}G�/��~��o���*��`G�"���IV[�FI��SAIߍ�"}K��;�S�o�2����N�ۻ�D�!�վ�O�/�h2k���k�����(��M��eT�Zގ�ߕD�����o=������VA���"}˔���.�W���,���K}*��T������%fp���o����:�F���a���R7L,L�XcOu�^�\J@�Tp_��_�S��a��l�s���D�B+f�L�1kLwu�|CФ�l��6/���О��>ԉ��}�����ՙ�����R�j6=~/�N�p�{Գ���2��R����\b�_rbyuO�GI�=��Wgm�E=t�{�˫S7�Q�5���K���Y9�����a����չ�P����%����0��`kv�@����KZ�S��!Z�o���5m[�,G��B�&��B��@�KY��aR�o7��r&!^n_1)^n=���t�m�ܘ7/��>^nQY$Í/W��/wb�v��m���8n��'h#ǻmژ������h ,��D�Ϳ1�7��o�����z�?E�#�nz�E�)����r���=���!�y-e����=2��QpE��w'�w��y��'��&�������_o� �����B��%T�Mɞ6��m~�If쮷����곏�G�g_˯��~6�׵,Q�o3�=��O�UP�`s�1O �-$�,.���i1��f���R=ż%���V����E�fvY�T��ڋ�ߴ�4���epن���=�>n���_r��qVR�i�k"Gzl	�j�]Bj����C)���^�\�8p�u)+AC��/�.-*�u)�)ޡTY��9gٞt�������%��喳������=��ǒ?�7�����-fw����`�h�lv��{p��Qn4����g`{=p\�}��kRF��$�K�Q��ٰ�~���q��w	_��Ћ�p�a��e��W: ��eI���J+�ږm��ق)HY1B��-b�8�Q�9�����.u��¦��l�c#@�FQ�&̗�]͆y���yH����;�p��nW5K�ϱ�N�Y_Z�gEw��J,�?�~`G�T|�H��-�����)>���!�S��	 |�>�E�KH>���|�j1�;�q�7��s��W��T��2��x�����%���?�$��+M�Dr����N��/%�ߣ�߹�?��k��zzJ�\\
�BӤtig�|���I	�����WD�=� ?��|| 	�R�ϓʄϤR�����P�����n$���W��>����D|f	��+�T��9�����^�I���E�G��>~���@|J	�|��`g�Ԑ�@���J���v�O]����O_��J�ϑ����k�:��S\����"t��\S/p����@|͆���4��K,�U0ji��
�j��)$��3�#|���,/� �@�'P§���2��5�5�Й��	�R�I�L�t�B�/�B��
����bk `S��-���'��u�������*��9���.��h��ݹ��~o,�Z���+!ڣ�qt1G�7xK���dtb�K��=X����ކ!��|��%�����Y:�~�ώXzӖA�B��=�;��e|���^�����_�����~���B�s��}����{���q��K�~���C�]Em��J��ή����/��=_��.��G�V��̾�����v�a��k�~�`�*�R��~�s������O�� �?���"/E��mnWyɊ?���X)��~��"�����(���/<A�/<��Km���B6���.�ޒ_���_���ڵ4�0n������*u�v�.���*��Ʉk�+�e���]n�������|������*�3\�	�_� f~`���7��������%�ꕕ\g���|�U
��|]�V>�A���|±�$��x��nWG)�����!��_0���]c�B��	w*J��[�(�|���|�/
S�`�zKT� �$��c�]�Y}��r~���V~�WVe~�&��Ds��GI��>N$Z}H� �e���/\�C�<�6�B���O�[k�7h��RHY��M����fH�O�zv�^)�yM�}S�?�}!�O�@[���eH������+�~�Fe�a�ꇧgcQ?��*�C�B�~؊:R�=a9A������r;��.Ҷ�P��%�Q�8�v!r;t4_��vm�U�ۡ�x+�{uƦ��7V�z6��k�n����C��[ok�i�[��^Px�؁�����Y�R=��c���(�7���I��o����1��g���U[�}i�q�C���3A߹����.
�Z߅��=tH8TbM��k8�B2�z�\6����k�N[���d����무b�
Q\Ҭפ]^p����oj����bCU��΃uڵڭ�v��m�7�&�wڧS{o��>����ڷ��>����N��Z�}j��ޟ��O���������Ў�z��c�<%;&���/�3����wg�Ba�}m�YSf9�_++�UV� �_�e�m��A�ZSJ�Z�V~$�Y�ĵ�O��S���������ޖ\�g�F�g?˷�������w�f����1ѯ�a�_�vR����Z�PPo�+�v�W��iL#�����z��<�lz�f����M�?6���|j�"�-�_X�O��Ō׊�6�"��3]�~�3\_�����(i}9;�֗ݏ�K�V��9}�Y��c��̓����10��[U�s����V���\ַ�G���k�B�������oO�s}[���Fݿ[?�6��-������>�o��/���~N'���9���"2��d4�=@R\,\���4��Φ@ު�VG�s�s�3��S�K�^Y����y�]?��K�ߪ��������@5t�4��i���O�OCwPgS/x�3����$޵:�����!��{��t�Hq��?����a������Uֿ{�=?<��9|$�Ͼ#���e�`�=P�O���*���c�Yq5�>��y����4���=W���(�?v|J�Bm�C]vxJ}��:�<�a`|xi��m��^��6��D%K�Ѭ�SQ ��}�v4�D��G������s�����bϟ]�f������9���s�'8��DR9we�!Q��Y�Fee��=��{r����B?/X���2���銧��P}������ĳ����M��I2��w���E0~)a�/Z�_D���_���/��z��!��������M����$|a��_ҭ�6ʜ.{�������ݳ������ģ�`/�M�~`����zwH�e�'Jy+��p�9|nu�?�z���Q9l��c���YT����{I?}�Z��^�K���� \���㑝fF��ܶ����V��l�X[��8�؏@��R��6���w�D
��/�0��X��o�*�i���V���0�=��[���#�?�?T9��V���jD�>�؜��a�o��/Y)[D�r[��3+��`V��4=D37z�eo��C�������̮�C;�Tr�=㽗]��^��s7��&���?ҏ� �q���m��0
�~��B>h�����C���p>JEa����*N��Ͼ��	���!>ʃE�[��w��M����U���dgyY�>���#_�����r�`Y6o��C���d�(���tB�	���@u$*�c��Ѓ�jn���Nq
�	���E$`��l۩Ʒ�Y^�B��v������n�f?�:0>pF�?Ο�8e?�,�:��.���{������%|�dAn���r�o��l���'�#�U���o�[N�m�߯�I� ��y@s��ɬ�7�d���%�g[S��z�S|g:ˣ�讄���r�|u�<��|�1%�V�!�i�8A���r��%g�����"ȳZ!� ����Q�͆�r���@��IP����7�����s�H�v!Ȼ��� 7v���[J|c������$��j]�z�S|';;�j��_S���՟����� ߃7���g%�;��. � j}��}�߆2��>�|	�]�|�|+���z�p�����OС_8�Iל�[��SoK��!��9 �:�w�%��l�uG��Գ�&�� �#W���,�ʟf	�9Mr4A޽�CN�� ��ו�f����ە��jF�jU���t���]߫�r2A.��^q�o	%���f2ء��|��Ju�v�r�[|�e9�7HcV1ޠ1���s�@�[��U��=�FBЁlW����ec��2�@��F��w��.+�����8�{��-��)�]8����u .;��«Jz�]z��&��a5��_��7Rz���*�e<4�|gP�í��.����a�:g�Wݔ�#���ԄoS_��}'�����|ք�_�;���U�#���}C��* ����[�~�|�)E�Do��˂_Ô�Y��v��I@��y4o�
;�#\L-���W��9��_q�o~c?�w����7�\+D[ؼ/����^�޷�ߧ���y ��o�%����:{�0�}���2Q�x_I��e��߽�@�����_���OC��M ����w_��s�5Y�	~,�_ �#�6��ߺ��2���Vs��6|����3�����_����A���6}�;���J�qr�{��qЋ���Aq��r�bKO�=�h�wH��
�ĸ���jpGI�Ľ����qm��ކe�q�����~�����g��"��Wi@�� �?�M�X�2�o;��8�?]����ц��\H�?��ۗe�ץ|���z��C�_����r��=�_Y��� ���'�����������o�!}E�+�C���g�����v��%	��?�.����i�߂�&��ևϙ�����*��Nס���7��߇���5��f0E��i���)��.Yl�v�6�u�����IG_t����NY�P�U����S���{H����fŘ�R��@c��wV���kx��R���yU8}�sU8}}��p0�rU������Ƌ;�f��,����7˒A��J�R�X;=ս��L�����R�g)!E��0��{V��z�_=���ge����\������b����*�C&7v�״�e�p$���+f�Ϡ�ya��x^U<�?\b�DH{8,{g���1�7�0$R˩bꦇ��\�&ܵ�!y͙�.�9���w��>��\Je|�됐f#��"�'��on�����V���`����7��1��>�^���>k�4{�1�n�f��8����o����3���ġ� A�_�*��G�&}!2)��y*3i����DdRX}&y���Ⴍb^�A`����g�%bZ�Kt{���`Z���~�"�$��]{#/FPҟ:���A��������SL�d�g���ֵ7��'��ٟ6XXˇ/s*��iw���E��r-k�|N%-�s���a<
� �s$�H��u�.�d�u	o6H��$Os���4�&D��������K	0�J�(1]&�]C̘�Z]$J~p����^��:�
�~ '�'$p��-󜺻À Sf��Fp=(Q�	�����9 �:�>�C}^��S�W��b΁,yO/��\���N���27`ƥ�o�t��Ս3u��!�E��w9}KD�(����r��5��Ђ�f��7�J��$i�b��a�X\�=x����r���x��˅�\t��(-岤*V�K��p-7��&7s'�|�B'�|��N��*;,���󥅭<d{���%����?_����fw���zG��մN��a�V���VZ?r1���
!)>�%��J״�>��U,P�M���{�2&ͣ2c��
�J��+�/Ǆ��:C�Ѣ��鰢a��@���A�vπ���"���}����u�h]�cV�|@����3��Qƽ|P~#V��
�"}������`J��[���^��<��OY�<8���"~�d4x�Rf3�rT<�����.�:�)9�z���ࢁ�,���8e(���,��.����Q������l��C���t�2&G�}���R<��l�i���?y��Oc�S;̭��.�E<z�Y@��>Q��`aɎ2%��j�b5�p�å�*z�Czt�K�?֏��b8	���3
��1�[ιM���G�e�B�!�H+0d��|���o��8�Ӕ����I�(Z�F>�X���%���(��D>ū��{@��!'%>�;&��1>�zG|j�+�	����� =���_� ���
�Sp���?W�quE@�x���+�O��jB��FK��rN�|�>�[�h_�����*��z��V��R���S�F����3&���Uf��檜��R�D-L��d ���-���/L��h2�y��d���&�`2x�RO���)\�������auO��
����"UW���'"�3!�B`�n �[
�
e[�=�8,�
s�?W�S;�?�|�>�1��I�Z!�����c�dȩ�կB2w�������a�
W�����I\|���`�ax�t}�O�J>V�X�Eg�}[a!'���]ٙ���
P�1��_ �\���/@C��aށ�������[92a��`�[L��V)���r6-�_2��,�QG�϶���U��/..��CT�-�<�|
Z�1!؟l��e��H��@��V����B����0^W�HS�>�4ĕ�{�m?���!�fa���ȸ�R��9s�D�\�{�UH�pg4R�T�
_o�u*������a[��~������ug�_���Mk u.���/�!l��?\�h����&D������P�֝�0����,���0�<w���.AD�|�1�z�U�_�XiN��?j���[��L��`�80��z�P���i4}_�^!��ɣVE~�͇���zE�����?������۞���G���ƶn��a�2\�����y���܃���V��Q|q�u��ChK���&�x�u|�Cv����x�2Ჽ�.ۻ/���o�%{wӻP��7[{���x�C��o{{wQ���g��U���-��������k���l�� .�b
���b�m�%�������j�a|��hC;m?E��?�_����_���_��4���U|�=�����^H�-y����+-��wT�Ӂ�����y|q�Ch��Fa�Q�,k#n��s_<2�>���A������o�[i~�o#���Q���秩QE��
�_�٢��+f3�����U��g�P����É�P��>.��QS��7����Pwqcj�M��`��Dsgr ��<�&�zMh�5�U�x�� ِ�P�6]|5�`��� ��0<��ɣB�2�x�\��[��B1��i;ܜ�F[s�8�����	�������u�ɇ_��r��0z�x�h79,�.�&��:t]N:h���N�g\Q���V��~Q:c1����a�S�'ӔQ��]8���j������{�'gD���Y1�P�=k>w�2�C�,�B���5ʺg�O��w
�C9����P�=��e�лgÇ��Y?�C1���P�=��<��g�Ç��Y�{�/�q�p��Ce��|(垵��g��{V;|�ꞝ�"M��#M�!�9��P�Z@&~�'��"5����i�'�ϻ�\�a�1u�H�x-�CN�Խ��8{my��{e|�v�$�WYRx~A�-k���r
8N�d�s�8��f4�� 3L�2���` v��fJ�5F��4=}�7,��"�� ù�����  ���ֹ�ي��f,��ӏW LB�^��@�z]ϫ������~��-�?N�p����j�_FًPI�DAU%�wFJ��SH� 	�
�@k�K�5��*���wĸ|u��{c��%��B*�/�iP�_����@p�!JHB$�M(���������p�)��B��)�*��N�gH/s7���,��Ѓ<���S9�� >��;p�e��_�*�4��e�-1M���w��9������F�_��#D�p|I�%Ո�$�|(�D'��/�k��Dy�B�{\H��|�4s#���53�8y�Vy�g�����Zg�ǵ��p���������g �
���"97Tu0',�iN,G�6�$���J�(�U�➠Y"�&v��0������?�4<�.�pίq�a�ۃ����|p>R������zJx���X�>{$|zG$�=��ylB-�`߾r(�*|��d�:ķT�wl$�j�npWUķ���!���� �v���w4�ۺ��/���4K?��ݴɈ0��0z����U�Ra!�8Ps��U�G��4<��T����K��D��h)���/��i/O[��)��!�]�0I��lM��n/E�*�{�)~����@�!�!_~��T�a8�QI:�t��:'z�C������`�k[m(G�i��yw��y�kt�_rh�p���Ε[8`Ifq���iܳ>�	�#�`�t�}.��P�:8Zj�x1y[7n?�������hz�����]ÐP�g���s�����Z`g!<�ʯ|�I>���u�-�d�b��Ӕ��x�$���ɡ��/�@o�%q�&ս�	�:_w�������=o�T�*^[�^���sKema�/�/��h-���=[�V{K�7���_X���.�D8{2�p y#kUB>R���"�"��&�F��<���zG	G ���7 茵�$;��α�_��
gZ�����Yq.�{�Ʋ�x�Ⱦ^m{��_�tX��*"��R\�(�'���/H��x\p�|Jl���܂@C�_0� ��Z����©A�?�l���f��G�2$/���~�/�Mn����QQ[8Wvda�qtl�qb��].F���Y�1���6ܰ�DR���ď��2Q��6zC����K����ƛE�ҕ3���/`X.+�sr� �s;S�K��K�|%]&���K��t��I���M8l��~��~M8/
���R�V�1v��ĳ>8/��<jV�K�(�~�-?��!H��g�(? ?�v ?�Ů������G&=�Q�ϒ�v��a;��]=}Bu['
����5ͩ�I��7lH���Vl�/���d4�O�Շ}}C0�b���ɭK J��hTf��)͗�' �S� �'W_�l3�N� ~�e#O�
y��Bhd��b�/�	�����ۼ�V�jlC:����To�D�\$ա�)$J�ؠ���4~��"�9���'繶��m��qi�g��9�E���s��ɢ�h�I%?�d'?%�j��?*���-�y�	�����l�zY��[/�P�Xf��K�]Ϗe^.��'k��3�y5@��U
��09PE��K���&�*
��V5�SE5X��Z�Ȱ�*�s��=.?��c�DK~�mF:�T�{kt��ٖN�~������.i裣6%h�(Q����y�,橶��$��U	Irz���!H���i!H�,�kn�a\H�m���*��]kU��+�GK:��qq��S6	�����
�h��x����$�M;���^G�ܬuQ.ڔ@^L�x�r��׳(c��t��#uA>�B}WI��x�\'~,ģ��x�R>R;�U�X����J��0���Q[�س�Q7_I�#���і�����i`0?�w�_����ި�2���@V�HS�T$��p��Aee����F���vb7&䋕�FC�c6�1���xF�u�ub�1T��v�K���`�+?�x\3�%�����[q�����i��|wɑ��9ɕC.r;�,�"��AY�K��O)(����9�s4���L�:�^�h�I}7<�6ϲk�X�/��|d�Jk��\��r\s��q� E��[�M��"2s�lC�k�D_���?u�'[��Sa�w7aGy����g=E�x������5J�T��cٞn�'Df��@���y��/c&�*� ��?g�EG-fcq�@ഩQH� ������+������ZG�3���؋�e�(�u�ڕ��5:��ً"��
s96�]�PR���J���\�P�w�y�Ⱉ��B�o�uD,;U�$"v���vz�[_�m�[ZG�p'a�9K���Z��h��v�v�r��՚`����x���Z�B�m�{L�c�傡�u�"V.������ct� 9u�A}�o��3�&&a`_l�5ط(� ���bq��E��m��Oy>�b1 Bl�Q�?D�Ғ�Z�ԁhD*SFj�r%R��V;+$!�!<y�"�V*-���.�#i�P �uX<}¿�|����Q�pN����b�z�Y?��r�������º���y8�o�W�E��!W��MSt.n ;�]��?�&��o�(e�������a��O�?E�o�8��@�|�+����3����<˗�p�d{��n�u��pA�����pёE�ؓ��+i�Zt�ĢFU|i,|P]B���"�!��S�}y"L�b4�[���n}�Y��4���őu�Yd`82CT+����T!�� '�Q���i2_TH{��k�ƕ2Dǯ�h��w�oR���y4K�PS>��YS�_̛`����������6���^!�ؔ� xU�����C��t�|���W#��f�k�5b���o�����w��w�ʯ�-���U�o�N��:�6����U�^җ�i���tZ~�E���d"�ߝ�PL>,w�V� ,3�(�^3��s����|=�^����Η��_�}�U�_�����Yߨ(0������uM 
X&"�Ye���.��b�Z��KZ.�����ެ�2ԪAS����T�H��w#�oٽ�s�,^M�t�X�Ϻ7������b�D� 6��J͗���r�i_M�څoeSm�0�\���6����+�I{���x�n���G.p|&��%��0//	WXt?�%���(�g�e��M�����ӗ�	}D���^�r�j.l��,�+�_�z�|-�3j�z�AA�
L�g�UJz�倞O�'z�,���ۆ��{$zf7#zN�@z�-�)��XE��/
C_���e�>�zN�dOϮ"��k����=����4��V�]a78u�x?�����a<��J�}.-��e>O`�e?K�o0�&�f�i���4���n�ozK�B�����iE��~�(�"��M��q��7��9��������@s���
a���_���Y����K�z%S�oY^�n;N�k����߲p����E�}b�
����Z�#��J����J���~����`$���])��!��k<FX8Vv��fz�;�����*g˩ejgKZ�z'�.;yCk'}�{)�?υ�<��Z<^�ߛ�����Ӆ
�|gK���d�\[����#�c�ߕ�b~����d)֭��mN��t���}C(=��e-�����Z���2ѳC�Ng<#f���M�/v�wO��xm�������[������R��_��}�}+Ħ��+1"�����gvQ���ߒ�[��-�:�RP���yU�fYN�b��4��3_��Zd���� 7��ܳ��{�G�P�=뒎�� Zn8��?z�,�e�����-8�]��Yh��81�y�)Qu�Js&���>E,�0�u�`�"X�Y>0���Ԉ�����n+��m'g��*1G�W���c��#����F��*PC�oX$���cE�ߜ�F<B��T���qZ��ɥ�<�@<G���q�'��	��Z�"Ns����
 |,���{2F�9F�J��8�c"�'�C����K���q��%|g�F��?]�/{^*��wpbܿ��/����O^�w���J,��K����e�O�����u�����>���(.���|c�l�QFLZ9�*
j�W���X��XXZ�������_��+A�ߚ��z�ÉLSi�'_��K�����/U�?�S��t�JyNS�Rr����`����B�F��%��D��.� �WX	�>���_CJjr�]����"����8|9���Hބ���%�c�}�nѝ�f'�f�7��Z?���~����/T�X���yL�e���ȫ
��] ��<S���y��Љ��\*�˹����<��T����򲊦s������F^R��y�s}&�U�K��Jy���RA��_*�e���X^f.#y�������cĿ�(yi��2m�J^��'y9vBS^�~�����Z�����1�3y)�D!/H���e��*/u�;��V�%yY�ؑ���́���2m�B^z�����������K(�4��?Q�'j�R^�/R���dk�PPg�
y���?��~K��P�e�CĿn����.���c�J^��#yY�������%j���4Z��8�XE���6�r~�B^�"�)(�3����w��K酒���H^��v /���#]!/ş!�w�P����l��B�ϚG*��3K)/;(����?WP'�s�����K�EJyq)����>��&QC^.z��Ԛ�����$/��4��b�����%/���)�衊�f��˚/�6WA��s�Wy9xۉ�\�/�K�����˙�e�|A^j�V��6��W�K��6�rm>�g�}��(�e�|��`�����i��B^~����K���Q��]���0y��4����U�C�|DS^j/T���D-y9��#�>���	_(�)�|��"��hʋ#�E&%�F��Z)���d�<�r���S�.��(/MEyi�24ǁ�$���y�B^��>�3T%/�3m�e�<�O�=�~�W�b?7O���Z�f���r�e?G�٢�%Ł�����csI��7�ӟ����0��-��q�3����L�`��!-w�Ǘx<s�Kz�����x��U��������m0Ko�Y���B�}|���a�M'�b�$����CO����\q�����椯#��?������玒>?��<WAp 0��2}
ϔ����G��\���Q��vN�׃4�!�8����*y��C�P���<�Px�%�?#�����R�?�o�O���y8J�.~�U�\K@*b٤�RQE���sP*J�!�s�XZ�(�Dy��at �sy85Ri�>n�����3l��9�����ϒi
���QЧ"��Od�<�D��[��?��Ϥ���l*����=
�ћ�v�@��G�X7S%��H8^�i	ǵ�V���7��R�6�߬����϶�I1~� E���8��d�D�C���]��jb��Y(��攱������G�i������o�B>�V����N���΢�/�s��B�Єli��1��*0Xagf(�C3&��bh���"��3����xpb�H!#d`DAɘ��20V����K�:z#o�����Z�:���f�YJHPi���@�6*p�(Z (���+�hoe 4���ei�.HK�OQZ��Ѭ���R�/�Dy���,G��O���0A^ zi�;���ߏm��������^��*y����T�OW�k�t��̜.��a�,1!���}
�)^�1S����r6�*�V�3�NV[���(HQ&� }8�i�Y��1ГfY�{�\��y�rT'����.����џ�(�	3k��0��D9���������'���I� ��雭S��.� ?�(�M%R�k>T�O�,�)�	�����Tr�J~~0����XA�>+��ǒ��-�r0�2"S���o.����gT�I�l��ߴ�M�O����Z������f���ɪ
9A�V�w�����sΉ���(���o�7Ə�?���A
}s��hBu��T��g#�����u~�J^&U��r�e)�U7K!/ղ����5C�7;
��].� 6�v�o��v���X%H��� ��S[ߔ�D�oN���7ۧ#]�^V�e�D[90]!GH�La�e:�7�<�t$O���zƉ<}<M�����i�(OP��5��@���	����^W���K%O'&���W8�����'T�To�J� ���(�v~�B��Nq"O�\����HrE�����h}w���=���V��iYj��G����Tm1����������������>��m���
�B��HA���ru+_�Oo�_7>�d�.[�_o8�������l���S�/�T��Cm�L�����9��Ot��O<�R�'�b����~���~��g=�cq��5J�'g�6=4�P��Q2FLUm�&M�-ԦmZ[�e8%�F���_�d�x�S��ñ��؍w�$y��'9�_G��ڿ0L#��$Ҹ'J��\�V��� L��b���S����A�5
B}�?G2����?��f���'�_�r�����?^���,4���!��v̐��Nr!�������(�y�r�Ob�B9���Pn��x�����0���L�156�8�^(
D^(ʃHT����K��d\y�}0�O �5�"��m��s���?gC��.?�5����4��(�72]1�2v�;:A�|5�k9�/���~8��~�"ٯ?�rn��Lw4������ϟ%�Ǩ�?�v�O!������Q�>R��p�3^��������ׁ�Q�?��􋱱_��H|�����b�$��0n�?o�6^dZ��e�vӲ_C?���h����d���X9NA���4�׿��)���,�������h�qy� �{+�c�i:�謒��t��1��/5}ꦩ���$�|��*�3a�B>��J����x�i��_�o�OPD�NP�H����E$}�r�%5&��Oڌ?�V>LT�`z�� �34����;�KS��Y�89�˟ ��?.��u�;�S�'��ߞJ��_���������N���	��g��|o����;�&1]A�~�
�蒮}��q�Wk"ٙ���|�E�������f������J�q*Y�3�d%�g�ýH���/��Bj>e+'��#�W��m�͹���
)AJ��D�1��@"�Y��^<�,�qR>Ծ�}�H��Q��6U��F��|�ߌ��ni����\����j�C���n��C�i�T�|����PW�K�P�9.h@H��z�v�Z!}�N��^+�����1�:�8깤�z ��%P�C��w���0��' ۻ�y�8�|8�:��2V���;�H����i	�_F���������|��xg��ۇ^u�a�:@��Q�[�5+���tq�K�j���g��2��:�H��������[Rk��;oa�x�U��	��bW��x��MR��!�ƊW��0�������;��.���a|�e+h\{���;�Qz�1޳7�uS|��xu��[.]5�	��G��Z#�x�&9��.�7w��ߝ���M��l�c��B$���G���4��!�d����S�'��"��������O=���Me��Wc�Z5����)�)c(��(���L�ΈyE��?�>�?�nP��B
�ƾp6
ِ"M;|)/�\qXl�>-�?}�s��po�Zj$VA��E�6�`Ȝ�ӥ���5�|G]����b:�@����t��`w�X��/]�T���^x�C��p�	�d�Yj�p�k���������-#_�� Tc|��!= �Ta�<o���|��hw	����k�*�$]<D�IZ8	�t�\�7��*���P��H$n�5��M%�?�I]��R]҈H��im:���&";*�j~\�>�Hcχ>������G�D?�%���`��u�#x;�+��o�^b%����� �ٞQVᇊ���d.��<��\��?�Z�/���	���H�߿i9�V��p�:�-����t�>��������S����dO��	��֦���"��$���,������U�_7�_��ng�,����Q��P���o��`���|��~�$�C��?BC������7I�?B-�#%�(��0���Tqm�5m�4��^�\X�o��/0"&I��w�"QCh��"ΞFFԞe+���iyj�M֢�o���V������`ȋ�X��������da���NTq d�ȁ/��9P8�c�V}�ˏu;��c���{�ȳњ	Z�E�%���� l:��N����7�x�����a��p�C~�~�����5Lŏ����('�c�`?����ϯN��(Q�ǲݴ���:����@m~�$�DM_�����~��G�P{~L��0<uƏm?����Q}�ȏ�~"?.$�����O~��������9`?���`��͏�c�"�t4������*~�lϏ�}�[;�G�#"?�V�c���������G~��O~�;�G��?>ډD���yPa>��8m~�ӌ�'jz��'��o��&Nŏ���ѯ���3~����1H���"?z���� ?F����?���nubO}2X��^���=�K�\�Y��o��r������ϫ~��=�s??>hϏ��${j���Q�S���� rc/��T����ʞ}��	�K��?v�g�K�!�Ço��H?Q�}�g܇��~���x{�w�)���6���_(^E���"�#z��_�OE��}�7{6y�}�9P�G�����vPjS�_�W[�4&�����>��>���Z��4���w���>�Sq`� �y=D��P��.���G�N�Û�|���w����	�/����`mH���}���o�û�U�(�ߞ������hχ�?Dn<��Ƶ�"7�u����j>D�热�/VEy�@y��j����Y�� u_���n��8�nm��_���Mq��Ʌ���,i �im�����t8�S�A��ďX-~�	���O��הdNO?�X�"9�@
����v%��m���0M��C~���Пu�PŜ��D�,�*2�Por ����C�D���O���d��I���?��#�m��d?Q��Ч}����U�?�h�?bd�s�^�)�?���}%�G�����t����s2?">��ǦH�Sۑ�͸�3Kwg�#�>�O�A�u�o�GJw����m??fv��{�ȍǕ�Ios��#2gBg�9W{(���]U�����cl����?����S~=��.�A_���:tsƟ�b��[i�*u�o��gW������N��������?������=U����ȟ�D������.�^������[�_Ɵ��ö mKև��1o�_���>P���`����61��_�������|�;�_'D�U6Vł�=E��(�`gW��J�L�+��L�'�m��}���<���4J�C2�$hv]�?�l|[;,���C�.V�<�?��Swq���5#ر�
���O�ݣ��c]_v/�Z���*d���n)��=)��^��	��Ƭ{)���ǐ��2��:���6y��^�UZ�As���b���9	��$l�I�̎F#��@���M��qij��}���%���r�+Z%�-���yzI�[^䜋yY�7�żN7��W�.�yJQ�Owż>�����ҟ�͗+��5�%}S���\�q�f;�E�������S���o�����h��"$>l��`?�Ȉ�cT�����s�ȈN�*}�����k�"����eVh�����񟫑��P�yr���(����l���jb�ߩ-��i������(�u�������v�k��V��Eb@�.*��0� 2�HG�u��;�ů�C���3�#��UH�N�H���?ҩ����R��Сl�����������-������BI�G��gI�����R��W������m���:�[��P�x*������;���+�!�^g@.w�8�X��haEq㲅���c;��W��|ޗ�WBx�:wT7~؉J۶�)��,�;���m���ч��c���R�&2� O��ʦ�����o@�:��c^%��H�V�]�V,ǞT7�SB�-��;q%	���6���z�|���r�@*��¿�e0��ϫ.�_��?K����l|����uP?"�B�B���_�b���u6��#:���5��ٶ�B������o��~�꣬�b|ҵ[��mϚ*�s��dZ���d�i�̇��:]��!�s���d�z��lp%V�I�d;��^���2z������c�"����T��а��0)ڮ�:���ll� �3ƣ~�i��������{�>�������N�>��m��~*����N[�X��4��9:��Y��J,�>�d�����s1���H�T��|���j�[R�rF�U�cS4��\�%��?�̆���.�
��L)���3�U�?L-�p|)z�_�f�R<��W��|�)�����<𼿏e����%��.I����bѫEU�W)nBQV�>Uju�j�PP������V��o�,��`2�b�^�[��{�����U�P�|>>�[]�G-�`�n{��q~}�$�sA���u�j��2`-�5�=&��	�W�v���	Y:/��z��ӄ��?�_;���.��%��B~:�S�R&��m��!D�jփ���K��&�Kk�V��~���/-fW�:�����F7&��L��F����]k�K��}�:������Of���4�w`��o����^:�?N�ߘ��0�_E��
�4g�+��O|���k���m4�{���r[�?���UU8�>m���G)y/�����=������&D?����e��oXI��ە9�E!�������/�x�%mh1�\�Ǯa���j<<�:�]���v���)U���nRza�Z�ԧ�p�+$s���T���[�
p:_e����4�FsӃC����u��D�\�)�v����a����]�o�����TI`�ܕ�(fd����"M��GW�4��9�Dy���jphs��ZHf�KX���1� ̲��Wr���-�6<�5�:���>���.� �=W��&+~��&�5S���ѓ�0�������;�G���)F�ޙ#n)��f�q���#L�}�4�Q�0�Z�f�	�K!9�.|�ʅF@�m�5;�o����	5C��qI��cYI��*��n�ѯ�&~�Q�p����[f�,ˎ�/(��3�B��L�`���2�(�W�x͇7p-�Ԯ���|j������`�L�����?�/�[N��M����\�<l��C�%W6�VSr喪��b�SU��"�(����A��N�]����.�~��B�=�~�>����%�2®&G3�R&���������[0& �J�X.�Z�����1U6cZ�n+|춚�v[uwTǵ$-��}\�O�@q�����}��Mh���K8L�p�a�[�z�0�a����eW�-�j~ �sa��Ngt;���nX�0���"�-�7��}�}8�:�Jht��w4�̗ir�]�o$l�p\
��J�o�[���G�A~���['��7�q�1�>ȩ�w��χ�f��v�lD56o�U�:M����6b�'oV'M������W�b�+KC���Ճ ����6����Ղ�Φ��6s��p�F��������Rh�]��]h��guQ"�5_]�D�_\i#\�\�-�ª����"�{�ob���R�����p�2����)Ã5�����}8>{�a"�a�X�@j�t�h�~��6`3��.�<�1��U�_�[K��7���2$#��U�]�O���]sEޙ��o�{�doX����B��t�r���-�������So��͡��R�a�[���cZO�[���@�j=���v��4��t���L�'{?��	�։��p� :m%zO~(���W��qSxO6�ޓAj��9�}�
gI�V���`��P�aUK�e�}"�2+�(SZ��(S�am���-���XjX׮a��j�IG��T�M���\8�&
.�+C��n��Ay���ۤ�3n�@�Z��iw���S�eS�W���W���F2X�7�zܟ`�$C�6u��5�v�r��Ю0oӟ�����1�U�$�[�M
���`I���_q8�
���m�;!�;C["��6��=�XP��o���7-��gB+��$�ί��I�J˿˦��$�9�G.�B�H�����,Zh����&8z�Chp�5��5�u,�x�I����Q��t���2~�f���
���߽ͩR]����vӄv������������v~x�n�TwWk����K�u6y�@�$�oF����Z��=���Ю��n)�6o�W�'��c0/�W�'��?�����y�ܟ�*�7R��>nD~�k%ɯ2`��*TJ�*�hTxV4'#�\Y����t�$Q�$�2�D�!�Sϥ���s:J��~�vo��?} �����9 �ט�xXn*ۏ�����c�]��ϲI�lc����OydMc��2���`s���4�`���E�[(�!����ZE��K��.�ZY%�O 6l頠�O�*��_�g����Y�����kA�?�=x03=x��A���=��M�Hz�4>�-��h��b�|j�hE�����<�,H+�w�>���A�� �9>ι%ud��i��9`C���>*ؿ�[D�wK�W�������ө���)�������@�ߥ�'J�������S������m���O�B�ߐ�w�r�\D�����E4~��n���?P?�@�O�����������4~����o�߷��G����������C��)����m�c��S�?���������>���O�i��]�*���~5ZcXxn5�����|,�~4�|�::�+���ȸ�j5@+p�"s�"�1���4�Al���ܶ���W���in�����渙�0����^#2����6��?Cտ��xր��3��oԾHc��Hc�i�F?|%�Q>*>z���Mknt{���LQ+�����H`�Aё�5�� G�r�^��_!��N���`-��� =OsN�f{ܳ�J?��]wR��\��Ͼbܛ��I���`!�öU� (㞱U��Lc�MZ������Ȓ��.�����.@�ο�w��ʺX�wRQ�?W��p���Y�Ʒ�.���1����]�ͼA���d}z��1.����s\�2ui�����,�
Xbm��8�����m]��J�4��V���\�]v5���9i���[3o>�7o�^�S�/D�T�Oof���~��.��֙�]��al�z6<kZac8�����37Nd"�9?�H�E�N�C�f����\]]g���lRu���rT0X�d�_���|���o���a���!������t��`�o<И�S��hl-k��a��%�N�^��%V��r������0�6��}8�L|}�t��K��^=3�b�N1n�xkl:�鮾H�A|`��̥���yO�is%u=�Z$�����,����&��� D���P\�����qm�;�A�MA'��n�7�.�����s�����k(u���,㟳�M
3�$���6��¹2�8����@״�yn��!+*G[��h�;��������I>/�m��^>�X�	�z�]3��ndR�Ϙ�ġ��F�������䓚�84���W3��.:.~x���C�|B�����Z��ѽ�KM�K�2t�`�AI)>5Su��&& )	�I�c�÷qB����g��m����MMKI�7t�.�C���~�܄�����/i������:��S=ȧc��H�V���.1)_;(%i�!9%)>!5����%
����-�K�KJҘ��O��� �_B#yx?���RR�R�em���'�L��X˴�a��L�a�:���ؤ�)�g��		S��ɉ	#F�����3t�O��z	#�P?�� ��"&"*:2�_HLώ�����t������Q[�C�|�e�	|�W}�DbR�����94u�����q�cG��4~��P�K�%ǥp����'�3�ӂ��08)e,P99!%�?�/|Y?^�kx�N]z"c��(��klΉ���	���b�n��w}����MN�U3��
��~u������|�s4���?�v�����_ Ĕ���_�/5!����O�����SG�Ǉ쨿�ߡ�ȸ	����w��N�'�C��̶��{b�!	:�"�S�F��l���§��1	���o�q�C��ɠP�q#�qj�#|�?$��?(�υ���iI���i�kP�A�����A��㓒ǂ8��$�Ƥť�N�Eƥ�	@t�	)�mxILLJEH�P>�RB��ĸ�Ԅ�]�rwI�����b�9Z������qb��K�뺦čL�1'�l�78U׍�f��!q#��D�����m�Q$��)�$��`���Đ��22�V�2�F���K&�h�}OUuf�M$�KQ�:U��l�o�I*�4��$�mPIQ��|�����Վ���d�w�`��q�M��b�z��nX�=?�wY����Z*ԣ�Db����-���C{^���~K��tr������%ܧ �o���lE4mSƻ���i��v��+?H�tS����?�l��RE�yɉ��>�?n_�]��D�Gt�u�����ջ�D4�^��
e���&j`ۍY�9Z���!�x���hc���@ϛ,�
����{���2�$r����+�Runӭzsȥ�˷�k�K诛z#xթ9�z�v�������u��:R��"Mw@ü���^[��V��
K#���޼u�] ��I��qVϬ�|+MY��7#&�u�,J=자�C�H�}R6�`�:��29�fnNg/]=�*�>��P�צ>��G��0R�E\ɱު� Z'L�:�����CnʯC�KrU۷�vu ���5��G�9��a��?[T��i���g���*5��u�h:���W�r�3ݰ7F��)Z1N�7�qq1V��l���:�)���'n�L1�>�����l�x������P�P�Dw̟$���k�ű���O�p��Y���<2�"���"m͠0	���*��&�N5P^EJ�N������%񛜲�y��.��]��"�R�'�4���4��Qz���Cl��r6J�@.�Z�((	����,��3��u�­�qR�oq�,A��P�ą�?���H�J��L\W�4�O�md�>a����H)yHG��bu�J��<	�a��b�:*�b�w��'�"���h`��,���t��K�	3����Ťأhf����,iɟ�;v�A��?Q�$��cR��)��EcF9"��J�^j]����zؙ~b���l���ڮ^��1�x�̽|SY�7~�2Zi7�.jW���-t�:�ѦMچ�M&I��ڴ	4�6�$�2VQ;����UQqD��**�u�*�.��n_W�e���+?E7��}�s��o��߯.���y�s���?���؞����D�y�hG�����Q�Ҳ�u�=�)�E7���\vSzO�X2��5�Ǔ�x�����a,5���&S9׮�d̕�����=�K�|� �m�J$cZ_*��<ގ�@װ�c8��
�<����t���]�{'S�qWj*��QvE�8r���IW,>:�����t�k}��g,:9O&��ɸ���]�~�kf��=�w��;�~����u5j7�ݮ�tbr�k*�K��]��+�J&��#��Tn�E!��Ĺ?��3S��#�\"5�H�2�7����xvO.����6F2��lt��7J�<ywΕ�f�qW|:>�f��^���ɕNƣ g��T&G��鐍�#�Օ��#_��5?S/���6%���
b� �q<i<�xd~zϰTb�w�s�cѱ��0B ���2|r��%�z���\<CI�7n���܏"}vgRS�1����dj,���})>�OgR�3�lv8��?9V��J�Ȏ���X*�S���LD����l.>�ȩ����L47�ܧX$�^Z�g��$UM(��g2�D6g�>:6G�Sɨ���d6M&�d<k~,>̋�,av�M잌�P�Lie�gvo��V>G}Ύ�e��/��Djo��K�'ߍ�C�]�ק�9�cH�LJ�j�(���ƣ���M�,�[�χ���}y5��!<q4αl���˧����Z8��Ke�2��Ծ�d*+��%���`,�C�k���Z��l<�7f��O�Q�*8����?��֏n*=���3�Tƪ=G���.��Tr���k�?�$��L��@�Uk:�ttߤ���->�n2c����p�G�.pF�����O���\<�Q2�Lee��+`��kj2>���A<�_�`_��j8�eR��ON�F��ة\A����͠Q��Gc����s�c�t�D�a���4d}�}��"�Q�=�d�	����lEHg{�_+��)׋$cG���+���짴!�k*K^pvb��#����
�#�~��{bqa�T6�i41���X� r�Phn��7���qA�;:%���ʋPF�_G҆]��O*,Rx>g͂k}��7r��C۝A* �ݗ����)D��4>����56�Ƥd,�e*1��ʑ`z*;N�ں�Ҙ�J�hr�&��]���x@��V?��^f�	�E���+��y�e������x�Ao��T�\�`�T\�W��p!�& �JPD�F���]�%if	[��J��w��̞��_,��������/�_�_lë�/V�U헒�k�-ï�_l�+�K���=R�����e��:}�q+k����/���Ix;{�b��ƞ��~(g��6��(���{��k{�D.���4��Q��s�T3��v<ݯ�+��.��w�=_s�}�W��Z�ύmJe�3q6LR�X�i�(]*�5��}��a�GX��������R���Sz�
���^�ݸa������m��L�Q�!��U!�[Տ#�{<��I'c� ~kY��
�^���d���D2;�x|�H�ׁ�ޯ�y�^w�{?N|4��ϰ�]z�z�M��f�Ͳ�B�b��M�2�,�sh s��w�<}=�>�-1�{ˤ�F5S�Q^P�2	6-�ФY!��ҋ2�qxV�HLěs�� M�s�R�=�h�rH�=��Α�ɍcB'̒\\3"��v�~�<Q4Y�L%rBw�����p<̤��]��O-7��o819wK�:��n>+7Θ�� J�ci"��$Q^(E:��S���Mzp��Ї�DX�C,a�x����	�R�Hq�2苑1(��0��%v��^n���!��0av��H�dQy�ԇ5�q�Ԫ�yK�Ȅ��4Rw�W�3{ �.&6����1bsV�r#Vd(��y"Eg��)�ٽI3�I�c�$Ǉ#��B���K��#QW�j I��1����(ͯդ	��5f�Tf,>���&kS�95ӹDL���e�2
k���0�-��LI��#wd�dFM���J��k��2�}Eg��VںCC%Oy�+��f!L�\��1xMWQty�b+�v<=x�xF���s�)<g�\�s� w����L����
�mJp��R�l�	f�9X�{c�)�J��k�nŽ�|��fhi�E��!��YI	)_�+voբ�B�-�My�����-'��[���S���-��SX�s���{ׇ����e��g�����a��C�c (�$T^W�wC�)�l0N;a� ;�Ə1!<��G�N2�M���p£P��dO���$l�	�D�ʸ0�s�,����'��!���N��2� �S-0<R�ʻ^�7�	�`��06��m~-M�(��A�A#�QZgJdYKKlB��:߶Z���d]�B�͗���W��� Y�e�S���<Y�͇�r�;�gHޏY3�`����vQ�Ϥ&SS��]]H؝�29�
���Pٵ���*�_��&�]�~�+Ky|���?�^�29Ws�~_�/���F3���Q�i�I�<V@6�F����)1��İ�k���6�4�)
���%+������5�('�$Y�Tz�A+�|��q���0�wjQ�6]��x��s	�ӏ��<����9�ǃG�4c��K��§�2I�_;���z	���X|2������a�4B�&WXZI�V>ݲ�a^�iXv��/j�n^f�!<:��,̞.�����f���4RI�MD�B?�sI�7A+�Q��p��Dn��1��`�%x'�i��%���44�I�]��ދ�`�v�h��&3��ntYqib���eЈH#������{яN�'�E}!0J�hN�'TaY�2j�I��9�(�3�t`r�$�+��E�^���kiZ*>9F��L�F`.y�F�տ+SbzwY�#�4et��JGd\��#��=���}PH�Jd��l6QNW�2��ɶKP��M����4{�yVu?ڥ��l��6iݳ��$�K�ɓ�� �����$��T���B�Q��P��̧L�M�L5�=ڌ"dSI�/4��,O
0����⻢S�:ȉ4a?M������#�bLH�څ�1���1��+!L�F)����3��2�hG��\a�l�������j^<#����D�9��E##dǣP���h�jnz?"���I�$F�SH���T��,���:�;�[H��!��'�j���1��b!���1M����dF��cT�P�RjK�I3j}��J ��f�Ֆ<���iZH�0j�Ҝ��&+	i$+�^z�2>�c&���M�Bcz<1�ض��x��Ғ-kD'&H�]�DT1�vO�P��7ZD�O�S_R�qʦ)TV��*���
��7�R)T�d|wtl�����E��D&7���S����$��e�>15��1�����(d�MR8Rcl-H�SZ�b���Ek{���b��p`�TB8@38�	$"r� /3$E�kRL��!����@���,͂�N'�����h&�'N�lС.�5g⻦P�`z"�Q�2����F� OKJiD�_X��<��i�ZN��f�y+��H�E�S��,Z�Kڕ�-cʼ�씯�jJ1F�)i�MW*Ên:ՌD�%T�fibR�jfINÙl3�,+/����x��h*5������qiq85�kN킏�O���F?��,/��$O"T�fy�4���4�h"����{-��Ӥ���>Z�.��J���_9�MO�AAG���1������`n΍S��YU�`��))%�,��ʹ����e"�P��J6mV�en慅6�vN�EJ�S3Y=�!rG�z�sZ�b���,ԒR�5�SR��(bH٧��l� ʺ�ʵʮ�
�DX��T&���I�f&kst7���PU`�`�����R���jl9�cJ��#r���Ơ�1��JsռC�P���`i��
��@nf�Gb�zD
�hf�P��	d�UՍ*���a絼��b�a�Y�ɋI]\�\��h��GE��&wdɣAqd֐��؂�Ƨ#�5F��g�V�Z"JKe2�fm܂�6�Z�yl,8R���|l*ΈS�dl7��j>@U�N��c�D,��DI�TJ��<�⹱q^n����4�]L�VhִGTk��9I�*/K�%;Z��b>J��E��F��R�J�%5�J�yJ����u�-�"ϼ����,�
�������
�K�P���glE;-�7+�����"��LMc6�k*�K� �<�5I{<�}�DN��Dxx*���m¸ڒ�%{7JK-$�p�dؐC�!�J`5���]j"W-�"��dj�J��Ly��F�,��Bͭ\�gY�f�YC�2�hRZ*8qrE�<k��jX$Mr�#5� ʹ|�Y�\Idɪ�\K��sVv�ٶ�~������:4j��$S���T��]vO"��3<�g����LQ<��$��x���O=xgrVw�*�i<G��s�5<k��O�[��x���s�%<74O=��������P#�5xnL��x��9����x����q��smt�9��$�#x�����ӂ�����~inI[�-����NTU0/�F��~ʛ4�-��b�wrj?imx*�_�Ӊ�ɗ������_�-�C@�d���M%���&;�B4��P��Oݼ���nZ��oA�r(~��԰��w�7��f5�hֵ���ݲZ)AÀ0z�(y�6��װ4�%Y)�x?��Qى����=>����-[j�H����bԃ�R��W��\��!o8<��ݝ��n/mZ1�Nol3������O����6�I4qG�fz(����C�B�!}�`�������3��y1���:CZ>G�M�����}z�!�Fà��4Yڬ�4;�L)��3����&1_�V��Q�u�FB����3B[�����ao�@�p��k������i��^_�G������[3�|��>�ߚ��v��6j;}A�7����qDz!߃^SX��ް�?`A��G�!J��^��s���s�`�����XQ=[�ɾp�]�Y����M�����fb_�����9�����
7���
�G��h&�vJ�i1�T��B��:4sdf��v$q?�73�娇}ݖ魣w�M4Y�~�1Bߨ�qe������_������ѓ�[�>��^%�}���=�\��I�3�!^{TZ�@w�o��_0������΁�/�ݠ���5Ճ8�n����ߠ�1Qy�M���9g�v����������5��B��1�/��BN9fbCޠ;d��R�B��9����@8b�ے�6�H�+�Z4�F�Zܬ��F�a9��L94ݡ�@����I1���y�0���Im���AC>	�FҲo�������������>���c�	Dz�!�`W�љ�3`j����v��� {
  typedef internal::Types39<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, internal::None,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None, internal::None, internal::None,
    internal::None> {
  typedef internal::Types40<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39,
      T40> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, internal::None,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None, internal::None, internal::None> {
  typedef internal::Types41<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, internal::None,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None, internal::None> {
  typedef internal::Types42<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None, internal::None> {
  typedef internal::Types43<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None> {
  typedef internal::Types44<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    internal::None, internal::None, internal::None, internal::None,
    internal::None> {
  typedef internal::Types45<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45,
    typename T46>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    T46, internal::None, internal::None, internal::None, internal::None> {
  typedef internal::Types46<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45, T46> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45,
    typename T46, typename T47>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    T46, T47, internal::None, internal::None, internal::None> {
  typedef internal::Types47<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45, T46, T47> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45,
    typename T46, typename T47, typename T48>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    T46, T47, T48, internal::None, internal::None> {
  typedef internal::Types48<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45, T46, T47, T48> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45,
    typename T46, typename T47, typename T48, typename T49>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    T46, T47, T48, T49, internal::None> {
  typedef internal::Types49<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45, T46, T47, T48, T49> type;
};

namespace internal {

#define GTEST_TEMPLATE_ template <typename T> class

// The template "selector" struct TemplateSel<Tmpl> is used to
// represent Tmpl, which must be a class template with one type
// parameter, as a type.  TemplateSel<Tmpl>::Bind<T>::type is defined
// as the type Tmpl<T>.  This allows us to actually instantiate the
// template "selected" by TemplateSel<Tmpl>.
//
// This trick is necessary for simulating typedef for class templates,
// which C++ doesn't support directly.
template <GTEST_TEMPLATE_ Tmpl>
struct TemplateSel {
  template <typename T>
  struct Bind {
    typedef Tmpl<T> type;
  };
};

#define GTEST_BIND_(TmplSel, T) \
  TmplSel::template Bind<T>::type

// A unique struct template used as the default value for the
// arguments of class template Templates.  This allows us to simulate
// variadic templates (e.g. Templates<int>, Templates<int, double>,
// and etc), which C++ doesn't support directly.
template <typename T>
struct NoneT {};

// The following family of struct and struct templates are used to
// represent template lists.  In particular, TemplatesN<T1, T2, ...,
// TN> represents a list of N templates (T1, T2, ..., and TN).  Except
// for Templates0, every struct in the family has two member types:
// Head for the selector of the first template in the list, and Tail
// for the rest of the list.

// The empty template list.
struct Templates0 {};

// Template lists of length 1, 2, 3, and so on.

template <GTEST_TEMPLATE_ T1>
struct Templates1 {
  typedef TemplateSel<T1> Head;
  typedef Templates0 Tail;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2>
struct Templates2 {
  typedef TemplateSel<T1> Head;
  typedef Templates1<T2> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3>
struct Templates3 {
  typedef TemplateSel<T1> Head;
  typedef Templates2<T2, T3> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4>
struct Templates4 {
  typedef TemplateSel<T1> Head;
  typedef Templates3<T2, T3, T4> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5>
struct Templates5 {
  typedef TemplateSel<T1> Head;
  typedef Templates4<T2, T3, T4, T5> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6>
struct Templates6 {
  typedef TemplateSel<T1> Head;
  typedef Templates5<T2, T3, T4, T5, T6> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7>
struct Templates7 {
  typedef TemplateSel<T1> Head;
  typedef Templates6<T2, T3, T4, T5, T6, T7> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8>
struct Templates8 {
  typedef TemplateSel<T1> Head;
  typedef Templates7<T2, T3, T4, T5, T6, T7, T8> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9>
struct Templates9 {
  typedef TemplateSel<T1> Head;
  typedef Templates8<T2, T3, T4, T5, T6, T7, T8, T9> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
   ��F8K���j����3djt�J��������t^{Q��M�3W�dɦ��b6SJ�E��������|�:��C��E�|;'�Z�S;�y'�=������}�P��P���.U���+����ϔ������W
�m��C�U�������o��,�߸��p?��ۈ?
��p�����F����m�_��Ɔۈ�Qʻ�){v��׼�(�e9�B3V5,�R8�B���Z8��?�_�{��˯���gE��gk�?�j������G���պss� ��¢�<�?3�O��ρ��v翃_��/��S���p	~ã�߆O��~͋���r>���,�p�E��ρ�����?��%�y��� ��}�����{���_R���1���-��Y��?�>�e��u����}Sv����#�x��3��������|��0X��b������{v�JTU��"����~����E���M�Rn���-�VM����{Wc��z�C�>���R�.���o��r7s�9�h����J���܀��Z�%�x��v;�;�Xa�9�~�|��O���ˊ�P%��ʹ��/��:G�J.\���x��EݹD��}����o�:O���Y�l.*�jڗ���9�"�7��T�0�������]_�@Oz��8"��M���N��8���/B�p���n���P㺡���kY�q�9�3r����
�ﱟ[�8���_3��%9#��_���(��+���ռ���Y��%쟚�����A��|��9r��A�͖��s��9�g2���od�;��d!���X�ʿ;���I��O�\�qlat��:���P��R�0�^����4��%e�ze��y�����cB�Dگ��6�q?���_�J�+��{��s�|P���9������}=e������&�_�p�!}9�u!f���цrY�9u�i�v�����uQi����ү-�}�?���Y����0��ކ��^_}���/���)���?-���J�mQcmᏯ��i��k�{����(N�//�nߴ�� ��}�]���_��7Q{=�q�OTWP^ӎa;;�c��zaZ��������z�'��m����|Eѣ���Ny�#��|�����;Ȏ*mw�|��귨�E6����T���1e��a��P|�����:���B�S�[��>���������ݖk��Av� ���[s��?ᾧ�h�^ç��kG]��e�??!��n����S�����@Q|�>|]t¸�v1Σ]�;!X?�(�.�L��(��=�9Y�wgஹ�ty�]�tղ"����9Yyޅ�u��9���?�������'r�ɇ���nӟ��w��Y�?=;Vޟu��k;+�oi��;����2N��V֯?j��?Z�_��:�-�ݕ�C����6���a �[������O�{a�.�����w�����Q�s!���:���_V����ގ\��G��c4Q<q���,�-����L�|y��>�'�Eq�m�ϿZ�#XO6��i�o���+t�t�x���6<��L�h{�j��nAo�{���%�F4������.a����w��ﺿה�z���)����i�K�������*��`�{��0��bd��<����u��������b����ރ4`}�R��w���?�k������G�{�(��v�z�����a��_��#3+����WN�Q�v`��_�~��,���7�`����7�\���C�yle�O�\�O*�����J�{���e����!A�y��ƃ����|z�}���V&�h>1	���^wߡ{Q���;��۽�s���Ϗ`�<�r�x�o<Q��{34ߧ������wݙ�f���c<w�(���b5;W觺u�!�_}w���� |������T��~��e�[;�J%z*ڟK���>���E��7w���
v�Vt����������k�\�Q{;�~�Ѣ�"I��?f�7$���_���px4�I�wl��Z�g�+�K�W}�Q	�:��>^����<��cয়�w���h�5�g��hޮ��^�q���<�=ס����霩�h�AW�wJ��1M����Ge>��G��� �k�L�����2�ޥ�{8�����Z���>
i������`��x��C�ì��o�����b�C.���x�\Ξ��;���/B���������R���qqWwǌ"�Տ;x�Ơ�����������}�����<@�6���ug�Os���w=.���z���n�����-��l�?X�o��.G���Gn���NBtX|�.���'�?Z�4����{>���cEӽ�AZ���O[�c���π~ނ~�k�y��?n���݂����:�G,�u'Q�-��@�l����ל���3t��B�mqmn���4v��A�����{�zv�cw9���{::p�{r�*�}U�}�A~�1��m�b������GGY�y|H���	�P����0��$�������kHZ~dL	[W�fi]�-Q�.�g��*��E��f�n���sX��rJ;�[uS=L��n`>�y����~�~�����>�޹��}�l����(�����p�_�����>��������������������gK ��n^`����oq�D����,��b��K^4�\?g�믿E_��������[��2����������c��;r��\�Ys����+�K�=9������M��4��{��W����K��r�?�~YQ�_�Ӷ�(���P���S�g�W���wM��Ez|���+��7�H���"=��E:>mEz|�e�ߵf|�F��ܔ�W���{�+m�����Qx��g�����>�U���_Oï���~>>:����;�-�2��{�燝?�����^��^��W�c�W�c�W����G�z����x4�����ѩ��r��_�z�%�z~n��x�_ƫ��^=�/{�������S���x���|�Y�c^=�F��|����J�H�U�Q���7��B���,�	^��7�߮9��g�ٟ�k���>}�u>�>��W�������W��9ߧ�7�F�ׅ>=_���k�O�wG���
������ׯ�t������n���sj������A�#�u���?����O�������/���y���|����7m��G�K�u|�����u|'���^�㻬X���b��u|�W���zqn�؜?d���9^��O�'�q�X������~=���u{��u���������z������������a�_��^������2���:���u|��������t�������oz@���z����[��ﾀ^����L@�>����[�����7Z���G��;2Z��s����E��p��'��^�'��< �3.�G����1�_�����|��!9o�K�S�a9/����������¿/��x�����x��/��9/�'�+�d>�'ÿ�������S�|������^#�	x-|H0������On��dLP�'A��T��1'���}c���Š�V���>���MA�?<��î���^
��b_P�go�~����_���~P�/��rEH�/�Bz)���s���R��ˌ��_������_��������|;��l�y���:��?�D�{����:�����/���_ީ��<>������qH��g!�_�t����|���}�UH�?c�E�����p������%:�KJt�W������?X�_�%���K��˾��r�D����䶿��Dϯ�=�������� ���^�������K�O�_ea=�������fg�0^�g;��T��6�R}�=�7���?�.5�p�#���_����8���_����K��(�8_�#�����Iy��^����U���ۥ:���//��]G�ae:�>��2�m��-�q_�����Ҏ>�<g��:�(���a�#��վ��7�_�
�~o��+�>Ǭ�yst<%>���Z��}wمͣ�g���p]�>�0�}�_0׭��Ko~Q�[��@=��E����n}�:�o����s�߆r��=�n�����Wx]��͡�w���&�v�#Ơ[_�}��/Dr�_GĹ��[?a;��^F��������臌�P�<T������؄n}�!�V���>�B�_;��Ϝ���m|WT8��F�*�'<|����u���\��%���0��������#t�\]�v�MƠO3�{'��_��:㟴�7��.t�<����,�A�~�ѭ���/�[�3����܀n}�q�֟)��v�i*ѭ_s+ױ��%�ֿ�D�>ηЭ��4��u~�n������s|���֝|�&:��':��I���Bt�W��s���D�~ӫ��w�O��M�2����:������_�}�����}��B��d�Э_�Ct뛥Ч��]t�;�Mv+�I��Ht�d�����t+��N�����֠?j|�����o��0>�������y]|.Y?�>Y�k�<�F���������x�����99�n��i��W[�n�����g{ ��mO���$��?�ra���S���o�?����Gr�'���nG�`<��梗�`�b��v�[������/�9��o�F�PEy�#���g����:��g�By�d��A���~��Ưy��5��t�_�nw;��)o��0孯�孿�����2���wѭﱁ�X�c'��A�Эr��"����*t듴�[�d��Mfq_�?顼�Q�[?e��ݎ�J��+��k}���~K���w�Dy��F�>�~t�Ǹ�p;�2~t��<A�O3��֯iG���vt����[�(��s
�ݎ�N��w�ѭϳ��={ѭ�ӏn���w�ީ}�up�mG��P�����[��p���/�C��Qq�h��˦�v>���οO�V���|�v�g������t�����6���%�:6?�`!���)T��|���6oa�B�{&�O{�m�At��P��,�yU�� �OK�r���*��m����$~��Kރ���!�IU�s�į�������C&~�^�}�U;�߈j��V��rQ��ƿhB�z������_W���n�v��T����yR���S����͛���F��R�ͣ�]�ϋ2?��m^�=��j���N�>���~�F��~�yWJ�Z}~�n���&?�V�����G��k��iC��吏�)�h�>?�ۼ����j������֯g����n�#�6��6t��݄n��ס�����O;��y��	���?C���Э��!�����V~��裌Y�H��d}�P�����܎~�b�[_�k��O�������5�y|_E�� )t��{t������	�j�J�w��	��V�K>���bt�GG����m^�Q��R��et�g���7x��xfd��?�	��!T��|�93����m~���S؀n�v�ۼ�>t���5ڵyGe=�|�G(o�^D���_�r��P�n���m��t�����A�G���/���E�A�%?B�ߙ��{�3�ou:޲>�6o���o-B�y\�6����m^�S�6����y^?����:�n󾎠���*�o����U��>C�6/l��kF�ybw��|��m��nt�?���B��d��m^و���L~Y��3[ʸ�|��6��6�c��vR�桵Q��mD��4Y��g^�:��L�{/룏~�dfn���g���!���	/3�g��Y���0K�������6Sn�,��^��f��wh�>���+\���������ѳ����#��V�y���ß��z����5|��^x?_�{�|���2N2��|����ǟ�:����S�|��O���`^��>&������U��0Z���S�)��1�O�K�Y����l��P���k?|�C���s[>�	)�Yo��۲�}�.��9���Y��~��,���]X�6{��/
փ10&�.0	v��`
L��3"�ׂ>0F�z0���&�n�L�i0z��}�F�(X��8� ��$���)0f@�������`���^0��蹁�A�`=�`��`7���4�=#i�0
փ10&�.0	v��`
L��3��A�`=�`��`7���4�=7�>�#`�c`L�]`�{��3����A�`=�`��`7���4�=7�>�#`�c`L�]`�{��3��f�}`���`��	�L��`/��`��B����Q���q0v�I��S`̀�"�}`���`��	�L��`/��`�xi�0
փ10&�.0	v��`
L���}�F�(X��8� ��$���)0f@O1�>0F�z0���&�n�L�i0z��l˞��J��*��K#�\^�4�����<+�,������[�.;�C���������k:�44�B+W�i	-[�6Ը�mys���u��6�nu��;W��\��5�o�-��V�Td��w-�N�O��׸Bm+��;��вUXӲn࿱u�Ъ�5�PK�XGÊ�%��f٪K:::�5��_n(v��f�r�s+ښ\'��6��r���';���/o[����s�����w��"S�gO<�fκ��Ki\p�>�6���!Ϝ�7M�s�y��?���v�y����%�J��R_��ݗ����γ�py>\zڸr��ϟvo�?���?���ԯ1�7��<��3���J�<��O�O���_H=�S/�\�
����æ=;~_5��QO��'y����.S_�w/�����K+=�|r�._h��k�7��Vx��go�aS��«�>��=���|�|��cy˟�`�y��c�W�ԯ�~�9��1���_E��	g���|�\ޜ�_���}��G���i��l�=g�`�ԗ��-�?�����ԗ�тm�6~�A����N��������v�SO�_�:�������l��)��[E1x��|�E�?��
OPЪ��Z�Ŗ������H��"�m�����6���նʳ1nu�]��]}]������ri���J� O(JE�ʥ��sf�d2m������}~h��wf��9s�̙�3ϝiΉf���i�ք���,�����4ɦ$SO��� Jm
����!�&S��|=�:���/����4�����od��o�8��ʋ1�-<w�4sV�o�)�;�g�s/�߫������>��o#�4���t����{�Q^��e
�6�@�g2M�:�����^9��k��X;��w&fa�����G�����T�UqQɽk4K�ɓ\���5����%�Y
�2�5|V��6���;�S��x]�O%|��S���c��~'7�ƛc�<ܯbΥ�wռ�����M.:�t�ұS�ۨ;��ʫo����A�zpe�ux�=ع���������o����i���9�n���~J�����K���������؜�ŏ�����Of��s2�4�2m������M�Kb��z2����0tf����o��kQ��/���G���0��8�{��0t^9�{|��{��>��,���a�k�w�O������a��
#�g#��������0����0��]D���u��c�?`�ηa�����ׅ�Ä0��4��ņѷ�a�Fn_��/a���{G=/�~��{yn��`t���a�˸0���?�?�0|y��y]�0�7���FjI>a�]y���W�a��S��a�jT}���F����c��ua�|v�vi
C�0�\F;���z���3�x�F�����}õo�z������ev|P=�%�^Ն���0�Z��K��a������Aa����	co�¤�F?�'����������S�v��������^c�/��� ~�����d�&�9Ծ}M埛C���,�����N{����G�Jt�����Qy}8��?��L->F�lc���Wd_�����r�X�	�ܿ�axM9Fv{ �=�T3/��y��%����ܫ����9��M,���8^�������x=�#�O��.�l���;�v>o+���R��x����߰?\�.I��9��op9�^b�H^���>�>Nc~����E�s�F޾�����q=��z8�`8'gaQ�Rw^�;'ǔ�h�"�)� �L9�����%����K��',.^���7oq>��>&g~y�[��VN^�3����8��4�Ԕ3{��e�551a�y%���,�O9�����Cƒ�y���4H3c��EK �Ҳ"$���<Ǖ_RZ���+r�% �%ˋ~���6;ӝh��q�/�Y\�p������⒌)�π��)�	9�.�}5�Y���8|^^)P)u�,Z��1�'�/�+�q��-r�:�e���4{Nz����<w~���"SQ~�|�
S�%�KM�%���f�K���[r
�-沜�[�3?�=��#%���|x,�w��߼�9y��GƳn ��y�-K�T�9r�+\����i]S�ߥ��K*�U&� �ԝ0��]C�8J⼲��rL�ƹ�U��̒�W&K��h�`������V����\uA��BQw!v�[\��).�)����!ŭ�^m��-\��?����zɨ�"�{֗T���>'�|~�˽�x	����uJZT\
�Z�?��gB@R�8� #��/G#%��h�IFI1X�
'���j�p9�����%ݥ�Jq��%��5<sx�/J�`jfN�� f�δZ��\.�� |�ޕ~��Wa����y%���y�(5U.i��Ԣ�1-�Nu���i���2DRgP��_�]��T�X����&��	�-�t�Yw��p�,+K��<}1���
��jN��BF�됖ѽqM�I�b�U%�5��b4QLp�ii�3��rN�$F�⃔ N>��J+YT�����Id~���LɄ΋�.�I�s�/Z��$m�e�(�0�i�9K����$��H�H)q��R�4�Q��A�i�C3,�)[�_��_���F�]��0xBh���Q����%JL���&5�Q�������4��%� �eЀ��@Ь_I$qd:ծ�y��s���A��-͙>���;����s�Jn��13�#痖�<l�$ �_����8�Ș��x�NcNb����"��cj�2�-��D9y�t����[��d~��0y�]���=����:n�ZޜƔ͠�N�|�2�mIqIQ��E0k��\7�	�q�f�������b�$��X�d��2pŧ�V��c���	��i���G�)�hq^���@��2�Y�q})Xݐ�����r+�wF�{�"0�(�@�g���3<�V>h����!��JݿҸ�|$�)��P�l�aغ��t�I�������J�I���1%sD�bY�ܠ8��E%�)�.Z��&�d�/4������37V����.�ݡږ�*.��$���P�=��Bp��R�����%�A!�V!���?g����s� .�|��%�h�QF�gp�>|Q�hn���S�N7�eځӬ����|ӧd��YQh��V�
�T��__|f
�����u q��Ja��	G�e�}	�&l?���L
Qó2�ygg9��3�t�R8���3��3�;ˋ	�99ˊ�]M ��|0w����,[T�.��=���g��,���|7ĥe��E��,]�d��5�Y{ia��%+~a���������*+X��/-�U�EMae%�u�-�/ʻ%�$1!#=�x~����E��e.Wq	8�i��=
�۱HeRqi�y�wZWS����\y%��g�1��p�C���-��j	XO��i�`��&KVZ<,�R���W\���,
����p>4�M9�� @�=��bM��g+$?i���t���3|���������F���ِx��	!��Đ���R�;r����.p ��4E��:�#��0Eç���Q�2�����g��y�<^��r�O!��h��>�+
���SH	1�k�φE�J������6��T>����O�e+�`�/4�i"MKx<�]�hQ_�c=�(�F.;Q/����f��>���{�f�/�:���1}Ʊ<
�6�a��!�i:��;���R�u/��Q�<��%v�9��s_�9�ڛ����Ⱦ�Hx.O_/�I|��Y�[n��N����n	�r�U��8]�[9�.��7M���zZ$�e����}�X	��x���p<^��9� �O����d	7%1\��V�>C��9�-�VN'W��8^(���p���.bx�L�����&2|��'�rk$�5�����q�\�d��N���A9^/���f�9�"ˇ��v�x�܎v�벾���r�r�CnGN�t�$�[$����U�ko�z.�-��$<��c�L�o0'�t8�,᭼U	����,��|eKx�s%<��^�q�\.��e�8^!��_%˙�5�8�Z�M�p=�p+�������O�z.�_�K���i����\����Y�;x;���s}��������I�8n��Z�[%���^��8	o�x���q<A��9�$��O�p�n��z���!�U��\N��z.Ṽ%���u��]����b�U�|x����鯖�8������52�������9^/ד��r{q�E�[8�[nG����8��m���]���\�%<a)��i�x���"�V^�U�3x;�Ix<o�x	w���,�-�~���q<Y.�㪄�r<C�+8�-�5ϕ�V�Jx�]^��r	o�x����q�-���c���v\-�ke��v\#�9��\O�����۱Y�c�g�>�-��W��lN�]��O�L������U�]�~���r:qrz��Kx��$�8�d9=��Jx2�3d��ϕ�ZN�P�+x�sIx�aWeܰ�r��/�����Z	o�t��8/�N­�N��wz%�-\�$�f:׫0���.��4�W���2%;f�%|5�Ix��C����힄�\��*�{��%�f&�+	����[���Jx.�O��'s�ׄ��Z�O6��΍��H���['���z	/��6��y;��r3�$�������.ᵆ�Hx��'Y��a	_��q^k艄Wz"�Ɇ�du�W�L���*�/�z�>��j艄���Ԅ��Z�gq=�p��뉄�z"����z	�m艄�\��D��W�e9O�~WV��	����]2�7͐����Hx=��U��x=c%��σ�ft_�x	w��$�t8�,�9|^,���̐p+�g����<s�ԳP�3x}\���
Y>���$��׳F���jY���a�F�x}�$<�������,�5�~�z���S��׵���.��������A�?��E�+���V^�X��!�~Jx;�� �&C?%���O	���H�\.���7t�w����zN�\­|\���5<�J�cg�p����r��r���&�5��O��U/��v�Y��aw�����y}t	����:�{:�^7�뉄����K���� �	��(���d	����U	O�x�����B	�m艄g��z"���5a謖pޢV9�:�/���Y���t�=l�۫���3�￻��|^�*�#/�]�U.�Yn��L�R�9n��\N'V����J���	o���%<n/��$<�����_q{"�&���j	O��٬����^���l��c�	���w�I�KxO�&�i�d�yzˬ���J����K��	���'�I�JxO�+�.���~}�\�kx��0�k$���_&�	o��7Hx�!޾��_h��\�^��s�=�l�><�uv��3I������w�$���������	7}��3���Z���������i�\��4���V	7�~N������'�I�,��<�&}��ǵs=��%ׇ��������><��9��E�r}���&�k؁��������l�_Ix_o��p_G]#�u��.ׇ�K-���V	��x���:��y�D�߯�}��~��
	���]a���Hr���%�x.�|^(n�W�랾��{�)x>$#�w��+��5a��p����$!�x��7��[��ap����0xr<;�
��
�ׅ����apc}E��������ǅ����ap�ϕqï���0x�Ў.S��*��A>7	�n�#��%��0�{�0^.��0�����q�;��ׄ��t�'����,��p������&�`ˍ��	a�$�N��'�����a��#�~��o�I^/��D�	�oE��~��hQ��8�'+��v��"_~�����N�G��
�5"�^,�+���E�gx���r�<o�|�_�B��������&��(�w)��.�G� ��}|I�S�[��*���%����l�#김��BW�%�V/p�
�SY%�g��)�D��s�~'��z+���{u~���~���~���>H�[����"Q�<N�go(i�KD}p�hW����]���*����Q�|���~���~���>L�O�_�E�����Q�|���~����$꿀�E��1���XQ�|���~���~����,꿀���/�D��TQ�<M��(꿀����C��,꿀O�_���������TQ�<C��&꿀O�_�o�_��+��<[��%꿀��_���/�7��/��E����x�X��C����&�����E!�ղ���?�bH�������i����.=�8��Z(|�q���S�7�q���Q8����j)|�'�q���P��q��UP� ���>���0��\
�aR}ށaJ}�~�8��(���
��(��8������e�(��qH��wb�/��~���
?�᳈
��g����
ߊ��?�K0|�O�1|.�O�y�%�)<�������
O���?��cx�O�k0����1|!�O����?��1G�S�|&�)|�/&�)�×��������������_F�S� �/'�)�%��
��!�?�w`x(�O�1|�O�������F�����?0<����s���?I���`8�����N�S�wA�S�n�$�)|+�G�.��h��7c�j���0�D�Sx6���?��c��1<����x�%�)|�����k�
��u��	j'�>�)�?����x�½1<���p�S�
��p�O�#�H�S� �'���*�O�O0� �)�Ó�
���)�?Kq�������L��S�N�3����v�aB������T��sTOr��uΖ3L�z'Y�ʷ�j�Q�֡j=��U�U;v�EUkV���ެ~����0��7ь�B�To��6�ށ'*��5�BZ��Y�����O����Q��.��Ô��

�k�;�`��d�u쟪g\
 roD�;�]��j��. ƽJ��5C|�S+;�-���f6\����Z�\�x�,%X&�_��������$ծ6�ש�F��Nw,{��a�X~�^Ÿ!@�Tv�Z9�"� $�}�`�8���[`XW�Yol�6AB��]���0ȧ�:SY�M���������!Iˍ4^��L�!eFJ�C;5#Sվwh�w��?����'�R4=�Ve�t�y==�I�g��h��T�a$�@��A ��1�Rm����R ��9��O�Y(˂Q6
e@(�g�ٌ>�֨7���uN[��.�x7�A���Y��+~Eٜ^��qjS2�C�� &ǯ���0B3-U�?x�$��̿��K��3�t.�i�oLvA\E��L4U�
��	�\�Y������
�T�!U]�������	t1��c�Ԩ��o�,�XZ�N2�kR:�T��Z�ޡj�A"�^�:K��8��"ͲY�(7}i�`3d��z��+P����
��GR��� �QN[f��nj�x�����o*��OԳ?��v�H���d@Z��$����F�5+U?���a*26B��C�H�j#T�&[;����o5tգ*J�*oi�hb������Pdb?T�m���z��( ??�������&�(�B��(;H�Ơ����fa��n������ �b!�7ʰ�G땴�U�Jո�X�aۂ��Q'�l��W!e�;JV|����>���I���� �i��7�wY,d��-e�"U{;$x�V�T�yv��K(���N�}��<DQN�t��z���!�M�7I��i[���m7Q�4(�@��Z�E��U�� %��ɡ�ҵ2K{��E��+U_�s��p������Eԋ~�Y�� �ƷR8uu#��V��0=(�Q1$�� �/ �:uP	���`��}&8R�~]�,�;�8�+m�ԓ���8R}��_���ɲ�����F`�>�L�AK۩�7+��q0�J�ި��H{�1�\c��%��EEl����8���
��-�R=+Ѳ׋���yi�${�Ll��(ZXK��F� Q�g���]Q����cC�g��XjY�iK�H�(�'o!��'�E&YO��mK]���#�=�N�˶X"v�Mi����rZ,��J3��]L
�)��);3�oQ<���9��scZ|�AuӦ��L���]cZ��@�qCcZ6@��3�D�� �]����Zn6��|��E&Ge���^����{T0J�`&�^}T�nE����:����Q	&u��w�?l��ԧ��ܚ��#Cupd�6F�֙>�ѩ��*k7c��B���Ũ��އ�FA�?����F�<*�VQ�����@Nm�ѯ���=�U-Q��@]j�X���m�V6P���>qT�p٬6�P��5�rr#ʋP7�/ڳ�f�c[upl�^Ӆ��:���g�O�gva�%�N;�tT|�2�����05�?`�S֗�hKc��~�_?վ���nT�U?�w�sH���a��qu���w&�`�Yj×QꐷU3x�������~�N�|0��u�^����`a�vG뇿cHi���|Fz?�H�ɚڛ fŌ	�l��ýU�/}wY����M8ۤ��]6���87�r8�oe.��"C��!��ш�:�����c��X﷉�<Xc-[� ��E�rO��-o"�Y(%�]f%�/�,+������N?�=S�>�k"K~�jtU��bωd<�\'�fXSF�s*�(<�,�t�V�B�`�����=Ei�h�� crQ/6\��@1�|i��+��`fԻ���=�Ɣ�)7�ܔ��|Ю;��a߹������0�`�˙�~�p�JG���Z��2���Uݰ�!l3�����s���:�mX�pV�0�����c���R�1�:����g͎>�����}�����͓_��	�����r�����T*���޶�6�F́��p��w��D��m	t��ng��9M�{��p�n����z�bǛK�_�n�k�;�T�v�f��рZu_o�����|��ܒ��x�뽉u>�'2�z4����v�!;cu)���0 �X��.��<���Q�}[bh|R=���nV�@��O���'�e0���gP���&���-v�&�g���=�#�m~?zF�{�XP�����ka6ݰ���G��	���
%b)
�4���|�N3eC��/0i�	;ˁ91%�I�\v�Ǳj��8��ePCXT���Um�~�A�h�po���U@t��p"���CA��+m�X����E�۲��
&�J�W4�J�d7�7x³>��v��[��n�E���lP�v.�>� �S�4���T��L%�rf����)�=������Z<jƨ?šs�lX58G]e�E`q�kE����jtP8fϪ������0�,x�"a���f5���R���8	No��+�lh���t�ìD9�<؊��:�k�H|��~6Ne�-���69 �:.�]f0f0�bV�w^�J������mn)�����4N}n�Ƨ?�I=�I��Z�r`K�i�f�57(�,0x�P�w�f�f�������j+�à���ɩ�G��ֿB�����æ����i8�~�P��UE���* �y���N����L��i͜@3�B^�Yقv�����������*�A����U/>���n����MQB�k����M�k<�!����`��µ�E�i�j/���[\W2ߖ˭���d,?���l;S���,��zOpu���cc

� ��,k$H}'KM�[�-V'ل&���Ʌ?��O�O׶������{?�������i�'������o�m���^��!>G߫g��F�A6�4"�ܓ��8V��.�68�ı�	
Fj�����-�DÀ*zS#sO�B[�zoF	����տ�&.�T[2S��Z(2h�~���&�9��[Ps�{'�e��#�+5�'�HI��|�z��k�^SI�Y�_(A��{$�{G�A6�=���M����)4zV}�d󎒀҂��Qbl�e<�b��L�k���$c����H�	cc���[
R�����!fQs;�x���lجVZ9LU�����c ��O���]�Բ���m�I���଺�l��	����bz�����i[E`zE�U�G/0�|]pU�u�vH,�1�W�KDJ5���n)�q7H��Z��"E*�rum���Q<Λ��}a��vZ���e4��FTOEh��'Z��fч!���S�E�nD=+�_������+x/;)��C��es���Y��r���+��dxM\��n����G��~��7X*��8���1}*�!ߏ'��ԧ�2�b�Fr�������bv��l�d�*�� �"`f�p{�j_������M$�[��@�w=�m�w�L�Au8d��@6�ա�sO�Z����-��l����<n�s�����U���VVy��Bϳ��Op����Y�;�0}:ξW��r?a��,��H& ��}���ĺ�F,�یʹ�s
��N��/�b�]��G���b����9������W������k�	b������?1IŶ��'V�9���K�u���A9}pȵ������R9�Xt	���+n����d'kr�j�w��}����ϐ��V���������	.6�}�.�-��j��}�|��`*;�3��-��'���L���������";5��z�:�z��W�����L�pj���4��RР���x��$ V�'�;�ǐvGCG�S۬�Wӫ�︨��uO���H8��N-�ܡV�`�7��?ֿ|&Z��6,8�l'�܉=�j1�^���@Md��V����{%M�!~G��(Ԃ�I�S,�&ms�Uo�5�|YH�<Ò�)��L��~R�zO�i���j��9=�����G˽�� ��X֊{�Nm�:�7�+[����qN��k��Ծ��Χ���?(ku��aU�|�V~Ѯz�����OQ��P�[���ZY��Üޑ&��}����GSc;�3�̺��ͷ�7�]�ao\�D)h�K�
p=+-�ߑN�?L��7���0��O$M����J�OeU��Ӡ*�cu���)�W����HD��#ݱG�ϭ{�~>�Y�~�d� &NA��=�A���~�T�w���w�w9f���'��v:�|�V�PTm�m9�jg@]O�Dn�{tݲ��ji�ƨ��.PG0�e��++�˖����Oܡ_��a�9a��TE�$:����#WEP�q}�V� G��dCb��Ry��Tv�T��P�X�"[�?s�U���c8����5����_X��P��G�'R�"զ	���h2��E��	�����0���]cԯ���q�Ť6M����I|kR����|ut_��WG'���Nk6N�6m)�	�jy�!\q�I[Ufi�i���t>��-�)�	�2�.�?@���I�`L�U_��s�v�9��f���pK'�L}��;�^�,{���Ƨn8[�u��Y�D�;�ݟ̧n�LR?�K� �àf��d�&ۜX�g��'%�c&%�/��.��U�zn�0�0lfk74m���)\#=m?����g�
uʀ&u_�պ��[��a���ީ��6�¶�����P�����Xp��z'�	�-���;��s3M�9[j�\4��3�v0�\�z��zc�ǩMQ6�r������}�*Uxy��ԃEOd�<ca:7f�M���O��ZG⎶��ztR�6p�[�� �Tm2I;���`<U���]ЩT� r;�8N��p�!I�C���T��Sh���wb��YA�+�X����3U�-P�7�oSiM4w(ʾ _j�I:�V��i��M�f��ڡ��J��Ml-{���ҫ�v[�)�p)ju�D+jۢ���l�$�c-eˠ��C�=�>���zMb}➴į}g�����_��W�7'( �������������_?r�������>��ܨ
l���̽J�F�l �@�P7�4�C�����>Z�N�fk�qƂ�zE
�u������m�j[[c:�����Van�t�_���|�-�y�'�!�mF3�������+�۬3K��hA����}#Uo�)&jeZ�~�'�o�4�ү���A$��c�R��zs�e�z���[y�G(�T[FE�I���i���)p�8�(�����e�d<@��&:�=d���L��N@`�r�����Ey,E�����m�����F��}f��B�yaV�XdX�՜����.�B�\����S��Ն�H�������"9P�q[�xT���q�'�\�z���w���7�#�~2ү�lT���{�8�衣,+m�jd�al��#�ZY��U�52���M����0f�{�g��c4�R�;���L�B�63����R���ON�|%}���0��U���3�*�p�r=xԎmc���wa�?���/W��,��r�s��,R����|7����!��j� ʊ ����	ɴ)U��q��[��N�4�e�/1y2��@����{ĸ��K
p��qX�j8w��q77����`�5!ܕD��L�j���T���y�{���^CHU�t��/ށ�^k�����HC)�7R�=E��{�[�~6�̷�S�|�6��������%��"�k:��Q��L�7�+�C�
Ε����{��H�2�N�$z�'z1�k9�OO�l����~?�p��r�Ĺ�~��8Ҍ���x�	���w����!���������p��wa'_�β��M5�|CN"}m/�{���>��K��>N���.��a:z�#�E�?�������'���,��o��+,l�k
�\��~]���+U��Y�h�����JuM$�^�1d�Ӳ1B{�յ��k����:��_�ɐ��Uv�wk��%z/qz٘��}�v������e۩��5�~`�N�ד��k4-�a{��o�*�*?��#��fp�}�N�Q�q,��L6^�i6�m�l���k�B�gE�a_Ѹ&�w$���؇�3�K��pCޛ����ݿڐN/1���)��a�V�0�������.��t��{�C���D�B�3��P���R�����'���}N�y����FCN�����g����Dam�)4��H�����(���4CV�����&n���Ci�Q?i��$zy���<�����Y���~Z"~�S��R�[�!D��0߫�����]8���**U�vv��.A.D�X<��mџ��g�p��u��;�N]�r����֫�Z�3y3-�ǡ�{��H,ce7�w��Әa���H'z��l~u�-du���Z���u��|K�b99�����R;m��O������zSm��.�u��$����b��f����ȿg��\6[(T=�S���,�@u����kF���ӻ��D���[n�w��-f⅝��tL�M��î�u4[N���G־���Qi����4'�\t��g��q����S�L�2_�szG&��9�{�h��B�x2L<��M�&c����f����j�A�����6�k���p�j+�hߪ����IXq�T��9�ɪ�ȥ�ԠgA/Ίs>=q;���$e��,�S;戼.8�'�i��|v�Gp��t�~��p�� �"?���Q�HAO"ͨ'��1jG ]�:F�N8F�R�)=k�(�Hw�D���X��t�G蕥�К���@(��|���<Vߟ�G�4�����dI�������������E�X���+&�@V�z 0`�{���|���)vM1�`<�k2��1'ɞw���JT�nl��l4��9�0nM���$h[�����M�U_�I^ק4�}�X4�C��=��\����m��w���lSYo�3ǹ��smm�z�C��׳�:�qe�Ds�J��q��0�/� ���W�P��=؅������JՖ�4ȃ�QAq�(;�C�Uw����!�-�=W�hNs+�������v�Ͽ-�&�Ώе��>v�;��N�@�$��-�r�S ևxk#�5�Ǖ�6�6���L[�#m�;���Y��!-X�a��1�jz@�;�q:o4�<d	h3;2@��qT���6v�y��,,ۡ��ʒA�"��Չӕ͈<�I�-��/P����\V ��0�˹W?k+���U�O m�s\���ʴ�p+��=��n��Ȏgd����ޜbdߴ�SS?jm ~�� i��Ba�X�)��p�s�Ɨ�+���$�$��8U 4�K�F�� oPx�' �� �� w%[w�#��O&�>�̸[�5�����o��  70r�_r��@-2�H��̱{1��p��@?N2ज़��: ��`a�f�Bk�"��y������Ê�J1��a�֦/m��S�uS3S���n�_3ҔuK�����U1�\N���g���U0�'�r��K0^�������3'Q�7Lb%_�%�K[T>+�89�������6+w��iU�(��fv▖����$�u30�V���)'���;C�-�F/���
������\�@�c"4E?7�S�#��zt;	B�V����P�i	!C���҅��獺GY���/쑪�ϵ`�4�^���;��A�W�`e�ve��4e�V�`�x����Lĩ��ϛ�V��7�A�Tvb�kx�9�:��{���Ƶ��L�Z�X��`���?�'z��Lm*�Y3��ƺ��X��]��8zV�8C�{�X����H���/���{e� ��"��F�
�%�)���]�� �_Ǧ���;�(*	�؈��x��oRQ?ѧ506�!��>R�u�T�g�K_��I?q��o
�*����EW]�FUGUR�m1�h�����[Ǟ��~ls��m��r�B�&��/{㌲Fӹ 'x������\�[`d���Ry$m��h����A6�QvVi�EFJH���-��^�`��u�w���&Ks�q.e-_��;��g�lL4)�`uW#��X_����קQ�a���2~�5Rf�v����Ğ�z*�K�k��,C��1�J�Ct��_�=�e<���M��-�N:|�a��lb��ys�脼��CR���r��6� �7���!�D������:��3t{
C�`�}!k�)Bɳ&���1�d=7��z��s[���ث�g�@�Cv�Z��A'����귔���6��kP�]�~�k̪�Ҫ���D�s�
LUK3��4���:=f��3ՓbI�&Y�4����zꮲ�N.>��������@���cx����ެz�$�5
SE���Ae`k��hJsIw���2�AS�Բ��t4B˲݄��ja{�$�<���e-���vp`L-�#�R�#�Mꐝj$�(��,��|?+u3��5y�4�"�����P�{��/>�~G)կ����w`E25��d3���_#-����p��5��b
��O/$�~Bo
|p.zP�a��@X ��bY���'����_�{�U�a�f�f�|��\�E*�y��\l�vD��,ԗґ���QO%m��Վ᳖�q�W��>���뗿1��ϒ�ڶ1�c�����]�z���N�>0߬ށσ�ѵ��j�&[A��3��v��+��f��ҁ�k ;`eԓ���<3ӟ\�����o֔�*��`.3S,�h����(�ab �[�O��:��Zهx��x�*��n�2
��j�)�#���~e�OY�W��Mt�I����������K�*mܫ����
)M;�=��k�[E�k��z����`@��)`j]�`HUfHۍMi4w8���e�`ʺ)=���+"��޳a{[Ϟʽ�ġ���z��]�>@�jn��x�G2���_��oYǆyҸ1�H���:��x�d&��2��i<�3���M����c����{۫a�e���c��C��r��r�:6�E�'��}/��m;�U/�w�����q��#Ǳ._��Ad(Z���Fpt�z6�����cY�)�_x�ő���6�t�x�4��+�(��z ����Ǯ�G�lƓh�0��Z�#�"�ׯ�'�#����M�Gq�3��ɏ8���Q��#϶ �<a\ ��J���i@�,Q�dV㷧���Z��4]՞�v�	2Y!���:����^�Z���`�Ë�wx#B8�!��~7�[�ߕ�t�cwD��T�'����];��B�Kd�gH�/"����(v<
iA�D�+JI1�b����z2��H�՗���̦��y��]�i�7�"-��W7�o�D���V�|���u�p��i[+�|���f�@��� ��f��]��
<���,��ʭV�� t��2=��b�>5Qxlu+=a�[^���r�Ԙщ�٠���u�>��6�(�Y͙*���OEt��VE�B�&�=O�@��`���zV�J0T���4$IP�d�*�Έ
ՊlA{�]O���ZQà��Z��	�V�~�U�tj�BD��<*ЖQ�^ 	��V�A�H��`Z�D�$zo�
3�QP)j����ԘY�+��dDq9֏iʁ4D�a�4D�
��ACf}�j�B�8���F�c�]m4Sk��z��I=�{0�8k]�z�=�����z���qG1ِ��y��mIϠz`%P=�^���J@=�C�c��t���f�wK�d4�$v=ѹ�F�[�ǽ"t�GRsF��J�У�4=D�-�G;ҫ�c����_-��cMP?���>���/ÈÎDs-y4�ۑh�%���m�\K���gX���C%�G�oq<{��"U�ͪ�����d���rb�N����F���p�����,��(�R�H�"���ĳ��,ϳ,�<�q���E?ͣ�`�m��ʽ��Ξi��тCc���Q4f�y�g��
Kk�?��㗾
#�
��H��_�-�W���E�>#ۏ��_d�Ϗd�[K��h,��(�*g��x|��W%��a�{y���������/�����ͱ��$������6���a�ʓ�Y�7a��|קFv�]�f'�[?�<�� 5r�P?`B� �G������v/8��D�X�0�F�z�iou*[�4�K�H�!�R�/�c���_ŉ8��I�����e��;y'<9���}*V¬@��ԃM�V��9��ofcd�1Q6�����и�e�(�����U�XVe#���Tp������6C�0;쇖���d��W��Tϥ'�;��a�ٖ���搬˷�T�-��UD�C!N�u��]��z�ֆ<�z���@=T7�]��M^�̭��b�^�5sl7����sL�`B}Eznw$�X��X���8h�d[����X/�um�,X?��� ���6�>G��el���l���k��ֆ�잀 �F$]�6��{i:� ��%�d�$��5�2�9P��y��|�s{� z�v���-�6�-�:'��h��bw����z�s����YQ�B,J����R�^���*���_q�cP�oo{жܙ@��2����ϑm��0B8Z��-hɯ�X���	����A	h�Cv"h3'1r_\��c������"͜�q�aۃFd+���*�V�!s=����_���뷄.���0�ǃ���u?��w��x��#,�H���g��_˱�Ú�F�=ɵ!9�@n
#�o�z��A3}�c�1Ϭ�(?�X�^�
U?y%���߇f����"Wp�k1>�S�&��H����Y�fY��Yݘ�����a�m���s�흠�}|�g��v��4O	ip	ڷ�8[�=�y��$��������7�x>"e���U��X�>k��s����K|�߂�2�I�L=Ϗ����:~U�iF����n�8���%ӥfӄ��=�>]r�O��|�*���o��|�o�����o�^�R}��pa
�G��yD�����I��8-Sp�T��h��U2k�B\on��fsr�f���; �To��F\���l~����w����l ]Z6���q���>������90_�K���(���M0��!>��Rև��ú���]���(�ʶǯ������ loR�������p��r�Z��]����n�Y�o)m�׵�J��o�=����%��h�Vt�V\i���2��]<�V�-��ߴ��r@��t)\�re=_Hږ���D(W�K: u#9� e�[B|��~�~�6`�Fm¶g;�f۳f�k3��듂h�Dƕ�ρ����=�J�Ĩd��x�E%���x�q�Mp]�d���>�rh�t��[�tsHҋ0�ŘtlפZH�.��ǰQ]���$}���I�=���5�%�\O�K�E�x�p4ƹ�)������>��w�ߍ�sB����{0~Ə��D:�I>�����#�S��/����:��0���#��Ч��Qpא{�6�<)V����-
g��(��pQ�SA?���>�,���mڷ�ƨ�n��Փ���O�Ҏcy���8�w/�6|��Sϧ�H��K�_jœ���U�l��>�+�%�oS�M�����Y��/e���'��Sֹ2����ʺ�i�'7���	�u�le�:[Y����eU���?�ώ<�Ύ\p)����z[�:;�qv�ysД}o#y6?����,
�x�F�	_zQ-;5b5���6�td�MԺO�玌X���i=�1��`�zj��M���l҂Zf�6=�;�lY�Њ+m]��D!���I&ާ~/S�bVΏ�xB���2|[>3*�m�G��?=�T-�I�!��t�%$��K��H߃t>$�=��5�Q�1���8c�]KN��4F�=ۣ��H`?��b����G�b|�bvf�7O�����O��ꋩ�n��U�`�x�D0�h}��[~N����"H��Ip7̆����I�N������C����g�ŝ�Y�Y�Mx�W^�O�a�N���`�~x���a��'�G��f��<ʽ�ng�/p��x8�vO��/y�[É冤�����s��G�9[�����q�����WҸ�19HW��Gv�(�\/?��z��������������U�m��P�YV�y~iq��T����5��]�m�z�C�6�<dz3៶�M|�6�ϛ��-�[�W�UZ�S{��*��U��'q���
Y^X�H���}$�v|e��=�&V�^ϙ��b���k�bW�I����`,�B���PqV�����h�o���ǝ���c&>0��)�Z��j�Ї�y��A>�r��Qh���$w�=�F0��G�NxB*.#L�3�)�t>
�ǀo�ph���3Um�Zy(�.~�/?ů��	f5�����侄��[/4a�ǙF[����e=�q�e�I��"0kM�ĳ��|�h�|{��� i�oށ�ay�xm��˾�����It�c54/x��h�rk�q�oK�m̅̑8@��G�6����g�N���YӓV3��z���#x߁�#��0DP��N��6�F+i0wJƛ/�$��;�H��x�N|V�S,�K��1t�⌇q��<��_��p@p6+��$Ox����X���6�th���lq�J�q� �N6�P����F�\��i���;�{��`g|�AT�� 	]�͵e8��tl��]�Q?W�G��(^���L��m��+^5�o���.��AxI���:"�Y�x l4������@�g��,�)UU��ڌ�o���恤q�F�st(�7��<��i"�	7�U�o4��sI���>�ax<i����ivh�xk�ah��ؓ�c�UԱN4����n?�T��'�<H������"����+8-W��1u��%���Weꖿt�e�\w���X����`��[z��M��O{�u����f
�C��y����sq�ݿ�w��"��FN�/�uƯ@��T����������h �/�}��`f�H�O�7D3]~��y|B�m�~��P��y��a�t9=A)��X�V��4�U�/��������ï�!6J3{������Md-�o�x���$([ߎ�}L�<����%!7B�tg���Hz�A&����h���&�剆����NU�N�f����z���R�%�4�s|�?�G�:]�+Y~oh~}��s|1J�5���'v�g����^���u�?�&��?`~�?e����c�~~ӎ���r�-x��s����9�����г\���qz���:���iv���ҋ&�c�Ն���5X0W��}8�:�0F�j����;{����D�b`��&��*�u?��=�n.���{��vX���A��苷XC����p�o�#,��Ū�[�`�S�'��g�IP��\o���T�@}�߰�M�U���s������ޟ����3{봏�)����P3^wc.����"NvG��á]�����}�f����u��_U�8��;�����E�Y��2�Kj;�~��S������!��o;(���q�[�'��ۀ����s�.X��{�}�}lа����Q<��<پ����{ ��`���s-)hk݀<��,
�g��X>��ў�ew�m�@�� ��#e�B;����¸y��1�N¡�*���O��X�����n>>��N�X�EK��e	M�Đ7�c������V�Zh���آ�)�2�R���}�T�#)��]P��A{ӌ�zq��s��z�'� ��T�%�#���N��
L�8��Zӵ}�+�J4��J��?O	�إmg��vT~cV��!����Qy�p� ��e`�+C�i3��t�W/������+>)]��k�����S�1��PvW�>F?�T��-�������;�T�ؐ[f�v���ϸ�Zy��K��w�߸�f�1��-J��馎���iyo߂�s��p��w��"�� ��a{jy	ْs�� �J'2eQtoT4D���y7� ���/
�Wl�֢�!�Q?�3�}d��AJI��	�pAOpӣ�t���#C`>�T=�J�6<T��s�pXB�Vvm�vڑ�Ұ�[,� &{����U�4j�O��"{����<;Z�ɡ� ��'��8�NT�'�|�ON��_4_ɲY�>"&�iV\������t���8ƼvX����i�:���S��j�U�RF�$@���S��l{�=L�H�0->���R�`��~�>W��v��N�"K:���Kl�x+EY���F_J�5O�9H�=�-X�L�1���h��5z-�a�gZ,^�zg���:@��ER6��S�;����-�LΔUܠ;�1N�M���I�1�#�%��g�/9,̿�J��{B6@�t����X���e�[�{�Ќ�d�v�3��I�`/���OgZ�؍FO�[;�h�2�w��A-�>O�^^G�L�Vˏ��U=��f�'5���9?UY?=
�L��[�B�Hr�E���<PkQ�C��pW�ߡ��؋�ߺ3�m0�+ƨ�z>��o,뭬W-�dKپT�T�(�3���h��K���s��6;��C\��>:��t_�C�nc��ʯ�uzG:�#p���{h����7����vh�}O�z.���[�G-!�3ْ�B���Y�qn�S�J��V��wnu,އ���vw�7]��t����5L�o���̭�a
�v5�ZX��uˬl��Sf۸	�$�	�/_H\��g�� �&\|�z/�6�%������S�G���$�GY"J�%"C��rE�̓�[��ZqeO���Īx�'����g�@��E��N�b|R����OO��vL鈜iE���ѫ�b��^<I�ͨS�|�j�a��;�B���8���Ϥ�[�[վ�&u��*�=���l��J(���3�9�|>� ��zˮ�[��C���z�VUTO0��f�w?�G���_�Ǎܶ�t�A��������P��t_AQ,����HOE�L�g�ͩ�负p��+;/N�Q�vz2$�4$Ϧ����YL��C��w�iq���|�+a>rB����z�UO�G��Y{eZ��#x�r�s���m'r� $�,���۠�	�lV|N%˃����UN��G�tm�͡-&����jD��������?S7�=Ԧ&>z�j��4F_i��і �S�^}$�� �Zw��Y����ӟ�dN~���K7�xӓ�gJH��J6���?��h�ە��n�@]��l��G��czO��!��8KL�@�cm&w3Έ����e��Q� [��mk����yw�:����莀ʡp�"j������>�.���.V��Zm=u?Pn;�2��N?�5{n \����o�{������s��Cg�o}��vS����?���������/��_񝉿�������g��:��;���!��*g'���s��B�s�s����W���
7��]�nin1���C�~�Uؠ�K����w�Ü閔l���suh�sx{n���R�7*d��"�4ZJ��1���]lI��8�,���2�hT�2�Ӿ_�A��QdF�Fz�mz�;��2�M�؜�b��=/�����H��J�B��~���~Ņ�ж"��T�N�jed���}�5?��
�]܃����β]�צkwps��uL���D��������� �s9�קJ�B2��LN;X_�����~O{d�A���nK��:�T_��/��y�=���$#�g2H�'�P-���g�����g��4�r��5z`���ea޾S�J�y>kp�eu���$�K��wP����3�'@�{[�se���<v��)��"�;�y˵�ɸw-�%��C�h�`/
�5+�"����U��2���G{X*�À�B;z�X�=������GǪf<=ؾ������<� ���6���o���V&5�8��yz[����Q5�6��/D���(h��x�@�Ao�(�!e��~�0��`�c>}l9s�&��4��+;%�ob��.�-�,V��c�	������(���#�u��rK��i�b�{lt72~��d�E��d-���M�NN�)S0k�4���m��aߚ���?�����;�#K��F�q0\�'=^*��k������%���#z�]��5*U�����݉�h�Ԧ4�e�ˈ����0����٢ܻ�'{T�/���VF�gow�hhꙎs;خ�p����Ǎ�aUo���gi_��)�.28�N|�H�@�)�m�f��1=ٶҞ2��l�F�D�Ӭt��O	��s
|�Q.�xSZ�Ct��M�?�x�"��Y-�&�w�n�ӴʶX�_��.5��'�?�}M ��ٯ��N=��~J�z�Cx]�(��:�`�c��9g���^V�e����N�q�zOd���?
��/,�-��q���̟]m2��zѾ�}*8��kX�|�6�BA��E�tc�oa2�M��{:��Mp3�Of1-v|W�w*�H�j�ڕ6��|vM�cf��»D���tinӥߗu	�!b���5����{��K����m���݊{��� 컢������F0f6����ouzKa��FJ�`	�ҵ���ѝ�/���_�0f�����z���ro$gs�R��C{,��Xݓ�&�O�/�a��(�Ws�U�V�בּ�Y7�i�<��b��/��=)�{�����d�W�C���τ��Fi��*Ks��{Ώ�=�G`����n��Z�.���t,��@���d�Y�g<��8q��pF��p۴:�ؙ��(;U��r�u�·9j���6��uƞ�����c��N����{�tD��-a�N-麳�������2���/A�h�{�S�'#(�X|��a�#�_��MEF-aǲ�J�5�{S��[�a�~�%�c��{�lS�[�����%���18T�J�#6�aE;쟗n{
*���U�"���i�ͧ��w0���8݂�#�.���d�T�!oT��w�(�'^��<��x7.�~i	��Ü��h��B���O�>�z��}~������٠�����2���7?��k~��n���x�����#��'�g����+�����n��0���|~�&g����:	��ω[�+y3�Ex�^�ro.��B�
IЂ���ɯ���N���x~�~���ШW���ڦxS�L�ޱM���c��x�6`�QȂ�_u~��G�/���C�*ԗx>�gϯ%�����'��"M$V�#����&��n���6~^�_^�^af��ǐ���	�����������-<������0�39	�1S�f����u�s{Yh4�E��be�?���*i<� ��@�Ek\[Am���&�R��,+��]T�	�RL"��5�]Ww�]wW?]��]) }� �D�pCx�W)��?3�ܛ������}�O�ܜsϙ3gΜ�9sf������0'���`"�#�x�U2X��~RPi~_|�W�W�~am��8�Ck���d�v��]o��d�	��<�@�0�QB]������{���ޔf:`V=1~�}�O������;���a@���ӯ�_��?ӯ��F�����l�@�fu������������죅r��a�*A:�#ٻ(���вKL2����E_ͳp�t&:N)frk�4</�+E�(5��y:v�P�?��H�^�{�&T�dB���K�ljգ��/��~	�{�*ԇ��[�5��(�G��.?��Ř߆��ctΡl���[��{���<߯Q1������{�cW�����+���2->�/�#��cR�Nc��x�xh�^� -)�0�o���+�9Ki�#��Ǌ��]��c:=]&���H�t��ۃ�B��I�}̎3)r@�����|���d�SS�J�������R��B��.?�P�o��C�԰K��[��F�*l �"���z:˘��,o����z�����a˵�ô�X�vb��ŶQ��w��h�yL��~DH��h�'���}In#B���t��}�a@oL~��E���,�����9 ��~Aڀ�x<rn�KD�A�~^+OD�3���;P���Ͻ�-C�N�܁�l�(��a���j���?�\�歏���ԙ���Ѵ��j�U�?%v����� ��1S�8���ѯA��4~�h~��Q1XxIν$J3:�IwKܸ�}�-n�
�;��w�x'ŎW�:��1H�H�J�h��Xp���V�<vuO���ˡ���ytծ.O��B^��R&���Y�q�����l%Z��N˙��]�+º�%ʋ�!�}s�J�����i=�ζ�9O@���S��{�>m�=�h����?O���!%�Q�n�r!��=���*Z͢�
��POm�ݢ�>����\�b���+Z�M$��U��=�M�U>��K�-
k���[Į
1Ȩg�Y��ԁ?#�:L�J�>�a�=<�H�~�QP"���hߡ�Ͽ!�9��8p,Wx��.�S�v��N{�YX~V�N�m��.,?��|\v�2�Wv=�/h�xQ:;vE��.�Z �g����]������� *�7�;�cž��y
4a\s+ǟ�FǑ��0�5Y��TW���h���p�8�N-�:�\��ʍ �Z�A�l頙���Y�<�#2��I�:ob-d��a;%&���4)k��mE�pa�OVfN&}~��bl�4���N���8�T�>7�X��$�?_7�	a�w�H�tR�?��v����C-��l��A{�8��DV� %.b�=V���U4��I�k'Q<P�����T˪��a,?@(�Gx� �d {O)����m�N��(���^ة���ɀ��G��z�� ���]U��>���g�����#�a�q좿Ǳ���bK��bpB��+TJ����1�ۄ"̪'��>� V�\y�{x|~pԧ�җ�>�tq��}G��Tk�Ba!�F]H���V�C�hS���v�N���C[9��� *�	�N��-���� �R}��mŎ�-�&fJ��"F��K�
ս�c�՝ٕL�~x ��Ј&Wj���ށV��.��/|�S�Ł��˕��I�K[D��HZ2Uvf;�CZ�t��z���i��󜸽p�[Ь��9��	<��?��P��f��%��X՞�;n^��÷�#C��䜡�X�Sw�4��;�B��MF�qxc>�F�P��D�/�L~��@K��N�_Bm�����h���[�m0 �E�5u-�J~�W�0��5�W�vګ��R{.H1�U&�ѣ�8�Rr���ܡ����?�]x�U�3�EY�@SN�K�3O��r��� ����J
���5�(��Z�k�R��P����6��z�%Ak�#�tR:�A^���� �f�DTv=��P�5G���L�����W��)�BzL�9��86Qwf���b�|�?��(T�g��Ĉ'��O��רY�N�.�vX	F�I��>U�
��Jj(�2EL5���G�
��琑�(�J�7�: yX��{F��P	�d5&0Ny_��c�k�ߕ�;ʺqLc�b"��Ͽa,a;��ۥM��)}�,l���R��y\D�S� :����r�&����9�U�?)�6{@Q�[f�3B|����.y8�/��\AW�2��1O�|�'P�),��Ud�}X�5_����x(R�1�{볛}�S�@־�n⹓n��F*��V4�^[��KGX�"��B$b�4B�T7�[-��O��PNŽ�Q:)�����sI�`�uz!HV�C깪v�]��g�f�P]��X�ppX��̓�FE�.�̿Fyw�V�i����E��A�w�x��xQ�4�#�Hn�*�ݗ!,�F9@�]t�z�a+E�����;�d?>j26�t��vMN^��vx�f�Z�!�}���U��f|�$�\��5F�0@@�~�O�Ë��ס��r�5�<%����מ�2�n�U9� (����.eV[9�v��>8��Z9��=�_O(_�����/a���<~ڕ_���Q���}�2�0~������|W��*�3Ί�3�~X��*�u��˨�joFI�h��^��r-��y��>��Q6��S�_����h�e��ܡk�\��Z����X��3y�Z2JH,���� Z��Y��t��t"2k�LXˆ`B �[*�5%���'l�Op�9�q�=v��l���2otO,s�+���Ѷ���>>R�3�԰�qF!&���A�9�(��R>Wm�cջ�׭\j��:�8���4zT���Պ��X����W01��c�aTA`�2¾<���w���a�z%m�/ƕ)G�Ty���\���o��;F���*�5�^��@���)���:��� H9u��O�r��(��d�S���5=U2d�����Q���Ⱦ�1%�^Elĝ�SW�D"2L��t�8�Y���R$�I�1KM�1SS�c�Ab��d1~��b:|L��r��M�� MW�C����}N���>�/����ՙ�-����(A�k���T��f����~d��Wot�ڄ�A�P�tv��X8�u�����V���jU�w�K����G��_m�	��碏Ŕ���&(S7���	%���˲�y��m%EB`PD�\��_�lZ`��8�Y�6k(�A��+����#�Ա�+F-�J=K���*1F�A�
EDcyEZ���ZVϸ�ܣlv
��L�/~#On�b���*L��x:p	Z��DF�,I.��;��t�E8u����6<����lHFv���}�ni��0�p����8�Y��U�Z�܅D���>a�dc�Jĝ���7��h�a�|�~H_� n
�n��琹}N�
��m,1���R��.ُ�{�AK�6�(Jx�9����g9Q^�>��$���������4a�'�%�<U�*� ����Sr*i|{�'�g͍��V%���c�b�<��s�4�"?�V��Ǔ\a�r��
S��W̒,�d�GN�W����V�4��jS��i��<{�tDz.�҆o�Y1f���ҕk7F�T�ʆnVw�_m��3�V4g���Ufl�>��z�mStQ�7���:e�����_K����n�U�_ݤ�ߺǏ1P��� 3��CY6@G��,W�P��}yߺ�}y�JNo�I���b 	��*�Yǖ��x�f��m�({���,#�3����~����B/���\�t�)Z�N����s���V��r�"�@��"�2$R6��}q+A[q���������y*��"W�u�ȡ�W��*��,�Ш����cF��
�w�^
f	�.,�[�'̏L��{O��:z�K��D�}LC�b�?�Q%��z��V���.�C����C���c��#�qk�k���LĄĸ��>N����*1����4�HS�r��>��fN[#���:��I�>��u��3�����y��D
���,�y�J�<py!�M�G�a�8Ȉ����Uu!�P��،���t�y#���rdǶ���vR🡠�D��'��{�Q�3&y�YzF���ʻ�1A��}Ap�4�2[��h>�sb����3��Y4�*@�(�#�m$Î�)�l�,��	�S�qJ `��K-��I({R�TLQIYT?�&Nm`�S�5SQ|�T���V`<�^�םL�
&�v�@�Mjpa��������n�Wb�(��ӌa�$g:Ɠ���c�����i���%g������c��̂���s|L����9��\&�8���X��/s� ���6������b�V��rϵqDє��Ϥ�r0G�T�7C4V�N���Y�a�q}2�t>��&y�Yz�L$�Jsێxw��c���b�LZ�V }G�i�P�y��[�R�-��x*S��F%���QHZ"�6�9Г�����ZrK`�i�ާb ���y:��(�m;���!���m:B1VFId�a�hU�����wɵ��'�g|�����h~P�wE��GE�O��'��tZ������<���xJ�.�c�����X_00�E����N:{���o�����#�k��x�Y�"Ǡ�v���vc�G(�:��t�jv%�'��4�1l	}s:Q<{#�P��N���ŀ
��转N֐=֯�W��s;St��ӂH�X��վ=�>�n��;��l�
7��N��|S�B;�Wڙ)t��x��!B�©Z��tj�du�dgf6�3���kx+����g�h_(O�o�x ��8�Ev@�����޹���Cy�Q<tfQa$t�<��e������x8d_*b���5w���
�Jq�*|�6F��M��[t��UU�����[�_��+�(k��c��U�\k�bl��u�N�]��,�)��Uh��Bs���ZQۚXsT�V�gM���I�d��Mg���Edć�+��E"kE�H�2`8���Y���IY1�<����[����V�Hn�Ȅ?��
AoIA�z0�tv�N�2�
� �h7��'�+ɒGZe�e�{�
�+?�"2�9�����({��({�Y��<{���=c���+���8n��@�W���t���Um�$ެ����� ������+�}��+�3��Nn��ѹ�k�f����u��w%��eq�Q&�ђqX��X����iS��sB�)����s��N ��R�ZQqlQo��Z�q��1��{p��T&���	��֩/�=g5oJR�n�k����NW�]���Ӕ�kU��V� �O��U��W�Z�b�+7kE��E�(���Xhb���N�Q_sa�[��g�V��h`K/��/K*Ɠ�g:��-QPf�riѲ�@D�G��Ǖ�t¥�H�J�kvys���X�����m�u���,<�H�A�5��]�v�k��{C�g�N�����T_�f䈄�RF��2���E�Zyj7c�8�c-$K��.�Ϧ��a"k̶c��<O�nEQ08����o*S���+�]x�[�w�qa��y��<΋U�Q�Q�Wq=ݫX���\���/��^�d�Oӕ��"�RD�Q����Q:L  z18�D�a�Ă�g�i-���E.zF0y­��;�&'�A���cפ��	�Q�@��dd�ǆf}��sO�3�����H�<��#a�C綝�*� ^ �7��Fz9�mĖ��,�⛔ge��R�`1��!.���7>я��X�m��)o�ү�G��]��~�*�{��~Y�$��S�7g3�Xʛ�?�/˛�����~���`��,����=�T�D���;:rq[����B+��reV>���&A綜h:�(s_ B#�IW�	L5�܏k�|���6�K��8h���9Xk�f\�-�ae�](
-�am7(Y��r�n�����dz��C��]��V�˙�sb��c��)�l1��\f��QZ�t������:y��g��0�"N���R-z�"N�ڷ2*O��'O�툗�>Y���.��S���S��^AE�<��MͲ8y�A���e��T�V�e���uZ�gY�<��=�L/O��#O}qg�<�8�?H�����|7�ߓ�FL���v5��S�H��6���_��J�����S�6��Ժ���w�E�������kF�-?�%]^هTͣ;qG�$PQ���1C���)��e���.c�ʍv���e�,lz��DaAp.s�O3x^�$+7��id�A��K�4��4:�!V��hqQ�e�[)��GǛ�P�P^����6�l0Ef��zӭ9P�Αn4(%P쯔j=\ӝ��wp��s3m�.۶9���!r"�8����7�o��mӝ$���dٵ�1y)�H��v�"�b3��{|fe�Cl�����C��Ǭb4ct������ٽB��d�{ud?m����L�u���<��x��	��YyC�nQ �Ŏ��Gof ����E�W BU6���7�m�!|����7w0��O�����b�s,����\}�Yϋ��3�3�E��R���c��P�%���jT��gcG�Hhf���F�O�]	B�3��i�Ԏ�
��,c�5�Wk$)���{"��xF���ED�CQ�kU�
�ߚ�㻿��q���8�/��7��rƥ����;j�/��p0ʸ��=�-�+����}ʸ�c��)J��,����S�?%�����)���͛`l�����{��T��E�­M�?�ֵ�[����������;�I��o�:i�t�Sz��U������?�4#�N	��0g��P�)ap�PQ�e���!��G�l�b�=�SN}�#�=ܮ�ϙQ��fm�a�ճp3��7#J�㝧#�r �4�w��1c���|�w
߆zk~CP��a�\Vo�A�c�J̏�}��G��~};�_.���z=��6�B�T���ΌK�����B.H��J��}���	*}��,^*'O�`ż3J_�~��wX��7>�
��o�$*�,ݢ�.��(��q����K{�I�~֐�B�X��U���j�`_ƛ[ ���a�ͮ�hA���Y��*��+n��g\rC�/v�p(f7�P����Q��|/a�����5�|Z�g��?������?���\��m�?��'^�o��vs��G����`a`���/�5߈��"�d/>��z:݊^.b�u�bP�~p0p���+Cv�w~�Qt�vm�<MʆM���Y��(*P��>Ё��A�r��h�{\�!y�5�@*G�����E�%�1�v�F�3����rҊ��췞��h��R�Gm����vᙉm&��(x��r�Z�HCw&r/�,e�ȓ���0�>��!�6�s����Z�� v�]��vDvv�d���乎iH�Z�vA��;f�Y���5�^D���$��Z`���)�#!z��Vq)���^��Kf�˳,�l)��Ci1+�e(�f1�xS�ԝ�ri��Ue��3��=D����gDBs�%�G~/�nf}�A�P�
��=��!���;qH~gb�v��iv�6g���#:-..ǻ�oADwe�M�N�s�\�6�x2�4��Y7^Er;;�ed���?@�=W�Q����d�8�����b^�hd/���ڌ����n9#�TZ$��~*B�6����䵂	��(����g俪�u�5�z_��x�(����p/r_���]�~3�������{�O����'���f�sv� ]��1�G0R�M�����k�[S������έc���8�$S��ĳZ�[{b�ڢT�[h&�W��0^y	dБ�/� 7����P3�����(��C��B���Jۣ��}G��m��_����\�#[�tr=��I�L�Et͋�skY�o\%f�����-�-�s��
�<?��U�[�j��v�ì�N��63e����aX�\+H?�i���mT�.p)�r���}�Ύ����qy������+�{з����o2|��]]���y_�K�&��Y�a�펿�h�$�'�1���.0#j �W����-�(�W���ѽ�F@!�B�2b�~M>:��QK���s����o0v�&��nR �H�X��2=9A$��i�%����t��d��mǑr���g��"[J�Kƫ�ձU� �+�����ƴ�����S�u$/��@v�	��@9ǭ���g�?W/�Kf)/�=cI����#2D�Щ�s�P��:�$&�*��{�?�]���7�����\�#y�,�}Oql�g.w�$�ծ�~��u?��ѩ_ٳ�X[~*����<�۬��Q�C���{o�{�:n�|��8x?�+�n�ϗ�����s|>CT�t?��?gWƾ��>c�}{x�\�L�	�+b���5�����:�L��R,L�B���H)J��ʘ���^?G�����le|����w�=�㞭qσ��BE�%f�q�f��ߟ??��+��*�y�2��[��x��� �~^����Z��ψ{Ί{���79���я
���q�����N�����������wǛ?����7���u��������Wď�ח+���Ǐ���#�h��������ǿ,~�����w�S�9zUEzވ�SI~'�)��[��x����c2:)RK�d�mcrg?(��#�	�U&̃8�nKN�����U��[�Y��IĬDI8�%��/�Ko/��wZtKcr��BO᭺��TU(I<�,V�o�����B|�cr��&�vr�ݙ���i�n��	����+��nl)�V�26�����Pz]��?Fb,�l����4#��2��v�x���~���������3�SG�7��X�rӖ�[R`~.��T  3��軐��]an�:�=��6`/�vW0-�ek���u{b��g�iۣs왃��Ӯ�J�[��-�g�x��3��~���� Y��7�+B��m��,j�fh�8��= �}8�B`�f_��X�ޖx:'�m���`r��ڊoJ�%�{�����L̥��S��[���J,�G}u��bV��8R�ML�{Kk��Dz���K:#\+ښDyn��t���H�,JsӅ��5΍h�>w��z7�Md����~Љ������lu�޹9�#��z��#"��1^��{n���켂ǋ�r,d��F��GT�<(���q���/��}�=�{���*�����@�{�Na,��U4%�+�Y�q='"�|֔�Z�njj��zb�=�����~���J�����ӷ?�
�7����=�����x��շ�l�����Gh^����I�M�b�'�����~q�O�w�ן���#W��)�=劾�B<d�:)t�/����[�HD �4�6=]
��/%�~ Ä���݄T!5�:�F�:q�
�DI��/v��'�L%|�����������G�)җǕ&W��v^�]�[��I�����{���u�/�hޖ���1��������&�������Ў>�|�������:r�v�9�����==V����7�I���O�D���L��N�_��ݛb�j�|���wp+/�́�>�>Ǌ�:�uQ�酕vt�o,���ZVN��q���ߊ{�m��k�F�#s�L�8A�:���N  �,2#�^/R毅����u���B�>�*��[/��Ŀ��Ͻm��_����cE�Gf�[y�6�RLY,�^����D����To�OL�����Ck�.����1�g@��b�)X�R���̛N�pǵ��۫K'���^z~�����B��������4��0�^���W�̃>�3���~ڡ�"��1��>~8�Z�'�_��f�=�99<tܿï�}*\��:��o�a�^j�p*mW���i�����mLyE|ysl�o���[>'�����	Z��S~ҌŃ�4��]xH��(�y6��W�;vΝ�ƲmBgQ{�If�ywV�w�މ�y��҄�y�N�wg˼RL�s=��Ǎ��x�?,�탞��9x�����|z����;��t��Ø��x��|<W�	����s�e9g�	�����W����p��p���b�p*�Ώq���3��l�S�>��F�=�U���p��zv6{3p�Su�Jxޕ��USǛ�f節H�Hf�.�yv%��y�c��y�XPX'f`�P?���?�r��\�(�Y�93��ǘt�,�$�ւ�y<������3��I���R��㍪Ϲf�m��<�jR�G��gv��R^(K��v�O��Q���0��љ;:�t�(/4�9E��	j�IQ�����Vてh���tè�E	_\h��(�G�e�����8���9��~����u@�kZ�	���ܣ�,h���Jn�.���oT�O�GW0�z
�ͅسB`��i��)�ڪ���ig�kv��,�� ���~7��Dl	��x����D���H��w	H,O�C��4�Ѓ%��K��#}=��^��=>~0�S&u�����\.'��2�n�E�@yI�H���L�\��=8#��;�6¾a����1�%E߉��E��rW�3;��
(o%��3;I�g�U���>���nzxJ�ge~����x$�����gF��Uxz����(�n�,<��u�B�ثq�Ĥ�'1�S��?�-�<����^?N>i��w�����5D��������w��[�����������_Ó���_%��K�j�E,�>ڍO�ͤ����o���ݥc�����=�֟7�ߩ����]���?+o���_�A��W�/9��sj��7���j����^�JMb�o�^���j�hS��U�e���ta�q���^��zc��ݠ�׌���M���1S*b�y�x����v�_����㿬L�]p�)�P����?2����?���:�;�i~0��e7��Xy���D��R<�Д�h�,�������� ��������i��i�y��'���'�Cߣ)���l<Jh�w4��]���X���~������Q��q��qo�8^g��K׸q|���aM�y�8��_�ɟtU�]��dC��O�D'{�\ٞ�7�鮜�b�P)�hE��^�b�N"z���֏Nr����B?)̠\����_T`�h�.��*����W BNf��L.�K�1yz�Zb_,q�}���܏|W�w�pVm�{�'�X� �6s�j�}wy��O�ĳ�<����9�;N%��"��F8����p��z�Bj1��3D�� m�G��I���y��3���.��P<���@�Y�3�¥'���&�o@����k�2��]�J,RT�]��b�y�#�$2��#�����% ���.f^`](�� ,�-W���;��_U|$w�#�_	�S�e|5|���d�/_��4|�K`�Xa`�x5��a��c����K�*>�&w��)mW����2>�����ϗ4||q��c襫�c�9�F���#턏r#�㓋:||�Q�L�x5|��md��V�]]ɷ�7I�t��H�),�0�KN�#
����_Y������R�^'��~%CO`i��m�q�9� m�1�na�tNeƩU��K:3^} On�1��G.�noN�A������oz�yzi�����,�)�T�=��g<���R~}�תz������4	P
�
/�x-z�*n���w�XZ�>7��p�bP}�q Ӭ��37�����³"��=auJMy�*5���S�5�o�zV#��8�<��z����~!�`��R;_I�A�t���*Y19�	�Mh�P�41��o�z~+'蝈i����%�a�ait�ߧ�;Z���K��x�� ��RX��x��6j���k�i��e��s<��8�&�*���=~@�|=�y��A�tr؁*z��_����Xm�����,��JH+�a
��3v�o#�Nn:caq���h�<�1Zv�깰(H�ے0<���Xxx���B�i�A��|�r;F�/�W�C\a�r��B��+g��GD�f�rks�)c�M�&���\:X�<��&2I~�gJ K:��O���a#hS��4p���뇒tƇ��6z����f�k������)o^�����.3#Y�v��N>ũ
s�t]ҭ�bc�<��9X��6Q2�A��!�vȣ�hކ.)��S���%5����d�}Dy\=�1��M�)F���{�!�sH�'���&��y��%j�0\���T�K"�sv�I�ʌ��%����<r��&v��e�����	s<���e�$��J	�`3���WzR�r�	ӑ��,�m���&�_�Y�qԪ�DWpf��m���%)n通�����	� �3O�U! ۙ���i���F3H�~���c-�5�����2��t�U_׆yw3#!K����h���n�N���@g�&�Tz,�U����	&���ԇ�M�ʍ�ڳ��Jy(�xR�����Y{���n��$Ȕ ���=��RX��S�C��<�r꾄��= �� ��Xc��c�I�<��o�d'l�%fy�/��r�	3V�Z<�/����fv��(x� �Z�<>M.��:�����<�w�z��	�;F�0���W㩓���K��>�`qL��g� �GB��OJ�sloQq��V�����#Z��_	��3��ӋW�����;/�����דg�&�S����Fq���Q���<Ny�Y���JIP�-�5�kBv��>�?CϏ(K(���9�oi�*݋��NSlݬ��*��*�B;�m$��u6�Q�<����0D����/��[ ���@��'{�w���Q�d�Q��d�%�nFOK1(�������CX~;��i�y4I��i�P�p�1�/v�?�R�ψ���3��`��bi�t���(��212MƐ\���؀I�`�@_�F jQ���Q��4�y�D��te�7
@���(�P!�.�ۻ��BvHw��'�OqRnٓ)eS�8ʦ��yB7�s*�ٳXiv�=�;z%���*Ϯu!�}71���Пe�Y������Z?c�[�;8�EW�w	x+n�)���e�67��x���r�'�\��]�h�K̢�௥omx�_����W-�r�Ius�@��Dۗޯa�KCiL��
��h��q��-��?��lϛF��l�7i��"'q7�vB�f��]�w��\㒎��k[hl����@Y����_����0��4�:����p�3~,FN��ݚ��ҏt���#�0!^��KZ��c�5Չ7��ò��� 0a���: �S���0&-K;ක��eqq7Ijѵڅk��d�B����S���/^�*�/���?�ß���Ы��ŉX�'�`�;N���?��U�O�����~����_������1N�'�1��)���2��g#))�S���������Œ=��?=��ss4J,�8�=���N
n;�����T�v�)�1�iS9�.�q5]��%|�	�A�_��������`�	�]RawI��n-���ɔ$�Cp��w������i����q�����	����F&���H/�Z��kF�X�u���#�rw��MI�JR?Q�:�<�d�&�cS��K*�L=��΄�������C�X3�<P���������j�պ����Q�b�#6������dh���.i�_����^	 '8%�DRt^Z���lG����3�m:�W-G���<F�'�[�4׻%�9TB{QRo�b�\���v��}�㧎Éѻ��^�*m㥸����������Ϭ���֟���n��I��`q%p�ВKU�^}���H�:�a�l�Q�����W�wH��B����G�\}�b�M��^:�o����mJ,�����
�>W��劉���b�[�cc\��0��?�-ྚt�@�?)�4�T.�R�@��-����'��:k�?`�^u��/ٯ}�T��k�:�_Oߣٯ��)zG������T��O�������z/�Bw�ٯ�O����ǭ��(�����7)������x�����s��w��د��_���{���{�U���������
��^{u��a{5�>��cT�C��=������6�����Q�����~݃^���1�������w_�Q���X�i�c��/P�ɗ���_��`��۽+j�.:��ׯd�~H�_?�M����l�D���҄�S�"�+N���(m b��=v�:����\Ӟu���m�v����� ^3�Ȼ�K4&�+�5�	<�%�)��R���^�po��$β���M��s�������UDY��YF��ŉ��B�7��D�'A��H��~|��θ֪ E4������ 2�cL�{�s�s��Y�\��oO��-�j����Cݛ�ڒ��ƃnt�kF��2^�m�V��hR�൱��"1�dv3�\p�_b��mE���n�
M(D�[@nV�zV���6��/�h'v\e�����i�>������w%N(R&<KA&�:@k<|����}�dEd��(V<`T���o��h���<��_[�!����ǃq�*4�ݦ�^�N��� Z�����l`�� ,��wE��k�&����i��p�'��.�Q��>0>y�Ŷ�O�Q��c6��s��m�};���f��_:Ht�MIǗ�*� 4v�� B+%��4v�3;"�Y�6��}���7�#L���;)��qFXB?<��`Gh"tf�����D��\e��4��#3�+����ʾ�ÿ���׷�r_t�-�Z��mn��[z���
d�k�I(��^:�-�;����"������p��<{�>�Y.yc|i��6a���K 2/�^e��] "\�S�NҔx�IU�@_"	�mI$���xt��jQ`o'j�բ�n����I( ��ԡ
������-?U��B<2�VbF=hއ�$� �ѷ�5�#��4�9����}.JO�yR��o�����Ğ�{��L_w�����
�&���	��H�Pg1�c$4�i���Yf�]dr�\.�Bο$u���/�pA�:B��QaF#'��;�?��	�,=b����9eJ��"������(��`�"<��v�����z�g�D6H�:fv���=R@�X'c�u����T���^&��m<�I�$�[��=xg����Aw�$���C4n�҄L�f�a�
4[�a;C�Et�	D�}��R��D+m�',�qR���a7�Ӫ�;<{5s�w����>9��YSMz��
Kz�t��vǼ�����qwL��b�~�.w�O�a���G`|�/�Zc-�:���*,2Vu^���3^U�=��I�|�q��ͻ)iBF5@��,.[
1*�'��ݜQ���)e��ȇ��-�߯Z���~��G�uO;�ç�oq��l����v�#.�f�6��.����ޅ
Mvs�҂1�"�8��-�y�EwlE�h;/��@)����	��C���'5ųQ����C���Z��L�ID�2a�P�7��qO&��4���Po��rp���K�L�iԃ���qRYc\�*#v�g��hou�BwG�/�}���dh.�������f>0> �A� �)�;՝��uX���?w�k�Q���c�X�v�s�P1��GeA�.#4��{c�39����P��#b�i��*
�Z~E�j�$ܶ����sPg�1 ��FXy5���ZLx/}��ۉԖd��JD��%%=���k�t��p�Q����&m)b}��=͚ܲ�π[��y��t�6V��I�x��aͧ�؀�r����ث�x��v�8�U&�¿�.�ƶ��W���J���V�(���*unNהk��a�*;����<���x^Q�9u��C:��iִH��{��ݮ�Q�QT�@
�ܯc �.n$Z4�ja��a�X�] aIx���P��&��)m�q���I��{V.�(���p����&�Ƽ�9m��a��)T`�����6���#Z��[�^S0�m�;x˥i���ˡ��F/�Q��6����[X2/HU4��9^��;��`�!�V��etIw�lC��O��A�I�X �KD�CC+�wöEqABuL��z��sа/��t��@l���&�c
Q_�g�]{?)�J�R����c��	a{�KLa���AT�p���E�P����Q@R=MN`V5�'}D��P.U�~ծۯJ��`�0-�x""?o�=�V�'$�.܈1���Ճ

Q��{bp��>1�׸3�x	O�x�:���R���9HI8�͉HK�"�#���e��rGΪ�u�A�M�����Z��A����H$���,@���aH�V�B�1bG�f�'�ٶ��D�寈�¬3)�hXSБ���=xI���[TݭV?�!�s����x<��J���f�@�Lf�.�B�P[�Ux�&��p�,��s��_A�����NGwuf������|�ӏ8�S��D����SHtc�r�kN�!�e�/����F�CI�R�H�X׸!=��`�[ߑ��w
K�Dv��Ǵ�ii墱1�O'�lQvl�P%���]+��Z�H�*�o�L&6�c��JX��?lӐ|o��H���Y��4+�M��&�5C�Zy1�'��0�o,�n-:�:��|�A3;��m<�l��dW��y\;�^�\�4�v_���5n_�$����@j2ڤBD�X���m�4m��=,O蚛��y�{�o��{ �l_z�*`7��&�p(��ּ`�ZGp��FO�PQ`Ж�-�|���d"R��xX4K q9c��%E�7���HN��?��EꝆ�!V��PM��˓���<"�=4��8'�*?�w��@=�ƱY3����6�5���}*���� ��-p��� ��X�����ǁ�dD�X�����a�o$�8�O8B��FO�P�%ʣ-O���O!��C�}��"�V
��3��{�~Jx�(�;ՌN��T����ƗA�`�4�v�h	�mW��"�>�T�^���_����=���b!1�[��h{��)J���=f? �����w ������ϳ�f��F�E. '��c�թ㮐~P����^��4ZX!�[� ��\�]��3�?T�,b��	��B�;��9Ű��?$�F�5�sr���}�|&�99t=��rN��"4�kH��,H��P���ӡ�����v*���X�9��^.��C/���}�B��,�8l�ً 5�#�	����z��ޏt\'ՅV�cK�O��g�>��ũ��L�wWh!4�-���c�~�v#OV3Κ����{%|�i�d�-V�0�I8+V]�jM�
ꄆC9̓=�!���H� ��=��wǰ���rf+*/#�}'�	�w�@�-h�ִ���G���ʇ�JCx����-��]�ތ�c��d��S�����,7���(G	Y��2��Mjl��Z�2��md
Db#�����J�4�ϔ��@���n�y03X�{�����!�ɒ�-��o��Č�c��@�s������0�ֻl���X?��{�I�H�������?0�՛�ݜ�*��M�ʍ����@Ӡ�,q�<	Z��[��*Th�Z��u�U����	a�[HX��V`S��(�]���A�N�ZS���+;�<ؚ���H�h�[4	��l)�Ī �>T�܁�v�z)�ބ���Y�)@�&U����^IN�[��4S:��ɷa�C1S��F�m���W~ʄI���FѶ]x>DwB�	�^(��2�A<7���ԋ`}1��(���ˍ,��}��#u�6C��ap�t�1\��+���@�E>��Z޲p)fJq�+��#,Eyp�
e%=剥��~�� �����99o��<*�M��-r�t�yF�6:��)e) ��m Ќ���XT�6`&e��3��g����83�44���H�G6���j��/�#���6C�~����t�F�/e�K�e.�1��`�D�+�h)�+_�g�5�/+����h�ڰ	.|�p�e�8^x8b��!O�C��2�B��z����c�N���GhJ{��%�=��.-��[�W ?i��uL�'k�6�����H������m��g��A�g䶅��I`f��QX��U览�hg@n�kP?���^�"MW�6�`��� GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT> {
  typedef Templates16<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT> {
  typedef Templates17<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT> {
  typedef Templates18<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT> {
  typedef Templates19<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT> {
  typedef Templates20<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT> {
  typedef Templates21<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT> {
  typedef Templates22<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT> {
  typedef Templates23<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT> {
  typedef Templates24<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT> {
  typedef Templates25<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT> {
  typedef Templates26<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT> {
  typedef Templates27<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT> {
  typedef Templates28<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
      T28> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28, GTEST_TEMPLATE_ T29>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT> {
  typedef Templates29<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
      T28, T29> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28, GTEST_TEMPLATE_ T29, GTEST_TEMPLATE_ T30>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
    T30, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT> {
  typedef Templates30<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
      T28, T29, T30> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28, GTEST_TEMPLATE_ T29, GTEST_TEMPLATE_ T30,
    GTEST_TEMPLATE_ T31>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
    T30, T31, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT> {
  typedef Templates31<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
      T28, T29, T30, T31> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28, GTEST_TEMPLATE_ T29, GTEST_TEMPLATE_ T30,
    GTEST_TEMPLATE_ ���i�_m^?�pYlĮ�~�P4_-�i�g~����3���LW�#�~d�/��/?�����M�v5���{�.�QJ!��������R?�����ǯ� Ċ�ǵ3�7Cj��]����}�K�^0��� }]%Ͼ з�;`���
�+;@�p�ڛq��y�QJ�`�k�?�jU��՗l�/[ɜe:¾�9	����L����k��)~l�T1�c6�m����dv<��c��.��U&�����U�a�1�*�0�������燐��S�Y��n��g���U��,�X�,�RU��wv[��m�qr�{��l������}|�/��U���`ǮlU�����n�c�XءZ��)!��	��6�oϟ����ux�r�?g�'����7�b��T����gx��}��d��f�S�m�H�뿍��'�_1���������W3�#�?'<������6�v�	���F��������'C���_��-l�J�đ��^�2���x���A�t$������X>j`[�Q�:��u�#H{3av��G��<���r����4z/��׷��<�|	�gt�������d�^?c��b�~<!��2ﳡ��1����k�j)ӷ����+C��w���呐�sb��}�U��v�A��)m8B�'@=�P����bo��vy�|0��󺆳�P)f+B�iy��LPU�y������RR?��ꏃ�s����9&�Yq�kJ
��B)�F'L��#XI��뤥�q~�����C{vv	.�^�������sA����i�Zd��K���ϖ�g�;����j���.�ϹKJ!̔�>5��nh���*���v���,�OG;��O�@�wVp~����Y��6wn3?���槛!/��1^+)Ou���7���q�U��؏A6���z��0ݑ��:��<U�J;n`�<�Xxe�Y��\�Hܿ�����<�ct�8��wC[���;���<�$b��`�_&-��h�-�*B*�:��%�{t�9�����內�qvM<*�j�D����&�o���^�N��Oo��E.P��}�f��?���e2�?��k.߯��\��;*8d�c:��s�)�H�#���#C�M���6v�sE�ps�(�wD)|�IK���{>uh�xc�yN[�_�������C�k�@ߎ�[�u�Q�w�_Y���)|d�Ck��i�ߠ=�{U5��� A��a���r����r�>���[V�9�r�Y����������W+E����L�~��R����suo$���p�Y�&	m��cz{�\�V�|�2!����tDn[/��A�g���gy�8!0���c��E�Y&���?����O�؏5�R�h�O�A���O���C�y���uKk<1?�����w*��&HG��;,пՠ7�O=�~�V�p�#K?vh{}����/}j
���¸��z�7���7>5���G�E�.�����-h��>{����S>��C�nқ�כ��D�\������OH����y_j��@�
R�zg����>�O>�ox}�������8�^Z������~������q��1<�oI`O�|��<��q�ǽG���B� #�o��*������l�c��6&�ε�o����G0�d�sHdv/�B���7d�_��q�9�d�|
QՍ,���
�#�N�.��$ס���ZUe��O ��]��5f�hveϭ��i`�[��K���]�y���zU]�,��g �C���>�������:9.�۷���Xg�j�s'W���,j�G�c���ݠ�ѣ���.�;�L�PH���o�׽)���Q�S�O��Y�G$��F�󟀷X��?����3���Y��<�	�:�p�z<���8���l]��]��֧��u��~f�z�yM�ǣ��"��D�x�߅�Z�D_EH���ߛ�<��z
�z����^=����`=��z·����zv ���.��ίõ�/�_��п�P����/����q�ʋʵ�ɡ��<_X��@I��Ϙ0�
��0�m���C��ѠyJ����T�A�U���e��NzyZ��L]�R���n#�H�'�����S�E��?y���N'5Q"�/�Z!H#��Y-ݗN�DK��'ۣ��IK�����.��r�eidM,�ӏ�K7�6���#�� e�D����;�W�ɧ�i� ��}r y��^a� �q�؇���n�&)��<��B ���$�����0M5��ܿ��n�eА�u��c�1�W$��Wt����A�����_�ide��@�9�?vY:y$n7�3�W�}w�����;	JJ�j��n������@�~b�(��d� <O�o�e�2J��.�<K�O�:N�]b#ـ*�ۨ��pS�H�u��V����6��C��U�"4��(v�P��k�ϰ�5v�!GȘ ��{�{S9Δ-���«}�
��E*|C�����n�IGl��r&"К�o���N����~Pu���m'�~�ON�<k��z*F�:�>���-E�!Zz�I�F��r���V����E�*��+�卑��$m�!/ƀ�c1n���eN�3��l�9i�8�3��$�J�|$�pV��2sꚩ¤���QQ�!���|�@��D	k�����l�y��I��g��Q>�X�X�������z�A��q��9t��6�
�!�Ԉ�K��A=�"�"�xr,Jj�%;�,Z�Ңr����Q% ~*Z�����";�/��#�b�w��)�.���X�;YP;��,s���S-�9)0�4|aG��vd���,�;�`��X�2���b?u1`��ǿ\= �\7Jj���,�v�L��"�l҇Q�����	��#�Q�4�"���"p�ɀ�(v�$
����@�{Qz\?.�3�WK��ad�D�6�l�F�@ؓ�CN�s�~����`L��{7E�xE��%
���"��Q �+�|���t$�9�c�7�8�_����c7B~��(>֝��@?I&/vzU�4���L׏'���w<�&�gǓ׻���|�A�t(dk��eCw
�{�������dՅ��I��t�$roO�Ti�Iw�ʋ��"���."�R�+ɪ���d�%t�D���|"y�RZ7�l�Mߜ@��M7���Нȫ}�����>���˷	P۩�U�iy�eO G�lpߐN��'G�&���Ț�̤'�<=�5��u2����k�e1������,f��,�B�0���}}~<Y>�IJ�D�J��9�>��	dI.���2=�r�Ա\�gi��"��k)��O�c�'���G\�����!U�:?3��5�ώbLU��������9�s������ѱ�m�x�3&�YZ/��"9�2�R���̍c�:\<g#��f�2�DY,�"H�,m� � �Riyy�&r�&��7����"���a�/"(p���A�L����	���o�.���7�'�N,M.���xQa^�����/�tb�b�lҧ4].�&���d�R�_��W@Z*�����Y�'�:��>$@�	� .�di�@<��@>�]���B~�BFv<'	7w|C^�"�V����A�!�D��L��>���BJN�y�#�:J����LN�fgH�󻻵eQ�t������$S���	�G��"П��m��H:��E�^�?����%C���1�a�H��G�N�g0�ڡA ���V ���O��#�G�29�<� �=2yY������"}L$�a�;6�c	y2�>O��~&�ᐰ f�'lt{�����b�β1�3���މ��a!�~qЅѤ2���Q ����S��z�{� ��������0�.��7��]d[,��n��']��(���|uV|�E�t��īЦx���띗CA��6Ƒ3�� YKy76�\�~����.��"�j�k�X+�X�q1 <�\�R<= z�GK���5��wֶE��5���#���XNK�)�|,��"�7lk �1��� ?E0įcM�`/�5���`�ݚ����gA�=#HO�t�H^MD�'�����AZ'��<���n���~R��]�`�K��j��N���3�>���.��H���Ry�����E�t��8�z��Gߌ�ލ�+��	tK��1�\�*\0�Br_$�$d�Lw����#��K����1�s�hr�I�I-�aa�M?�&F��#�E�VK�I����ʘ�ؖ�$~��2�^���xL6P��"Y/&b��.N���^��e���&�J���I={�]N���ڟk��΁?C���.������Rcw�󩸫;�q����8Zӝ슧g����C2�t�_&�&�M��TgZ�,Tw��$�MItm7��TT�LA��d�{��d�x2�	-�Δm�����f�~�u2��	Gdz���)��	���9��>Z���-�|/o�u�f�� �"���&���NG�c��N���xV�A����nq0����� ���HA����z�C���h�L�3:�*����PrH�5�<C���$�p ��-���d��=�3v���N����f$=l'͑���(�����b�{���(�v_�6�v�I�aPQӵǿ��Hk%r����]'�G$ݦ�Bdt�A����R���M�"�A�,!mNҏ��J�ޔ�-=A��]G�������4��,cծ�"ܚ�x1��ψ]�Id�D�>��������܈���h͗Q��:��]�Y'N�^ě���e���%z�98@��H�6"� �"%:m���N��H=�tZ<�[��\��"_��d_�����/��G�hԃԋ��vv"u"�Fڈ�ynF~����E|�پf��~*�G}�H��z��#� m1�7�DJ�B;�֣G E�!N���|�}��>�t�C}n��H=H+���6#�"mDڂ�B9���\��G���W���s�n_3�ϋ|n��H=F=H�6#mDziR2)���G�ӟ0������/�+�����m�#� �DZ���i#�î���׌�5�}n��sP.�l_&�w����j3_��w"us|e�W��eHS9�Eȗ����<�W�~�r��by&��2~|�rN�����B��s��R����:��|)cu|5�L.��^�~��0ʬ�~"��ds}�\1�e�}�X�r�E(w����_����.�s�|�4�?�?κ���4�1ʬ߃vV�3�g�5��wT��o�y&a;˱�PO�(s�#��?�]'�y�i�����,߂�(�F��|�|�Ur����^�w���_�rŜ��=(O��9�T����3P��[��O�fy'ʹ9�B��D�f�o��o1���KQ���;ڜ��|������<A�'��?�#�P��f�^���\�v�����g��u��[�zRQO��A�HW#�ȵ�0�-��;�l�A>2�9��/'�|�������k^�y07��,��v~����\^���G����9~���G�.4���|��M���o�y�{����?�z�!��!���5�/<aݾ2čy�o�o���O
����'�����o��	"'/r���Y�\9	�o'W����wf9c>W_�w���	�����xc��BO������FN�ȧ�����,Wl�����)�!��͟&l!�[�0������m�w����{���9ԇ�����?⺐�w7����j<��K��9�s>+��>�Q�5Q�~�ߝ�y�Hݞ�F�C��f,O"�9�So��'b�3,��d��f,;>_��S�l����1Vl�kwD��7��G�ɰ�Ќ{.6�y.E�Q\}>U����x�?g�Z��s���/|�I ��������v�U�`=��b�؊t����t��H' ���v�5HB��N�{�����g��&a�H{!MG��tҙHoGZ��!���D���H�@z��Y]�^Hӑ�"��t&�ۑ� }�F�;��E�>�/��Ej��G�i:�\���Dz;��!݈t'ҽH�G�ҳHm��~����#�E:�L��#�A�ҍH+�q�!̋W��]9pZz������e\93�ߌ+g8ufZ�i�3�O����?�oɌi�ݤ��p(�;�t^����H�9����{Ӝ��N�m��>�J��T:u^)�[r�ywޢ��z��3�Λu���(�;c�Tƈwe��I�Ysf�n��t+ܔϨ��L@��֒��SI��SfΝzˌ)�%s[�@���SfTL�QV>�=CW6e�ܹS��u���L��j�N�e�t�j���6o�f���g͹��o�K���$�iO�_枓Y�@�4����'�|�-CH
� r�A�[�䍼���En>2�1�>Kf�\`��ߠт�~��98����bЖ ���ж��̠�|���h��(?��j̧�����~0h�0�?��o�h�9'G�p���f�����w'�8�L�] X�o|�����A�´�
����r=��֋��N~5����v�s�E>�DWj�8��E���v���ZT�֗�G���W�/&@�XnF��0��~Cދ��vʿ���B�](�Ӷ��;�����/�����\��ES.D�V��ߠ_q��z���ض���1OWL-�M|�B̐�G��i�����y,P>-�����=(�ږ�o�8Gx��{\T���]�oxKT4B�drQL4�[
�E��.��\\V"�n���4����w�������i�j���7��f��������x�����t��y�̙��k^󚙳�(<�y�J�����T}L�C�W�v�	�����vB[��KP��y�Zv�_�\8�W��|e����QL]�Y�=��l�+� ;�{���V�Q���� A~�Ju�O��kD��
����Xx�������8|�R��dgS���a���_�.:xyC�;���%����Q�G�=�zو��G�:4@��7�
�T� B{���TPw�*��fLV��>���4��g�Y�f���t*���-�G���&�}�P�*�e��7��+~� =<B�9�Q�Bi'�N���~�F������U���(O]?��I#4*K�}W�^��(h2�yYr��xOh~�P�A��'��	�O��5��6V�W�+0xXt]r�w�,mT[��<}��6Pe�j������s#Ԗ.�v�����
t�ȡ6���)�,4l� ��,�����0MSRo�^�U���<���<rrlޯ	�`ѩ�_��z��� ��`��:A��2�J��h�Y��)t��*��BR��*X�To�"]�P���-VB�ad�PO�j,�N���^�j������������B�ū*�Q�Z�*���Q{yh����BC�o_�Z_R"�t�����	�~����F�^��4h�8 􀧥�64�g#c����2l��z��`�[���m���nҖ���c���gp�D�s<�b�|�n8�Dy_1��f����[8�±�~��<"��#(��x��+�On�~�'�8��?�q
�_P>��_�����p�G�����|��a��8�|�����p��u����M8nqy��\߆�.^�������I��Z8��QIÌ�k��p�G8��ہ����u#�n��õp���)�p4��s�%\��Ïa��W�� ������v�$�� �?��#ʝ��� 7�tA�����;��\�����g�r,���T��g�qi�<���x�A���p=���e�C����;�1�	�{z��0�ΥG�y7��`������pG$ʣ��^��s��X�~�{�xN���/�<�a����7��i��N��~4�c���#�{&e#��H�#	�L8ς#�{&�4���u���	��,8f�1�lL;���r����"<[��V.}.�K��C>�l��R�.d�kx]�e���b����L��p��7�x��7䟷 �ۘv=��;��%������C�����x����3q�oy+ñM�ܟ0|;\���3�;��9_p�v3�7y|�8���}r�������� \����p>�P���������1<��	&�I�>�/;�\W����������B��!���y8.�q�I�'��%�/s�/N�3���
�5.�uF���p��m����.��^�gأ��?ԩ�	�
�=O��<��>ՀI��irc�����Z���s3�n���s�P��s���|�v��=��I�����3�p�GW���;�{�u/8���xb������ y O3���c�v0����Ł��u�,����.m�h�S�N~��Q�Ҿ�0��1��E�}����W�o��LY�ƶ��ݿk� ���#*_8�{�୫��S�k�lQ��F�l�֯gn�~�^�yh�w7Z5~e�A��Ӛ�~c�O�}�[p�j8;2�-�d����s�<��yp垼f{�.���?���,U�M=TU���/�p�X��`��o���]#Ĵ>���w߲-�pmJ�)��}�m	4>���7�u�5�>2W��s�s+G왝��s�̙��,���/3��4�����z��ʉ�,Z�b��ECZ?u��A9J��P� ���g���Û�L잽���}��;�i}��o�%][>��ܩ���dį�_�<e�m�M�w$�����m���|�F�a�߯^�!�R��?�.���`�tz�ܳ�.�x�q�kʀ���v,,}4���Jq�Ӟ;7}>�q�[�/��+�k�t���x'�w֞��'ߞr�@z�	��4Ř��6=}�ָ�[��=���ɇ�4��h�ʎ?rc��6�2�������۵깩�Ըc'�<��O��iY�^c6\��]V�����:7�lm1>��[�'�N_��פ�#"J��!v�ϯ��XcC�� a{߃=~��o�W&�w������w-*֝Z�YQ���0�}����Q�X<��Ͽo{j��٥%��[��k���7̌8�����_��y��۫{�jӮ�Tp��7���}z׬n_^h�ə��Zwj:R�~H�Ճ.MX2����o�vo�F�v��O5m>R��hN�z�L�r��@툒ˋ���iў�-��_:������U����vhΒO?)�k|t�����/�^�]Aơo瞞~q��Ko��f��έ�]/z6�}��	��}^]ǜ�u�dv���!S;;��'�k��^�۾�c����]]��r���Գ���3=�K��Մ�F�;���F�ٔ�E�p&w��i��~OމX�~��M��h��މ�_�����+^j��7�������M��ra��d���[Y��k�zAj���ڼw��-����������G����������V;E�t>3�����3��8�Q�'�2x/xem�����/�:p���RS���~�Yٴ�c����9�U�/�y�6��b^�_t�N�q���y�-x����.%�
����)�Ԑw�u���Gi����Y�>F����C�>���@���ӳ�:��Ʋ9I�m�߻���9��n����O=�~sxf��G�;N�m�� �`Zd�_�[��6����	?�꺮��v�_���3`ub�g���Zz��7��ݨ�-h�լ�����'~c٥�>�e;�����;$���m/?�~S�Yf]��K\��������vw�>dF���o<ئ�4�U��?N��{��&S@��e/�Xӿ��o
�1�?b[H��-s�y>[���i敱�3Q��;�tWӱ��ꭙ�^�u���ƃ9	/v��{Ϝ��_�~k���f��̱�+�\�էo������%����$�x�Ӎ����x�w��'�;i��.�y�t��K��1o����X�������|�풚�c��N^����g��iۖ{u^A������m6[᧟���b�	��|Rf���w�\4g�»��"~�og���Ē�S������9]�^y�����<F?���6�{�[>�������o�����^��7��O{�r����� Uׯ_})�G�[��g;��՘9^��y�[���_��q��f�y��j���Ywn��0�p������y�u~��Ew���oò�o�{���~�~�Q������n���qc���-�3m+�ݤ%�;�M�{���=�R��]��
噯��w�}ۺ��[!�=��C^
�Q��=�{N�+��|���+��9W�8������+ԧ�{�������>�y���\��}��=���=�V(�x�r��`�ʳG�ݿz�=��.��圂nV���g+���B�{(�{s�<F����Vx�B��V�Sz*ح����IA��
���������=�P�K�
z}�P?�{)�/�z{U�N�UH��B��
�vT�/��풂?���.���B=oR�/������y[(S7|�B�MV��
��M���۷t�~�B=�P�?�*��x����`��꿣�=(��K
�<��Oc�rV�vϛ)ُB{mU��� �xi������f{X�P��
����{nP��U��~
��R��q
~�[aܟ�����h�[�Ўi
��
��Q觵
�=���Bⓙ
~c�B;^zB�N��&�y�B�}��	
�'Y�-Q��*���
��O�o��Я��?E��*��L�|��P~;��`o�켗B=G*������B���gz(��J�v<�P�d����Pa|��ͺ�M��E�v��0�+��n
v�]!����ո�+�{7yn~�I�Z�cE>y��{8�it��	�W���H��yn��#�M�7�=����,�_*���/�i��y�1��ȟ�/���b>ͥq�����"�i�ڷ��E�Ki_�=�������X��|K��3KL���;c>WE����a>}�|�"��7�O��^DSl�P1�L��[e��MIuc��"o-�a���|��W{`�?'�p �Q>X����=P�P�\�&����"�(��DnI�pƗt/�-�a��~�Կ���|�C���=�<�a��Wby^�K�.z�ōP�K�>��r���r�&��\@��ꅛA�I�'m����l��ExI��$��	�e�{c��30 �!�A�9C�b�n%/�������H���9U^O`=��&S�z�\�T�3����t��c�q�uׯ�a9�q�l$�/=֧��8?�L��U����7.��aWn�?��Uw����!��yf,OS�����힑��?�����a��g���B/��7��7W���ڃ�Oyq�=�=��r���d�b��+��<X���c����� l�Ry;v��Vp���9�3��6hω�ޒf�����@;4I�H������]�~�
�a4��:�wC����q!ǅ�R9�?W�+�χ�_Uq��!�[UK����%�<ڕ�O?L���>S�G��-3��0�;ꋛ����AؾkD�_�s�ޢ��H����.����p/�q|�d���,�D�|�/���r�?nzB7�_G�xU��c���GZa���~�l��l<j��K?.�^F���\rA%���Q���"o$��KK�sݖ��f#�D }�y�Uq�X���_F}C��.i\���r��l��n\��#���������_.c�QZ�!������fa�)����<�%��n��}�qN5�_��X�'�˱<�=d�A@�:\>^4��T5���7lǊ?��{��i'�aȟ��7�s���TXo1�uF�?�F7�4��*��_�z� �C�|�^�J���{J�����пU���/�7t�7ʥ�I)��+O?V�oW�|�_U��؋�:6��bߥ9�LoA����X?e;8{@��R�7v�8�Bw���1s����o�7z!/�q0���<j�'�,�q��ϥ�d<�;���o�G��T���������'l����q0B�?��X��$�g��	_{���|�/I��Ey;n�x/f�ȥ�I��?%�[,ڳ��ہ��2�a�J��{-��yY0�G8I�����Y�w����v�A�Q��~��v/�+��l�z�5��}תV��߬���+p����ߕp���3e��K�~]�)/g ���$A�^�փ4O�&�g"�Q��x^@>�Y�^>���O�h�7�;X�?�+�����y��ǑR��I��.��㇎��}�o1�x��kA5y#�Gŗ�幎�H��[���Pߝr^)��@y�{��=Y��5�["�o��=������xd��HZ�X��>]�<�-��\�����6W~|o�[��9�Ӫyrr
��n�ܮ��~����������A�O�^�a������E&�����^���^�I^���~���O�����~�W�F?�f�U��W7.�E�tV�n%{�B^�`i=�p:�0}���c��E{�*��װ�pQ��;X�\h���/Y�x���0O�"�!�0�����'�U1�g��?`��/��Hk0����~=��2���5��1�	l#G|�]J���'�̗���ØV"�~�T��f�x��Hc����7P�=�WY�<�.��S���K�����Q>?���L��bz�7Uqܑ�'я�E�&}�]��{b��b�5���S�?�~�T�qK�*1���,���^�y�l������_��?��WI���J㻴��Ezo3/B���H�>�^Q��Z)�C���i_i]ǣ
���������]��c�Y�V>��j%�p�����a5����Xc�y�Z�K�	Z���r?���P���؏�-b>o"?��[<X�K�b\4�����#���[��DK�]$�:�a�cz���?��
\��~�t��=��ݶA{�̔�?���K���'�� �?�������<^��xLZВ��#��%\ܲ���_�8m:c/��`���h�%��R>`����Ǘ �3�-��?	�y��<�++��ρ�WT�\�B�o��z��x��(�Q���>��W��3��	O �ຮ����T5�s�w���c<��\+���g0���>���*�ϊO�|��
�xO�ga9���y��~~M��^����V9����\|X��2�}D(�I\7�*�zC�b0}�h�ӗc|�]����z�uT�w�[0N���I�l��9�D��;��cv���명����OCq��3i]��,�����Jn������y%��R�WJ�q��\*��9�tɟt����������[�?��vn���\�~Ɓ���u���~�CI~�s��1�uo���[�{�`���,���v�'�O���c�W"���}�����y>����.���'�On��.����qп�d��u�R���t߅$��p�D�g�`�ܺA
�U1_n�+�x�ݸ�(|�㵅[����P^�}��z�|��x�u��0_��)�ӱ�v��.�PU�緱�����$�����~]Z,��a��?�3�#?��s�훀�R	Λ� �F��ϗ�[C�/�>��s#Η��J��烁ܾ�1����Vi�Q�W�����8>��*o��h�Uhϣ�݇I���ӷ����:̧�^�#��p?�Ê��|`;Z�u�mhWM�󻟰�1mE~JO�b�?�B�������p^P��#i��!Ňoc</��H���^�|m:����_'���Ѯ�����g��\�ϖ��@��K��w�����{�(}O^��^e�>ȳ8��P�I��E�W�~o�Ԑ?�|&�w���9�<��K�Kf�N�����
0}�N��,�#�	�}Uo�+�x^�߀�`��_�[�8��o-_?�,������4~u����W����$}ׁ��Ow��}�*�?��z�r�Dz�Q���VҼ�J�.�W�w['/�Fi^�?\<#�ڿ��[!Y�/�u����;��J��ؑ�`�)���������Q��3��t��}�+����R���a��ř���VM����8nZ�ʿ��v��'�ΧV�W��K�b��~�A>�yG����|�ʐ�����Ӥu	n|�!�S��q�Oh�1E~ ��w�~���qV���Y!�﨤��O)N�h'�/�3��C9�!���^��[���4[�>��(na"������������2�����H����x�����gF���2�߲R��{D�g�����D?��+���'�&��)���V9��߽���M"�B��������h�96�-DG�o�4&&����񣇧�����H1���߉�ˎ�NHN�MI������0��X��h��s3��qD��0gEg�f�����3�L����ٱfctzB��H�d�Y�i��	�	��)�sb3Ӓ��F�9!8�4+9�ym�L1�IR����)����Ғ���IIRcSR��I��,�1;�Y$Ɍ�YN��F��t�:���͢�2b�ӡ�b�R��1������2U��(��4'C��M��Dc�1;#�IG�m��L� ���'��w��P��
c3c3���Yi�s!}zZ�1:9-��k$٦Ϙi�3G���n�cg��$�d���q�IՊo1�%&��S@��Bh�I��|095lA|�$��Gǚ͙&d�F���r?��ͽ4c�Y�&e.(4�uL%��W!	U��3& E��b����7���yfdg�/�5���mr�th>�$��Ds�$%dY�H6�I�7����Hs�2rWpR�l5�rHN#vo2�^ˤI ÞAL��&׳Yi���q�b3ܿ;��>�����%��R�k;[���Ś�*t���	5�ݤ�f�HIvU 4c����d� b*hkc�I�q���f��ץ�����ZI�J&���ge(%re�!ș9<hN�����!P1��'�Jƙ�]�!�b3%r&
�T[�,�Ct��Hc��fNP҅�3ҳ��n}���.C�w�<djr����Õ�qE||
���<W�Y�+�avlfrl��qy�G��crb�c3y|
Q ���c��\��z\��O���aJO�������ǥ��mv���mM-"٘oRJ�j̄A��v��������@�UJ7gͤ���>�%�G���_ɊMa]H\��H܇B��X���L���q��Jui���+�g��'e%JW�xfzr�l�a��+����ěӁ<&}B2�����NOI�#3-��$�F&���D�%E&�a҃������+��%�){�M�a�����萛�'�,�` �3�7�q!6��0���=� +�ā|ΘR)ch��ǱwIm<�6:���ɩ$ܧ�;�?6u|rb����!&6f��6#ݔL��S����f�A\�����,�9)3=+1�?3��v�9{�ڈ��/N�����xn���<�R7O�A_l���������2��6d�(pÝ����in�9�H�<�m��j�ߥ%�܅wb�S]!�,��d�9����b���*��=���@�@)_�%�Ŧ�Fj�w�Gg��Qp|����;4	;3t�����rn�������W0G����i�U�2�X���H��W�{'ÐM�f&�f!47��)�鳜�@'� �L��An"������l�D;?A��,2m�xB:h�If��2�r��B
��ědD�0��PW/{qh�_z��.ߨx#F�L7�a\�co�}>3�T�j��ԃ)bXE|�4	b!C)�N:�ǚc��f!yJ8)�~����k��4�c�)I������sg�S�n��i�&��� ���<��I�n�].����~q΅�Lc*�0p�6�]݈�$iΝ辨�*�����z�(е3#9>Y������������,������xb$)0�O�����i�cFs�$gf����|���#�͘�Q8���l1n���e���W�lx,.2���b*�J�J�I���k�]ց(*39[*�_%��|J��@�I`@���))��lsտ!��b����0��.�w�������Eek�4ʊ%k������*�P��@,�21l�<-+g�=d%�K��1!s�4��D�,�|�$��8�⇹脬��v3RH�����*���kA8����l�)|�	Ց�,[�,	��ls}3��U$B�MHnO��� Kξ���Ҥ��7�����^���p�I�0N��>Y*S�us�� g����hV҉��*�T9	Ʌ�u�i�[��&2s�t��-�S�zO*�v�YK����m\W���(#���|"�
Y'�v׺�<cf��)DC��=�����)��}�q��&�Λ�����;�ȝ0��7D������(S�T���<��g�\3c�ȩ��8u���YRg�Y9:$��"+^�7�A�iOk����&�<��'_ofn�l���F���2Zl���H��;�%skhԴ�$an|�p�U���@�zml|��n�]���|��D�H�39b�!��!��U�A^p"�3�����5���֛s�^�|�c�n��%�`�|8 zd�����\���׻�@�`(�j���R/�+��n�Ua�Up7�lD�s]�\&w�aq)"�*k�h)��9&'c�2Bȭ��oHk]&Ȣ3��]�<H���M�"#l�Đ�,UZ~DA�:��ʄ�LV��s��Q�}kʢ��6@����ת��)�Ź��@&7���&nÒI���I�5����g:�6�z��%kGin�vǩG���p{Ä��t��T�!�{�	������A�'INp�2no��f�y��
��n��gR��R�V��-��O��H}*�i���]_|���ݴ�'#�SR�3�~��p���X2�$p%�0�p�A}{���{|���H�Y�1q�$.Θ"ێ�	�s���,���.Fck��X'Soٕ���S�[�d����\�d1Ό7����*r�f��8������(��6+-}N�8@��5��v��"�d|zZ���+��f��y�Y:��4w�w8Pl�M�l��ik��l�����M�ܠ�w[�- �;8�{�}ǫO��-�@�n�+;�7V�S��X��˭�4�;J�!%IqmC�����c�����,���f�8�w� ��^�4t���d�����}�H�	Q�w)Zf�{��~|�c��+��>>	�a.��)��*�:�įկs�;\3:�(�h�.J)��Dnʾ����8��	%~H�66v�'�`(����8��bӢ��O��sZ�N�'@������Ѥ0�����-r�Q2]�T�;�$��Q���⧩&�|a�+>R3�)�I 61s'��"3�DF'r0�JN�sv�u4>�� �H����J��H覐0L�AZ�tW�O�J7ɒp,	�\��x��5��t�E�뿋�}W�	0���)�W���'՘U&�*f�C>������g�3c��SE~W�N�v���0�KO�^Wgv���+�h��2*�q�eR�E'����A����Czy��gR�ͤ�[�Evy��H�1�ݕ�}��FP7wط�6E�M7�{n&X��=��$Z������E�gq��4�]�0�)�-^H/ �#�I%J��	�/r��2�S��e�HF�[�� ~���*��Kֻ�H���+�kt2��G�<::n���*�TY`wf�C�����gƳ25���4�_+�sHHN��e�š�&W7��c6M!�mʚ!n��ӟ&�-#�*pFVrJ��C>�7�3���[t�3�"��3'}M�%���\5���a|N3�Mk����\i���j��
f�j�H7�S��hy�Oav�^qm�����-����Ӯ�lβ�����py��k�w�oF8(}�a���^�7#�W�M�X�RbM
�9WC�F�XQo�@�ֺ�+�'����u\l�����&z\��K��w�>�}L�})�C��SH%WO��s��;q�;�@���,FDFݯO�>�o�GD�	r���ο�!�����s����������!���,k {����p�� �?^n�?���������i�&'������߿����Ё���[V�do�ò��U?���;Z��s�����d��&t�V-_Ӏ��"d͓��?�e�y���+d��-�����q�z�E?a�x�j��k8^r��*9E��x�O��k������s��G��<�c�r\@��Dʗ��/��"��ˏ|_~�1|���<�/?���ȳ�����͗�f�W?'���㥃E����w6��PȧR!;ǋ1�j�g`>5�B�Y�<������}y�)���O�B>������x�3��:�I
��P(O�By
�)V�g�B>�9�W���W�^_�~�S�P�J�����J���2�~��1��Y�`?k�g����q_��5��cP(O�By&)�'����0���ߒ�q���+�g�By6+�S���n�|��PȧR!�B>�
��(�Y���{:�K��qy7�|�	V�ǰֽF�uo��ֺ��$�|2��Vȧ����w��9^!��^�~ֺ/J׺/v�u?^���ǿ��q��W���1�Y'��f�sD�W����o"���N�1ߋ<�㧐gs�7���B^��G��q���o��R��A^��g��s<y%��#���L��7!����9_�\����s|�nߏ<��? ��y�Qw ��q�Blw�� ��x'���D^�q=�u����ӑ�r܈|7ǳ��s�U�_������9����\xS�D���q�~���ǯ!��*�;�"7p�=�I�<��C�gp|8�l�OF^��ȋ9������o��k�ws�y�7"���G�+9^����ȫ9~��_E�Ḱ۝���o�<���s|r�ÐGq|"��OC����������B��_�|�7!���O��r|/�2�F^���+9~y�� ���#�5����J�7G��xw��OZ�~��A�>����C9>y�'!���T�I�B����-_���� _���K8�y)Ǐ"���s��9��
�?D^�qu���B^���ȅ�r���パ�q|�n��<���C9>���K�O��r�1߄<��ȳ9~y�O!/��U�%��f��,�v�x+�e��O#��xr;ǧ!�����A�#�p�M�~� �?�� ��>���Dn��y�Q�A�q+���A���.�-����a��q|����������8�����!���J�U߄��� ���A�w��r��B���Ȼq\����qo��<��ݐO�� �IA����-�����)��q܄�����K9�:��y9�7!���Wȫ8���㧑�p�r����"�q�>r?���a�s��@�w������Q�'q|���D���L��y��@^�񏑗s|�
�?L����1Lo�x
����5L/���]��^ߍ����.���q��wo�<�㝐'q<y6ǟCn�����:��sף8���+8nA^��<�v�oG^���ȅ��|�n߉<�=��]�?���D>���v����+�3�}�яq����|7Ǉ /��G�9�"���x"ra#7"�p܂܏�y��9��@���<��;�8~��or�L_��s|�������c��wH��q;���
�G��������������r��5��ۋ��ޟ��N��2�1}��#��x!�$��<��_"�p<y1Ǐ#_���o��#���a;r�5�r�D^���ȫx}�Ws|
���A��@Η �q|#r�w ����1?�<���gs�r�/#/�x�uo�ۋ���K9�yǟA^�������(L_��wp���x4���xr͇�z2r�?F���b��8�	y0�?E���ȣ8~ �$������!/��}}�p��ԎoQ�����ȫ�6�yL����~�ܟ�!��'�g`��M
��gc�$��C�����1���!/�����q�(�r�W ��x����9���.��k8^���ܾ$��q����w�x0�@��E��)�7!����c8�
y��F^��8>�p�L��������!�e�y��@^��R\��jL_���_�H�=��q�r?��E����9�y0�G 7p|�(�OG��X�Io��l��1���q߳����~��}��ӗr���X�e߆��9�y%�"��x%�j��E^����j���ߘ^�q[6�;��0}7��������C9^��$�w��[��g�C0}��#_���K8�����s���x�r�/G^��M�5[9{@��xr��#���ߤ���%�����Eq�.������(��e�^[��w,o�����O��xoL_������㡘~�V��r�Ga�
��Wq<�}������az�c��Q:�����>v�Ս㥘>�c��Q�?��_��'q�������9^�<��*���7D^�������m1�f�D���a��8����8�Tr<��9nE^��۸u-�m���~���s��@�_@����F}�8�yǟF���q��wr�
����s�b�o���o��2�w`x9�_`x�_dx%ó^�p+��_��j�������p�R��_l����g8���nW3<����ǂ��^+�����fx�1|�3<��>Obx�g0�	�g3\�p�u/`xS�3ܗ��ތ�%o���o��-��X�exk�nކ�[��e���X�ex{�n�$k��g��Y�ex'���xgk�pû�����3�)��ލ��wg��=X�gxO��ދ���f��}X�gx_����?ÃX�gx?��ޟ��`��Y�g�Ӭ�3�����?��������3|k����������X�g�P����?����3|k�;\|8k�c����3�y��>���X�gxk���?�G����H��>����a��Q��3|,k���?�ǳ���	��3�%��>���Ob��Y�g���>������?ç������3<���ǰ���X��>���Ǳ���x��?sq#k�O`�ቬ�3<���'�����3|k�Oa�ᩬ�3<�����������
k��d��&��nf��Y��3|6k����?�����y��3|>k�_��?�����WY�g�"��na��9��3|1k��e��y��3|	k�;]<������pk�_��?�Y�g�k��3�������?×����b�������d��X�g�j�������e���X�g���3�-������o`���������.k����5��Ы��Y0䕙�����d��|��uy���
WD��QU�ty����f�
*� 2�b:ʨ���dj�(��b"�)�����L���b*g�L!*�$2)�#��3�L��*O!2�B:��<��d����H"�)�#��ÈL��*&2�":tT�Gd25tT�Ad2%tT���uT*�!rS�?�}��K��r#"7��Sك�ͩ�T�o�՟�7�ܒ�O�+DnE���"�Q���+�[S��|��m��T>J�T*�#r;�?���=՟�;��$՟�[�܁�����ٟ�O�7�ܑ�O�D�D���R"w��Sy1���T�G�.T*g�+՟�3��՟�3�܍�O�)D�N���8"���Sy$�{R��<�Ƚ��TL��T*�#r�?�{�/��!m"R��܆�AT*��՟ʍ�ܟ�Oe"��S��_ ��S�&����S�
����S�����T��ȃ��T>A��T*%��?���Y�?��9��O�D~��O�-DJ�@۟ȡT*�Id=՟�+�<��O�DN���b"�Q��<���T*g�y�?�gy՟�3�l��Sy
�#��TG�T*�$�(�?��9��O��DM��r?"�@��r"���ߧ�O�(�?��y,՟ʾDG��r#"�H�����S��|�2���T�I䗨�T�B�T*_ �$�?�%�d�?�Oy
՟�G�<��O�}D~��O�=D�F���"O��Sy�����h�9��O�7�K���
"Ϡ�Sy)���T^L�x�?���H��r&���T�I�D�?�g9��O�)DN��Sy�gR��<�ȳ��TF��?�9��O�~DN��S��ө�5����A��r"�B���/�3��TnDd՟�D6S��|��YT*�$�l�?��y՟���M���D�K���	"ϣ�S�(��S�������T�C�T*� �T*o!�"��]��D�P���&�s��T^A��T*/%���O��DΥ�Sy���T�$��?�g9��O�D.��Sy
�mT*�#�R�?�G���O�aD~��O��D.��S��_��S���Q����'r1՟�m����Oe_"���S��WR���A�UT*����T*_8�YH(;��o9;㶢�����ȋ�&��l�֚'f��pn�91��VW��� ^v�~�%��vȕ��>?�M��Z���ZO��ڰ�>Ԡ:d8^k���l������<��%d,�#d=e��$������P��=4��?�yu��U�<M��{�C��Ǝ�R,7�_��w�,�*��x�^?~��
gjy�
Å��b ���4���1�dC��Dz@~umXe�m��v=�Vn���4��������n�N��y���-,����3��h�`�B��2+��W�;��T�Y�/�����z�/v@-���pi���Br+�ʇp�`��2O��'�.��!���ű*�r��)�4� ��o�\��h�^I_�����o}�=膡��v��X��]��2��1��B=��3�i��pҮ�gPU�O(v�̋����I?A?>��*�vҐs���Bu�l�~ ��q�PI6u���:��� ������k�D��h�%�Hs�"�R���Ak��j :�a��nd������l��*�x(��}t}��:�vW� ʨ����G�鈢�*���Bd��9������l��K&��5�L!;ϓ�8h��i���?����<������?�o]]xޟ�Ea�W�:��O\�jh�}*�Oa�~�ϋ��tЬ�߸UW9�4kH�n�7��o�/VW�"C�R��b���������	l��B��C���I!!�HۡHR��Q
��J,�z�N�KRX�A�P�9�Wyk�� Q��#�{��ݶ/i������"�Z�u�L�F��!��d�a�.�cnj�YA�=.t������Y�͛��=�Nہ.��Ϋ3_�(j�LĠs�ߠ�;�%�}�pX �n�3�΃Ƨ�i���܆ƶԋFM����(/ L�Z�	W��J�f����vM�fo�}Σ ����ͧo�d��]�����cv�0�=`Q��&��͟C�D,�ޒ�� ʦ�6R��jsU*�g�i�^,ų�HU���ۡ��U��\����K!!��eaێڼ���@Ga��͛oʹ�ğ\�{��u��+�v��J�7���RC9�l)j���@[j]�Q���ֺ�����og:������ x�S0��撿�2�^F��hw�2X���>A���#T�i6/@6D������ ���W����zp�{m��5���;��}r�!�����?��p��r/m>�w�6ut�I�9�HP�Su�	m��>�����Zh��Z�9�k�*(�L�{[��.�`�j��(d4i��9�FC�ms�]*�r���}ZK�oK����P+�3Ae�i�}b���m��f8�[T��։�v����N����z�Ե�V�O�Λ$��j�Vzr�6�mO�yB�h.=�6&w��h�}NMT�]b�o���p=�ޛ(��E+�C�	�c���Oߒ��2�ڠ�xH�8 �^�*�X�l���ӝh�]���@Ơ0��������t�����R|2^�F����
h&d����kԐ�������v�'c�]�x�o ���dm"L;�j7Y~�,\ �d�a��eC\X@���r@ d⇮B��<��~�aPU�e"<�e���v����z�g�	ѽY�8��������6���d4�H��� E��j`(�5�[�
�P6P[�;��i� ��c�Ku������[ԳA��r�=g�;T�7�L��P��E��m���{^z����G^���g�}��Q	6��+�}a�>ua�*�>0�B�Az��E�/QK9�I|ق �ޢՀ/��
�U,���kW���^��]a}��V舋���+Z���!�y1�uU��Z��|:�A��=סs�r�N ��EKh&�L������
ݢ�v�>�}��@ � ��<u]oIT=�, ��E�[��^��y6��(w�'�`m��j6�����È�>��!w��<�y�
FC�Q5$�ִ�.�����K6j����Z���nD�k���XY���8*���hXe�S/��4׾~<�5;�MJ���p�J!8�	Ӱ��v�g}NmX�v���$�j˟�BH�4�	9MNOA}���U�� �$m^C�s<�MVT��ۇ����xA$T^^y-g����j�6����'��P�C��W�����[�I�%�����3ԁ-�l5V��22.)el5��w!u*B6����ʊ֒ժ�����	�K���``�a��'�AOo�������}uU-�
��A�'is��I���{Ec���b��:�Nn4i��^���жm���i@�Zdu���]�*�Y-$^�/���)�>�=�#��g �b�am~Cھ!��~�T��.��K��Z�@_�P,?X��ͺ0[@ ��J��$��j�z'�y$� �^�V��*1n�6T�>4邀vĘZ�Y�35��r��v�p���}`�~ڼ7T$�vsZ�`;��G�g����Z�H�?����.'�&uB}��wiG&�M&H���d�Fw�Bĕ�����]96<@�m}�]L&j���%BҢo�a.�?���a��2�r�:ڒ�Z1���\�#􎎗i�Xᠽ��%�;z�iO	�e?z��h5�����mH�.�B�zhZE/���C�
���ϻ�t�������ڼ�`!�/8��eA��߻�X�PL��%{p��ޠ�v�`���?UBxPٞi����)> �jqdc-������<ڑ�� �s�J��2��ʓ��Gb$�{އ�8S�����@)s�&��.�B�~�� �b��^���ыn��y��l˨�er1��h�N }N�]B�A��u!uZҟӀ��*�VZ���-=���h]f��p���>h����El|(1?����1*�7gV�4(�����X4���:�v�!�8:��ݬ0��`>�&:�!�ȋ��
.�]��Z�4G����'�#/�������*���\}���}��{Ek��A�� �6�k�l?p%��ŵp�0�4���=�![U$j���J�x f]��2NᶊoI�7���9�u���{\�:��v<qr���[ [VPA]�}�zBE�ԓ��ۚ,@�y5t�$�=�:�67��@=����ı{ks#�ł�(u�/���I�^tvCnh�yy�Mއ��pE�+h�X/<�ՔQ/Hhe��W]���P�^D(�2�G��U��鋆Ր4"���%ԑ%������!���#q=Q
rzY��D� 4*Lv��C~X��m�h_�O/�]H�F���>�}W�d8s���*WNm
�u�����ă��x�������W5R>Ekˎ��<��yȰ(__W��'��e����ܵ-H�C1�th�%��fh�ڎ�j�?�]؏v�\����y��(�׬!�f��Ux��l��FF*h3�/c,�Kh���T	�|x��g@�d��Iq����N=��c�i��?���!ьA�����������}냶�mh�� ~�A{�.5������Dm�G�k�>h���-�����8��6�vj]�����S��W�jL�����5�J�҈��MV�b,>9Ze�������u��֏�I8+)��;�_��bҸA|�8$�c��i�e5�m��0��!��}��%vL�҈o2;<!�=��7�Q�q�i��B�A��@�@�g��^s�cRH�;��k���6�K���k��So�vP��n1�X1����-��-�ZG��Ҽ�>������B���؎kR\@ǿ�^����/�����Ek�S�:@��̃��0Q	:�s���4����a�n���QC�z��r��*�H^��K�r1���Kf�#B-<�ˇ䑉�4� ��k�}׸�����v�j�y�i��Ox�,>Ϩ#��)�F?p��E�V��n��=&�����{N������#��	�����b⛢5#ϒ,�k�$�Ÿ�u�_��>���D����OW�j�L|�(�#qm�RQhHK�P��B�(|A{cD*��E�gE�)�[_:@���E��48�<�6�	T���B��^t�!rH�5wB�s��Z�:%C��u[�<o_�6���pY,�����v��0�7f����Wg��N{��pK����x/�G�ӯ�~����C�K�i(9Be;C|��!���LTQ��b�`m^*�*垒O s�d��m��h�vd����Ȣ�S.?��C?U9i!l]���k�_���i'��f�L�����[��Z�I.������[:���}���tҖt޴�����A.����K�M����Y����~9#���ɤ�t�������_�e��[�4�>�I��fKP'A��Cu��C:N�.�%z8p�~�����<�п��o�&:)��h���Q�4$p��Ŭ7�8|�z���Ar����O���97i|#������2M+�|r�Y9����S�H+�VY{��a�������MC�-��b,����bP�,��Ш,�k9
٢��� p�:��oC��k�A�L��2}�}z�MU�v�	��b:����/�4��z�q,S�_��A{���w��gz�+��5�}�`F�]U�٧�;���C��#�z��ɪ^��
�7�S^��O-<�E��Zk����u��b�Ӑ����b��8Vᆼ���������T�C�A����M~�@���͈o>N<�8�yܣ�E���=�RHף F�ȹBbr"j����r��o>���2�9N��.y�EL�dy-Q�8�Ω&�&^�~�G��f`�ij�� �	&����h���7��v����T�$� ��WL�I�k����B"I*�P��Ί�
)�)��)O�);��Q$徳���xA�Lֻ���8"�1Kν%�z�a71M�(�"YZ�vc�vq>�s\���S(��\7�n9D,��SP���\=�A?��}�v����j~���.pRG�!N��?�s��Gt�b9�`i�<��Amm�9x�1\ ]�r�[rD��$�]>.�-:�)$��ܬ=�KF�f\�"ėC@�3����ő�h�����׋N��h�{�C��~$���U��{���� ���A^�!�]��Sk��^%�g���P0Հ��<�}]�$5����Mg�PwC��w�<ܐw�<�,�����O��n��6���C�R;�
F
��`�5�lG�%�!����E-��ئ�6����7�a����#r��3�u�����t��zM}���J,����P��e	������;�E��G:k���+��d���?���`����R��<3L��\5�kW�%��4G�b�+�_z�E�C�>4��ݥ!��>UyĠ�s��W�*#%hv���7<�����{�-�l�������%חD���O�2�ԆU0�Ξe�`nDJ�yI,h�׮�k��^�W���k�Y�W������K������OW��&W$�';Yb$̛PG��G'h_{�v��Ǩ�$��\&}���bY|�,�l�L��c������:y,��s��f8��Ӏ�SpM� x(�>�T]��	7K1!\���Aw���*�������St�D�)y�\�Ms1�� ��r��?�%���^�o�#����Arj���b�&~�
� �+�����A���8^���7��#��'H{H�l�9�*��7�j��Aт���;�d���Dl��2l5���	��
Z�;ig��=�q'�\���k��� ���_m� ��ӏ!Q�� ���֒Ş0x1Y�E�H�l�ɎQ���?�ʹ�Cmۯ�?P��>�-R�b0�J"W��*�\�:�w<�g��Ddᙬ�h���T�Q�L_IV
"�*� 7�|�w8��W���7�w?EB��A07M��Ĩ�U�~ח]�V�B+�.��.e���^T�_���Ar�GXQ�*��\��?U�T�0�Ov�o�"!vҙGA�T�����{��o�%X/<�U�@L��^~Ta/0��m�U����2����{/����d	T�p�9{%��>��ZT8Hؠ��eå��QA����r�'��.��7C�p�����Ǩ�{ѻ��>��q�-��'�ޜPl(lX8���0JS8B7�|��WM��j�]e(���^n(j������H�.��"���{<���+���f�{k�+G�C�Ӈ�҇�P���-�"�|�4�1��>���2��h0����o}^�!@�d���+|��>訹[�0(��E�mx7�:��*��3\g(Vh����'BS�/��%~�_�����x4G?�Ӂ��E���KW}q����k&�2�[D�.P?g_3	��A)�Wϑ@[��ޥ��s����'p��ӹh���SĿ~��v����ӟ����i�	��0�'���q�|�d�m�J��'Y�	`�h<�V!~�*����ɚB��b�NA���#���i�NٯV�A�Ȁr|g��n�k?�G��0q����y��Mi�������o������>���{���aڃםj�ٝߧ�����5������Lf����.��S�'�pپ�%,?�� �k��?�ቍ��.P�3;���q��֓�y���"�Y��Q䛢���s����[�:��+�C7�a�4���^Ӊ��E�BU�;C�����N����Z�"�Q$�T�!�l����E�=!J���	��^3�l~����P�P�\K�����.Hr!F� ����i��>�|S���~��N�M�u��
�^O=_g�i��ǭ#v�ͽJ?Z��~R������S��-�0Fc��E����P	z0������y'^�Av�W��Xa(ҫ��,�:!������ެ۶	��N�ͫ������i"\�Fl�J@܄$ja�ن��j'���������i;��<u����G����O�x�YK�����C�b��%͝f���ϓ�R���h��X��E���R!��L�"�>����3����cH��ޫ?����N'�c?������k��$���C���%q�B=��P��6���4����>�r��|Α�7����'�����!���+ �B���g�rAm=E�o�No;p87@�9���'�����g�B�����ѯ1����E��FX�l�|�l3�=<����Al�&����A��7H?T�������f��.�ݺ��������P(��Q;��^�4$"�Ƙxf�S��l���чUP�v��_��!�F�O���lNO�����u����Ġ���:�yⲶ� e� �c�NZ��Z����&�M���p�M!`u�Z1H�VP�J�i:�
eӪ��"
n�P���Fy�u�놻�]�Q�P��E�*��"E�"��Yf�����?�G��y��n�=��̀���d��$}�*�:����a1��%U%�# i�X����](��I�F��иoY��G:��=!��{œ�[�fR�<�����<<�o|@��EaOG^x)"�9�������`vC}Rs�#��b��-HX��)���(p1a���?�ɚ{q��"��Ki;n��'5◣����5I��F�����g���հ�E�.ީV�D��|؏���P�m2/���xB7��y`��H*�QP�!*R���\e�*D�"ۯ멷 _��=�j|�0�Uf%S���g��N��ozB/P�ȵ8���DZp�*��\Uf��xؕ�w5��*�9㞔2}pO�I�"j閕��D80g�����u���O`����=^�7���D����ȡ��C�t��B0V>���
��5̅���F����|@tu���.���̍p[ ��!��
�8L���lLzv�*�e�Mr�`"�Y_cK�m�Ҵ ����+�`ҿ�E��V��f2F�&�ࡕ&`F�&�� �,�L�)b3�O�Hj��^�3�"Wb*��a�`]�u]��z�l�����`��JL��Nq��j�ؐ�93�8(?�,l(Op���O�"<���O�"<X����?L���2����\��l!����HU�	«�����:������|��+�����f%Pk��8�ٿ��\��{�i�2�D�(1��4MMb>�nZ\��iS��d�PY	����y�J� P�-/���Y��N(�"m����:��I��d8��#7 T��QïHXX�q�U۾
W�^yU���	S�z�
4G�I����-��6�W��]`r��_#X�F0�5qXM9L@y����!�}����%ڥ�?#P/)p�iK��xA?�@����@Z��@&�8�(ڣ(.���/q����e_�o��	?g�RQj5G���͍�B��u.w��L�W���q$�����6��2ڴC��F��L��ѹ;��Y�;�s�p�|@���/I�3��wͤ[�/�K�<xKf������E��vΖ�a�\�ɣ]�|�sF|�%G���c��2��υ���ʮH��= ,�%������T��C���A��!�����Ӧ�y�6\���ŏn{���2��?�"�}����d��Q>�����DZ��N3��e�&bp	^$8��+l��@��V����|�K��:~�̵�zw�Q_�v���G�)�ho	O�/�W�n*��z�0��'�N�:�g��i�;ğF�Qy���8�)W�hq6�I�G*��Q��H�(=㒫���.;������Gô�(�W|�ބ?h� �j���?��
��q�=A�I�|G�J��w�����ϩ\���J���B�>
�^P�!Pc�߮�^��j�U����%�r���'�qV���+yE��"�M��h�Lx�Z�����=�<YY�[O������8<�9��뀲\�v{�F���,�ـ�߬�JN�'��F+�H�jW�!>�Q�"�)��ل�[[��}1��%6�/�m�d�3�����͈���R]��� ��j�"��ğ��v�|����	������Z�]�/���Yx�����.�V[�ߡ��p��n˗kk���먗+�X���zߵ�����u�$>�~�N�?Ԋ1��T3��N2}�@�q��7�_M��J:��F�z�!�o�L�h9�Q�.I�W���o��0���������n�7E*�of�}����5��E�Ll1D_*�08F���� �ZZ$
��YI�	�4�+=�V��<�܎?�G1ʅ;���{�7t��!���CX)_��v�67�YԱ�wE�%�s����o�B�Ptm@�d��>!$�qra��7��a��	7��d}ʿ�)�nŋ����p_������%�bH�\98͖�lvI@���S2xah�1?I Um�:�L��ݖn�2kYYaC�ر����c��e�����Q���9X�·A*��,�[b�����Ÿt3���cy�7���7��Xo v�]�J�k����|!������S�gۖ?��;N-��W�6�Q��@��g�**����^)ی�5�{a�.L���y��ÔM,@�:xq!���j�W��#uhx/ (�P���u68V�\m'���KlR�(-�3Cx�`����~RL_[�=|Ϝr����j��~�c�S���hӹZ2J��K{�w�߱�<��l��h�Wn��X���F���bKVj%��sA�;X�>����O�L��P����U!����Ɠ��R�dwi|A�V/x���jS��4K�����|q\�J�+H�t�^��fMeO(��GYڌ�A��Վ0�g��|��7��+ٞ|-5猪L�s>��SѼ���DjZɗ��ϧ�7~�ox?�ċ��!Dgt-�F�Է��2k/CӇkL����L�z�h� ���(�	t���ྐྵ}*f�M>�34� �{��IJ(��9U��L��&_oű��G�t~�o�T��/?��n. �?�����WtZպ����fooA?D �����}�"VyC���K�y�"1��s8ֲ�ܡ/�:T7�N ��S*r��jF���>��C���8�s��M���*�����i���=������k�aA"K��-V�Ϗ����S7����N�WLՔ�{9M�� ������vXץ�=��=��r|��b(�s�0��+�Z�E��
�y���V<`�.�4�nW�"������R��w1���:�
E��lH@����xbV��6����/�}��?���9#���C$b�@���	��x z�E{������1�-���%j�8��L���>O֖,g�^r�He��1}v��>�ݎ�e/�&\f�w�jQ��o:�]�����&�C���7���U�b�w|d:� ��4�
@�7�2�b��X�$��b�'�-�$��*n�~�!ϦO��)�e�`(��Yq�Okס���4���ѻbxwiR`x���ȗ�x���?(���I�����r�n�ְ�Ǘl��1�,1�٠'�����]��#���i�qNF�0i[[��0R���eq?�먟[����~���`���u3q�|.o�X�h�Ĵv��s�Y��2)02-���n5+�~�уA��[��Z�����|�Gz�W���d����s��k��|�o\������q�[��(��K�ԟ��p;�S�]T�����m����������P�����J2۹U)؟�����7�f�7��h�_J\y\~����/�3���/'�4�|Qn����I��V�j�l�%���������g����o}��������b.�*����߫�:��� G��+�h� �R1�{�)�Yh/G��ۛ��<|Y:|��o��[�'Wv_�vJ�8�&.�����N�/5n|5��������^��//)L���[�����F���/W~k����Y19�!l�%���K��yğ�?�|�cU^�*Ibx���8Q�(
,�d�dQ�O~��+<Y�)E���]�d��K���S�v�wGߤ�	��/,�E�B�(H��iJZ��_��ܭCC�T� �e�V��|w�ӡ�f~F���Z�{��>�[׿������7}��>���d�b�3�Ϋ����I�ۧ���أ4���=�7�#ߣ�:]!0f�<�P�m�p��^��=Hr���Fb������>x�2��R�{û(��n�ڎ�ڳ��h6��婸����e��#���l��r�����v>H����� К����b��٥�cv�ȶ-&c����Q	J���K�-� �t_�Z�i�ɫ��b*�r#ҏ�Ɏ�d�z���
�#S�R�ud�cX����ׅ\�q-ա�ؗ-�GÏL��{�ڴ�j���.���\Z��/��|��Q�#���z�|�s���듰0Pp/���5�;[��K�~Y���X�����^���5����r���9�ܧ�D�^�8³�:��{�U��=z��6�6�C�z���8-����<�b$5���߄�[a�a�'+<%���_����Jw�#���+�>�r�O�8Ԣ8
-�:2�E��D=�c����:��o��w�z��&uD�cd��K���Q>:����W���8�'q�#oE��%�����m���?����.����=��c�ƈ�����[��(������Bʊ�c�a���$�4I�-Un�]��'ָB�+jw&e�qV�@����B�6yhJF����ʍ���͡�O���U��mZ��{m�%�;��
m��\�Ɛz�zu��v���������J����������	��-��b�5w���qv����[����c�	��'Ɩ��ڂkhj�E���ˢ�D`�8"���^� ����L�¯���m��f*aM�2�b?�E*Vm�(�[��;˯&9�;M���{�D/F�:�m�ƢS+�
�>V���.�=���?320&�{�RӌR^�+n��P�+���f�>�Kl�ʁ�H1�;��&���iy���i��C��ɊZ�%|�+�	S�p�~E{W�!��|�+�?a�}LJ��%��=�#��O��A����UB�]�m����d�����h�ǣ�1i/����?��-��]��آ� ��$g�(M��Ip'��CMf0�Q|Yq�4�������� �r��6ø�\Œ���s�W���}\}�kr���K���%���1,w1���7F���ɞ�Xλfq����e�֤�a}h6 ��(�j0v��{�,�����'��O��{�w�u ��0Z�j�A�4��Z��l}/>�{�ޢ���t?\	���
Ҁ�A%�K-�B�O1��$�>��= �Z���t���g��9�?�����m��������9>e�����^	��<9x'��Y�>���^�� �a��ٯ�A�ț����h��t,~5=I��6�1�O��_��U�N�G�2/����ӽ�J�@tQ�x����O�`'.\��
x9A c�{44�\9��7��3V&	�e�������$y?Y�Z�_�z�F���'&�|j�q�@�A����	r��u7�B�k�CxI+{~ ;���4�_��}jїĎ.!ӌ}�s��8C�{p�p�@K�c���U�Xj�����̬�|_$�,�Փ47˕�����t�ҏ�m��}~��-������[�S�kSa����i�����Ϩ}�&��`����J��COpyy*����REM�9��w�W͊��`�3��艱J��7��X���3���忠|�#����{�T���M�$���n�ĸ:���*���#�>d��_��,F�4Uj�1
��_�G�r�������Sl`�{O�����r��zyr�y��r�G>���{�����/,���Է��jҨ�b�.�c1y��1]���k$�� �s�-|���s�u�|.f��Ӻl}�����JK{��V�l�k�u�q⪢r�S����
�#�(O�~|�ޏ�к\��NW\�F�����ti�m���Qjċ
u�����t�v�=�c���ly	?t���.fն�E���Ė������{ާ~�}���K:���^��������.�jY����=�!s�5��ս!?3,5�[0��v�d��ٴ�;�1�Q�ӂ�����{��������Jn���z�\�hl���hl�H���e�+Q��~�j�	�	��L�(������_.❱���~���(2���
&)& �h3�o��d���4��@5���'c��@�3/S��<��J�z�Zh�����������!�y��x>��wY^��3��z��������X�gԿ�L���yS���\��Q�+g�/����>��yc�����������cF�[�T?-~�\�{<~���g�/��������w-n������~��Hl�wzD��3_��Grד_���iϟ��τ���O�J���O��/���=�}�h8��|�&}��b4���uPr�&� �y�Cs�N,E����~{����#��2B�҂��u<����E�#~3ۃ|Oݢ�{�����<@�y��˨�P�����`b��^|N2���L��\��K�����Q΋��3�w�k���6˧�a�'��uho����nOܠ��̇c�}�ñ����y!��7!?���z����{��ӭw�+�ޫ���/���/��o�Ǽ�ַ�?���Y�K��z��k<�|�~%��d�o��,�x�/������;�߂3���w�M>�o����.k�����Ϻ���z�=s�FF<9���~>�X�ϡns�g��\�����m~���E 9z�B�0���ǡ\�1�za�3L{��r���?�>�ţ��?�vc{�gS�6�ۊ{
8G5�uh5��5�9�۪ G!ܩ�'Կ�vO�����p[��:��O��4�_[>�f�����M��3��#�U���T~hq�]٩�T����m����l\��������M��L��s��ii�
),�c���aJ�%�����B�,
��B<�e�i�䩃/���6�Q�&�'��J�(L�<��=�	������'wU�=.N������`_\�/&<��FC[���Cv��N3�C�/f�%Ș��Y����������O�Ó�]����Z�f�KOc�ms](�%"t��y/�1h�ϱ�Մ8�-3��ۋ�]S$��KR���1~�%�J��l(4�-��d��hUR!7p@���
�:5==�_ˡi-,ȃJ$�Udw����C�*/���ҳF�����^q�H�w
�٘�k)���{1�.�'�hI9Ձh�h�^���(d9=>�1�W�X0��K�CD��Xd�hv&ΰ���:.9qLzQ�,�&1�L��v�:��˒�[��4uɕhf��2;��fyDc�,�����ݒ�(J���WN`F=���g��(�
���Z�F��aG�T�VGX\��44�v��Q�Gn�]R�KZ�7������X�+s�[�)P ����c�<�Q:&չ���ٱA���<C	;��Ĭ"�%��2�v{F�t<b�z�G�U�A{���>�h�4�rEiA�`Z�Q�)8?��L�	�[�ar+ƽ[$V!;���N��%�Vn% ����F`e��)r�UCI��q��і.e2z<i�<�$�
U/~��bh�0�bD7����Zx[z�jW���6�?9��G(\wj�E{a�ة��;1�\��v6����Չ^yyr�����fXh�Ys{�>u��2:�����ҷ��3������'�!Ցd����4l��d��T��7%�7�g˕	�=�H�$�0_��8':�9� ��}*���.W��V���&�ץ:�Hr��DڧE{��Oo��uv:�ȏ�FϷ����4�|��/Z(,�F{�'���8�J�<�(�Uf����8*?2�<�u:�v�OLI�8����WB}�Q���#,�H�m֬�����}�WZmo�	�<���8�l2��:ŪH�޴=��1Iw���2��ֹ�7����i���9FW�����գ�ֈ�
#�~I^�~Q��y��>O���3���poxx�N��qV�����W-�L��娝�8�YŘ�i��{���S��[O�(�0�?�ѷ4G�q����s���(ʉa7�����P�� �q�7^1P�r�2��wo��O�*>w��"zE
�����-#!'he���t���.Ϋv�zU8Y���BWz��Q.b��_p�L��,ڷ��������+(�@�0Cөs$�.4��]��S��e;ճ\���܀��u��t�������
C)xᖽ���^տ`�/�WI���G�u, /��o�zQ32���WlR2��=?"t�sfoȇK�{MU���)�7��P�
�P��~��I�͇ت�1X�#XE���E ߜ�.��# ���v��'����e�:c:�ȁgi��=g&����U3q���/p�q��p�I���86L�84η�"jg�&����̽��F��蔯���4�Wll����7��=N��Zߵ�����4�/�䙈����}�$W��+pȺ@5�����V2�8�)��r�Z,�����k��A���O��~���ێ�xʎ˕�����#D�X��;�J���D��pLt��`bx֕���@��E�(��`�E��׀m�oӤ=�֗�]���ԝ��E\aX����������Ľ����.�bvz�	�dwm��V��v��S��JC�^���xy^|��#�ZG����p?Q@Җ���	{��u�w(+=7��B����L�P��| ���C���0Φ8��|f�W��cd��1�y|9"UA=�O ]@��Ϥ��Z�Y�{�t�;R�X`R��zX�sC�q����I����*�HoL�?Z��Om��i��3ܩ�y�'�OB�Y-�W�z}��S����0Ԛh�+��mHd߅�����f*������z =`ɀ�#A�E�yT�<ޯ����8{��؃�|�,�\X�9d�F�������?)�o��jǖb+Ư����z�l �! ~�qf���������ץ�35�Q��`��<�l)�'�֟?|�0���<�.�O����R�QΧ�7Bc���<˴���ʍ~����N߫�=��4��6dq�Xg=��أ�Va`��P���[����ޠP&������CJ�eI��>3�-_�5'c��,V�f{�VB37��FB��o�<�r�g���Yйz�S�Ă�B�H���S	��$Gۯ��a�7�{�F���v/"��Gx�e?̋���>�7��*����P�S�?�)r��j�=Jm>N]��z���?�H��J,�C�#�������ϓ��S/B�@E��=`��vDS^g�A�}�}��g�6��������x4+XhvX;Q��Q)��\]��D��2���-N^[�����_6��%����%�w��z�Aԃ�b��X�&�Or�)V���+4>ILI�3Y`�J����=Vn�>lC�	�)Q� ���
G�)�i��`�K��?���5���)�B	L�Ҭ6�o�~��آ�X��,���xi�"����%T�J��=�o�����z|��7�*��UD�K���k>�-穝�9m�ԼT|6�l(-�v��v� 8�v�n�rWs��Xn�8�?��\v��1��)��ɨ���κ7��%���;Ƿ��w~|��Հ�q(t�%��B�Lѥ`|�Z��Y�Kb�u����t�?u���΍5\w���u
~:]{�����Fۛ�?�7�$~�p+��V���[Q��q+����ws��c�1P7��"�[1�<k ;ŗD��Ѹ�����?4&��#�~�j��������/V������7�D�'��������u���o���:P�����Y����-�ݏ��Y�Rsό��3��s���㖮���x������VFE[y���<���n��t��</q+G�����xJ��V��rOGW�?G�A����v��Ε���P���~�IP�-#��o�/�[ɏ	����ʕ�Е{�h[�����U�,�b�����уq�c����ӳ�bJ_�%�̥��J�a%Q`b�U���ؿ�e��s�b���|"�����q�QX��ӖG�=[��{���:<���t���@A^ixwT�:>˾6������|�����èx�U���xj�g{W��v6��sϽ�������X��S��Z̾�Bk�b�Ң�"�7�Y�V�9������c?�ҏ��qW�ǺJn:�~���7x�>�������X�"��������c�y�>���ۼQ�ᶣm��0�� �7��{�T_Q�����55���e�a�47������P��t?������_v*�o��&mj;�,���>�giO�g�2��}y�A��l%��g�B��0]d_U��ɐt��g���r����Ȣ N��,���;�_��}����)�r�}�h�������9�ߟg����^|s^}?�Y�?������ɫ[��)[�@�پ�;�������C��?����;��~Y�{+������B7�w'˕�bP ���)�����˕�I.��-�9�~zz؝`�Q�P~�{���L�hO^��#�`�M��A59�[����d�c�7�Px�o�`j֪�dM����s�N.�q;���OpL���/���Omx.\��G�"+2��}�$	�d
����6���y��C;K�O\+��Yq����J��	�ޮ��,ӳ��0�ų�z$K����܂��ay�\=�1���d�:)���5� ;�jՇp��u�ɫ����,(YszT4�t�9#�+�Eή�0�7[f܃��5�F�614^�P��tj��*��{��)|�㒵�)�1�{D�ŗ��e�8�h	_׎c��"1�B�n�ǻ˂]u3�T:;3��/��8��ʧ9~����*�53`C>5���T%�ڃ/��/
'8b�"~���ݘձ�|g=���ۨ7İ`�ڱ"�Sp��'cܶ�/�J��S$�x��+z��	�-�����q�fT���~����)�Ў"`i��ĵ�Ǣ��\�$�J�d=b��,�Y������D��o��x�j^��nzgi�Sίs���"�C{�O�*�W|�&���z	�X�L�K�'(�U��)��W��9Y�����Ka����0�f��ݐ��|�̿���($�]x�_�Q�����Zy\Ck��������(\��`�l���iP/�:�N��۹/s��c�<�X�G�U��B�耲����K��"O��WF����Wt�����@�����/&}�J�T��cQǧ4��s&�[����dWQ����CR���EA�o '���,����Z�-�C{�������˻ۿސ&�]Z����,@D�:_��-q��qr7�.��_�34y��؉��LbuP����Pd9���塣���(I�,%�.g�x�<�>�����I�N���y�a��[0^�)) ��?���FM�<��F�9 �1j��Y�R�x&j�6���n+�B5b����~��7��i m�b��F��:ǀ���D�n��q�
�����l���k��6���N��O��Q��/j�sӬx!���d�R��L�vj���ty�r��ܽ5�3������8���:��eҊ����������>���:
��C����:&�X�{b� �t�].W�%��l�7t�N��#����8�7���v��x�-p_�E��*������/Qŷ�S�
����Gv65� �#�Rg�n��Qb����p��/9x~�[��9܏oP��(_�7F`e�q;4�}�q�&^�M�_kt��QV'8��<���Q��UV-���`�g��#�{�֪�9���~����Y��P�8.	�#x*��;V|k�f �Lʷ��`���[}�j{V��N�w �Я7�ݬ�Y�����"j�ݢ��k��	rpy��	�@����$1��'�]�f �L*:�wcF������ѵ��NL�df_j)|}3���+GbV����2��E�f��g��<��
j�P�?��j��b�Cґ.��k՜6|f�B����YE�Ӫ-ñ}R�Gڔ�e[��xhE��g!:?�/b�߻1���������w	�o�~Zz�hi�r�s���vc����Y��������N|ɕϓ2u�廉 3"��M���V$�<b�M'Eė�x	H5���=���n� �����h�/����^�`�G{�GO�j4�0�3���C^$�n��Ƿ�?�z���!���
x�z��V�{�E�����ū��E��}06L���7�ܦ��*Eh��)?F?wtƙ�=�O3iQ>/i�n��A�?��lƫu���d�dʵc���)���{sm&<��nb��f�͌麐���$ыxUM���f��d
܉����s�u��\��O�=�1N�M��(׆�T%&[��;�2�?!/��λЋ��׹�VѬ�4�8�
���:yQ��aBr�� ��h�������˰�|N�|^F���j��Y*LK���c�~����'���_)_���U-E�)
��������>��z���yK��˷�ŕ�Y�����G��D��?��c)'s%�8˓(�9q��J�{�U�g���7��DH������,Ǟ)�[Ksk=���^���$�!��;:�mt(.5kt|�1{ ��tg��޻��zr��Zɾ�Ӓ?UG�,�(*��gG�\F�<3n��>c��K�g4�,������L�0��.�m+Ϩ�ΐ/����I�Փ̧;����Ң�+���$Ql�Ƈ���B�0���FeM:�TB}�脅c��XQ����d����W͐�;:�\n	f���-�|Uru��K���s���ŃAĜ�d:�{��"-ݿ9J��W��J4�k��ɳ�}]L����ty֚)Qy֧*`��w��#wnay֭�H�5�:�g��J�ۮ�y�|�"y�H��d|��F^2�̆V����7��/�r���u�m�]��۴�oډ{�Q�<�<'9��u�נ�>Z)^�8��?��UB�H�8p�Z^�9�k)���1����.�|�J��P���㨭��7���5sԸ�(c6Xf��'x.�ؚ��+����L@B���dr.�b�}(���ͤlد���BiC�򒳊���r7��p�Ւ"6�+����U�"������5RE��w�Yq���i��A��r���-Fd܃ΐ�Z<��r-�@�\�f�%JH���<��O���e����
=�`�aq��y4Xsw�q�#��\��N4SRN�d��\������#y��zb��1�_���5��x���*	��v�EZ?I$�cb�� �ͱg3�x���]E���>Ԣ@�Z�=�`��o(����8�w\�4^��z�Ȃ�q�_2Qz������BC�7q��T %�0LЧ�S3�mڳiצ��Y�7�������1qd��N�b�{\4l�/��t4pL��[|�I��$Q��#,B�
���G�	��W�kw�NN����M{�����!��<9�8?�/�}���D9�a�"�F��;ئ>��8�b=�$r��,�QD����c��<ϫN�V�Bū��zB��<�Z(Lr-,,���,�s��#{bz������"]�=����@���>�?_�σ�鑗��Z�xkQ�L�x�����
�؛�?[�d�!�'�E���	�PP�<vA���G���@3pQ����(��ȳ7i��@��]������O�	=iK�o�3:���N���t�&-�a`}2�]%=����C��aʊ���Y�bēI�Kws?��M�����$D�Y�\)P|YQ%�';Yk���&��zJ0�7�a{�1�Ȃ��͘%!��q@}��RZC�u�/8���uܝ�-{�P����n\�s��I{COQA�, ��0�����^;	3�v�\�+����,�7+�/�����r�`)�u�Go��g袈o\jgg����Ed�{Վ�@�)`�D�G�Sķ�|+�[���:��M<��Z�+�ݾE�ZQ�	\����h�wrΏp|u�U���u��)�8��5r�^�3���h࿣�[�"���zvg��Cs)��7�N�5ɂ>�M�� ��m��|k��쾙B���;3\��g#O�g�RЊ�&2�$�8p�|��PC_�Է��e��u|c=vx��2��;��®��-��\w�z�Θ|��Wj=�M8�j?�u�_��f�c;Q��o���6��k�L.��É)V=\��ik��G���(�	���>��l��^|As��	>ct�p)!G���$]Pԍ�0��-Zo=�U���!X+kcj��O`W��*�H��*gD����4i^�]̩��&\R���M���Hx(�WO��mڑI--���}�VCN8[���"Z�.�����{���s���>AC�7t�1��˕'I^�5����'/�]�W�|颏�~�#���Z�U���#���5����]�6��2r/��%��b�G}��ϰ1��J�w�{�;�Mq~i��;��WgM��#0��|�֟j_y��2Z�z��� ��I�-����?KQ��q?*������TU��s�p���Mf���F|����g�V%0�
�#�񸔶����w��,���M���|+}op�X�Ge�?��`�4����#���I���إ-a�T���Z~�z��f�\9N;2�7�.��+h����fT=��)�WS}9�y��rp3��VX�c��שr�C$8\a,�E���a�5<�/H��@��勃<꣸�<�3�m��/`��lV�T��Wf�lz�6��@|˕f�+>�uh#)�� �W�Ӂ_,�4���1V-���EA���qL�ɕ�$Rjn$�C@��[!���4�*E�jr:ɐ(�qٟa��T�:5��Q���~�3H?"%�dF�"7,r��Bš`� 
���{���XL����Q�� ƨ࠿���^����Q�8�g�� u��8�0�+&c�����3u��3�\]�I�P~Sq<Q�t��o��ː�H���z�� ����g��{;�G���dyo�bɒ��Д>TEjXw����tI�v^&'<p"�� �wc��D���wy�9A��i1��ΰ�]o�4���bU����f��/?Y�i�v�-��b����H��sM&�"�V+�'�
=~eԳ�_L�R�Q�T��ݰ4���>[�F[��>E|1���H���P��3ś��pi6�Aئ��
��/\�~S�|���ϴZPyJ��͉k����׽�d�Gl�ۭ�wOީJ`��$&���!�n��Hd����$��������}Z�:&�����	�S��O+y0z�� ��
�N |.����ڭ��� b���W]4������h"9����>8�XQ���Ҫ������|�u��q���9���꒣f<�+�m�P��V3���c1��]Q��d"~��d�;���ro/��݆�]�����ۈQ_n�CӢ�<��ͣ�+�����Γ���#{����d�̼��d*�#G�{JAC��(*�s7�-�e��1x|�:N[Q��)mP���G�!#=�w^~t�(IC���E�0�����<c�|_��X��aQl��h\D5h'n!�����8!#��M�ބ�?b��2t�����	�lt'߈z����U��w�Uڜ�d��m���
����	�E�[�W��/���3P���
�U�Ҡ^�� Vb���l�Zp+��;���X��#��Ꟁ�k�H�?a	����M��+�D@���]:��uD���r��CiK�&�[Z�ǜ(3�	U-�ꙴ�BU���)@��� xo�S���1~��毈K+�&�t���7F+��k]	-��i�c�gt�ƿ�������o�6�܁�܏��1u�p�6 ���\̺������cK�įL^ �?�>�-I�)�U���p�A�z���;E�m�Ɋ�)�϶z��.̿���'c��(ۛ�>�WK�BA��H�a�W�)�_��4@��Exz�䆂{�*�ɰ����������_��f� �"�@��H� o\9S�S���?V����[ � �wsR�1�����JHţˡ�IC
���0M�W���9�4�#��t'"�) p���%3�z�G��Q�]i=P�Լc}���+3�R߭�c�u{�������'Vؚ����lF4��&
n.���3ϕ)):m��O�v�� �(N����i n�Kw�w�����C6�u4b�9|=�T�6�S3F��Ft�MIQ*�0��]�<��a�`0M����$5�yG�W�׮Ő]"P��� �Lg�h���vBa�V�2�`f�+����P��U�jjf^d���v��ڔ�B�\�x|4x�4<�!E!ZH�^0�7]qpm�Jb�U�W�V�\N�%�!
`C��"�꣙r���1�Bű�� ��m�!���p�Ƕz�S���I-
��}gO�˓��b}y�@2v���ys��}@�1%P�ԗkS~Ƕ
m�ߔw�� l.l�Fl��k�W�g'!��������)6�RGf)��Nӝ�3�� �w�E�->��m�!�n��;�Nid69C�\����N`�pP�N���Gi��vL����'�t��=��~"�$_��<\���c�#_iLʝ�e)�҄��J{��<�����V�&� vx;��6!�H�$�%c��)(P�a*w��)E0�IJNB4N��	��^5���ԗ�t�/#0�����d���I����.P'��DI*�É��
�ƛh����8j�]���7e�&A�F�������UD�3��Y��e��ȗ,o�ʛ�0����yْ��"X��Kؓ,.?�/�l5_��yu|��矋Zܝ`k�YE8m�%q������K�l��~m,7���#���U�8N�E�8���4A��ƐV϶L ߯b����,M������{y��`����\6.:����Qr`�}��9u�)�Y?�X)
�.C�eh�+/���hh$|�蘼�w���\�albݤ�r�u���?E6C��J���Q����w�"��� �`����!i�}t���4��v۟��-Վ�V.�	�{�Mu&������z}��(��6�������u�b�Q��8�D~L�7��y^�_NQp7����:�2��;=`� ���"&z���#̱+�?��ُleC�il���0�RgS|���������6�m
�bv���]ϱ�k����t��8�3|V��G��,L%j�͗
�f���Mb<���5��S�eEKit�X��������^[ޭO1����=��w�����(ϊ7���Y��� 8�7�3��[�}'�s��6�[������r�.<�F��~���q�1<�f���Eyv�y�Ѐ��I��~��_��#��V��A��K�[��?�g��K��[��q��]f�՟���ؖ��Q����?���b���V������B��,j3�C��Y���~��B#�g�𜁞���@w���O���==Q�B4S�e"�n�����������y)~�FX����Gw�����ܢ�)ֈ����|T#G�xL7�e�h��]tB3�F�zĠ�XM�7JE��.�S�c;��C���a�!��ᷱ�������L����;��y�=<�Æ��g3,�_�T;3G�Μ���D��e(�Ձ�:̿�nx�x�H=�*�At��gi�ឿ�:*��>�c��xpx;���2��������r����\�,7p�����7���O���U[p�8������C���m$-��;����͙]�]�0Z��V�~���4�����Za#�E.D�ۣ�-��]�tL۝jb4����"�uEB��$��ї���!&�sm��5?c�� Jr%��O�U�l��J�iG�P��-� G�ڤ7��*R�w�0��y�'���#�.�´��k��sQh�U����Pr�M�vh�3$Rk\�	�H�Y$w2��޹���y��'�"��øg?�� E��jF�B���V�lĕdR�z,x�n��"��4�߹`!f�@ɯ�\ �[��S���huc��:ЏΝ���	�F�N֮�'p��aIՆ��"c�v�C)�~��|���gv�p���P�f��i��o�r��,�f�m�7|��E����5����E�<9x�dL��Q�f`�VO��b�s���j}�x��u�:%Mw>��U�KԒT�>P#�C�Hj��_�F����

a�oX�&+�,�6��>���Df�,��u<���&�A��9f�!x�j1Ӭ�3��c�1��l��p��h	�m��9��ꓺ�M�n
3�3�LI��������"��uZ�vWuZ��5�_�@������π����g�_X��ll�TB�S�P��h�gq�ƤK��Jə3�<���{�/f�����$��@&�#k�J��@LDHtm#�W!�����CO� �;t��U��X����+y�3����Pߦ�8����}��}[��md�Qy��34.~
�z�Zh����3j�M�X%S��`R��X>��]�vS[�*~����#�Q�_����|-�?u�����5���w���㖜��9�0t��O���,�v?ؓ��v�����f)�<p������6���n����U��y����m�{༪�C?��H��[H�X~=nat3V.q���ړ��Nr9ϹA)ۧ��jV�^O�Xz� .��Ҏ�/ ���P�E�߮un��G�-��p;�;we�6\���˘�P/�G�c����2�OY9�W���~�R֤����fF)���loRBC�]����iӠ��(#� �	<��壜� ����G\�p=������wWέ��4ǧ�u�Z<�wY���a�Z=wj촮���6(�$�?�z�"���r�W]���ԋb8��p��,g��hn/?�\�%!&�<O��@jVǛ��{�<B�}M ���E�Hƅ�-n�>�����1�4O"�U�Uh�R�kg�ĮD��ORR_��wqa�9C�NɁm���E�X턝�9��u��5�2�'�%����$nj���́��{�境�jО{����:��޺Nk�s�@��Z���y��E�?����<�B��5��)���?�;}c_�is��6;�A�8 �8*$�[��=5�;u�Δ�0O������v|��ݲw�3�K2Ɓ�O��Vg`W�����[lr��1�r4���P��i����)�cy�7�0/�0���B��P����Z�D�PX�J��/P'�%J���ڔL}<5�LN�+����G4Ls���~��z�j^K�k���ag���OE�!�i��3��s��s���p�����0؃
���q/�M�.'�Q��혝n��A^T����m0��m�X�,r�0�>G ��*�m�|R�^e��]l�\;���v�g(�Zy���W"��.�����;4弼.�7�����M�и<��n�Ȋ�C#�6�_r1|����I-2�u��ZQl�� �����eY����a��k�&% Ѿ�*i�8~rFw%4N�BWh9��I�F�_���)��%ҭ��X�W=�X� �u^�ի���8���m����7����f����a�f�Mˆ�zVG�Y~�6��;

// Skips to the first non-space char after the first comma in 'str';
// returns NULL if no comma is found in 'str'.
inline const char* SkipComma(const char* str) {
  const char* comma = strchr(str, ',');
  if (comma == NULL) {
    return NULL;
  }
  while (isspace(*(++comma))) {}
  return comma;
}

// Returns the prefix of 'str' before the first comma in it; returns
// the entire string if it contains no comma.
inline String GetPrefixUntilComma(const char* str) {
  const char* comma = strchr(str, ',');
  return comma == NULL ? String(str) : String(str, comma - str);
}

// TypeParameterizedTest<Fixture, TestSel, Types>::Register()
// registers a list of type-parameterized tests with Google Test.  The
// return value is insignificant - we just need to return something
// such that we can call this function in a namespace scope.
//
// Implementation note: The GTEST_TEMPLATE_ macro declares a template
// template parameter.  It's defined in gtest-type-util.h.
template <GTEST_TEMPLATE_ Fixture, class TestSel, typename Types>
class TypeParameterizedTest {
 public:
  // 'index' is the index of the test in the type list 'Types'
  // specified in INSTANTIATE_TYPED_TEST_CASE_P(Prefix, TestCase,
  // Types).  Valid values for 'index' are [0, N - 1] where N is the
  // length of Types.
  static bool Register(const char* prefix, const char* case_name,
                       const char* test_names, int index) {
    typedef typename Types::Head Type;
    typedef Fixture<Type> FixtureClass;
    typedef typename GTEST_BIND_(TestSel, Type) TestClass;

    // First, registers the first type-parameterized test in the type
    // list.
    MakeAndRegisterTestInfo(
        String::Format("%s%s%s/%d", prefix, prefix[0] == '\0' ? "" : "/",
                       case_name, index).c_str(),
        GetPrefixUntilComma(test_names).c_str(),
        String::Format("TypeParam = %s", GetTypeName<Type>().c_str()).c_str(),
        "",
        GetTypeId<FixtureClass>(),
        TestClass::SetUpTestCase,
        TestClass::TearDownTestCase,
        new TestFactoryImpl<TestClass>);

    // Next, recurses (at compile time) with the tail of the type list.
    return TypeParameterizedTest<Fixture, TestSel, typename Types::Tail>
        ::Register(prefix, case_name, test_names, index + 1);
  }
};

// The base case for the compile time recursion.
template <GTEST_TEMPLATE_ Fixture, class TestSel>
class TypeParameterizedTest<Fixture, TestSel, Types0> {
 public:
  static bool Register(const char* /*prefix*/, const char* /*case_name*/,
                       const char* /*test_names*/, int /*index*/) {
    return true;
  }
};

// TypeParameterizedTestCase<Fixture, Tests, Types>::Register()
// registers *all combinations* of 'Tests' and 'Types' with Google
// Test.  The return value is insignificant - we just need to return
// something such that we can call this function in a namespace scope.
template <GTEST_TEMPLATE_ Fixture, typename Tests, typename Types>
class TypeParameterizedTestCase {
 public:
  static bool Register(const char* prefix, const char* case_name,
                       const char* test_names) {
    typedef typename Tests::Head Head;

    // First, register the first test in 'Test' for each type in 'Types'.
    TypeParameterizedTest<Fixture, Head, Types>::Register(
        prefix, case_name, test_names, 0);

    // Next, recurses (at compile time) with the tail of the test list.
    return TypeParameterizedTestCase<Fixture, typename Tests::Tail, Types>
        ::Register(prefix, case_name, SkipComma(test_names));
  }
};

// The base case for the compile time recursion.
template <GTEST_TEMPLATE_ Fixture, typename Types>
class TypeParameterizedTestCase<Fixture, Templates0, Types> {
 public:
  static bool Register(const char* /*prefix*/, const char* /*case_name*/,
                       const char* /*test_names*/) {
    return true;
  }
};

#endif  // GTEST_HAS_TYPED_TEST || GTEST_HAS_TYPED_TEST_P

// Returns the current OS stack trace as a String.
//
// The maximum number of stack frames to be included is specified by
// the gtest_stack_trace_depth flag.  The skip_count parameter
// specifies the number of top frames to be skipped, which doesn't
// count against the number of frames to be included.
//
// For example, if Foo() calls Bar(), which in turn calls
// GetCurrentOsStackTraceExceptTop(..., 1), Foo() will be included in
// the trace but Bar() and GetCurrentOsStackTraceExceptTop() won't.
GTEST_API_ String GetCurrentOsStackTraceExceptTop(UnitTest* unit_test,
                                                  int skip_count);

// Helpers for suppressing warnings on unreachable code or constant
// condition.

// Always returns true.
GTEST_API_ bool AlwaysTrue();

// Always returns false.
inline bool AlwaysFalse() { return !AlwaysTrue(); }

// A simple Linear Congruential Generator for generating random
// numbers with a uniform distribution.  Unlike rand() and srand(), it
// doesn't use global state (and therefore can't interfere with user
// code).  Unlike rand_r(), it's portable.  An LCG isn't very random,
// but it's good enough for our purposes.
class GTEST_API_ Random {
 public:
  static const UInt32 kMaxRange = 1u << 31;

  explicit Random(UInt32 seed) : state_(seed) {}

  void Reseed(UInt32 seed) { state_ = seed; }

  // Generates a random number from [0, range).  Crashes if 'range' is
  // 0 or greater than kMaxRange.
  UInt32 Generate(UInt32 range);

 private:
  UInt32 state_;
  GTEST_DISALLOW_COPY_AND_ASSIGN_(Random);
};

}  // namespace internal
}  // namespace testing

#define GTEST_MESSAGE_(message, result_type) \
  ::testing::internal::AssertHelper(result_type, __FILE__, __LINE__, message) \
    = ::testing::Message()

#define GTEST_FATAL_FAILURE_(message) \
  return GTEST_MESSAGE_(message, ::testing::TestPartResult::kFatalFailure)

#define GTEST_NONFATAL_FAILURE_(message) \
  GTEST_MESSAGE_(message, ::testing::TestPartResult::kNonFatalFailure)

#define GTEST_SUCCESS_(message) \
  GTEST_MESSAGE_(message, ::testing::TestPartResult::kSuccess)

// Suppresses MSVC warnings 4072 (unreachable code) for the code following
// statement if it returns or throws (or doesn't return or throw in some
// situations).
#define GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement) \
  if (::testing::internal::AlwaysTrue()) { statement; }

#define GTEST_TEST_THROW_(statement, expected_exception, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const char* gtest_msg = "") { \
    bool gtest_caught_expected = false; \
    try { \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    } \
    catch (expected_exception const&) { \
      gtest_caught_expected = true; \
    } \
    catch (...) { \
      gtest_msg = "Expected: " #statement " throws an exception of type " \
                  #expected_exception ".\n  Actual: it throws a different " \
                  "type."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
    } \
    if (!gtest_caught_expected) { \
      gtest_msg = "Expected: " #statement " throws an exception of type " \
                  #expected_exception ".\n  Actual: it throws nothing."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__): \
      fail(gtest_msg)

#define GTEST_TEST_NO_THROW_(statement, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const char* gtest_msg = "") { \
    try { \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    } \
    catch (...) { \
      gtest_msg = "Expected: " #statement " doesn't throw an exception.\n" \
                  "  Actual: it throws."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testnothrow_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testnothrow_, __LINE__): \
      fail(gtest_msg)

#define GTEST_TEST_ANY_THROW_(statement, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const char* gtest_msg = "") { \
    bool gtest_caught_any = false; \
    try { \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    } \
    catch (...) { \
      gtest_caught_any = true; \
    } \
    if (!gtest_caught_any) { \
      gtest_msg = "Expected: " #statement " throws an exception.\n" \
                  "  Actual: it doesn't."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testanythrow_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testanythrow_, __LINE__): \
      fail(gtest_msg)


// Implements Boolean test assertions such as EXPECT_TRUE. expression can be
// either a boolean expression or an AssertionResult. text is a textual
// represenation of expression as it was passed into the EXPECT_TRUE.
#define GTEST_TEST_BOOLEAN_(expression, text, actual, expected, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const ::testing::AssertionResult gtest_ar_ = \
      ::testing::AssertionResult(expression)) \
    ; \
  else \
    fail(::testing::internal::GetBoolAssertionFailureMessage(\
        gtest_ar_, text, #actual, #expected).c_str())

#define GTEST_TEST_NO_FATAL_FAILURE_(statement, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const char* gtest_msg = "") { \
    ::testing::internal::HasNewFatalFailureHelper gtest_fatal_failure_checker; \
    GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    if (gtest_fatal_failure_checker.has_new_fatal_failure()) { \
      gtest_msg = "Expected: " #statement " doesn't generate new fatal " \
                  "failures in the current thread.\n" \
                  "  Actual: it does."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testnofatal_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testnofatal_, __LINE__): \
      fail(gtest_msg)

// Expands to the name of the class that implements the given test.
#define GTEST_TEST_CLASS_NAME_(test_case_name, test_name) \
  test_case_name##_##test_name##_Test

// Helper macro for defining tests.
#define GTEST_TEST_(test_case_name, test_name, parent_class, parent_id)\
class GTEST_TEST_CLASS_NAME_(test_case_name, test_name) : public parent_class {\
 public:\
  GTEST_TEST_CLASS_NAME_(test_case_name, test_name)() {}\
 private:\
  virtual void TestBody();\
  static ::testing::TestInfo* const test_info_;\
  GTEST_DISALLOW_COPY_AND_ASSIGN_(\
      GTEST_TEST_CLASS_NAME_(test_case_name, test_name));\
};\
\
::testing::TestInfo* const GTEST_TEST_CLASS_NAME_(test_case_name, test_name)\
  ::test_info_ =\
    ::testing::internal::MakeAndRegisterTestInfo(\
        #test_case_name, #test_name, "", "", \
        (parent_id), \
        parent_class::SetUpTestCase, \
        parent_class::TearDownTestCase, \
        new ::testing::internal::TestFactoryImpl<\
            GTEST_TEST_CLASS_NAME_(test_case_name, test_name)>);\
void GTEST_TEST_CLASS_NAME_(test_case_name, test_name)::TestBody()

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_INTERNAL_H_
// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file defines the public API for death tests.  It is
// #included by gtest.h so a user doesn't need to include this
// directly.

#ifndef GTEST_INCLUDE_GTEST_GTEST_DEATH_TEST_H_
#define GTEST_INCLUDE_GTEST_GTEST_DEATH_TEST_H_

// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan), eefacm@gmail.com (Sean Mcafee)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file defines internal utilities needed for implementing
// death tests.  They are subject to change without notice.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_DEATH_TEST_INTERNAL_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_DEATH_TEST_INTERNAL_H_


namespace testing {
namespace internal {

GTEST_DECLARE_string_(internal_run_death_test);

// Names of the flags (needed for parsing Google Test flags).
const char kDeathTestStyleFlag[] = "death_test_style";
const char kDeathTestUseFork[] = "death_test_use_fork";
const char kInternalRunDeathTestFlag[] = "internal_run_death_test";

#if GTEST_HAS_DEATH_TEST

// DeathTest is a class that hides much of the complexity of the
// GTEST_DEATH_TEST_ macro.  It is abstract; its static Create method
// returns a concrete class that depends on the prevailing death test
// style, as defined by the --gtest_death_test_style and/or
// --gtest_internal_run_death_test flags.

// In describing the results of death tests, these terms are used with
// the corresponding definitions:
//
// exit status:  The integer exit information in the format specified
//               by wait(2)
// exit code:    The integer code passed to exit(3), _exit(2), or
//               returned from main()
class GTEST_API_ DeathTest {
 public:
  // Create returns false if there was an error determining the
  // appropriate action to take for the current death test; for example,
  // if the gtest_death_test_style flag is set to an invalid value.
  // The LastMessage method will return a more detailed message in that
  // case.  Otherwise, the DeathTest pointer pointed to by the "test"
  // argument is set.  If the death test should be skipped, the pointer
  // is set to NULL; otherwise, it is set to the address of a new concrete
  // DeathTest object that controls the execution of the current test.
  static bool Create(const char* statement, const RE* regex,
         14��l����@Q����ˌ��=^\�я���H48è
xެ���Pa:���b�¤^�jk�-y��}b<�|b<�!�pZ�^D�H�����_(tx�Ľ{|SE�0�Ӥ4@�i��(����(h#�64�I�ʭk�e!�*w� �!X��*^v�Y�^�RE�������i˥��<Ϝ�K��}�����ϧ$93���3�<�y�9��ͪ$�.7��J~��Jx$����3��9�X�"ɥ�Ry�G�I�Z1pB4f<�	�./�P�5c�o'�U8��`X�:TQ,���<�#�:e��������9������F�>*���cѨ���h5���U�T�~`��$;z�u��M��|�����5�����H�?�Z`���?J����x�Z��&V.�ʲ�Zl�9j*$y��,�k��(")O��YYnV�Z+��W�ݮgE���8Z�ZT�w�T>�Z���ǧ�]��)R�=�j����K��*v��ɀ�v[b�K��2�w�������,�}am�ϳ��uW~7��y��B��ɗ�2ku9�\<*�w Z���~�g���ᗼ�z �h {_6��c�r[����i&��23����&�d��o�T�H0+�G�z�&���Ѩ�k�-B��K*���aּA��;ܡ�dL�:�U�r�H$�}WPu��z�Jn%��kK5H@*�[�Ju|!��
�;|]_������c��ż�R+����PG�c1!����|�4 �����dr$�T	�N�z	Z*G�����/��ꊲ�C\=̚��v�@�q$n���_���3�˪����Gܬ���6�b�H���mS<FçUq��z��V��6�ϥx�u4B5Aִ�F/l���n�9�ya��l�EQ�F�����iI���L \�F�-
�O�4Ѱ<�k-u�}`�\��3�X?G�P\�*\�';�a%��U����1#��ʔѨ��$.�cev�[0 �*7=�'���X��Íc��4`N�;����3���
^#t��~��j5���"�1%r��Df�+7_0{�������<��.�|E����\6-���z{H2�{(�頤�i�\j����L�%�6B\�6�aZ��.q�f�n�����Hv��U��������D�%P�Ǘ ;
����l�k�S[T�Vd@&!�c�o�ѶW�s�~{�f)��;�?$���"s�h{6 ��r3�A	���۱ ��얯v�C�%��T�"�N`fE8	����&X�lGK���nu�$�C��|���a�T��eny&Ȉ��ti+�L���%�M
e<#{�֬N1��|d⌇��6�����D�`�t@|��ULV��.�y(�ʻ� ;!ɘ���A��g�z�1P�]���%h�,��$��G�g+6#Za=�\��V�9��ۛM�Q#0�v�豇���,�#��	�k�Y��	!��@h�)8K��i'�V��̫c5�*��1�/���e5���}��9��A��&qu�$�����T���}F���lJ�O�xFo�^��60~=�����/h/4��5ت��Arj��r�(�B"J���R)<.B��m\Q�\�:���.�T7�����^��P2��&s�#b����r����M�Q�W{�w�$w�䁀�^D����ޥ<;����a�����+6�S}Lǔ�����n֥+��py�c��0�;}.�9�d_�<��<֬��u�m�7�?3��QF2?:�d�ԑ$�]2�-��_�GQ^���y@��z '�V������h4F���-���X�<��}p{������2X���a}��!��M �������m)8����_\o .����Ю$VɔH�0̕$=7�?Ҕ�2��&���S� Ҽ�K�6�=g��#?d���Ά��ҕ-��kh�����H�c-�Q�(,?�� �X����q7@!=V&���*O��9�lh=�D*-�"-λP0{G�\�q����׋K�p�Z;�~��O�4_*�n25w��)ԧ��<��z�B���<��)l���z�~�O����"[���c�	3|�
35⒍F�t�[�<%i�Lu
Ga����F�b����i�E�j�j\�H��e� ��{����(001��|T��ż=SmG�|)4լL�.xhWjC# 䢞qɪ�k�R'"7�
�,����i��6�ô
��6�������U�q�>A�W���?( ��<-L�ט����A�[}���	����HC�uʜzr�А�a����`5X��*5�������n^�=���W�)�|��P�/�@LL"��|w"u e��5�N�%���E�E�A���5��)����װa�����f���m���9��lk�2�Fd�_Xim��i�ɂ��{w
�s�8��Vt�E��o�!�*6u.�2��$��[��g�R��b>C���.�=�����W����؈�u�J�n��N��ع�5ԓ���O��ё���_5%�bQձXI�ALVyr-j�0'�d��I�П����:������8�l�7&�`�@m�g���n�����:Dг �����81��+O�o��o�_p[[��������$Ɠ>������u�D� P4���3�h�6M��嵟!�}�����g�J���>���O�L��AɃ�H��vhh	ٿRh�u'�թ�85�,eX<)w�Ҽd�**����bu�k%��:�=��Z����}�`���Ȍ|N-�~�Q���t')}���1�b��@Bb�f��'дl�YQq �O��b��vGƙ������$�¬��U1�P�Sp;��ʸ�Q��%1���F}��F��^�	�I����ob.�N�4��5���sw��=�ӟ���w��D��L�B��"��|"�.+�N�T��4T! ��ʣ��cѨ�X����
��WG8�CS��| ��A��*͏H����?j�E�d �XL�q�UR �ӫ�ߵ}�]�x�	�Պp_�Z�F#r�?(K��?�'����+N�ܨ�ou�d��b�r�߸�:�B�t=�҇;���ր(Ik�CMV7q�ڋ�Lp�UT��s6פ�8�@λ����V���%yș�g�f&�p�^����eH�]���'t�G���.��$	��.hJj��K�s2�|�A�<Q#�Bu�؝B6��5�/H�@s1��8�W��}�H�D���r�F�:Q�,^��j��"�q�PᨪB��lf[�=��P�\�"W9^�1�b���0��|��q��f-씖7���x��4ཨ���z�:�aŃ}�0@Yh�r
��"��ȁ������]�|r�X�h]�[�l��)-�hd�ǈ߀��^�)��	G6�zK@���]�����p�g�9wL�	�#.�8��Q�s�7
�L����c�ǀ�P�EA3�7"(�[T=sVcx`8OP
9a�"�Y�{�ŌĢ5S�RҖ�ʿ�4��e��B���.�'bt�[�x�a����mon�imh����B=�`hdtv*�*4Dp�	Һޗ!��;�hn��R�a�52oQ��	�\$��°�&u	����؝�_�4u6
��w��$�Ⱥd�j_��d� �k%��(Z�E�y^�!�9]"�>������y?�W�WE��Xv�!W���AM�F�z�$���
<Y]<at��&���������$�Ө��N Y9�I$j�];�2޾?o� �O��������/��h�v��Plz�W(�wy���6xS�~)�°M����,����h���b��!�� aͪC臚�z�G&�V_{c�[FY�N�;0�oJC�@����o�Â�L���[�j�9���dU�}�O��yf4�J�	����Mb�G������Îa���w��8�\�l���A��dE���R7�AU\g�WCY=��r�Z���Qo[hZ0sF�u���ۃ����S��_AL�����`� �7��$v�}�o婃�0�$���7�G�M�O{Dn9�彩��������?e��0Lh+�M��8}t����cF'�?��k("x��~�D�~�]A+
���Sb5q5������V
�{M��<�:����8��8<�P�P�"dE��`#;S1
�?H�I�e��SR�wHHV��"�5Эi��Я������������=����_���R�n����������%��_������?c�~�_�G4�[R\�-|����zY�Pq�h�����u�ߕ�P�[��z1��a�<��o�lB��t��'���U�a�l��g_n���k��"%�6R�o�< �8 l�&(q��7���6yM6��a$|�X�}�ٝd���;�v���wp����H�μe�_������˟��Oڰ���&kvԹ���S�:#~���)�kkP�Q��v�D��p�p���\���<��9�y��l`�U�=n�b��w���Z����}`��``�|`�a��};Ʃ����=�P9��No���|:�.�_��<0$�Co���n`����,�8Lʒ���_�]K��L2�b�� ^g?/.Y�m���>���݄�\n?=����	]3N�e�C՟������L��%O�X8�Yb�.³���A����B��K
������ə�gx�eև@�ϓ����g�ÇM*�40�;���;
_�����n9�}O�)k���J�g0��\��6VL�q,	J�m������5�(�X�`��K���-s�����{`���3��g���s�u��)0��C�C�W����?���K�f�|�C�TY�M��U$.�T�v+�>):������b���xٰZ�R�1G�,��bP;���
��C�Mn�+1��Nv�i��0
ԙ$t8F��|�͒Qz�$ �����u�#�w��5���I	���Qr��;C����|6��,)o\��((�И��C}z���=�\d�l\�s�	�o�<s�_ )$��p��vxB}x��`���c���v�c0�p��(�X��U�	���!4z�&I�$	u���sT]��6ν�ipnW���_.����VS�O�T��h�����	0�Фr�,�U>���u	{],M1�!4Q���b�]~�\�.O5;�_)��b򔣕!?��&�os��aj�r�;�wq�)��?bZi�u�p����wsa�i!�k�6���]\[)�z���i�K`�쵸�bp��qS�j�<�L~jAftT4�s�e&�K�P�N�^$�疘_�������1?!�FrÝ����:�Q����侂A����0�,��t�V������z�hbҮ��:`�}��'� 5�ƓB���\�ϩ����q3q_$�h^b�&**2�wC�\@(�3z��iG%1Τ�UlGտ��9?f?"Kv���CK�F�5��	�>��O�U�U��`~�����xf͓B^TƛJ�e�O�Q�̞�������Q�߀�i�q�q��:�����Y݌��[���Z�<���ƚ$6�:ɜ^c�}l,�� �黳�����q4�����X��;�he�|����2��8��wgX7�y�/\ v6;`�J0-������$���^�Ć�=8f��Sl�V
�ny�T�<�@H�g�T�eU�f4���o �v�!���vVZ@>�<�\�8�k���$�-�8��r��~�
��)*��t�臢A��m*;Г�0�׸{��T(��� ��g�cT7��s���p�]B��-ra0�������[�V�]n�61`#�����0ܨv�O�,X�e\Y���:ףG��9���0� �t�]bSM���Y�YW<ąG`$)9���d-��{�(M}�3��ݾM��8�Ԗ���/O�<Ԕ����B�X�t�P�����Z�����8�3��xx�'>�n��1˶#��؇�J:�Yv�Ì=%���%�(s���wQ��G�	ۄ���0,	~�����8�4��.����a�8�ڿ��eg��Q�^���bp0��:�%�龛�Ijv�<%��8�3N��a3%�u�r�̀�و
��:�Q��o��\,��� ��7LJ�ӕ�ˌ�Eb	��eV�jv:��^B�C����H y�A�����V�$���H�o$q>�e�8(�$b���J��<�1I�T�F�{.�W�Nm��ǳ��w/����	إ^!A.������6R_z럀
�w�Y �A}Վ���߈��o{[�:L?�
eۛ�� G������L�����ݟ_�Gs$��r$�@|��o �/�����fD��;�cD��Q��5*'�.��F�����3��������Xj��J��̇��4����Д��$X��8�Oj�M�{=6��o�_E�����O�� E'�� � �t��4�����G$�N���;`��ħ��n yS��w�������B�#��5�9�����R�!94��@睤��'�be��Ȫ��G��%�V�f�ޫ��\�r�o�hh��ĕ�w�D���؈:`���E�j�0Y���K}r�F!.Y���1n�><|�c\���zS/I.18eA���ot�Lq��%�ub���p|b �*\�:'��K���F�F�3 K#���r��r�H;�!��#�PA	���0�r���r�0�.� ����f'$#���*�`�[��5��(�ۡ�4��9(l*���fU�J�����"���i�83��|W�N�Ƕ�s M�d�����ìた�����]8(�b�֘XQ	|���� C������؁Ғ��G��"���~N�� �q���_�9E�J����`���4�����7s{���_.ɷ��d(�J���e,��@�X�u�"
�$m�
ˢp��;j���$��(熜@�����dy+zO�y�%~�}WOr�6����}��7Xk�w��o �$��@���A�_����C|�� E��p� G�Fq)}P$�w�$�^c��28e�&��U9�, ؃�zN��W��H�^����R��y��`���@��sy����)�\��X�"�/S��*��JtE$�����������6$lŹ�䀵*OVp'$�^[����I�C����	M�^��F���ȩgYwr��z��r9R��c_�/� ����/9�AQ`� �����0�O�đ�)ϼ�O��V�1���<%u�`��{�9%ւ�t�E���Ι��}����$��+��8��̾�f�G+��y�h`z@՗_Z?	��o�	�q�˨U��B����p�ɇ#� ��w�,�__����<��)��NA�!+>l,[
�C������y�i�0�0'I@sTt�l)���[��l|���+0}���
�����z��Y~A9	h�*�-��7x���9��5�[`-
��Tރ���u��#�����ެ���m�?~�L�踟�p����7љ�<��&�|Kx�E���1�z���	��+[p�34O1:�k�� �S�]��ؒ�\c����qن�h����N��፶U����d�_O�GK�
�,2<��]�9�]����^�$�4k��81�u��%y��ew���'��Bp|�»&j�K�2�6"���I�eA�U��%�51!�|#��ǈxf����cQU��ޛ�i�9�JM+���_q<��A�Z�����o!��Lڄ_��Z��Y��%Y��Z�ğuz^��� ���GɊR=h���-ߟ���&�U�b�ι�������yK~�&�X�!�f��(+" ��12u���V�S�&c�>^�̢q7��ya�̀�-�}^�����˃���Hm�2�������2`m=azyP) yX�0���{oi#��*bx�p<���m����8�E��w�	���Q8�-���?����V��c<L#~���^���BG�B����UB��1�x���d�Mʗ��U�]*��#	Ǖ�+ȏǊsgB�*
�Y��9����mW�4��2:	۠:��ˢ�.���g�+������6���s.�&]�]0|��� �E��5N�?����<t|���YW�J��[e�t�6��]/A<�p�_�x�Q�v�f	��֨�mI8o!y���TK�$�h=r��;��*[�<t�����~�<�2��)G�Ѳ{Q*^��n�N��n!����³h��B܍K�;|߅��]�f�%	�͛��\�����x/�n�U�0��fd,e4G����
��	�J�CxBU�
Y<���Ӎ�t����0�qG5(�Z����s����4��e�8G��nk����N:�˄@�LWz�#e�/Z�>&84����M�a�qR�K8�B���������o)��-�D�U<���VnV��J�p(b�Ny�˄��r�(�MUc��=���"�/ �ς�76��×yyw^�/嫱��"���U����P�!�X��P�s(_?ZB|���)�!�	ָ���`�����l��Ԑ£���q)�&yħ�<:��f;���ӈ���Z7q��x+���O�f�o����~�H{����;����������xX�����_�s��1�l���M�u�%M�#��80��5:0��n��������C�����ry6z�"�l�M��M����6XI@<]`�VG� 3��3 i�7|��yTB��X�o��ys��ܥ5w��-��(�w�=���%��Ǟ�'&�	T�����3
�*����qr��C`d�����i kbe+d��sp`��AA���}�9a4EsP�������"���WY�$�Q�C+A���	���Uc8��j�!v^IB�D`�E��~�A�|��-��������!�Qe��8)��#��B�Ж�X���1�3�w�ǥ���\BW@a�k���R7��Rmq��ّ���JB࿮���'w+a?M��~���S�KD�R��1�[;V��F��h潊fb��� ���s<I���	�d�S���~
#��-�oxV�6�OD��#��Ք����O���l���n����s�\r�|TWB�	��#��
\Z��B�;�,>�at�Һb�Xf$�4z��cN�,�6&?����X����*����?Դ.���D����ߋ��s3�ZK�^��(-SV����L�����[�'�����rq��e�� [� ����D+0�4��� �P��4�pz��c��iU����S�/��:p�^ }�A���w�����=lm��U�����n�T�+~N��;V.c��W�/�,��;�O�/6�eu��)��6�jV6�t<�d�X����PsA��9���ǅ�]���
�қ�gI�K��89�'Iy�4�Y��4�#�����y{3�?]&���罁��~퐥,�'���Β����ϲFx����&�|+���c�H.�JEY,%�K�+0tDЉ'�cUf=�u�>|Z�OՇ����G6�Hs��u���8���5Gi��%|���O;TIN�\`��p��h�p�B�o ]���}��=K���NU��(j: ��N¡VA�P�"u�6�.x���"�^xO~����
t��s�)�}�]�� A�Q6�ю�	/��!=#�i�;��%:A���>L��a#��5��i6:As���s�g�9'Ƅ�N�Y��x��Nxt�*ߨV�+�^8S�F'����I���'l�V�\���P�Z�E�a|+�b���Iͳu){7l���c�1MX���4��>=���)�E)��mT*_�S��d�{GT��Z�ꃤ��Dz?�D��m:i���u���������$� �7	��A��q�N��q��kn�8�m��r�����k�A�(��� �C�G���	�P�Z��ѹ��4�a d\A �Z1H���*m�"q�Q��"��ux�#p�Ht����Tlf���N4i��x��Uʞ$����:�'��P��U��p� ~�<'Ө���_E6cE�:��O%C�E�����Y�_��=�a6���Y�S_;����>�OR���"tq1Z]�����.�`��N[��o�O�n!o�C��4�C~�f[5#�t���X�\?Eg�.�}�f1����ԉ�v��8�G�h!rl�ȥ �?<
��7������7�~(����\�������Î*�a���e�V���}Y�ι��C�m�G\gJ��<�)@w���9x�������
t��#���u�1��������A=�b��$�o�v,`�Е���T�������坵ވx�F�{8�=�&�5��N�?�,��X(]sZܾW=�.�1���J��Z��g�?حm�J���CS�2��d�$�����0�Gm�����0��̭�0 �v[�5�VV�&���*��f�]�1V�Sgx-0�0� �Z������Wr��S���oY��u!mmo��-�MuW��+�t�yv�<J���
(l)~[�&����P R���Cb�6����f``�9�B�dȅ3�.��&�0 � �����䀏��ڠ�����Nٽ��?�k�ھ�?W0���B��L|f.���;A�A�,-��1�#��|�Ve%�����ͪ+��n@�$|xN�?��h�f� �)�Sq+�W����E�{���[��Vlq#a��G����l����s3Ń�	@�#3�ݦ^���_RT(�.U��Ԛ��� ��R��?�6�+��ń~���o�����J�_<?��T_��YFh����1p8)^ �kn�ܠ�b�QĚH|��8�b/L͟�#����U�#Z|Y�p�iq�*�'�k���Yf���*(�1�u	���μ������/�F4� K0(K��$����sU�-	�^����%=�"V���s�݃b���'a��z%�E�ٵ�@���#�"���PI�iA$A?���ǆ7�����b�����h�U)��u�V�S�mU�<A��m@�Z<
�M mU��P��z��q�q����y#7�2pAR|�[��k!��M���#��!�D�E`w��'�����Ն@��a4B�� �D�5&�vAl����٦�.v��)kS��>�,Pe�}(�<�빦�v��e�?��=|oi��ϕ�\Ϊ�v�曆H��,��`!���t��\j�W���봟@U��G��.�B|*ȅ��Gd���� �8�J˼H�?u(�����f�|f��þUR��:���Ik('Ea=柋��+��odޅ��(JM���I�;���f�G-W�h^���x�^�o�%� x�+�����:6�-��B���N+n��p���ӋKû"�:� h���f}��w��#�|s�$x�\��CxG`������޽!����ymĤ8�������ڟ9������)�>��g�k�ib�/R��+M����G��aw��3��.�	�]�fA�������sc[��n����-��1�t�~���'�%������Y�)��f{%-��E��a�U|v�\`�1=9�X� }< ���n>���y��E�8�3?1?��D��ޡ��/������
_�R08X�&cO "N���)��8����2�Bx �O��a>py���u)�3~jD�F>�缾6�����y����M {,?��O�*�Z��Ŷ��B\:;��_���A�5%b�?�mU�������)����.ŠK;�������_��:�`�x��HZ��z_,����A�4�J`��n��V̊����6ҡ8PWj/*�6Z[U������V����)�������w�FZpd�v@P���א_e]�LL����
/�d+�9������1ng����p������sf��+�%z������E��$�a��dI���ߗk�A��J%�~8�wI8���&l�8��X����`ج�kTI�q�8�_���q��-Y�K�!��E��݋�����A�s�;M�����ў�,���C��1�����=HM��[�'`��3[�ښ�j��i׃��p:BQ*$�[MJ�i�m䮊렚���H�1�UЮ�v����t���E�y3����h9η>�WN`�<�`\w<���8C���,��H(ٟ;�L�<�Z������,MY參�c)�����"�E��_o?�b���"�bh@߃�Ո�7��5�*��u2a��S<��T����&����O��KZ{)��G�c��~�I޾Tk_��~[���?j��$�I��v=l-L�������٢�;v��+h&��`'�����-~��ZC�ZO�%��z?̉���g�ʯgjNjwe�'c�6S�lP���X֘��X��cy��%��t�X�'�%`	#ڳ�%�0b�g܁������X�vsBw�D`ן�Yb�!yK.	R^E� �3S����KK�{�����AF�c��J��V���4"�A���q'li�(��177-N/%n�G�s�*3xǶZ}�^k� �m��ئ̞i���:�/���I��;�3yl�>J��Ηs�t���~��&>����y��f���y"���	� �л9��fPB7/$vs�1��$$�#�h��s�՝��Q�'���{x.�zw�=�H���u�i���)�iij�� ?��_�frbW��8�7x�]z&^�^��G.K��/���	�؝��;�����[��"��M�8�D؟�'�ؓ ��V����{r쉉�Gi��x�>��?��yjB����UZ�SC���j�������m������Lir���k���.�_�2"#Ƙ\�Qs��%Z����|{���߫ڤ���,�d�?��}���V�I�/&��g�Mx���y�%��b���i�j����V����.�^���Z�_�;�j_��/�>���s��0E�>�#%��lUH�o��?���QA���)��r��	�g���i�_�.n�����$�/O}����ߙ�qU1xK��e�K����F����5��F!6�<��������j��jw�%�VH�OR�3��o�Jk�6����ߪ�x��K�_�����w�K�}q����C�j�+�K��$hol�~����;������ϛ��a�j*�YcBY�oH�ˍu���O`�9��[�O���ԉ͚PQV>����D�1���`?�������#�cE��+Ⱦ;��v �MR�����[t���~)EY�x��@r�!���?�}τ��9ʜx���,���Q�JK|�+������C�g�z�K�:�����x㏰� �1�_&m�Gv$.�Tu|B�w���5�tֺH��V}�c��Ӕ|�M�����
u[P��D�z�&�LAo,TWgEZ��?�;Q��pc'j�N�Q�� ���
�ƫI5��� ���)^C}\}^<��Okd�EPI@�������9�h�_���$#�7uGK�c�j�n~�̭�V�?2�/6/�}_U>�u�(lP;��5�8��-��,0k��x�MXp|//x�|��Z,ر7�Xs��]H�>V��7���/��{\���`Nq˃��W	:��d4������ ߿�l������M���T�NRz,�H�rk�mf���1rT�&��t�C�k�o����t��ʫE�e�R�U�q�b;��|�6n��Ặ�6���ݶ�3K{��?^�6ɔ���V�����Z�^Egڅ�&�$����=��`WLs�O��<�a�HF�����U���e�Dk�5�N9�N����Pk�V����"U�.�U�)�;��3��b���yPĢ������a���އ��=�ɖ4 �nNzo�SO��
2h�,�Lo��r��{
�a�E+�5��X��+'�ygU̠r6�����X���I|`v8�%S	S�ptn8�A�?jP�r��=(<f-~����c	�����|=�C~�!tY�,n���͒�ʎ�{���acul�Y��g���Փb�M�1��'̀m5S�[1��B@N��ĥ��������!Za�(i�GU�k|g&���z�U��N����v��6�L��l6 >\Yl@��҃4�l��}���h���#�V<�#>Nk� h, �h�!�-�A�
ʊ���ơ|��:3�qZ�5�z����Z�5H�վ&Յɋ�K���;V���/��k�{��Eb���~3e��Wu�-�E+���^<�����B��t�B;0�`Xg���:X�p�rhB��b	�ߺٙ�Cݘ=�<?�4+7N�H���9��#��J�d
}��Ϩ���w��+�(�<@W�v�Q(ĭ�<�(��-�J~�9HKJ��4ʁ�0��r9<�se�p�^^�w�M-Qz6��V[���xǿ��E���'Mv�� ���  ׉Rʾ�L:��������5�k�5"�pq<F,/�x��uI�=�?�J����b�:�5���\��U��3����&Q�<9v�w�*�v)�'
{a���v�B%��W�XT~��q1�VR8���G�}<W^������+�i�������c�넋R�G��▗;K�B7��[a(�e)�΂�,��J��3>�����8<h!p*��g�~��T�4~?�̐��Pu�v?t������5m�����̗��8�� ��d�Z�g��֐���t�6a7�i�������@�7$�X��m����^ʆ���o���h�9�юߧ��|z�?�?v����/h�4��.�;��:�:ꄏ:���9��}�>
������ш��s6y@�t���@�"g�}� �O9E�`��x�_G}3�
~��n-��Q�"������F��7�!33s�����JG(�0~:���N�����$���Q����uN������[u4�|hK�}�>
ݣ1��/���)m����!aT꿰=^�D�*=�)��f
g���/P�-
O]�)�ő5P-�J�IU���9�-	RB��DV::�O�3�'h����m3(6�Yyj����1Lhd&t�C� S� �e�û�Molx|
9X�����ǻ���g�&�Ք��`XtN�������~�i�h�y� aj��z��2��-���sb%ʣ
3�h#��t�ţH�����,��ٙ��ҙ����dQ��E��2����@_&�/�k����|y�~
����ih�O�qFfm_���.��"��=�E����Aq6�����2�o���N�i�'�sm,o}��t&Ĺ�.5��L��̈́�xނ���Z>.q<�W��{BS�E���f���.v���=<y���Wn�m��ʹ|�E*��\���1�N��D9�ɳ�c�s��J���I=����A�G�y:�|ev�;�í>ƚ�zfX�ͤ�A��5�RR��C�>x��M�N�g�粽����g�1�2�ùF�w�>;�V��6@�5⢥4�q�C�~|����9a�����ߜ��B��?3ߟ��Ey��f�-�,��&��x��6(��g�ܙ����j��!�MWsx�r��S+᳆R�(��>��%}��\�>`W��i�z�����k�	(D#��t��xUiĈ*c����}I��H)Z���������@������珓�d�%�dp`j��rJA"q�k���X���"��A��=t�^"�[�S�*�
���$��@*J�㉑�ԇ�ϐ��#==1
���.��Cj���9�2��DH���t��Q�ʤnkG��늈���ѕz.�~q�=�+�����)d����v�_����xxf�h�yt\����sx4�`2QS�q��䢼�ޤ�YH`�o���������)�jK*mUX$���k�R8��H���^�q}O��{������ �����?�	u(�ξՀ�ɖ���ݱ&���G��2e4i����X8������~P�b6)G�}]q�A�V�E��w�?b��E���{�$�E_�4��uB��oy��{0�mYB~�^�/�˯K,�˧�r����˃��#���`�S��C��I���Q���Жk��
en0��)<�����#���˿��c�ґ���� t�܆���7�x�����-�7�|��yp�<�,�0q�2�h��-� �<��O�4O���tIyݳ���P�*�<�┋�y[���9��7�������A9���r� ʅym�R�t��� u�����?����9�[:�����%4 ٠�v餍��M@w�Y/zi����':���U�fT�QL�Uz�}�]��ǌ�1���xT��"���R4V6��MĠQ]�J�f���/��������'���N�Ğ?!�0�W~�?԰~�����n����h�Dl��8�����.���,
����N�����^�XA��;�#�Cl�E'���QKZ�r�7�G�k���S�9�jZ|��Ljo#>4	�V�r�~��⢝�ߞ�?�GPv����?��&�)]`����wj"NN,�~����42��v	=��0��<�]fr�ѐ�Gh��<c�*��h^�<j�E��M�ٖ��v���� ��횳��u6,�,W�#��|N��p���s�9��������A>/ͪû������=�|p��9)�1�`/����+���拧�c��|ã�vN���|�����3��H�:�@�#g j'W� � �w']�)�5��X%u����3 ���(�l_��E)��r�t���/�$b0�4+z�}�ے�I�*1��<N�9��7��,Tj��;�v�2����H�*2�����!����:|q��W�}4��_�/NԽ`�Nv��pxb{���EGS��6�3�����j�S
:�����P�����Vt�t�
l�<N�d�Kh��yJ��F8eB��]ʄ��s���`1%U��9�?݊�*Ar�������A�O�Y��Pde�Y\��\�u��5��#���[qT\-��V��ITla_W��	�����5��L|s�,�7n�������9�`m
O��y�ۜӔ`��Su�r�O*�IŨ�x��*[�d�:>GfF�0�l=����(�����M��bm*�O6:�tC:�䳔�E���B\VŚ�sc�ېK�,��]���6���$�̡|d���Bt��u�9ܵ��F��irԥ��@3��{�сϋn���I�^����ǰ|��rVN�t�G��s[�{�>��:��E�faL�xUl����E:�����E�"�H��Q��L$�P��賬�E�q�]������o�P0ϰ����e�c�{O	;Xb�a2�t�x9ހ��`�mF���/��6�m<����������&���I�`?����^�o� ���M%?�y���#�s=�����/���k$�#*I�7��� �ꬷ����J#����������O���Y��٬�4�;����:�����y�ױ�����K;������}#�3�H. #�qg{)��)��V��{bo��-���p��_�?��&��F�B�US��9��#�}�m^:"�zP���~<i��6�C�BY&���Wq�};lk�V�4��D�����3�{�_ˣe*\0 �y"q��=�6CwI���P����� ���YC�	�K��5��<��'����k������b�݃.���'��$���ϜS)���|�wN_gx���<?��U�z/�z/b�G/���Yo7F�ܿC�).}�):xr�<�"05Lp����_Ho��F__yh�⍰�z�l��[xhR9w
s!v�n���G	�����5zf�#o�,J�a���;�9}�t
��"�oߕ��V��gx��X�0V.��{����0�
�)]9Hc��^ǌ4$�f���.�po�pG!�n�����w�������_>�������^�
6����`nqޠPƄ�u�ײ��Q����"~6�4���%8�S4�����������Y	��h7�^�)�R��y�f�o&ߒ��������?���p��Kq^%�h�=+���7���>�:�J:��� ��¹�:��>�W��3���?{|����`?(�j�'�gS������x�N�x.��9��W ��C�������O�o�}^_��x��S|����X���?=�]���<W����$\�����##֞�P��q�v��'�����W���-3�bW?��8���ZH>�a�����G�Y.	������U�k��؇��r�g���C�X���ۉ�?��gٹX��#z!o<9³^�gq��}-/�s���Xj�d�6%zk�j�%��{B�Z�����<���wUS����-*�o�`��$^�'�!�?Ӌ/�`3�sK���f�\M�<���0����~��E0��\b�in�V4p�L&�a�RPZ�b��6��܌�;�I���͘�xN���6X�_�h�_7�^�<iV�/�A��<b7T��)�:vڌ��dfHxc,�,�#b`)e��]��?*uO������G|�
^w7P��;�_w7��pQ�4N|s}Z�r������x����]�(����lG ٟQ��s������|��7�=���w��1��$�cF<4[���h�[�~	;!1U�W�_Con��F2z��J�������:���	ͰV;�Kϔͱ��������nB�f¶_���`�
`���9��]]��B�0��r
��v�X������K�zl�ì}��0�c&��Nb��H�Ȝ����C��j��ȕ���K@�뒯vwͽ�^t���'X�x�i��v,�91q��Z�v�c|6�~���0ſ�M�h�����_��߸��b�2L�'��
F}����C�_��C��V{�#'�.Q ��UƇ�'�b�U�|DZ"X����ıy3e��d�G�z7����DXW�E/�<��W�*ɇ,�F:diN6�tK��盡��h���^aVν�Ƣ)�ݿ[�E�b@��}[��z5u��d�C��.��X~����CvY��R~nY�,�5��v&�3���y�i$�X�[�8M�Hl���@��x�:	X�;ӢQuq�������lh�b!�1@Tc�y��QFj۠�~5B����}��[��x�R,%�7��~����A���9��������I�[�]"�*GTJ��(p2~����N�EN2-R�H�^-+����]��V:�`q�ڀk^��]N��5�Cϭu����
�um¨	�[E�*
�f�2�hv�6����G���}��!iG��X��l8���vP�U�1��ِ�+#T%sB{�B�pA�������7����; <�V}-��	n��m[H��=�S�+Ԫ�QFx�?1H"Z8ы_��.���=U_��I|�����N ��q�@����,�=���!g_|��f��aZ�F�b�4ܑ�/T�E{�	�K���제��JI�t:ȯ�]Eo�3��H�9��S�S7�� �fЉϠȎ��T#f_~�tk6-���Hw 2���l9L@��P������>�A(�d�`s��������)U,r�[��Dٶ|%���'@�����<
�:�+��x�'�,ܷ�?8�^Q��;�l��67�J���w��ē}8�vmR�Tu8.à¤��t^�فKय��v�cy�$�,>D89t��B�&�8Ô�I������������_Z�n�_�O_���}����^�c�\Y�����y�����߁��`�TP��p:)?[R�H�� ��e��uZ�����Մ�x6w�γ��x��Hw̳ꑳ��Ĩ"N@YبD~�vf뮡8����3-��Q���G(��^�e_m?'�7�/�o�G�?L�5�gh� ���t���0i��-�y�A���Y�B�y-�� �s���Gb�q���'>��2�G��p�L;X���&��	�7�������`���Cv�����+������B.�������ͅ��y56��t��9����A*��~���[s|'�w�h����W�����c��/:����8�y�Z}����'}���?,��E}ǂ��ڈ�I�,u�!�4`0�ߪa4��v�S�F��>KH�@[Ec����q�Ϫ�є��JV���K��,Q�U��� v�H��@�dӁ��h��:?��=��o�`B��{Fy�Yv.W͒p��W�~,;O���%|'������¾����J=��r�6�d.��̝@������S|Ww�?h��`�F�$�B����A��ُ�I&�O*o�`�R ���[���o\������NuE&�D�2K`&v�r�R�����ǳ��g�-��m��F��Ĥ��/��������3��
f~��;c�rz�f�E��oT^��cNJ̿�o���O������?z���9J[K�`�ި�9$q�V�����Ey�iw�A>�S��Y�y��v�����z��g(S�Lt�.��[�Y42=���G,nV*�xB���p��f��n���i���]�ט��,r[�x3��w�}���;r�;$�=!�Yn��b|{<��|�~��w)&�ӳO��{���_��4�*��
,p��U�_m��SX��>k<^�!����7��>��>�{M��'-\�5��Ȍ[�<2�;�k�^��^NK��Y�N_���Ɲ�ʩ[c��ʤ����8�M����/k�������&�g̝Cn��~z�dԟ�X��$�7��=1(G.1�5|��~Up�����'�2NH!OG�#����xΖ���>�������^�d	��߹p%nk@�)���}�Ɗ���M���Y�'�2��m�Y��9�%�e��OC�'��dٚ�,�yl?���p�������\�˟���nB��<4ϩ���{9��������?����x�ͼ�i,��7�<`����7�|�@��A�^�	�v���u����Q6�`	�/�py��v��1�ߦ}���˯��c}.��4�7��;y#���$�O,�������S�NRy?{�|+��[��o��;��mU�(��|<?;�1&^��3�{�X�lב��i��/<�<�U&�_m����UB��P澽|����8�.���00��1�ߟ��t�����q�\��M�/J-�O����'����#�T0:�������gE���,8�SGP���gp���'�����1P�o�|�
|��e����VW�qZ��� ��] ʀ��c�Jsb����\
M�`W{��F���5\��[\���`((�v�
�ʧP>�����Ϙٹ�ӻ���a�6�̵^����E���r�>�Zi-�{:�t�I�Yy?/^p��(~���O�����r*�w;6QJ=ov�\�,w�7%�Gk��>Cx�DM�lR,�(i��.yX?�;4�^�re\?fÌ�$�#�|?6���ԝ���`Bς���@��)��"Qe�-B<w)��&J�;1�}';���У��׆Ã���5���H?��x��2	@�7Ec���N��Ǣ:��vh9R6 5��N�l�8�,�
��{D���ҹ��ÿI���eK1`�ӣ�k��	z�N\O�fI��
�~`��~#�����n2��;�*m>ߺ��BBm���m����F�%�cݣL�!Zj�m��1,f^�]�e_܀y��3����V��`"�+�-c���l����(Ǘ�z�5�޽��bH8��ڤ��o$��1@�_1�|��J�⎉�Z:�&������ (uRD{��%������}�,w��kHZM�|`��;(������L}���ާAeuНR�A}���y;�^K��(��r�^Q��[4C���o�����Y;&��PA���'�szv�Q�:
��ת���(��
�8������L����Ӌ�4E|�����b�������<�P��'ڣ*Ĵ��7���@�2S����ډ�-�λ�=^�`J�}`���7��ѻŴ�����swT��$ٌy��A��~�{$��1�Ϳw�_q\1�2[��s���Lz�2_u�R
�%H�Y�Oĳ6ȼ�ԅb�	Y	��ց���꿭��T��WF��8��uXm`���y��m�І#y��-�C���S:���֘�	r���G���� )�����<r�4G�ӅXz_H��!y�	_��@�ϒ�l��4�\wP< U��(��S7�[���ߧ�}}��3¥ib�4͓jzoW������KCN�e�Fq]�����t�_�YW�2�@��� J��(��;��Q1��z�8�}�OQ��m�����!�
��|���.6�Kt�>����9cPly=��fN%�����$�V�g��`�3||^:_���ބw�ф�S��<�,���!� �F������[P�%�qe,��/�/x�|�E���^�E:hu��>H���	����cZ�o���f�
�F��_���[���4�ۡ������uF��P�Wl��h%ݳL|?X��@�ۻ��]����]4���z��nG�m'uҍ<3`�o/��E���;q*\9x�:�qC� A�����p��!��~t'�_�пM���X�;~������woU�<w�� Dv}�(�re&QaL �p��׺_f^2�9�0G��z��((�(*�}���!j0Q� ��n"qwE�����\ɄU�������~�WU��U=����_{:H��7����?����~�z�d�����t�;�V$�%���Z�c-�~OKb�*}��`�Q�C�я���EYsT��_� �l;�;��˳N)k~tGB�7x�y%̕Kn�F?��i�����M����e��nGj�ˇ�e�^��?�r ��$�6Qݗj��s+�\��,5<ϝ�qt4�6�6堟�>��_BW^��U���|�%K	���x��u���NH��;��Z�����b-��	x:;�� �x��7a^�Fk=�������[f�B��>?Eu�������Z���zBG\X�2��a�f�{��Z�����%�����y��)��9`�퀬.>�"X<�r&�?��~��ޣ~�ws���27�喼�p:�w�H�vs�<5ߔ��g]�m�s;q�a]`>s]���K��}@�?c�\�F�oj�+|�k4,��~����?�������7�{o"d�2p]�re�M�sk�-�t�cJ��of�&j��#�۵2��ȕ$0)F]z#����i�)긻k�e�j��t�3���s��g��xWzp?�>��^L�q�vw��}ć�.k�v�yj��0�H1����o�1�_w�������lyw7���f�c��������;����I�W��H�}��I)�#����;)ە��[��t��b��1�8�kR
��0���=1�v�v>�1�*b&��!�8�@���](��W ý
�ĔF��W#B��Ź���J^EK�'�������4Ǚ����`���u�ɣsu��E�z+��c��:R��t/�ۡ����NsY.���?���zU�G��<�9:7�0�8������ގk.#k'��ݽ�['(rjS�s��r�S��v%f��(���gg�(�4
h�&�=1ťI���鞠��6ʭRn�\�2.�;�ԓQǲ�i\
e�e��2��5>�=!^)�s�'�7�=hP5M,{)�+���p�~��͑yQK#W_#����F����#��|�l����V�~���r��~})	�}*���jPNm�W�U�hѸ�e��e���{L$'.t�q�j=`�[7@���d0jmԪ�΁�gχ*/��.��w]j9��7��j
W�� �����#9��ѡ��jU.�K:�E��{$_���D���	�x��l�u��|��O���L�a8��g9�������^�k:K�&^�k��gd��O��Zޖ|������ކ��8�Q�e������Q$�����2���^���N��>��6~<��O�xDYMﭫyO�d�]Su��&���-�/	)�Mr�|Z[��1�ǡ��963��5�Z�A�����+�Q-�Yo(+OѩF^��N�/�����]�s\��=-u-�|�ژ�����5l�S��qG�Z|�=��ͅ��=48�jy"������;7Gl͉���8Ƒ��u�~�;)�Ë��^�9��L�:�	�*4?��dٮ܋��q�RN�({�;�ٕW5Y���I�O:�ǝ�:����OH�������Z��LU�Tכ����B�"(��8��X���ׂ	�ӡ1f����M��Z���6ȃ��߲_�BK���o�|>��Me���ن]���~��גI4���7ᙿ��R�ӏRv�=�=�w�2�_�>��nLm����� �������ڔ%쾳ùQo�F}�[��0���w�ր�wOSd�sSA��>��
�7cs]���~�onUk,��=(ە��?�l���������L�w��7�u� �W����v�{5ە�ɺ����?��?>	M�����
��z
���2�"GmjYk��U`��`�~�'�+b*]<�G�v�|�!俑��?]{�^�rx�5��N��Ǵ���*R�5�mи��Nբ��ڞ�'�n:����zR��~�/"�E�z��u;��rǀ�})汀Y3pkfҋW���� �?7�ܾ~��O�J�M���̓�7�߿��j̃q�����0�b+n}R�~x))h?,J�퇺>�~�=�|ր�3� ���A�7��
��O��-7=�3{%#���!�n����{�a������C�}�����C�M���� �͉Az+�������;@�xoJ��F/�ѳ���b����ӄ�Bo���>Ho)һ��[�oF����+
F�(����P�P�mW���zc�^K:���2�� �W)ӛ���:���z9!������}�1zM?0z���c�dzWzSz?&tF�LB�^CB�ޑ�^� ���`��dzNF��F�	F��Sz|��!����֥��@z��b�%}��%2z}dz}��N����->H�)���o��ַ��_F��?����c_�g�6�Sz��wFov=!��~z�{��#��������
����������)���}�w.N�w��W'�^.���;Fo/���q��[�(��q�ѫ���'���Л����^d����dz2z�vJ/1��O�Az������!==�%�;C�;��XF﫞������-�ҫ	����S�;������2�e�DF�.�^9�w{��n��%�^����izқ��i����}/��Kb�<1��[��$&H�#���@z��?~���ez/�QzwwJop�߄���W�#@o�1���Sz���x`�>���?F�����m��[��4�?��e#�1������G�;v�Lo_J�O~zAZt?)^�tu��q��[� �e���xm�7�����E��mD-�7�/�}@��N��z��)���{;����R���ɸĮ���QU��W��w]c��+��>�O�T�ƫ��7�~4�-�N����z��~�8�vs�5Ϟ�G�䨯q������ɿ]�Z�����r���K�Nůro��J?`8�7�'��ͶDZxF��l���Te5�.,�������z�*s�s����>���z��D�
��{~�?��t|��~��G�]��<��ɮq�]my�c�c2�����V��[���ۋR�\���f���_�����@�G��Ĳ�s݋%��޹��\�k
g����]�Pb/$�=�Ui�L辖������z{V��5w�\��ޭ3��W�<X��!>�u��Vz���17&�� ��s]m2����([kϐsE`M��޽��k>�|&�ҿ^PB;nR�����TK��&r���΁��8�램�q��w���޹Qw�nѥӝyrvǑ��?؀��!�U��t~�T�Y��9e5�:���ł^����hy��7v�V���Q�;Ж2��*��o��.�9�����zw���'�ޛ�ģ���~5��LU���^��2���d�tݟ�wkij���9	z��w�k����X��i���bo7PX�0/Rg�n����t4&t�"Z2$���[Y�|臣���H��"JY�:=�d��������&�KGR�[-�7��]zr�L����؉��x�7j~���ʃ��þKj�|�zaWf�@�NQ�V9DY=4	O���H��|��0���q��r2�j����e5Fu�B����IM��Y��/�z@
)5��&{W�뚦��(M��T����7�?��P�j���A�8Y��f��;�Ԧ�Qf��f��5�����q5����e뫩MT�ٵ�W�\��qn܅���
�?[A��庻��p�Hr�����N�uu��]��N�Re..K��-Q3���ٕc-�]���G�˽�+��by�R~ 6��c�R4��与j�>����J?w:m��1nL���i�L����U�EU�E��pDj�2��
G����F諩��$r���	#�M���zv�1�e����Eq7J�gʀ垉4c�+�3q��)���A�z�R0(QFb�z.X����\+�4Y_;�FJ�=��m� ��ss݃r��d����Lh���F��nɧ��C��g��Wɺ(G�u0�U?���񰉲�f��Go�%eI�U��c�[��O����A��ӱ��4�2�5s}�PU	���2+H*Z��4��D��L6W����qx�G�度��8�����7X���8TiUr���G��]B��M߲���1�z�{&��e�eO��l��չ�����$�/
\h�vCD9
v�g��a�=�?���=�!=��qX��]�+�4Sٵ���p���j�¸��,��m��d���e�Hݳ��ٸ	!�I�\'�C���[p9
�ܽ��14.�����KG�����L��c���ǟd�]�H����Z�A^Ek�9M�a<p��A�����)�g��P���&�k-�*�w.M��C�ef���L���{n��8Y��[�[�Q d�J�#�8�����3&�.��Wڊ,W��下�֜����;������BT�����;.C�'�f�^x�h!���YW����A3@�������Z�z9piy.?0]�k}=���zGWy�Ae�pv}��;��G�G3 ���14_��Q�a��2�2EKO�B%=I���=.�ö�9e�3�u�L��17�)�����辗��s\�$��ޔ�آ�yRQV��<�a~T���y�7���B������;!b��0�~U��t�a�@2W=�;JY]���p�UQ/��*k�&40�OH��H�O�{���j��D3��l׵c�8�`ʜK�����ӓkOv�a�k�[	�V0 �0{�G�j<��8��G 2� -����?�mv��r�p�����*P��H�v�e��!iG��T�e���!����c�1�����Gy�#��z;[��f��a�j�w!׺�헪��McO�T\���+�q�z��`�n�0�{���\T��L��k~=�#�����C��M��i�WA��D�	�`��w� �u�jj�����ʵι.G��rv�����x��*�q���OR��M�����)��c��KdgŅ��r�'#��٭�i=�`����voи��[��g�w�k͸u����^	d[c���C�r�Dԗ��{�:^ǹaD`ݏ�N�#x�7��rk褠�b^����o���}���V�: �6�����5�T?�E����2�ܘ��V�٢k�����(IY-� ?fC(%h�������\�>5W���~����������Zuj݋4F�^�@��f�$0��EM��R��_/��^F�����/���P:�.ٺ!��m�G��A��?2`D�� pZ^��	5pA���:���~�˹�=kO�����;ҢP�;!�Xnm��"NE�c ڜEܱ���4����,\��ܔ����#�p&��;�A���b�<�ݬ���(���z���B�ݟ��M)�pO����	�9ܠB��
�N�0�X$�M,4
6�l�Z�@0�qH�7�F�M��|6g=�	F�$�+����/r�ŢY F����ۭ�<�7��!u�-�!c؈�9�9�yA�0��aÇ���xôPo�PR,,�T0sJޝS�s�M���3��N���.��@{v�s��0�x��U���X��sG_�̜M/9�:Nϗ\� ��3
���0�+tعR��0��)�Z;���V��.�8�`���a���
��g���x͇~|o��r>W�ύ��A���o�y�����<��c�p^��W���C!���>|`Z�=Wo��k�{���o����i���[���B\*��wC³�_��ч=�p���f���4xR��'}>���P&�ˇ��oiC�ɇG�C��q����bH��t���A�|�|�ob����0��?���=-$�x�=e\8>|��7�'l�S~t؋���V`���#�F�/ͺo勭�E`�@<(!�uB�0�C���_��Dˏ?���8�i���txpe�<7��7w��B���F�8V��OWxbCh���܊��:�}_���܃�G�����[xn�o��s|x�?<�M}@��E��WtH]ۇ_�	�����ȏ?.�]ژ����xB��k���	-�u������^�c����$��S���������s��������_�>�����	���Կ��|��Y~F���K�'��).0�6{�l6��d��S�̽L�5d�0YO����`4��X.��F0���3�N�a:.���4͔ISr���M�{0�`��)9�-�p�o,(uP6j���aa!yt&jv�Y�������v�?���Xڂ@!�-#`��T�RF�HVo$�M��v'1	v���g�
��\ڹqP�mc�:���D�l�lZ�h���LI�6�=v��$X��@�Y(-0�v�>,]F�/X�!����`X�0)'��J�/}�y�ht�Oy�&N�2�`�fr^�ܠ"984�V���L�ڟ7�8���B����q"Y9�3;L�`Z�:�X�B_h�����%;'�,F�����+�\v=��vZ#o�ᬂE��Y8�<�����yܿ�`.`A��z��f? ��94g�x�D(`�MB�x�V`s��zq�:����>�8b0If	x�;B<-!�EΏ%�/�M �$��*9��МZ�Y�ٮ�>��H6�������`���:�V��оN~�b�Je"�?��X�3����k��5�������֝㓣#�;� v"��i��^����RѮ�;���M������CiW$�4��/Ϗ,f.��+���K����Y%S;�M��m����0���
v�`e��5��ST���ڟ���w�m(ȰQm��|T����]}����������K�w2�~���^�,����^���_�G���X���_M��ɏ�Kx�ț�������(�_���������j���A����?c�t�dz�dP!����:�og'��\'͖J́0���ҡ}#��/��a9����n�G�3�O�u��F��z�:�E�W�e	��4����,�n��O�Sͩ���)����%�c��O-����Ћa���@���;�Ý ��� ޘB��a�����	��x�0�c�1���a��?��g&:�a
��?Z�;A2�B²ۅ�F�ưV�b���`�o0�w^	|I(�b�#��HK _0uK _x�L7�!��=֟���8�O��;y��W� �7��ʈsj�Q����\��7v6��T�Ƚ8���`�i@�0��v��i�Og*�����	f)ƈ�!&/KȦ���&��5��uBj�e?�����B�ti[���������?�����ga��X��΋F��@�h�|���Lz���P`��S�$�Z�(�<�ՕI�h�͛�@�f挩�H������� �|(9-~p��*����<�X4"���	�U���q�.Y�-�_�nDݡ���/n�5�E�5_#<��Y��i����t͇i"=���R����l8�F{p",�_Q6�JL3�$���a��[%g��Z��^~����Y|(c���ݟ0R���]�}��5��E��v�o�$��y�h�2��d��9�0c7<�-r�<�T�.^���mz�"��F�g2��p�L_
G�����Pl���Cy#R<.����W(�ġ�]$0�g��K��G�s�C��琑�3�N�B�����˝�8M�n@B����e���,���e8y}���_�m��	�E����LV_��$r��i�N|ߞ%7��O�!j�px�wU��� ��q����R��&)%EH�q��S�"�YB�e���FV�#��n��|����5���(9H�7I۩��I�����C�~�@>�����.4��#��{�6pI�}�$5�[?#7F����I�(���dPT���Qj5�����بO��IQ��_$�D��/"�j��(�G�m3�-�����Ѩ����QO~�F��*�o /GM��&����E��Q%m��U�@HsT�J���[��{| �wT[I?�P���v�� }�}�O#\��z/�6k��22�=n8�#Z��rw����du����@��Ƿk�{~y$��;Hu4����OEh�%����h��9B6Pxgt��dr$ڷWI��6w%�F7,I!m�nAA~�^�~=��AE75�b�f ��q��13�ɸ��|2%f���%�Ն�9��K��-��Y�'dIL[	!+b@�l�q��7f��r4��8i��q[�8�Uhp��n��{5���r�����HZ���?vW�.2"�ņɸX�-���ܱn�`��S�>�9�oil-�wn��$���*�#��l"�c���۱��g���$������6���ĺ�����䐏(���Gv���q�2<����8QI6u��~��G6���6"���7��ƥNq�yq;��'��|#F�eqmC���q��BvĹ��!�|W.�q���ɩ8����>��c����0���;M���)���;��	I�w;Q���#7����Lķ��O��7��r[�[L#9�s��!wѫ�����Đ{�� �?�5LD��۷/1��t�M�߯_?R?`� R�m~�����S��z+y6�z)~�U|\\���1�=~ԨQ�.~̘1�P��0vތ;v,i����	&���999��I�&����\�W(�R��ɓ�O�S�Gb����0c��=���#7$<���Kx衇������/dX��dd�V�%w$$%%�		EEE$/�Z��` �%��f���B���F�	������HyByy9�Hx��G���.]��'�q�$����,K���!+�͛G6$<��d{H]�SO=E%,Z�����x�bҐ��ϒ�J%�(a�ҥ�\²e�HK��/�L�MX�b���r�J�S5kH�bݺu$Y�q�F�]�y�fr�b۶m�St�ޝܢعs'�ؽ{7�T��Ց����# y�C��i�7�x�ܧ8z�(���رcDP�8q�iiiĪx�w�S���9���&2O���'~�!Y�8s�Y�8{�,Y���O����%��ϟ'u���trP��_�zEKKyGq����o�!).^�H�)������O�U�����ʕ+�'�իWIl"�CHR"�-�"��NKnJ�@nI��NT�ȇ�q���|xg"��]�ȇ�$">��|�p"�aq"�9�Б�|�H"�aU"���ȇ���KD>|9�pu"��D�Ý�ȇ���$"OD>|7���D�ÿ%"�OD>�*��D��ˉȇ�D���$��.IȇiIȇ7&!�OB>��|8<	�pT���$���$�û���IB>| 	���$���$�Cs�#	��Iȇ�Iȇ�$�ÅIȇ�%!���|�:	�pS���$��}IȇG���%!�LB><��|�q���$�ï���KB>���|�KB>�OF>쒌|�#��O2�a�d��A�ȇÓ�G%#�MF>�NF>�;��d���������M�ȇ�d�ÿ&#V&#���&#>��|�r2���d�Í�ȇ;���&#NF><��|x2��T2����ȇ瓑�JF>�.���"�B��o��tM9�p��N�rW��)>q�}�ϼ��S�f�%w�4<��䤸o+$SR��O�͚E�)mг攆�3�bo#�)w�J�N��E�}>��� �פ��攋_. ;S|��"�Rھ�!GR޴��)�SȻ)_~y�4��.~O����)m�/Hl��#��Gw�\ҿ�#W	��w��dQwR���Cdf�������e!��ln����ˡo}dn����E]^8�@�u�W���.a����1���Ǻ4��^�]0��K9̀-]��VI~����M��}\Iһ6���]��dt�+W�#�]��}roׅm	OaCWߞ#��շe/�ӵ����ݵa��lWw�@Vt�-/'����k�+9ֵ���|��}�r�+�c��뼓W�ծ�>-Q���6�[Y���ܢ|��n�����ȝ���K�=��ێ~B,ʷ��������B嫻�r��oS�|^���'�mmM�CeC�.r^�v���J�E�+U*�S^��%�K�Y�u{�����)��ԠT�^2R�hĘT_�N2>�m�Z���0x!����[H�OE�TLE�ў�o���"�[�TjSAy)u�=dcj�h7ٛ���,y3uc��|�����|���7�����&�R��9�t��W}�M7r�2�[n�;�ݎ��!S��p��<��{�R����9b��_���z������n����ѿ�e������d3�N݃���]A��ְ�M����!_t# ����?�������n�$����ߑ��}�H��;�n#��� �4������Մ�����m/2�{C!�vw?H�_��@[�S�ֽm<!�uoz]w�̈́,����C�bw_���{[y+�ؽA<AvvwOr�׻��l '�?������/�^ �tG�j��H�#�_�g�A�v�
�ڥ����}{l�����֣�6��Y�3��ʍ��G����Ѡw���I&���}{������^���;{��-ӣa�r���T �h��9��w�m�I��z�y���u��^&{��Fr��ߖ��������D��mi#	i�6�.i�"7鑶��%�m�h՛�^�#C�i##�����M���Mr��dˣ6\ALk�5�4�c���dxq���bMk۵�<����d~��g�4�9�RZn���K���Fv��V�@��&'��.8�ve��|��[ ����*��i��_i��,r5�_�&	=���#�=g�^!}zNi[L���aF����}�F4Խ�g����=����D�������W9���lsN sz6�����I���=>L��9���
�PΞ�n#�{�4�}=ﲸ���al���|��gyq9�S|�����t�����e�B��M�]{�9pC�W@�e�q=��f��TG��^m���^0�L��v�Ƚ��ԕz0'�E��p�"`N<�kb�.�����G6�zhS��k��r��(�����]Hc/���T����G��+>��~�V�y/���W�f�]/H�+��@�Ĥ7��IIwC	{����H_�Ho{h��05�d��G�B�H�m$�	؃L'`>�N�,N'`Z��*ۈ3��[H��}�%O��ݶ�,MoP��U�����������N��}ٟ�ּ�x��=K�Jw?VD��˦�t:΀���%���.��w:��I��:����	F�@4f;�>ߧ�ឌ0�*̧�e~������⡜ ��B`u��V���b/5{e�BA,H�hÕr�ʐ�*���ߐ���O0�f�^�i�&ɬ�@�i���4���1bl�{E�(�I��n{��K�^��a5:K%I�2��*��`&���	v��(#���:f\ѱ[�M3B`U��1�����]BAP�ArIV����R�����"��\d�J+���m�� 2�* �P��&�d&Z'Ϝꪨ��n&����;1%�$�N0[���|�^U�W�e�'Yy��������A��d�X0�y
O5�%B0uЛ�ίj�W��Le��A0#V���؟U�u!`F�
��!0�z���M�qP0P����{2�|�0�:���NG�	��Z8����½�pof�W��l�$�y�f�e�h6�� �
@� �I��'+m���B=�P�M�n�ƒI�by,��X�C�LR$Z�B��* eAUT�L2ш�I쉒U��Y9�z�ȓb^4�
%�D&�%��%,��[�ɠ���j�fR������*����X*��bltFP7���g���CU�f/�7c${�b���5����eS1\*�K%2\*�K�p�.åb�TK�f�����R�q���R3\j�K�p�.�0���d�2�L�+SN�pe2\�W&Õ�p�#���H�k$�5��)�d�F2\#����p�b�F1\��Q�(�k�����p�b�X�h�k4�5���p�f�F3\���r>�k4��<c�1��k�5���p�a��0\c����2\YWÕ�pe1\YWÕ�pe1\Y�M1w�L�3W�$VF��0�I���`��!��P{��+��F��(��^c؋�ɲ�.å�.åb�T���R1\*���W3\j�K�p��8�K�p�.5åf��K��pe2\�W&Õ)'a�2�L�+���d�X���H�k$�5���p��S2\#���H��E�b�F1\��Q�(�k�5J��p�b�F1\,l4�5���p�f�F3\����h9�5��b�1��k�5���p�a��0\c�1rv�Kv�,�+���b���,�+���b��.`v�d�:�4 d U R�L�+��*�3�����@&�3�Dތ�E ��� ���D�X"b�du27��T�f�Lb��u3�K�^j��$F�D���$_`z���}�^U�W��o��M���Jw�Ţ")ܓ�S���a�L����(#���:ʹ�9Q@AP�APFԚý���v~u;{t�dd���m4�)+�� �
�� (S���8#ԣ
��C=��~Ֆ�d�/ԓ�S���a>?ʀ���TW��.Ɛ�~oF;���_��/�mog�zT�u��h�B�d�h��I�n�w�P����*If��!�U�[-�3�����J �m�@�x	�d��Ta>u��O`��j1
a��0�*̧����C�zV�[pOCh������ A�7Yԙ|�h��ix@6��	3��� �
�� M-i��M4�)|	?Kb�{��Q�zԡ�Lb����~�Q��g�$4D	5G��|a��� ���DbF�$��l�J��*�F*3V�aPFTAuD�3$�'$�$�$���F!(Ѩ��Q ��� ��G�7�|�^U�W�e��|����½�p/b��N��B�	�V?�QT�2��*��`&�V����Pk���B%��
U��a�NuU�US�K�:ٌ���e��ERy0Y�ad�[��V���dŚ ;'�U� �UAP1��g�2 eAUT�L2����fcӅM�)l�$a���<5L��:�|\��y�;�k6���A��� �
@� D�l��W��V�o���d�P_�ST`v
LL�9)0�U ��� ��r.:a�,˄,Ʉ,Ǆ,��5�f t2�������,Dd���U�G����2d��%C&Ȑ��:��!;�AvԀ���P��H�xY~g��P�� �x�$�2�J~��7${Ph؃����(a�UAY"'BdD�|��z��37��T�f/L����M�A N�,8e=�)�NY;pʊSX��Z�"RVƶ��;/�Cq��P-�����L���9uʌ��gp��,f0����B�?t;A�[��qK:�[z켈����K�V/�������N`�[9��NNr�-�0N�7���c�l8�c'b�����4��qV��^6�CBh����r�p�f��c[#����z��ͧ���-�͆~3��uouA��LR	
N	ʈ�BZ���_�y�?�=Y3��hG�h���vz
ۿ��V��^�����˕���j��*i�� 7Rz������!_k'��ۆ�b�|�?���;c�O�u���@~�;��I<�7K�Ʈ������ڟ�9��B�]?xz���h��}'��gg�^�>���-o'�_y�ײ��+��Oj��*���ɠbp�`�(�F<C���>,/ /��~r�M�_7��?ķߎ�>�]l�x���
s���W�O�Y@�o�7y�!4����#T���e#���Q$�qL���m}�ȯ���0����C��f[�!!("�i��F�����E>^��4������3���96�M�ס�a ��o?@:��Y}`>�����QH.�է��`�1�I�ì�x	DM�7�D��V4C:��l������bq� �:猡����` �Q���v�-����ᩢ8\q�:�M����B���u�r�MXnĤ@�A���z�m(� 	G.�Jev�h���������;3�=X�[n��<Cc�M�:]~)��Fg���H���~�5:lag�~�}@��>ŏ'���?$=�X�f���K#QY-�.F��¯cإ+Z�8�������eJ!}��ɟ7��(���蘈gR#��Duv�����j��=4{Ə�ǳ��� �������~?�t�F���cQRQ�:�Ix�?y�A�oʜ࿯�\�Ev��0�ˆ0��z9j�<+�Kz;���u0IE�̳����z�ɠ��/�#H�`�v�0�ѽG0�q�&��é��F�����a��#�`s���ۆp�d�T��;S3)���3
6=迅2�k�x��B��׋��D��g~&�b�?�$H�,����!��	қ�r�N��f�msZ	���k@t%��\yE�����fRhp{a�u��(f���MEi8��"H��1ϖ���cYQa��۩�ߎՂ��1��{v�*���a��+���!L�3 94�!�5x�=&�!6,��1oI��9#�(ʗw��X(�B�#>��J�a֡��p|f��Y�a���DRX��1L�X�B����0S�t��W(����0k��ֲ�e�EH��;��i����|��Ц~e1,��!+t|h�!�U�1,B=��a���5Zm^�E��N�&��Y'Ӹ94��c�	�	�!�54,�x"���]��fX��cX�q���jQ�Q$F
3v�!]�zE��"��cX�~+��oźaBy/6FH����S���tL��#��v���Gh��Q���Bǰ��~��C�7�xC�޿+�N�P_1Bۋ�^,�&����0C�1-Fh1�X#�ׯo
	�%������n�Y�ׯ���u���c�"�C��a�P_C>5��Gzh�̻=C���f��W�<d�u��P�"(�����u��!�nmO��q�0D���Wj�����O���C݌���r#_�5F�_cYb���whX>5F�?�q�1E(�)l�P>S^3ɼ�'4�<T�U�1<���f���b�:ο&kGYg�0~M��o_���#��9B_����e1GhSs�1h�п���o{L�0��6�cX>0G�%m��:��&�)4�֑$;�a|�m�԰��C�t��h3��>��]X�6�؆RS%:<�#��1�)��C�5B�X#��5B_Z#�����w�+�,saa���"��Mۑ7l����a���Jf�<._�6Vm��c�&˒~aa���-�}i���6S�0>Bجa�a��m��6;B��c��"�+[��E�I[�1m��CNF�H�<,��far��~�������&�K�����;��=B��#��=B��#��=�L�Ghg�=B�"���)��C^�2R�8rD��<��c�$��["E
�h��F��J�_�B��T�8J#�(��8�`��Ďv�3���+�3��[x���1���¨xjF�8,,���>V�V��z�
�X���|-���b�6�Qlfs[w��PJ��z��h���M4[��)��%�����akm1L�cY�,�7
��̎�:���qq�^�ltC�˟�c6vv<����ƌo�3{��xf�K`6�%�����	�V�`��B�?�P0�ӧ`v����Kd�_�$f�=���I�vJHf��xxc��&ϢӔ����M��f{�0{�J
��o��t�?va:�.L�}����_]����L�4ve��rW�#�J&�*�,���u}S�>V��t��S�޵;��K?�2}hl7��uc���n-6��;�=vgz��C��K6�?ك���=�<~K��r��ilN{=��c��l�x�'�#j{2�޵��kb/&�-�����d�#���+70�7��_|&w��0Ys�O����F&?��,Xx#���xL���ۨ�l<��/Cs��q��o��ﭾ�=�n��8o抍������VN'�9�$�9��3�g3�:�a�����\��3Ug�8SÝ�>3�k�ټ�;Sټ����ܙ������w5�<3�k��\�R֜�j� �� ����̷�yK��0�LM�>�����5o:Sݼ#w4o?S9�L*)�M�I4k���-�V4�8�m�g�X.9� e7�̂�pV~6gp���/2z�$�#y�A�s������f ���[u��3:�T���W6�⚞l��x�� ׸�鉦9�;��\�T��T��vpM�u��`l����w6nk�߸�k�߸����}��PSUS���� {��5�F&��?i��@�a�L"g��v+>�x������]s��Y�]sл�»��<�];ϻf���@c�A�!�O�b�1�bX���Y.��z׼F�#��޵�p�W�"����y���w{��|�{`?�_��3�@��E��{`����"��Z2Q4s����eTء�f	�9�;Z[b�١�̳ģ��.��W��2�9�d��凑�$h�2�h�_*�R�h389�T�����iz�Jf�؁zQg���N+���tѳ���@N�w�$�^�x��Tz`~��7�&�|H6�L�_��l�Wp����Ւ�h��s�3�o���y�Y��h�>�YQ(m�zγS�F�K9q *�htp��N;��:u�!�@���8�N4qNHQj:���a��N��C,�	F;_,X�0�,��.p�$��г�
��㊌�:� CU�ZjE+p��(������Fz�,d3��j��i��$�0�`�g���� �<�L�"H8�p����8�!����� ��*y^��t'^��e�V?��|��擯��}r/wr��'w�[}rwr����n�� r���8���[s�܊�[On�:��䁓����Wr'_8�	R�8y������w�<����f� �/;~P���^���6���8��}�9�Z��7}I⎺D���|�f��xʬ��8�d�����N�6���6��нEb�wpB�^,���+� |�muآ�����J�b�(pz�~oν�
=	�M�/�����(lA���c�鍍�kA����. �'�.8���Sg�1ou��3��]yvA?ݼ��B�Os���3�A$�=�F��${- A�>����:����yיJ��U�z.$!=�.�_d ��0��yH�� țwA����,��Ƚ�`���`�8�x��� BGA�A]�h��R㆑{%�G-4�g#U����?�@�p��+����0d,V��"�:+�<H�Y�ݎB�X*ڠ���8�7e\#W��0n�@��!B�ߩw�> ��Ѥ������@�E:�g�]o�xV���l��Ez��z6�P��6/�~�E/Y�� �
�"0�t�a��V��Lz`CIDv�Oo!�^/!#6�s��$`�2�l�yVKyJ�\jƏ�B�	X�������x^�g�Ņ�U���� V�i����Y��)kk�s��ӟ�Cl%KJ	��:�j6��n��n���x7�n�yfó��d��XЋ�U�ݰλ�V�=�t�w���\�ݰͻ� ������*����N�4q��i	�D;t6�,���bl�b=Ęh�\XM��z�Ƚ�:>�x��oǐ�^��������h���0&O?s�i���kO�;�
wz�����N/�N/:���K��gO���^�βӫNo8�*��O��N?I�@������y0-Fk� /�~q�:諾��s���ѳ̻
��UK��yW�A���&��
�e��|�R�:�-45��+�yW�`1˼��,pA�cFpyWm`�w������ж6� �a��.����о9�NN_�ݎ�ї�<��0F�={�Z�g��~�N�ٯ��!(���N&F+w�`�	F�z�S4{�A<�@-�7�gg!R�C�9��ԊS�8p�����F�T݇���Z}j��<��FH��W ���+!���Cܩ��ցw��s>t��=kPg��ٳ��r�z+�4��잃�<;�&����g�"{����9�Vl��<H+F������9$����T�|q��0ۡm�(��&�:i9_Q}���|����W�~���|�:�|Ŋ�O���t��}��i�ŵ�|���Ư�\�24d��� ��JaЉ�]�S���%���;����P.r:�/�Pp:��(��?�a�@�7��YУR���7�EN���N6����D�188��S�	#4�e��l+��sU/��z�\ղsU�U���U-9W��z^�3 qԷ�A���sUKiH�F��u���	Bb�sԳ��k���;�vl���Aap�B�L��U,y�w��m4S%�͵�����ݱ����
��]CsȨ���U^^����7�-��9�¶������sP5竝˿Y��L~���霅V'�k��8���aR��N���sR)H�`vB�M��<VP�@��9ʆp�Q�;�<M��a�d��}t��Aǃ�Q$h�v�d�fI\�
_��B��p�V�f9l"̄|������G���7���xka���5@���l{�����Vަ�ߨ����l�:z�0�aF�h-J��Ҏ��׋�S� �Va�����(ZF��[��=Ը�kz�]��T�T	�>0v��Ɓ�D͟�\�|�ڍ���v{w���Z�ݵλk�w�!��ݵ��:�ݵʻ�o���
�4bM�BXR��]鞤h!&�X�w��%�]�"D#!�&�-�pn��ܹ���un�V�h��+�-�sn����-?�|�T�1��:��5�o:�|%��#�3|h~$A�Ȟ�0��z�BO ���A=��v�,_�$�*�!�*65d�v��GI�.OU-^ ��F��FЂ`��6Yt�@�A������ᤁ%��,T�����L0���Y����"`�B^'x�*�.�*��)���X�P]�273�q��,�̌Nss0zJ��d;&р��`l�Z�ҋ還�6j��H1����
6��Yo;����S��ּSq����g�g�ٳ٦/��z��vzv���U/�W��(��(|�j� �A~��%0�J�2�#�LVѳ7��o���\���k�旅�M������<�������)�M�M0�oZE����QnHCl��nz��b��ݴλi5����@t�����u�j�s�u;��z�Ձ�Y��U�]�Ļn�쥱��ƻn�w=�d�<�|����������@��n���@\;���x�mdy�RO%*�-��[����d�fB��4�HB}\�&h�&���Gk��/��G�r��`P�����0+9
9��E����Y_��p�0�*p��Q���5[���0?t���z�9��zVJ g�b9��Ы�ksV�t's��GE;��D*����Jy#�.�x6@n�f�g%���[�y�ʳ�y@(�I60!i`7�g�g���9�`p ��=��@��0�,���2-h��oϫԄ��%;�%������%�W�0y���,��l��h�����^�4�4�q[��\�ډ2xOc]��"���6�5U6�i�j��׸�q���l5U�Uӂ���xG��q/�T����� �A�SMs����b
)W�kQ�vS��V*�j�[�9�CΟj
-Td�Q��&\u��������4�mf���_D��#*�DY:A�����K1�]��a������1�z���c6����#�U:��]fu��6����,40w�)0���Gk��3�xV����e%�1:����%�����x��.W#r�f1f�Y���� 5�TZH=�֭	W�  ����ј��p���Y��2˳�q-L��^�ys���4�^�i��^:����
�n�\|^�6-�>���mة���1������o��3v7h���u�*5��i��p��ht�G�@����
\J��1�m�e��T=הL�jw�HV��
A�P\Y=�l���G_u��� �rf�8i�:�-�[���,�nY	���wpĖ�g�� A��»e�w�<���-5�-�Їiw0tOR��\�[��n�Ơ%47ô��ߍ�����ܶλ}u!ö��z�-c�U�m�0Cw��x�m�G��/�%,r+E�Ż�}Ø5t���ֽ��;�[��[���u޺�޺W�{x�6P�bLS��[����@�]޺�Ի���u�4�3�����u޺���{�f\I��%o�^o�<�p��n	M���\L�A dt��K)��4�K~���4P�)�4�w ,����Jȼ�֊�\�����e� �z�Vy���TҔ�nnH�w{�!����v%�io56�y�[�R�[�{�
Z��{+�@{Yܴ�P�-޺=~��,i���@(�r
�J˶�v��%���D��&��/�^ֲ�RlЅO�vy��ܻ���-�����NJk)-Ty>��2�Ŵ3XSl��9߻��l�w.�n��-�y��?궒�Qw4��ip�xЊ�<�t������t�����;��D�iy��� �l��9����^�տ"y��6�Yә�N��.�ғ��6_
��a���!܉ef�e�&�Kq�q-�K���sM�5�A��`�ܦ'������MUhK@�:�q(چ�o*s ����R��Lu��5�E qN�nz�qG?r��삏�q��5Ώ���A\F�	!p����|��5O���y�G�>�5o�Eγ�Tpg枭�80i�����wP3lS��������4ЈգST�N	To\1{^S]n�J'������+��v������g!ZE�ق��-y�J#O�s����0zV#��^�+TkO��kX��^���O/;��ú�����9�;�<��s�_�,�p�j)[��v,��g��]��l<��=���\��6��h��ѳ�������_�����'_���U-s|^W���U-�6~~���s*;M�E�k��u���%��~�-���2"C��9j����P�P�����,��d�,��6�K˜�,����?���?�0���K���I�	�bK��a���jN�r9_��ԙ3�A6�vp�P#M=o38,᧓�|<���7%�ݫ��ˆ\6�^svv��aR�|�U*��~3�.3��>�Ȏ%�����D<I�����<1������mc��dgw3��$��c��rۦIvF�d�5�d(��8�D-E�q�A�dZ�XR���.0�S���E�E�(��X�ڢ�v��_�a[��{ν$E^ROˏ$�̍�s�}�{��K���"�>�? Q��v/�k�õT�Ι/!���
���sb�^9м���<�9x�G���?s�����}y����;?f����Q����ˣ��˗G�߄�s���#�v?Ys?���J�f�"܃�!�w���c,4P�<0Z1���S��؝�N�^��[n���&"���xz�vU�����'�?��m�u�S�H�����Ձ�Ӿ�M�����nd��l����������鳆��?E�U��:�V~�
������@
$:}�3s�j1$>W��O�!9�	�̩�xv/��׍�8߿�XK�cǏM:B�\���axө����ۅ���`@�~d~aN�hx��ް�N�J����wD�h��5gh��cx�e6�}K����4|��o�(&�<��F
s�p`�9�����<R4�����TP�!x�/��z;�C�t|���l�ínowx��eӯd<�_�x��SӨ�RgP���DW�|H0����1|�@��������nsX�C�T޹�yb뇻l���:��<ʟ��|����
��#0�@���mљ�&�oJ{���Gw>�����wA����ݍ���z���p��u-!V|߸9�8�H��3��{./Q��Mҩ UE�=��7�V��7	��Ǣt���:ЄOZ�čjY)H�5YC{}<N*��-D��ڞ�"�N�oڐ� �A��0�������4'H��Cb��Oz>�	���g������p�����s��L�yx��l�sw6�ޞM<�gϽ��{�^��+ʹތ:�3�㦳:���wk��l�y8��ܽuo�|x��L�u����òf����SN��Zp"x�z�sw&�t�Ç��w�����8%N=��>
B���rG@8n�wg�ww�>�M<��$����c6�?qW�h�mR3��^�j[���AL�F�v� ;z�1��l�0k�&�F�jYv �NS��١��*����?���C�N�w�k�z��q�r�/t�Խ���Έ�������)x�t_T�v�nh��*2r�֝H��"Ky꿿��s��h��ك�6���� E!d��_��)�<^�+T��zC}׳�6I5dә����A��,Xm��z^����kL��<��e8B��
А�%��O�����z�^�D�0@��	�A00�	�P/mP4?�&���Ӑ�J�-z�����{�º�1�:�x���~횐�u���  h�P2�OG�܀g���*����ɘ�E�X��/h���g�2򾗍��A���9��+���&~�d�Y8��+����]9��mt��������Ҿ�H��ȈW�qyP���au��e;p	���Wτ�WshCf2V���	��(cf�Qxfhd��X�����՛��SIp=�~���~S����eC���u����c���]�5x5F�L�N���8�����-d &W�^���uVQ��^��\#?�p���Q�;�!�j:$�"��;��at�8�9$'Ϸ��iN�ۆ �M��T��0�!M�ƅ�<�T�	�������� ��G�O�t?�+��3x����G?������_0O��<���|�y��K������غ�;l����mӳ����R1����/������t������/�ޡ������S��S`�ә��MF/}���������u��x4lcH���m�^tL����k����U�GO���ݠk{��Ւ�j����Mb�����5_�mkoSZ��YI�T�G��D(�kbY���.w���9����d9���� ���G1��5�����k���>���i����g+�-�~~۠m���a��m}�mu�[u�Z�����0=�GվF>��:����a<�ۿ���C��X������|�7\{{�њ��A�������Т�@Ȼ�������-B�� ~���e��_�;���������-�߾�vmjUݶA_����	3r��!���kzM�04t��O�=�Gkb����4��3ݙQ�>�,�����>�m�[��Q�&=��w��
�����wF�ٖd�����F��M�EA�����f�W�Hz��d򈬀�ÆdWΖ������UϤ����a��PEÝ>�,$8i�Ekw��.W3~�/lۮe	��pcO�T�=tP�n�3�5������c�������{�{wS�){�F��ӽx��H&\_��y�����^ޔ���6����1��:��&9R���s���`�=K,JvÅ{�.h���~�}T�$�D���^[ 1^ ������f@>`�e�=���s� x�޿����M����Z�ap��z��T|IM��m�����\�;���)y�����t��>sW��M�
�Ұe��M)ή{E�{�P�G��"��u'�����^��A�T��c����}q�ё����+gT��U�"Ӄ2JV"�>`�Nc�e�BA)������q1�$U֤,o64�v�@TŴ�!�|5�Σ
RQ��]�Ϯ��T\�ܑ�*d�C*%���)�fu�=k��r�R6$��!S֮)PI�L����l�r>��Cۄ���Y��F�P��.�|&�uQ��Bo�`�0���d��ݦiu���%E]�*i�݈Tɺ�3�aA`>�*I���]Q��@�I���B���j���C����mr���g#�7���8��V�M�4j6��0JV�n�"i�Е�v���X�"���m};������=�H�\AR�ns��"/*��[<P�� �\�
b^�_��hChх#P�G�:B�jE��%�J��6̫�He=Q[�&���VeMD���"�VD8U��J�C��j��@��!��5�,����Z\�2p��AS��΅�Ă�g��V���
���^�ǡr"6N��G�P2"8��䴤A=v͚�8�! ���kx���GC�d4,��䃲y�`5"<Z)*
2i�mq����,���Y>ʴX�1Κ���
�VE��w�*[%UV4۴8ѐ��
^�\�N)�"6-�m�q�9�rd/"���E���'�u;U�"��
1S|N+(�P �P@ED`Q�d�+�kN�(z_��~Y��4�$�^ϋ�S0�FKǮIF��d��9�Pt�F�gѼ��U� q�����*^�b�)Ij�	;Ou/��6r���s <��x�r�]^�U�Ee��h�
+���ꭘ�f*EI^S���چ�c�\/��2��Nӂ���b)'���%��p�P�PH{��▘> �x�7S���J���~��Ԑ>���6>�����R̊���e�hi�bE�2U�-z�֡2m�~A��c�`�*Uo��\~���x���*T[��X\��h���1�,CmG�
J�!a�t�\Aƾ��3���X���r�FA����q� ���} 88��D`���'�p?���M��)}8ư=��@4�8\:xp�.ˊ*���Pıl=�X{�oj��[P~�b�Wt]�
-��
�C2-f6"+��=��I�P���oKբ���6"��!ٹ�� g� ��L��9���<l�b����Y���@h#�'b@�L��z�z������T�@���A#L���9��L��u���
O:��Aw�j���B$eMU���h�%� P���T�4m���0�Xֈ���EE�mˎ�ؔ ľ!�T��t�d,oT�P!؊���V^�@���E����h$�LgrQ84l����a�Z����wg�b�!t#�ojp���05��P����T�H��3��^����(q�H������^"�v���#YiD�*ʧe��Ѳf�d"�a0�!O��n��%���a!&�( �-k7v+.+HY�R�Ɵ5�F��x|��lL1(����$��VL�������%qy>�a�]�=�Tf�1R���t�p0R�y��}�ۤ!�;Q`���L�Y�+X9���r������<��&�ӱ��d�s1��@�{핕U)��
�GM��T-�iZ��v��T[,�!��"�M<����nl���qq��F%����%pZ��Um�$U�Q�*��m��a6i[����HU��vˈ�+ �FZʮ���N.��i�l#�L4`�\ mg/O�4�ƸY&�N�x���� ��0�]��c��D�Y���ի�`��&iY�����J薍7�k��-�ykaA�m�G_ #)$8<R@h���X�
���
YR8f�r��&K��k!4��QhD]�P^O� oHZ��CQ�r�0'�$�r��rF�Ƣ{��
	#V��JU�\3���ٶ�w�-.� ���n�&[����ι�@p1]V�Mbu�����)� �AUü�x)z�o�5	=膴U�3~�-��{���)�Y�`.q�Hc*���M��"N{��
h�0��w��g%9���[�\9D���C�K�] ɗ�[���+��y�,�E�Dd�\&W��WI�����:��&y�| �&�!�%�J~��{���o �{��&�F~�\'7�M�}�y��2ٓ�"��=�_!��m�!�C��ܮ�{�>y@����#�|L��ߏ�S��ǥ_��'���8�d�D���:�MR�)ـ��@�D!%���A�̟�y����������������������������������2��ϼ�����������+��\��r�/,�\\\L�[XZXZ��%
L��x����@�����~3s��&/�a�'G��������O�\�w��C�K��e�x�;m~<W���7����q�xؿS���]L&/..^\��'t�9|�w��]<�%��J�H$�K�t�BNW_�U-�����\s%�(� ��k��.��]�0]acׁ�<	�H/�
      const int other_index =
          CheckedDowncastToActualType<const Iterator>(&other)->index_;
      return index_ == other_index;
    }

   private:
    Iterator(const Iterator& other)
        : ParamIteratorInterface<T>(),
          base_(other.base_), value_(other.value_), index_(other.index_),
          step_(other.step_) {}

    // No implementation - assignment is unsupported.
    void operator=(const Iterator& other);

    const ParamGeneratorInterface<T>* const base_;
    T value_;
    int index_;
    const IncrementT step_;
  };  // class RangeGenerator::Iterator

  static int CalculateEndIndex(const T& begin,
                               const T& end,
                               const IncrementT& step) {
    int end_index = 0;
    for (T i = begin; i < end; i = i + step)
      end_index++;
    return end_index;
  }

  // No implementation - assignment is unsupported.
  void operator=(const RangeGenerator& other);

  const T begin_;
  const T end_;
  const IncrementT step_;
  // The index for the end() iterator. All the elements in the generated
  // sequence are indexed (0-based) to aid iterator comparison.
  const int end_index_;
};  // class RangeGenerator


// Generates values from a pair of STL-style iterators. Used in the
// ValuesIn() function. The elements are copied from the source range
// since the source can be located on the stack, and the generator
// is likely to persist beyond that stack frame.
template <typename T>
class ValuesInIteratorRangeGenerator : public ParamGeneratorInterface<T> {
 public:
  template <typename ForwardIterator>
  ValuesInIteratorRangeGenerator(ForwardIterator begin, ForwardIterator end)
      : container_(begin, end) {}
  virtual ~ValuesInIteratorRangeGenerator() {}

  virtual ParamIteratorInterface<T>* Begin() const {
    return new Iterator(this, container_.begin());
  }
  virtual ParamIteratorInterface<T>* End() const {
    return new Iterator(this, container_.end());
  }

 private:
  typedef typename ::std::vector<T> ContainerType;

  class Iterator : public ParamIteratorInterface<T> {
   public:
    Iterator(const ParamGeneratorInterface<T>* base,
             typename ContainerType::const_iterator iterator)
        :  base_(base), iterator_(iterator) {}
    virtual ~Iterator() {}

    virtual const ParamGeneratorInterface<T>* BaseGenerator() const {
      return base_;
    }
    virtual void Advance() {
      ++iterator_;
      value_.reset();
    }
    virtual ParamIteratorInterface<T>* Clone() const {
      return new Iterator(*this);
    }
    // We need to use cached value referenced by iterator_ because *iterator_
    // can return a temporary object (and of type other then T), so just
    // having "return &*iterator_;" doesn't work.
    // value_ is updated here and not in Advance() because Advance()
    // can advance iterator_ beyond the end of the range, and we cannot
    // detect that fact. The client code, on the other hand, is
    // responsible for not calling Current() on an out-of-range iterator.
    virtual const T* Current() const {
      if (value_.get() == NULL)
        value_.reset(new T(*iterator_));
      return value_.get();
    }
    virtual bool Equals(const ParamIteratorInterface<T>& other) const {
      // Having the same base generator guarantees that the other
      // iterator is of the same type and we can downcast.
      GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
          << "The program attempted to compare iterators "
          << "from different generators." << std::endl;
      return iterator_ ==
          CheckedDowncastToActualType<const Iterator>(&other)->iterator_;
    }

   private:
    Iterator(const Iterator& other)
          // The explicit constructor call suppresses a false warning
          // emitted by gcc when supplied with the -Wextra option.
        : ParamIteratorInterface<T>(),
          base_(other.base_),
          iterator_(other.iterator_) {}

    const ParamGeneratorInterface<T>* const base_;
    typename ContainerType::const_iterator iterator_;
    // A cached value of *iterator_. We keep it here to allow access by
    // pointer in the wrapping iterator's operator->().
    // value_ needs to be mutable to be accessed in Current().
    // Use of scoped_ptr helps manage cached value's lifetime,
    // which is bound by the lifespan of the iterator itself.
    mutable scoped_ptr<const T> value_;
  };  // class ValuesInIteratorRangeGenerator::Iterator

  // No implementation - assignment is unsupported.
  void operator=(const ValuesInIteratorRangeGenerator& other);

  const ContainerType container_;
};  // class ValuesInIteratorRangeGenerator

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Stores a parameter value and later creates tests parameterized with that
// value.
template <class TestClass>
class ParameterizedTestFactory : public TestFactoryBase {
 public:
  typedef typename TestClass::ParamType ParamType;
  explicit ParameterizedTestFactory(ParamType parameter) :
      parameter_(parameter) {}
  virtual Test* CreateTest() {
    TestClass::SetParam(&parameter_);
    return new TestClass();
  }

 private:
  const ParamType parameter_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestFactory);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// TestMetaFactoryBase is a base class for meta-factories that create
// test factories for passing into MakeAndRegisterTestInfo function.
template <class ParamType>
class TestMetaFactoryBase {
 public:
  virtual ~TestMetaFactoryBase() {}

  virtual TestFactoryBase* CreateTestFactory(ParamType parameter) = 0;
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// TestMetaFactory creates test factories for passing into
// MakeAndRegisterTestInfo function. Since MakeAndRegisterTestInfo receives
// ownership of test factory pointer, same factory object cannot be passed
// into that method twice. But ParameterizedTestCaseInfo is going to call
// it for each Test/Parameter value combination. Thus it needs meta factory
// creator class.
template <class TestCase>
class TestMetaFactory
    : public TestMetaFactoryBase<typename TestCase::ParamType> {
 public:
  typedef typename TestCase::ParamType ParamType;

  TestMetaFactory() {}

  virtual TestFactoryBase* CreateTestFactory(ParamType parameter) {
    return new ParameterizedTestFactory<TestCase>(parameter);
  }

 private:
  GTEST_DISALLOW_COPY_AND_ASSIGN_(TestMetaFactory);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseInfoBase is a generic interface
// to ParameterizedTestCaseInfo classes. ParameterizedTestCaseInfoBase
// accumulates test information provided by TEST_P macro invocations
// and generators provided by INSTANTIATE_TEST_CASE_P macro invocations
// and uses that information to register all resulting test instances
// in RegisterTests method. The ParameterizeTestCaseRegistry class holds
// a collection of pointers to the ParameterizedTestCaseInfo objects
// and calls RegisterTests() on each of them when asked.
class ParameterizedTestCaseInfoBase {
 public:
  virtual ~ParameterizedTestCaseInfoBase() {}

  // Base part of test case name for display purposes.
  virtual const String& GetTestCaseName() const = 0;
  // Test case id to verify identity.
  virtual TypeId GetTestCaseTypeId() const = 0;
  // UnitTest class invokes this method to register tests in this
  // test case right before running them in RUN_ALL_TESTS macro.
  // This method should not be called more then once on any single
  // instance of a ParameterizedTestCaseInfoBase derived class.
  virtual void RegisterTests() = 0;

 protected:
  ParameterizedTestCaseInfoBase() {}

 private:
  GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseInfoBase);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseInfo accumulates tests obtained from TEST_P
// macro invocations for a particular test case and generators
// obtained from INSTANTIATE_TEST_CASE_P macro invocations for that
// test case. It registers tests with all values generated by all
// generators when asked.
template <class TestCase>
class ParameterizedTestCaseInfo : public ParameterizedTestCaseInfoBase {
 public:
  // ParamType and GeneratorCreationFunc are private types but are required
  // for declarations of public methods AddTestPattern() and
  // AddTestCaseInstantiation().
  typedef typename TestCase::ParamType ParamType;
  // A function that returns an instance of appropriate generator type.
  typedef ParamGenerator<ParamType>(GeneratorCreationFunc)();

  explicit ParameterizedTestCaseInfo(const char* name)
      : test_case_name_(name) {}

  // Test case base name for display purposes.
  virtual const String& GetTestCaseName() const { return test_case_name_; }
  // Test case id to verify identity.
  virtual TypeId GetTestCaseTypeId() const { return GetTypeId<TestCase>(); }
  // TEST_P macro uses AddTestPattern() to record information
  // about a single test in a LocalTestInfo structure.
  // test_case_name is the base name of the test case (without invocation
  // prefix). test_base_name is the name of an individual test without
  // parameter index. For the test SequenceA/FooTest.DoBar/1 FooTest is
  // test case base name and DoBar is test base name.
  void AddTestPattern(const char* test_case_name,
                      const char* test_base_name,
                      TestMetaFactoryBase<ParamType>* meta_factory) {
    tests_.push_back(linked_ptr<TestInfo>(new TestInfo(test_case_name,
                                                       test_base_name,
                                                       meta_factory)));
  }
  // INSTANTIATE_TEST_CASE_P macro uses AddGenerator() to record information
  // about a generator.
  int AddTestCaseInstantiation(const char* instantiation_name,
                               GeneratorCreationFunc* func,
                               const char* /* file */,
                               int /* line */) {
    instantiations_.push_back(::std::make_pair(instantiation_name, func));
    return 0;  // Return value used only to run this method in namespace scope.
  }
  // UnitTest class invokes this method to register tests in this test case
  // test cases right before running tests in RUN_ALL_TESTS macro.
  // This method should not be called more then once on any single
  // instance of a ParameterizedTestCaseInfoBase derived class.
  // UnitTest has a guard to prevent from calling this method more then once.
  virtual void RegisterTests() {
    for (typename TestInfoContainer::iterator test_it = tests_.begin();
         test_it != tests_.end(); ++test_it) {
      linked_ptr<TestInfo> test_info = *test_it;
      for (typename InstantiationContainer::iterator gen_it =
               instantiations_.begin(); gen_it != instantiations_.end();
               ++gen_it) {
        const String& instantiation_name = gen_it->first;
        ParamGenerator<ParamType> generator((*gen_it->second)());

        Message test_case_name_stream;
        if ( !instantiation_name.empty() )
          test_case_name_stream << instantiation_name.c_str() << "/";
        test_case_name_stream << test_info->test_case_base_name.c_str();

        int i = 0;
        for (typename ParamGenerator<ParamType>::iterator param_it =
                 generator.begin();
             param_it != generator.end(); ++param_it, ++i) {
          Message test_name_stream;
          test_name_stream << test_info->test_base_name.c_str() << "/" << i;
          ::testing::internal::MakeAndRegisterTestInfo(
              test_case_name_stream.GetString().c_str(),
              test_name_stream.GetString().c_str(),
              "",  // test_case_comment
              "",  // comment; TODO(vladl@google.com): provide parameter value
                   //                                  representation.
              GetTestCaseTypeId(),
              TestCase::SetUpTestCase,
              TestCase::TearDownTestCase,
              test_info->test_meta_factory->CreateTestFactory(*param_it));
        }  // for param_it
      }  // for gen_it
    }  // for test_it
  }  // RegisterTests

 private:
  // LocalTestInfo structure keeps information about a single test registered
  // with TEST_P macro.
  struct TestInfo {
    TestInfo(const char* a_test_case_base_name,
             const char* a_test_base_name,
             TestMetaFactoryBase<ParamType>* a_test_meta_factory) :
        test_case_base_name(a_test_case_base_name),
        test_base_name(a_test_base_name),
        test_meta_factory(a_test_meta_factory) {}

    const String test_case_base_name;
    const String test_base_name;
    const scoped_ptr<TestMetaFactoryBase<ParamType> > test_meta_factory;
  };
  typedef ::std::vector<linked_ptr<TestInfo> > TestInfoContainer;
  // Keeps pairs of <Instantiation name, Sequence generator creation function>
  // received from INSTANTIATE_TEST_CASE_P macros.
  typedef ::std::vector<std::pair<String, GeneratorCreationFunc*> >
      InstantiationContainer;

  const String test_case_name_;
  TestInfoContainer tests_;
  InstantiationContainer instantiations_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseInfo);
};  // class ParameterizedTestCaseInfo

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseRegistry contains a map of ParameterizedTestCaseInfoBase
// classes accessed by test case names. TEST_P and INSTANTIATE_TEST_CASE_P
// macros use it to locate their corresponding ParameterizedTestCaseInfo
// descriptors.
class ParameterizedTestCaseRegistry {
 public:
  ParameterizedTestCaseRegistry() {}
  ~ParameterizedTestCaseRegistry() {
    for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
         it != test_case_infos_.end(); ++it) {
      delete *it;
    }
  }

  // Looks up or creates and returns a structure containing information about
  // tests and instantiations of a particular test case.
  template <class TestCase>
  ParameterizedTestCaseInfo<TestCase>* GetTestCasePatternHolder(
      const char* test_case_name,
      const char* file,
      int line) {
    ParameterizedTestCaseInfo<TestCase>* typed_test_info = NULL;
    for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
         it != test_case_infos_.end(); ++it) {
      if ((*it)->GetTestCaseName() == test_case_name) {
        if ((*it)->GetTestCaseTypeId() != GetTypeId<TestCase>()) {
          // Complain about incorrect usage of Google Test facilities
          // and terminate the program since we cannot guaranty correct
          // test case setup and tear-down in this case.
          ReportInvalidTestCaseType(test_case_name,  file, line);
          abort();
        } else {
          // At this point we are sure that the object we found is of the same
          // type we are looking for, so we downcast it to that type
          // without further checks.
          typed_test_info = CheckedDowncastToActualType<
              ParameterizedTestCaseInfo<TestCase> >(*it);
        }
        break;
      }
    }
    if (typed_test_info == NULL) {
      typed_test_info = new ParameterizedTestCaseInfo<TestCase>(test_case_name);
      test_case_infos_.push_back(typed_test_info);
    }
    return typed_test_info;
  }
  void RegisterTests() {
    for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
         it != test_case_infos_.end(); ++it) {
      (*it)->RegisterTests();
    }
  }

 private:
  typedef ::std::vector<ParameterizedTestCaseInfoBase*> TestCaseInfoContainer;

  TestCaseInfoContainer test_case_infos_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseRegistry);
};

}  // namespace internal
}  // namespace testing

#endif  //  GTEST_HAS_PARAM_TEST

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PARAM_UTIL_H_
// This file was GENERATED by a script.  DO NOT EDIT BY HAND!!!

// Copyright 2008 Google Inc.
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the d�����Ք�Zַ�oW�I?M����۝Mظ�m�t|R�I�h�frw�P�G���j�a�#%d�j3[H�O�ؤ*e�y�[���ѓ�"�����4�o嫫�P�q�'�1�k7�W5Q�����s�*�����-�^W����K��T����&5�|�:Ż���+�SB�8����R����&I"�#�Zק�ɓ$m��ԻG�Ґ��;�� �6/&���n}J�_�pf?_2�t�����аQ�3U�;ҵFmү���$��sye��>�����||���΁�1�O2j���o}�ѧ�æ�FĴ�O���V�H#i$����U�T�?�O��*Mv�G��*[G�_�߯�Ω�|@��$��;i�_���OZ��W���£������J]��,9uU�2���$���<=o����S�vr��d�7r�Ꜻ ��,�e2�|���m7	ާ��;�>�3�s	sH�&a����C��9�,!�#�����$䐰����ג�z�~#y�L��"<޷�s;<w��Nv�����$ �S�?D��I8
����g>��B�w�������A�_��	�$��<</��Ex��Ӿ� ��+��	�I�Xy�@�M~�<o��$܁�w��	�$���}z@������A�����g$<�Q&f�,�nIx�"���\L�e�<yV �"	/��qjk_:� ��2y�BBU�^�<k�P~�!Ϻ$ԃ�Zx�G|��F�1y6!�)	͙�[8g.�Zó<��SG�zx�g;x�g	�N�3���n�;	= �	O2I��ޟ<�$ !
�A���2�`CIF�p^#a$	��`"�(8)����Q$$�0��D�D�SH��T�n'!��2!.�<�$�-&��6	�H�L�@�i�ǻ�}	36���F��'�sI� ��\H���"�����%$|D�2&�c���<sP�
򾊄�$�!a-ĭ��F��L�Vv����](�n��k/������@����v�<���	�<I�)N��4��`xI~E��$�'�	�"�K���U�F�u�]@�ߓp���H����$��x�
�w��y�N�=�]H�����y�����x>$ϿIx�)��=%��24�}]�?_�GBI�I(�eɳJW�W �Ix��J$T&�*	�H�NBMj�P���$ԃ�Zx6 φ$4A<�2elF~7�<[³5y�!���^:��I"!����.�C��a���w'�u&�]���w�I�EBo"H����ُ�WI�O��@�����z��C	6����	#H)��:�M$D�`&!�b�8�{	�[�3ޓ�3���ӎҧ��8��$!~�I��I�@��$L$a	�I�J�4�{�<�E����$�$a	�Ix��9�<����O�H�~/"��L���KIX�r�\�+��֐��[O�7����[�޷�s;y�B�{��~�~��OI8�����(	� ��<O��I�<E����y~IB>	�H����$\$��%�2	W���~�<�#�	��$�r��&�	�I���;$�F�]~G���{!y�I�}�"�����?&�		OI���g$�K�s|�P�<�H(	�K�gixw��e���L��Hx	p��;�J�= ~W�gU�NBMDW�ׁ����6����C�����4&�MHh
X3ל�Ւ�n��6�,ߤ@�ڑg�&�!$t$������ :z�޻��蝬���$�"�7	$��H��h_%�Q$$a(����5F��`&�4����9�i�x�;���9��3��l$��`���e�ǡ�L���D�x�>������ lyN&a
	�Hx�C;���9��#��$�a��'��0������!���s		KIXFY�J+IXE�'@��<ג����$l a	���}����� a'	�H�M�^�p��C$&�	�I�ҞD<N����y��/������S��Y��nz^͞�*N���`���]����X������.�o1�t��~���v����j���ߐe�l,_^3����͍��[v`�e�)�;Lx8��~�O{S����U�����o�ޚU0�wǗ���߿z�G�W��h��7�������
���y�o��*�����y����]�|g�k�WV�����v�L�߾j�M��.���fy�:�6���7?=�U3K��pǬ�q������~�Wk�J��i��T�k%\z֥�ߘ��vTn�a\���)uOlm3�#�	�W���j�O:�]��v���Y#�Wf:����v��{1{�/�z�˳�MF��x|ㅹ�×>,�aPB��_%,�j�u�N6����_�k����V��y����}J5��j����z>�7�v%���;����Ύ<WX�y>K�`l}$�T}ՠ!m����7�޳��������{����9�`M��[=���su���GFnl�x��A�s[���ǅփG���wo�ϯ��hr��]+�?��r�M�;����mi��֭{�|��_v<���m�wQ�����:�����ęi��Ҏ�W9aVP/m���fZ뵖&�{��>ێ�^�j|����7����̼Y[}�j�k��|�v�g�F薮<�dil���o��V�t�����[C�<���Ro-���xȑO�(<���P��ߪ���+U9q��%7u�$jy���_~���C[/l�j��f�OE����9���ג���\{̭��I��������%�'=���۟u���=�ݺ��������-U�;^���K��;n�����s��ݘ��;�{���|�|7�|�ŻC�u�x����ך�������׬G�x�L�����Xr{N���|vo�=�S���&�o�QGo{�|$3h�Wa�~��"8z���u�D?�k����ʞUK��Yz_?��H�h�O;�z�t�7n�}��`l΅�喬i���<�N[���ߌ�|8,p��m���͂~[�~/m����3��Y�e�O�η�n����q�}����KN~����/~e����m;��W��+Tm}�ͽg�YoN~�=��߈;I�+��_a�����O5^{���K�4v���w������������t��o�O[�]���ۯM)W�޻I��'�{�)���w?��8�g���}tE{l\�@�k�$�}�����F��ܜ7~�վ��͓zW�f{\qwe��w�����_���5ږ����W���kF�JM=��zcé���0s��z��/	�\ޯ����r;ǌ�{�����dL�s��~�.?;��쨖�o>Y�b�����uUO=����\t̓���)1�fL�f���a��>e���қk��5��5�ؾ	��������VU�o'ϟ���.���Wq�;=�����;�W�.]i�Wk���m� n����o���Rsҷ�k�.�P��e-&ViU�q���*�����r�?n�6�y��r��99%9�fɶ���Xq�y[�~Tf��p�#-�ʼ
'�uoUr����I�K�����-����7Zݺ;Ѽ�'K�%����C���p����G�4��C�����R̈��ӎԜ]k��J���JK�
���Kg�|��|�`T�����C\�w��+9�Aė��mu��sp�O֎������;��rt�r����ǦU����<�� ���>lW��.D�7'd��k�8�zl\���_Ƨ&�9��.`����eF�������7O,��aҭ�Ã.�ڵ��Ŀˮu�/����fUn_kY{֜��.��1'���Ο-�?�ս�I��5o�2{n�[Ϫ��X��O�"��}:���S��'����7!�'���hV}����":���l�༌���tl�RV�����+�߶�6s�	��k��������a;�n8��e��v��W����/ʘ���{�_������U��X3����jַN�o�#�泈c_��q��3���'��;��Z�|[�x4����n��R�V�Ր�5�_s��A�ՠ�C���Q�V��y�N6\��o����+:}q�L��u�~�p��'˻t���4��9�O����cG����Ψv�x�AY��?ح䀆���;u��f��i�^��龸ó��O��5����}R���|>v�ŝ��a���zmH�K��{u�	�WZ�6z}��ʍk���y㫷�*���É��u>����Q�̯������?9s����=u`mƥ��jwvsR��~��|�b��3�m�kߡV{ڶ�Xe|��?7̜ԭ����}�M�R�����E�y}��:��7�3����=��ju����p����M�1�Ͳ7�������g*o	��rQ��-��������:��}������K�}�~�îWG]��`�)]�{祱��mz޾�Q%�KSv��{�����6�����l����N�&�GM]8Qf̒>_�������F�����(ߣ�]SP�������x%���z���R\�Gqw6~7�r��z�{�bӓ�g���O��_J���/���N��2�Ժq|y�'��OL�Æ'�qe⏏.�R����_�7?�m��%sC��Є�}�H7:��ik����������������?5���E��J�%veLIh�F�+��$}p����k}~���n�Ok����J����|��']u2���r�o�����u�/2�|x�����U
+QcT���?|{��qFk��!��Z3��Ѽ:)�i�V�����A�KGV�8�g���M��_��j_e�)���3ƽ��ި�ͿR��/�ߏk�$�̉#�?��s)s}�k��]�Y�����+=<�o#Sp�S�|?m�����>��ܴ_�>0k����:�����J��������{߬�rY�w������m�����oY1vĽ?G�~�f���B#4m/Ic'���bc��9�;�6G�K��������6-���,�I��?*S�~�'�"��������̬ٚ-I����R��ӷ��^]~�Ɲ�w;�q��_�|�o�ui��}�>Z����N�vY��&g�����)]�g��o���W��B*�6"���gb"z<1u*��;�������au,�.����4�^z{�z�5+n���p��&���Ƴ'�������SVΛ�m���gY����/�=<�H��ݹy�H���cƗ�UzǤo'�{�~v�
��p����Kӟ.:_zL��v}FF~o�Un�Y�ܰ�IVe������#Ƈ^^:k���S�]x4����x����Vs���~ޱ�j@꺝ң��t�׶U�7�%�X�aĆ�.����GO���ڡ�%o}v����i�ذnç�,������)�<����G���lY�=d��_N����w����Yg�
3Fj�����ҳ�����J롕;G��ޤc�;Տ����?+������7VN���፟_�����m.�8���ss����Ơ����=~��oCύٞvE���u�����c_�:kyZקC��d�|���3ǖ��J��%��Ȏ��9Q�!uWWX��o��K�3�n��v���g�.|�3��V����t��F/U�]}�՚a�����zǧ�?����c;[��n����=�K�Y�cδ�?W[��߯�m����G!���]Vݭu'o���������_{� S룃�ߏ�\����ّ�K�������.'^�}��0�C�ɭ�ݳӧ�>~����s��/_�V�w����:��sa_�J١���o�����{��z��oS��������u.o9|��J�����y�������v\����o�9�ﵨV�i5���Uݴ��:.�}l��z%�:QB*#��N6�� �-���g��i$�Χ���[����x>^���߶����<=�O:��oo��Ǵ��{��Z��ؙ|��{|���|�Yy>�1��_���;�������_-��S���_>�[O>~��ǭ��H�||Ck>~/���	�K�n���r>�SPNKA?F����|��� �Ƿ�����.�w
���y�G0���u���Q�q!�c�����K|�5��W��W�����t?8��G9e���1�Of6�����ǧ���Æ��M��2������)Ыu�v�=���/1};(��7�A}õ|��V|<S�-���I��:$/-����|q�,���9||XK>PS �������l���ch/>>c
9��7�E��ߣ���`|	����I0ߕ��o
�ׯ������y�m��'�?����+	|��`\���������G 'Au�E�?��X0/�]#>�b<�P`�
�ƨ�|��UP���{9�^$�c�x��|��e9�-�g�(D�(ד�]/�3�
�������no8W�.����d��$�����n�x��a�<e��f���1{*_(�Ǿo���9!X'&
�M�㴻��;�rr�G�>�2/�����	֭�l��6G���W��
����x�@�����+�xM��8-�o��QU���I�Xӏ�$�����<<�$X5�����2|��`q_`w-���A����Y�y����0K�M*��b������i��+��~���(��v��>���Y||�@o� ��>�ߵ��N�`�*X�Uз�	�ֳ�'N0.��yN��`=����{5�ͦ�����Y�@_	�R)�|�T`�n�{U�N�!(�>���O �#���,�
�,�=v���N��~{��@�_̃��F����`��_���T������`���'���x�����AfJ7A}~_A;,�����)���	��/��~?�RA{6��=�]�*������a|��@n����������`>m(��~#�/��.�~<���
����(M�o	�m�`�h�S��S/�;�n����^�*�c7��Ym�`���U~�	Wu���a��='���a �\���~х�����J���&���=�$�?�?O�0�5�
����H�8#X��;�VS�N� X�!�O|�浖��h�`=�J`�|&��(ׯ
�՗���`���a�`��'��	�PA����������H�7^'�W���>~V��b�^&Y0�:�����	�|TY��'w���`�u����»���
������T�������G�%�>�:t����R����w)�u{���~> ��52���ң=�nl3UN�}E��Z��/+x��OWu]0p����kX����ɿ��?�*�w����Xg��Qp��2	#������0����a1�_��/U߅�)x�M�O��<g�����i>�R���C��?\�W��$�w����
��L��x��_Q�j9@���~5�.�� �Z�]C��О�<����_�WF@;�H��Q���<5{B;I�8����a�(g=�ڡ����n$#ԫ`�_#����X�� � '��4� _(�E�0��C�}l�+� �}�u�/���B�Y��d����zO��� ��-7���G�$�.��e�A?�Q�@���v8J�y���O%Z�ۖ��Y�зܖ������x�p�O���f�<0���
�4}ě0����N��)g�� �+h=���@$�_��/:ߕ0~`�P�k��K���Eb��S�K�7u�8������g�r�F���)A�Kz���́~iL�C�����>T}o�<"}K��`�ۂ:
�)���T���i>3N�V ���|/����_M]Ǖ��n��wA*�R���L��~W��C���z-����g��9]��@����GaP�>T;$��*��DՇz��d�vh|�'h=�,�ISK�=�����|�_r���˃�|M��� 縫(�����9�B_ݵ�}´[{U~��Hi����h��y2��������Ƶ���Q���� W���l>����7��P�5������D��wjIhf�}	r��ͧ�%�`U���z��摛}��E�}�@����4��\���,(�R�{���/��^��7��W�a\T����� ��y�1̳9��n���y-��Q ��h�(r����#A��^��o�>���i�H�Wz_EN�w���9��P/�~4ȹ��j�A�ݠ�QSh�ݴ��K���y�>5h�G`\|C�I�: ?���J;J�=m'WZxZ�[b�}���Yʳ�����(xUu_�C.3�>}b���֕�=�k��`o����mڎ����<��?`�;���W�K��^����n���P@�� �=M��`]��E��`�*�yJ-O^)�_F�ɳ�|;y�Rh7-=N��
����������O��4����e>�!�9����sy_J�sC�u\u�;6���ׄ�l��ǷK�@{JО�<����^�L;3o�>� �
�Cz���^vU_j���et���y����ހvc���Џ�����<�i��݁c� �ɯ@�{!��52��: ��h�z(�H���x��n����iH:��^O��j����������x�^�n}e }��5�?����0�ژy� ����t�|	��\X?NP�Y�a��O��j.�z� �vnZ?lN���x���%t����|�����2��r%ݦ���w���������~{�:��-ZϛϹE��E`�i�N��v�/z��6(���_�m�g��q��qt�X�~Z��}�=����_�nAN���vQ�Fz>}
����vІ vi}UO6�v?�j����L���C��}����& ^H��*����Rnz\}k�Hσ#��x�J뇵`Ge3v�e*襲
�(u] �vc7� >�����)�W[��cӀ��w��C�����;�hZ$���=?M�;�<]@��l�7�G#��%pԷ.m7&A;6�|��������]K>�K�_����࿲���ϛj��+���/�>YM��QP�{��I��6z���WX��Wø����S�=@���=�^_���6h���<�V����C@ok7�r	����?����I�U��/���\��5��g��F�^W���:�̳��i��/�W���y��\(Տ���
�[���/�-E���������O��XM`�w��T�=�~Y]��t�F���N��:r�����*�E;i9_z;����;(~����f^�}�|�{N��@��+r�֒
����3�S��a���<��?Q`W��t���>'h�Z��:Ə�0D�.����|����}��մ���F��S��>��)�o��v#�g!����|�*}�ʸ�5�퐭F�^��t�z�:"���&�O5�}����w�7�y�F ���_���_��	`'G3v��ƻ��,��あ���<�h�ﺵ���$���m�x�~��|Z�e�8խ����[s�u�_����`��P_�3��Cw���#����?�zi���
r�==�ۀ��;Am�Q������)�\U�}Rp���О�\Z_m�����O�}�/0��Ɗ��c5���FM��.|�!#?�B�g3��6��
�_e�2.r�v`CXG������K��&���Oh��i����֓���V��?��� ��~�A�.xs��+u?wD"��Z�ς���)���譴é�t;�uw4�� ƅq��1���BZ{	��������jh�i����^O�3?���t����7~A��~ݯ�ݢ�r����7��v� �p��l�q1�#��EMUyh�̳6f���;�ߴ6��/�v�(gN#Z���~/d�}����z� {�V��WSa��`���� �et��;���O6@;��b'�+�2��zX o������؂Ǵ�^ ~o�uZ���������o��oü�@�����f���C�_z�M��1�*���'8��	�ۂs4�!"�F���0���E���r�L{8g3��l�Vp��?����?H��k����D��? 0I�����I������vX�U��'~�W��i;m>��a;�o[[i�ޛi��!�S�ث�a~Ԭ��9��6���+���`�q�vc�j��O�K�}"d���ǳ]��3��~L�1:G(���F�C��ss����F��g���I��J���v��OX��ߣ��v��
3/�Rۄ�\+�g�~��r����N��ȷ'	�K�>�c�u��]��}��>0��0���	��s���������O��:_��>�̾�U�36�3�~A=�G��ǉ`�攤�S�_tW��Ճ���L��'Ly���'���_��P��{���U��������"`�%�9��K����W��ps^�؁��z�9��9�zM}����9X7E��m ���s������ݴ���Z�\�oP�|��à�s}h}��[z�6 �d-��e��#��� ?F~ލ�����Q��W7�C�Ka?+�W���G��9�9�W��&��
a��y�;�K�7���'1뵩���6��uڛ4���О���~�hv��#�~�{H��u��$f_x��m�i��g���<�����t�ӡuL?f�9+s�j�'5�|��r���ΑJ�h>+`<:.����ա6���hП���h6؁���|��;΃���k�w�ld�ϰO�˜w��C!���qm�N��{��1v�l�y�hy۱L���������M�	M`]�[O��<�g�+��.�k�����f���`�J0N���������f9��l+�C��<+������]�0�1~���8�N��Z�N�E��� �~�<���{Cy��|v��\�3��r@����=H��<�/}9�����#���܀0�Cn���0�$G;U� vx!��3��z^��{[����s΁����8��k��\V�W�t�#�^.��o���f+=/_�sk�%��ρ�E	;i����*z��0�;lKi�M"�F�=��1��?�}���
����Y�sSAp�߸��w�����ğAj���d�?�[�2����9����h{&�4��z5�y-�!��'������v�-����?�������E��zm=.��|{�6�`a�%}B���%�C�r�<U�z.����uDY�W˴C%�oXMہ������>�_�-��S@�eC�{��{���f��B_��穌4�tXw�q�I�o�f��]���_����h�o��򄃞w0�_�?��O�_�0�@?��������UJ]���Ge�=u�h��0?��Bۥ�@o�s��`�l�F�m)�g�)z�_?���,;��9>�ژ����`�]��������|'�9��}t���42��¸(XM��H�/����a=(�K��<�����J���aM�Pɷ�'`�,��ک����N`��?g6��|�6��4�t�䞧��j�ߩ+����a��i���S�o������o���h��0/g��pY`w��I�/��kdF���M^e�o3��.��)}O��[a���s����"ſ]���s`�2�'?l��ZϷ;-�������t���-�_݈_���/�~��8�3�����.��W����<y����O��j��b�{(����dd���WF���<���C�����1��7��;`0�,-���^�[�ܗ�8�CU����}8�Bf>��9ۇ�����F��	�`������y'��r��v`?з�ƴ_}̿������y7i�7��.����:�`#=.�]�k�c�G��_yp�w���<���:�˸�n��`_5�"�_c�y3����~����P�������}�<�<�AЫ�̽��m����i8�`>꽹ZpG���3t��j+8��I�zgt?X/��L5X��~���Űn�2���������p..�9��g>�__k*�� ���'�C��j��r�p#�!����/A�˛pN,�wڮ�~3Ϳt;�uGNm�������.c���üSp�և?��t���9@�W���p� Ϗ�'A�0~xI�'W��'X�o�Ϝ��)��o�}������Q���D�]��kF�������c�����p�h��O��H�O�[�(��^�m {��*m�T�ȧ�-������G�����ܣ�;��/]v�[�:Q`o/��A�p�@�7/��[���=�{��w>9�G��8�_
��e�`�� �f`�II�gr{f,�k���s�O6#?#a�J�85��Cˌ녂���U�w������-d��sP_��=�|�����nώ`������ ���i�U/П9��LE!s�����O����E4s���s�^���ZXoڎ��V��<���vvu4cWo�{��Y��篠�������J��g�}XP��sf��1viO��d`�����0����L~���6�<����/�/� 'ZFN�A?�N��%�5@_J��=�'�?9��Ok��r��:%�Y����c}����Bf|} �;Ǐ����|�}��`]ldΗ����hu+��rw��v��W.�!�T������X_k>���|ؿ�f��
����H�=�����y<��h8��j�T�?�i�%������뵒 '���� ���_���r���f��+p�4����������������V��a?K���Aԁ{�y���yr�	z��
�"�-�l��K�v�i�y���Z�#�V�Y^V�%��oaў��j���o�{�`%M��?��/���W@��X��^.~������{)�����`\��\�G��ا�~Տ�a�u_؁�`�0�|��}�G��?<{7}>���4�h��	�^!�_��e����u�n5n��<����9L�7�{���4|`����:�*�9�Ι����v3��fc�[ ��'���,���<ь���g�����s��� �Z�o��SG>mG� ?�j���sܤ��K�;<�z0_pO9Ĩ��9�h��0إ9�]�P��U	�Q�Rz�\���� =O��vs@����!G���.�o���� ��f��(̛�?���>��m�^��H�iT7�ٗ��׃��ֳj�;��؁A��b`�Yn	Ι��3�F��?=�w9p�A]݀����y�C����^��i;}$d�2~���R��K�����<[E�ߛ��^G}��1����@�Y��}X���i��
k���=`�:{��_��i���C�̸��S?�����3��Z��*��c���~Ds�z��������.�L8��2��k}�s��3������O��M1���<I��P�������w�4Z���`�h���^}���G��&��SΫ8=�M�����
ƣ����'���i>��^�l�nZ�����-��~�~B﫿���n�.���:�G�1�%�)>)%�dO3���L�ɚlM�L��C2E�g���Z��4K�~�S�-��1�%�c��4;��o��}2LQ@�=�l�[��W��������ii�֘�4K���.����Q�u&���Mf7Ŧز��|fF}�IF]`��K1){8+�.�bOKM�r6zf��fI��8�)-˔��2��<�]�H624ޒfJ˲Y�i���nS��"_�h�	I'e�&Ǉ�L)(8��G*U9�K ���uΌ���>�b�@���t�b�����9
#dU|b�ޞ�z���8��gs�;���m(q�3q_�n�gD���{��l*6��xgs��[@�c�0|���&�a��ĔT΀Wp� ��K�5j��`��K1)=�⌋HN�k�B�\4P�EQ��]F�p��J�;=S�i��Qp� ��K�5��e0F������*Keϔ�{,o����^���/2_j��x��/�����:���b�Zj�I�F�Zmi֔�pP�,�n�j���8����7�+�^��EHM#�cDHc\�I�R��A�R�6��OQx�R�$�j1�@�KG����Y��ͷ
�)�2�X�Z�c�MC`k�G��hw)u��@�G���*�J��C�8\ݩ�H�<���)��q�iiiT}]1j^�9Ő�sr�pK-ԓ�����Ĭ�������*mZV�%�4o�@����D�l(�g��'�9����bFJ��S�aN���eV!C����1#bkI�M���w��2&�P=fF�˒�hM��+l��f��f�gcIK ����%�-%�V;#N������x�k&�G��	q�{�$D-�R�EL4qQ�jU^�tJ�aQ��4BK*<��������1x�91��C��9�1�z]�3F]��KuQ$`����-j����K/���i+I��Lv�t�t���'3;�,*r4Mg���G������D��Y�C��%N�{���jCu�rά��<מ^��,]�j�Pj���V��}��c'1�9�	*�Y�X��>ص����e����8�*iqn��-�%�o- �Qb�"�lae��g��1�8�fwـ��]v�;k�g�b���^�Mk�S*�T	]�[iRP.�Ϯ�,)�V��<Y�l�8[V�p�������d��t]Q֬��aO��JpsZJ*c0cV����Q:>X������Q����Sy&�W��r��f�p�%[2�pFq��l\N&cfp�8��LQ{z��WE�g�" �d*�rH��mu��M!ο�:�u�hMy"-�j�o��
E�UU��foP���"�@D'Y���A���k�rځ��^TbF<�Z�s�YZ���6s*�ْ̩c��ΝT�K�I��HQDq�50�5�c&��[8�.u0���n�u{k�ݒJԠS�lz�G�L
����e��8�m�dԼ�&(2S��� ���D�|��Ozj-�[Xح��W���]��UA�^�6�T,�ρOG��b0��k���T�(1�͂��HvQ��/��N9θ�����r�sslo�%Zc-r�V�G��X�X9��@�T=�M��fk�lB�3۠��:͎A��QJ߄cђ:��l0��^�?f4�_�Eኰ[�c��$;ƹ1��)�]��[�q:9..�X4�&Ǚ�M@}��Yy��4*=9V^o3�sD�ɹK�*ϕI���n�dڄ���ee,��M
y�M"Y��|���M�Ďqj!b�BĚ�il���i�]���^� g-]��u�s�&�뭦j&3s�����ēe�q.�]�R�pa�z�u	��bb����CM��^�&�'�Pg�9�9�C�$/�Vg�j�� �[�{6Hƣ���-iO���^eF�7�kg�s:�Sx�{�أ�\ZS�5���&�[Q�ze�c�9=Q8�	�V��QNB�!�"k)g��{Jb������rS��O��R6���Qa�h0����{'�?�����c&�;�urV�驩�����̓�P!��"<Y���LVJ����w��]���� ���k5S��9w�D�\g�tȫz��K�9ƚ�'�6٭�y�Ś<*��=���h�-=�bʰ����6�����B�1V]�yP������<i�aoJNI���2����I�d��oo�r��d͙A� ɜ��˺���R��:�p���,8,8 ,بw���gӟυ{.2���у9'�9�\t�f��5D�q�&����K2'R.r�B�v`���ɮE�''V�U�Q�����[�����L�Y��\gL���SL5/��3/]C P�J�ZȄ��U���1���^ɐo�3�YT�5���kַ�W&���j��VT�����;�%�B�:�^����@���5���[�۵p� !dA���m�Ż���xG�b��P����a�2�D���Ωp�N
N��9'�Q�)I0�k�*X�K�GYF	�W�d�D$<����Z|�=#o�$�IA3=��%���au�������S��5��{��3�iY��|+`�P��'?�N�.c�G��ά�P3�E�����q�Tk�%N)n�g�j,�: ����4�9՜d�����a�/��G9��('wު
e���mk�*ʳLԺ�]z"E%�G�`�1#�4a �����X
R%��YE*\y�#��6�K�ۃ�e ����]�qΪ�r �
,o��� �8�u�)�m�3���q�ǜy�'�9M����X�"�g'Cל��^��KL1��̋9���=j�sׄ_WRҚ���Ǭ<2�[Ҽ�$���O�n�93���xǌJWd��rJ����!�,��<��<����aS�98\��X�*�̦�&����R
��būN�$n���|:�maI��W���,Ca��p�+�1��W#lU8kD["�j��jQ\���Ņ�Mv�Y�T�i?��,��Jc��,<ȓ�"���mE*u�)��c�Aba��2���9�8��0N�cxӮW�������k@�q�x��[ef���^beXR���kɰ$
�X�1%:�<�Qf�Me�&�7�T28���WF2�>%&��(1\�==5Y��F�s�J���͕�í[�mcd��e+/Ʉ���]�G�4���9�[�*��69L�y%�3=,2b̆{0 ��s����"H��O�Rn
7B�pr
�z"p�Zc��jg�q�T�����eK�w��i!�>zA+��$�d܃�$�90��k��jNЋNWƴ�Of��Z9��5$�տ m m�z�D�z_����0�=�X�)2��(������4%��H���X�1��T�CJB��8kZ��#���?���c<*gN�!.01]Ҥ�yU⣮
q�ǈ��d;F��s��"��CS��x�8u(�s�$������^p���p%�?�+�3�p��nP�y�w)��^��D�DQ�b�	\)�G��T��p�^��)�J�zû��s��O�M�	�"���^ɩ�^|	�7ι"W�Ǯ>�I�"yx=��mLot���^���myy2�P���<h��SD�`�'����$��Mx�K��G
Rzk�0�6����L�i\�#Q����]0n��k���c�eDܼv�����
u��\�����k3z�'�e���fT��.n"*g�/1�E[/|M,��Py���f�3m[�y+�Ⱥ���嫙V�+Yх��E������1A_��1nq��-H�e�$�ً����[�ӓC���D�q
/���,��UL��/��k�c,i��$�s��ܜ��&��l=�#x�&�{����&Z��I��T"w�YƊ��^j�٧�H�x����\��>�W�C����<�"(���>����D��.����u�!o2ԙ� [tG�u*#j�����9.9K΍5���F��׿ }�g��l�����ݯ��fN���1��\��m@���-*��N������&��wp���=Ȭ9�|�j�%6�!<$=�Le����S��8<h�V�
t{��DQ|��8��dW P}��`.x���pU��}�����N�Bnw��+ nf��`�&l^�Ɛ�9�\Ĕ�60E15�D��Iym!d�֣u�+��B��X鹄��(j^�qv,\!�j�k�\(J/��#K��p��'�L�&HJIN��̱|��:#-�v̅�✯ܓ
�ݐ�@�\$�:S};I��9K�
�?K�:h��t�_�w��m��r��
��x9'ƻ�R�@�;\�b"��E��	�?��,�K���&�^�ܥbA<]�F�4�8z�>�Y��pɲ�"���q�����Aeo����������S[�%ױ-��<g����W0��fH�2�����T�~/�!�A�2d=���^b�^cŧ�)�D@�a�#�ߠ� :��ɸ�bL�9�2�b/�cE���X��¢�y���xe".���͖��iM�GM�9�4����d\za!l�8k<�u_ �@������*�-�n���xd�I+�ݎ�OK�ƎI����a�"�����.=��{�i�QA�8c��&�bU?�<��-��u�#9.ђ�4�2R��S����](W*<7;}r/h��$\��9�xXg*ȱ��|XTl��c4��	���S.,�S�"b8����~�.ٚ>0̄��g?����â�����s�&;=f$��C�ľ���$׿y�ǁb.O1S�bzJ��MɊ�7��B�k5��G"CO>e�5��$Ezj��7���<���Xx$JM�>EC�̅�r�H��|jՍӳr;9��%��?�1���"R#�a�4P1��yI������7D��(V>��D���:?C��E��y��P�cF��B����:Q���2M)�F9E�H�,��uu�I���οb�lN̲[]g��cD
�|T�8��&b�/�9�FQR�KV� ��#�N���`ȷ���,<�cEg�?hW�ڼ�"�-��y�rg�\���^�>ђ/�z!ܔ�kO�¢��OW:w�2��k/37q&r����"2��Fq�q���Rv��\�z4�~��l�x�y���+�!��*�!̬�h�����Ƣ,�c�̄��n1X��.��G�I�-�_�"�r���\�x�g��+��T�xg;(������P��0S�xz�U��JM���Zê����~�S��|X�x���OΧ�d�h�c�i�$f�:o�3#T!��jj�	o���d^�]b�r�ǃLƜޖ!�Õ2&���q��bV��g�r���dA�T/�&(Μf��L#6�ɹ��LB&KjjJ*ܘ�"�E��+�bK��e7�k�="6|���_x��|n&<*)IJ�$�ڲ����k-8t�~]I	m�A �>����&<	,"Z12�{-�x�כ�l�d����,@2�ѿ�TɱdQ���`c�%Zrz����!(����Zt �����C���#>=������"���޽NtE�����E���H��� �
�� ��	�P�_$©�����7�8�w1����|�~��ɣ����U�q���Y�E'r�)ؚ��g�C��ghAFX>)��Y_sVJ��8�+)X�!���c��f\�!I�h��w�\�!ו����łM�?�}�p�����T -r�T:�=f�G��Ä�|r�،�-���bc-�;*�v��d�]\�HN�@�*іbwYȐ�y�Un%Ʀ��S�?�BlLD�e�,��b��<�xz8'8u�tpPٰ~�Q�l�LKbQ�)D�,���
7cZN]_�u��z��*�V���
e�w�ʝ���}n�s����(�K��X=�,�d�g�+hf:�2�R�w��g3㕎�s�	�������dnm���T�Dk|�l���_䝳��o��ĉ.�ɛI$��oS�OL�ڜK]/�,*���*j�XԨ�|hʢ�:�55��`U;=���Kh��&���2��my�yšd��PHB�����;Gz������A�E:��PrMJ��IԬ��������QKɂ�(`fe�b���g-��_jB�[�?�`w	O�����s�rJO3��[z�5`��Gϸd�h�u^��MIO�7 M���/�=$�	����PI��8�˄��������*��<_e�%(��8Y%�7�\����8�%0���*+]���&NS���X:��
r��uV;|;8�M����bL涋#jH�)�;3xeǭ��l�x�Q�a����Rr�Mv�,ן�CYB�(K5%'KqJ���.5����Y\��I�����?�e�ȟ�r[4Fj�hy�fūN�Y��c@�2�tMM5g��m�H���y�����2ǗwT,��vU��>y��z��dX$�F������+OPE\9��2�䯃1��g�]�u��-¼�&:��S0�HN)���$��K�E��ţ�l�`��.�?��i<P�"�����~�ѕ�k}-������?�.�"��^b�[�_3a�ޤ���,�jO7'&�f�Z9�����\f�{C�����k���P>�B�Ë��}[�S�x�-A���켥vS�T������&G`�8Q�� ���7��\��t�]
}	Eucƍ���I8�|��Ȓ .%_����.j������:|�����,yȌf������p�GN�^5�E.'���	�)g�c��O;{�c��m|C0�7wU7�/ߥ'�$N����IW�(KY��S���2��b����׋Q�wi�H��q�^�5{�ҝ�9j�c��z�gƜ��ٱ�lh�b/&�#����R|�HbtvW�9:�p��ЮZ��/(Ztۃ"����2��=�n��!0мV�gV���H��fAj�tJ��)�v/0�@Y��c��Q(*́�KX2���<\��2*����A!x�Dԑj���[��U�3Ӌw+�J��	/��=��_4[9m��l��YG^1�PO����j4����h0�FqP�2���j=#���QCT��nKH�me�oq�̳_�����7!)>E�D�-]��HWޢ=I�gQ��R���N���Ƙ�ӗ���}���J!Zjx���¢�ͼe����\�V,�^�RɊ�(啜�N"���<ϊyʴ=͜�6�7g���d��l�����N�\�q�z�;��9�Iqb�D�[Q�^(2a8L�I�q��s�QZ�g-�c=v�(֌tG�7D��px�s£B�#�,}`��Y1����u��)���d�9p+��RH���!�����(ĭ��s�¨@t=˅⢹�`��d�N���0�B��T��y�4�|�LM���25��j�2�cXy����1Ѯ�{*���_�jM���_z���H���$����\O+�o���?��[E������qR5��hjtq���׿ }�g��l����P��P��YR�� ����K�����K�]}��4��l��F�jV�_����6�\Y��<��Q��j���F@Q�0�9[	P�^n�+�]Q�
/n˻�Ͽ����^��Y�	�iR]���THYȺ��6�S����d�����b^���id�X�L��y�3N����J��s���-�-'�+3�h2�hq�Sc������xIeͭ�������<�+_�w��UN����8��+o
S�"\��� �������#KT�ؿ��̩�/�*��#L��7~���089��$�\�G9S�{c?нlM3ǘ�N�>ʎX���'\Ư���Ry�C����~��,2s��	��"3J���<�	�`����1��P�e��Ν���l�k1�UA�^(8����8'>\���]z	��7����i����2j����pPÓs�Tu5�]1%��$Į�L�,������ߩ_r�Fw�h�p(тK6�T��v2��q��$cO��f�-Y����0����5����ցm���S�蝐�^$���΅9��C�d@��ɔ*��gW��P���R�=-.�eK���r	\o�&�R
��y�S2�b��*{w$�g�\��%�Z����Ԏ���7�[w���M�~l��F�����O�<�v�0�۴��_��E�%�����5���(W���S)��y��՗�iJ3����������������������}+%IC�/-	�&Y�3����VB�
��X��V�S���]X�iה\��N�e-㴹4���s���o�}�3p�Ok>��iɴ��緎)�sC �nSj�v,񑟡n ܸ��O�0��<�\�YῈ��0����x��4��E��e��un |�K����:7����ri|�������#����mLy�+��1x�6�<�� _���/����6�������6�'_�_���Cw0�70xඝ4~�2<~Og�E@�����
�������7��<���L��a7+o@����L�]��b��)w �ϖpi/3~��o?xo���u7��<�lw ���s?���/�������U����z���0��o����� x�f���E>~�c��7�����u�%w �=Ȍ#��1x�g���{��v���w4[����|<gO���u�����|<o/����Q��%�0��Gk�<����m�{)B��q)�����ǳw��a���v��������{5p�=0������ܰ������|\#����K|�>�#��w���l�	�½|�� ߻���	��_�P?6����q��^�����k�
��c/���|��>�N�����5���M�kv��K<t��^������>� O���O	��|\w��g#9\��7��G|�� ���ǵ�z>}�-��o���|<W�w����x� ����p�� _������p�~>�/�m�x�A>���0L���K[�x� ����S�Y��^�go��<{;������v�q�.>����|�� �G@/�s��q�>� ����/	��|�p��� 9����|�O��[�x� ��
���m|�� _���G���y<z'o���O��v��Bn�#��{�����ܱ��p�>��� G���W�e����6����zj:�����/	��k y��S��P<�
�K��V>n���9<w����'��|�@��v�q�.>�N�?��{��M��	���|<t�����|\: �G�A����-��\��B$�с#�?��6G��F|0^�����+*g!�����wE嬁�3�O�5��C�U�$χ�����j9u��!�7
�3��v��u��m�>�3���>�r:\-����:D��#���`<�;3�uh��W�]��������!�[�}�x�q	�k�!�7�w�^W����z#>���<_p	���c�yH��C�~���r6C���|��i��o�9�Ƴ}_T��H_�@���j9C���)D��5�q��\�_)�=�9n�E�����%�W�r�p��>�"�-l��z}����9��>�X� |,w���;¯!z�'"��1���uq� |-�s
ᝰ=��y��m����y���u�$�ؾ�k�:;�Չ��da3��sy:�������4��9��/������\����}�W�v�+b{	�/ay@���^	�E��z�W��«`;�U�}��jؾExu�@xl"�&�c ��^�����a������b��a��ZlOq���=��؞DxCl�#���7���&X���?a�Gxs,�o���-��#�������6X���?�uX�����@,��g�!<�?��c�Gx���a�Gx,���ᝰ�#�3������]��#�+��w����X����X����=��#�������,����X���?��a�G��X���?X�> �?£��#| ������X�>�?b�G�p,��?�G`�G�H,��?����p��Gc�G��?�c��#<�?���s�,�����X�����V,����c��#<�?��#<�?�S��#܆��c��#<�?��X������X�������#<�?³��#�M,��?��c�G�,��?�'b�G��?�'a�G�d,�����S��w�Ӱ�#�,��?§c�G�,����ᳰ�#�=,�����s��#�},�����X�>�?�?����X�� �?�b�G��X���?�c�G�,�_���a�G�2,���?�s��#|������U���3����x�# 3��A#�9D�@���PA<�E\*��qm�H<@]5�H@�4@@IH7�#$"��9a~���3�g23�������tU}�^�zU]������q�g�o��o�ؿ������3�w���}�fO������3�"����=�f���?�/����K��3�R��̾��?�/����?r�g����3{�f_����Wr�g�U���=��?������k��3�����}-�f_���ٳ��3�z��̞����s��3{.�f���?�c���������}#�f/���웸�3�f��̾��?�o����۸�3�v��̾��?�r�g�_��3�.��̾��?������{��3{�f����ً��3{	�f���?������q�g����� �f?����K��3����~��?�����ǹ��{�
�fW��3{�f/����'��3�I���~��?�Wp�g������w���^�����p�g�?��3�Y���~��?��������3������"�f���������엹�3���������!���W������-3{�����̮0{ߗ����z>���Ϲ6��s�<��o�����&_�g�Z|�����p��F����0{gf����n��[��.�������������>���71���ހ�_g��|���̟�2{cfOe�&|��7��ۙ��\��oe�%�ތ�Sb�(�_�ٛs�g�����6�������o����wp�g����~'���N����[s�g����3{���~7�fo�����q�g�X���~�fo����;p�g�������f���?�w�����q�g�.����+�f�����{p�g�������f����콹�3{��������r�g�~����?�f���3{�f��[W����v���>��?�?�������샸�3�C���=��?�����C��3�P���>��?�?��������r�g�����}�f��?������Op�g����3�(�����f��f���ٟ�����q�g��s�g�1����y�����f���f�N�����r�g����3�?��3�8����
�fO��<��ErD|߭y�����<݀��}���Lr��Q��ڬ��1�D���-Ӊ�Du8���j�Y�ĴEC]�IL[3�/�Ӊ�@5<���h����1]z<���d�O���Vux1m�P{�����8��^�T���i�j�&����1m�PO_!�����V�u�܂8�����A?8��>�k���P����UpC�W7�~p���.%n��b�&�.$n
��Mķ@?8��V�g7����ˈ���N���i�-�<��6��$��~�t���B|;�'���q�1�C|'�G��~�p���N$�����@?�7����B���B���~p+�X�� ������C?8���kw�~p(q'�_�"�^�Ww�~p�}�.%���b��.$���M�ݡ�M�����=������Ӊ��F���s��@?x&q<���~��~��H����%��!N�~�(��N|?����@<�����~p���"��x�[?��ĉ�nL<����C�\�x(�C��A?��}��~p%�#�.#~����á\L<���ďA?x�H�g?��L�'��O�?��N'~
��iģ�<��i��$~��Ӊ���)ģ�<��Y��#~��c����Q�c�<��y�'� ���/B?�7�K��B<�/���_�~p+�@?��8�7&~����I��I<���įB?�bg��A?���u��O�~p)�D�O�~p!���D�&􃳉߂~p&����O<������~p���%�
����Ӡ<�8��S�߁~�D�A?x��C,C?x�t�'v@?8��=� N�~po���܅x��C��B?���nA<����gA?8�x6�k��P⏠|�^�C?�����ρ~p)�\�
��B�Ϡ���s�g�����_@�Y�?��N'�
��i�i��K�5�gσ~�t�o�<��[�O$���q��A?x���"N�~�p��N$^����C?�7���B���@�/�~p+��nA������C?8��G��$�	�������I�
�W��~p�*��gB?��x5���@?x����&^��L�u��O���t���N#Ά~�\���$΅~�t���B�������G���c��<�x�o�~p"�� �
����۠܅x;�W���w@?��N�� .�~pc�_�I���5�wC?8�x�/v�����E�.#���R�b��@?���W�o"���l�ߠ�I| �G��~p:�!���B?x.�a��$>����G�<���'�~�8b��c�U��".�~�p�r�'��~� ���M|
��]�+��4���4�[���ĕ�nL|����@?�&�Y����~����C?����ˈ��~p)�E�_�~p!�_��D|����W��I��
�?1=�R�Ӊ�Q���FL���,�\bz��.�$�GN������IMO!�GL�d�Dbz���GL���'�c��Q�:<��!���É�ё��HL���(� bzT��������BL���ӧ���6��"���đ�nL\������\��&��7�~���4��~p%q#�����R���.&n��B���D|􃳉o�~p&q3�?��'��~p:qs����~�\�۠<�8��Ӊ[B?x
����H|���@?x��E�
��É[C?8��.� n����wC?�q[�?��'n��Vı�nA|���~p$q��$���P�N��x���\I���e��A?���􃋉�B?����7w�~p6q�g���r�?q/���A?8��7����~�L�x�O'���)���<��?��K�C� ��Q��<��~�'ۡ<�x �{? ��.�B��x�[?��ĉ�nL<����C�\�x(�C��A?�b,���\I��ˈ�~p)�p���~p!�c��D<���ďC?8��	�W���OB?8��)����~�\⧡ܥe�ѩ����WJ������A�Jw^����u^�IrD�k�-K�0�yp��Y|H��Z�}�����X����8@;�
���J�$���+=�jy��+I�Da���jk�i�˛��QN��;���gD��%Ֆ݋�5Q��$�32/�0T;�ݞUuE=S{����>.~��[Կ3Z�_�"�;Fb}Z�������%���"���	�%9lDN�Vδ¤�R�f��|^����^�|/Z�*Wr����I�̟N��Y���CE9��� �J�%I�$�����B'G(�a$H�2b$ko���GH����,��Tv=D��q�Hi�櫓Ĥ�W/]��֌B�⤦kL���t��"�9u�v�jjH��m�J��K�&�\��H5����I���F��g�M2�?ɻ�w���Ͽ�_�j:���������/]6���|~v�j������x�t~v�$������|~�e��������l)3\�T����Z��52�������d��/�����:��:%����m#�k{Fr���	�m��R(_$gyN�{cE)yt/,$_sأ-�H�k���obl(\�zw�U�/*�=���@w����;��{��>���Ǻ�i]��j��8�U�蓬�~k.�0�W�嗱���?�T���}��ٝ���G��V�p�i?�U+g�=㷼�SA�w�_��~�Ly;+Xy�W��� ��:��K�[^��`�;�ʋ�[ޫ��zY3��,qF)+���O���o��m?�oi{N����.��߽j\�j����ϝ`�P�W_h=$��r��_��'.��ǧ�7����o�SD�b<*9e�OX�1�^j��v4y�ŕ/�\���8�I�E�S�{���fa�C����I��e�Y6e�ﮱǕ����g�;5�$e� R�>�1��$�iWn0UN]�gS�l�O�>��"�-�o���k��ks�sԨ��z��z��.l�^�]}���SO�H�{%���/�f��ݓ�4{t#w�_EK�!і��:��(�"�7�U���|%`yc����|](��H�_���M~<F�bɞ�����ȷ��	.߮w2�|;�ҔoS|�"��9��O8�������u%GWe��O���;<�J��1>���R���B��t��E�jI�@�l������a8�m4]���#� �PYw�n��t����<��2�O�S��-42���24A�C�hQ$��ٓ��Q��ݢ��!Ѷ�)?>�CQ��I�6��E1��q���|���5bd�c9J�1j4�w�6�ܻ�j�%w��z����}vѾBO��R�������Da�+8gW_/��7.��4�Q�Ѹ��s�ⳣ�2o��� ̓9��{�*�G�[j�Q��#��Z���=�X�N: ��Vy�+�A������@��olA�ج1��}r�Z�SK��'ȉ�?:��Y�'F�7sܰ8�!�D��uo��9q��y���i��bv��^[~8>��ܫ�R��x�lLH����F{��)et���)��~��1�i���A���)nd��9wD�ۅ�ُPow�VꉋZ^��w��O����7�]WqiG��2·��.v|e����qe����Q��]����R���Rc<��!��P��'���'5���#JM��4�k~��ߴ��|����OJru���x��<�P�E%����;�|�d�J����}�H����R�:����g�ۯ��F/����?7�O��'���D�{T����s�����_�����z>7T/�6}>�\���f��2(JJo��f�,��E�7T�)��R&Y�=J	?��I1#F�}�˳;&�M<X>?��/�b�>~@˺=z]����'�ٵ�����)&�2ڍ��O�7@ݓ'h�[&�R�Q\�7y]����5B�ȑ�H�7n�(]��`3� �zjjC�zz���;�^��4��'�D���%��V��g}�����!�J:�.��Mu�I���q��K�r���~�+�ˋ7Ğ�l�Ş��5� ���.*���/K����3�Xg2�mӻ��G��UK�K-9�����GQT���T�
�h�?�U�+h��U��fJ��z(�m�+�;НK�^�vGZ��ߖhM~똡�=�d��{];�J�HD�S�?���f��Q����j�P�c�x�u=����q"x�Iu<�c�>����X�U����b�z�t�p=��y=�u��=�O��1ʛ����Iz����RjC��z�7�l����r��;_��gj��� �f�p�k����x��~�(]�5��Dg�P���"�~��-��C��v�{�G��M��7jX�����+�q�q��ו�?���U���֌J�.����R�O�4z:N�!N>���)tٓ��\�oQ�Mצ��1������2r��~��C$��;�$��u)��Q�5��C��X�E
�(��ЙhC��~�@s����W�ş�6����DD�|_+��,��z����E������z�6qY�í ��h,nS%s�E]r:�~x@����f�n��"��X��+��fA�w<�O����z
�\_�B�a�6���\ú������|�r�rCm��pxN����_���M$]���g=C!Z�M��LqW�0�Ϻ������G�5<���#���Q�_�J��}���(���em�ݢ�؃Lj�����^8�E��ŮI�bxC=va?�w��}Zw.<Ȼ3U}~�W�u�7o@~3��;�9T���bC~��A�7o�	��F�M"�pt�3�$13<G���R����烒#A������EI(�RJ�����#$�}�N��,����^�S�nz�a�TQ���(�k�j�$З􌨁�R��\}�oƹ\�;�u!S�1�����4O�+��#VI:�`� oP�ܭe]���*fz<�5M�m���F+��qk5��7�S;yo�o����(���;�)�ܵ\����˥J�����U��q}!8������ԣ��H�i1��E�Z���H�m�.9Y��A��8H�������{ň�N��_ʐJ�-"k,.�$Z�M;���+�u�Ŀ�t[�n�ӈϧ�����y����"n��һD�oS���w�������1���R��D�3���ݏ���I��C��D�^׫�S\��7ćY�l�;?�~��Q$���pO~�x�1?چLc_D���՝ZTz�WC~d�8?Q|��O܅�_
�b���!(:�����ء���C��(�}�0�|w�N-��.���r5���_p΅�|Q�f�Ǡ��z����w���r��Z>�U4@�]����g}aIh�Bz�Y�L��m����{�8�"��u:D��(���m���%H�侔#)	��'�C"���ȳ��V�+t/IV��9�����)ccD;5g����B3�(�Uɝ�G펖�5�-��穉Qʥ|L��⼤/�Ҫ���.���fMƄ��q��2h�5�F�����N=��Q:�WH8�yeN!%ʡ��S��Μ���?Ǽ����(#�'�,���$�H�����b^+�r�1��6�4p���� [Xٲ���]��Wlu�\����Ѓ����j���=1mm�|���_rܣ<S�$�j^���̿�?����Z\	��'�)ꊴByi�%.�_-S�ce�g~��Jw��(��3�|���=Vd�����/J~1����y���7_���y��i��~C�Ul�?|b���=s�����{�߾���ԟ���-ܿql6�/���z��z���Ϫ���s���4����/uR��x&�/g0.��W�i��~^y%��Hνޠ<��ɣL��]s��Z�Qo���g��W wO\�e��S
��X�����0w(������l�~,�����w���+�[>�n����rA�P_��9�k=^ޭ�����6e����F�����r���[��=�hAy����Y��T��Tp���ZW��R�E���_��[��2w�a~����֍����%������5�	����K���x?�WZ���o��J��cz�e�F�}=�g)ʪ���/s�^��C��l�՗P����O�g�s�B�?��
�n�SqY�����l���O���puڜ9����?둘�]�
8����?ۍ� �?[�u��D�M{���l��EG��|��g���m���ƀ�A�r��϶ �uW5���E��\���7�P`ĤsQ�����󟁢t��K���ϫ������y��w5�>���CY�_�7�ܹ����Ceu^el����Y�kʷ�|>�n����{>����d���6�̡u�a�Ե~;$[��7�𧻓
L��q�S?�`����8˴��g#7���'Ϊr��{k�r���5���������f�w��-�>�Ĭ��z�+7����������z�7��Vl���nt�ϟ����u�kn������?�5�e���#ǘ�e�;���ȏ�1���t�ׇx�S��7�����T_���fy�j��z��ҚT��H}���V�L�����6��y�_Z�U�eU���ݟ}<oy%K������[�U�{z}����W}az}���1�_�n�Q�d���sp|��z��*���
��q����Y|�K�q��������<Z�s�χj�u??e�s���y�)���N�g��W�?�������S�k����%ט�A���'��ҐN�О��v�2�N�!���s��������q<��
_��́���J=��1��?ʟ�d�?^��������I?^M�|�j\���Y�� Ð?��Q{~P|���@��7k���Ѳ�������MV����}�_��+�hwe}�m��x����q6��^���*M~6����������">�-��Z���LC|l�T|��'����x|���xh�'>vĥ��I1��+�1>Vw;��d�����K�1�,[�[���/.7ė'QtĜ��K���rj�!�,^8>^Zs��D�n3����3����-���a˵��mlŊ@��Ɵ�����������&>��	�c,>�K�&
���h����@�1y�)>�*>6��|��a�w��xŻ���Ļ����*��'G�䣾��������:.*�=���V_o�;��W��}�'ލ?�x��!�U,��x�ǽ��μ�x�y�5Ƌ�e���Þx���x�2���������Z����/�-b���kl���ͥ����KVh��K��Z�{��\(�ݲ$�x�g��JV��wϧ_M���D�|�Ż9��1
�Xx(�x��@���e�x��`U�<��~-�y�ޫ��t�0�n�7y\�
��x/�I�ǰ�T[�����^{�|��p	����bwT��	��`���r���V<�mp3�¦�B߿z�|�2c񵭧��*������]��<���yp���� ��ծO~��Y�l���c}r������7���>�f\/��1�ϙ��B���w���߾6�ʴ���a����&�&���'�~�X*:�*9D� ����I���α%������5�52z�\4����޳~zʹÚQT��<��ml��X4\ɤ�|#$�������vra���۰A
���RrQy}���*�%��T��|��E��������V)�t����;5�'��<��S�<�H��1�ؐ�<�����|$#͝�|��������Sm�{������_c$�Vp<��[�������G&-����[�����i����(m��/`��|����%���M����6Y����ܿ�>R����#/~��0���#7�3�#�Q`Dע�����tc>��ު��_x�#�_y�rt>������>��^�;�������>�������h��G?j|��/\���g����P��[|ߧ����$)�p)�h�E�,��������+.Qg��*>:J��\H9ʔo)Sq�����Ao �?}�J�N$��m����%�H�i�q�R𽎹��\Ob�����F�ǽ��Z�����^�w.�	�.f|���&ʥJ�A��I�F�W-�lso��g��d�\�*�[ � t�o�Y��2��w������M���Q���J�!.8�P����]��Ի��,�=d�{����֥6�}y��6g��_��<�ο�ε�hB����o�Y��3O��F�����+���?i��@��>w:&��A�]~�V�]k>��A{���Z{v�wc����m>�񾔎�A��������Rd����֌�}�ӉZX��}��pqG�����#Z��I���_�V�E{�=vy+}��N�ȏ���C�� ��]�۠�Rk}�.�N�k*Z�h�m�������5�h�=�~r��þ�7��1���4����Z=nIOו	����:Qr�$?H=�G$s����[���~Z�~�Үr��5�?3�y�������/���/}�w,��G�8�}1���K�x�"O;���k��fG��sj�מ�V�o��(TX,j8�}�z.��{1���S���F���G?1��!��P�_��OD��Q�o���#�g���}��<�T��{#�|�d���/�����Y��+��W��L]��U�ob�9���|�����-x[��"#�^Y�F��C�)�Тm]�鿇�S�%зf�G6��HՔ�ȁ�'EO�^��Ȕ��#|G�z�*�/D[^/�Y�:m!�������B6�� �*�>�dfaHK���N��Gca�§:)����3� !-�&��>�#��O��h�>t\�����d��C��2�|J�7G˄,h�:Ʃ���}C�M��W��Gn���;�J���Ƀ��9�~�ʻ��*�k���M�z���&��= �Tj����6^{���^�����vu���x_�������+7����n���6��AE�k�+���S�&2�̿���B��t&6�p4�k=�0��+��*�>Q$� �]�o��O6�T�y�o���(�����(�ꔷ��vb�����I���q����{ۙ�{y!9��煛�ha���������hK
k�0�'��/BT}e�W^߿RZbz��z�#.Pg�{�E��g��*�ql�rZ������$g�
�oC�ea1��g8���v����E}�#����M��xί�i<�՗�b����y�������9p�Ռ�V���l0��5>���~���k�2�K�=�~�ii���߫r=X�����z\�l=�9���of����@�q�����o�,ʓ��g��7|`��q��$��	T���+�&,��ͤ�FuC#J>e�x�؈u����L�giL�mX`��	-0y=?��^@�,�|�&rg]^����S�ó����JA=�J�C��=�xg<�V��_W}��>;��']ňY���swI�j%i�g�Q]u�t��r��ytA��>�~�C�����i��Od~{)���f�f�z��O}o��}�%U�<��ޗ�~kU�K�
���y}�x㫪f�*VO������6A�Q��B��[��[�]%|�]�JG���'n����� �?33p�Φ>ۿ1��3�S�Y_�M,�g���K?�(�R]�K���z}�ҝ���i\�������L��l������R԰����?}��g��۽�o��W?���>�;F�<����Ng�W��y�;Y��Em?�y�����Ey�v������D\L5�_x^���<��>���������/^���9���dm?ɺ�������}d�������W����[�x��x�g��=	I��4D����X�v�Ac��h���mZRJ�B	!)CHÐ�eZ�Rb�6jD�ͮ���wvT�n��f��d�g���"G�lY���-j�=��|��}����;�9�^��1���x��~��~��y���w�ޟ{�lʏ����Iw�m�_-�yz�r��V}�3��l�������ft������=u%���ܽK�ݽ�>�X�����5�ݽǱ]Շ&1���(��ǣo�<9��7����Ϳ�ۦ~�t������{�x~��=*��{O*��'U�s�sVG�;GH�̣���?)�*ͷ�������o�{:P��f����e6w�w_U���P���h����������X����(����^�{����Z)���K�*Ṛ��_��e)�S�m�e9��e��G�7�����;O�}��ͪB����.4���gw�'P���߫�l���q{����M��b4L�{z�I��ߪ�#�Q�9)��?�������_|(lt��,(S��[S�����[s8��}����ů�{O(c��;奧4���Q�e�ո\�e8�����(�6�#;��$��#GTw�wM��q�]�Ӊ�U�u��TIo�U$\L�F7���w�����h�u�y ������ݓ�����3e��RR�*������J�'\��Gk�8�wY��o=���7�X���E��c�뤸��s}%Z�+�~�'�̛/�ԏ���@��FwҘ~rzw}�:�x�d���?������>������[���˔N�;�''w���cZ�1��vOo����ߗ�|vY�W�?rqJG��4��$h��~�.s����^4�O����펌������������i]3�����9}y�9M}~s�����r��������&����-���#�'��cy��7s{�18}�mߓ>;vL�������3���z3�fH?5�����Ѣ�f���V��$7z�v�v渵G�m�̡��)u���{T9��4����\�%�/�$]�Xt�މу����]F����Uy�4��M�ɓK�4�sd�1K��vS�o�������3A��cћ����\��/�˂�,�唺��K󵌖����bf���@��J�\�ə���N]���� ��O_��k&�c;ga�d��}�gc���$��ٙ�w���]����؏�0�oړ�~&����Þ��Wzg`�1�7���������?��8���Jḹ���dq2��T���v��5O�-N�i�XO���w��g9�v��OI����v�����Ėed2�&5�7w�1)����T]�f�����޼�2^��*6�Cf��Z"��Ц���蠶��F�"}71W���xtO�6
�և���!a�Q컦���>�=�Ceu�z�S������)��u&m�>�2�'o������?�4�}$;iR{({�	e��R��O(/���_}�pWt�#y�`1�Z����I��Ϳ�~����2n�~���?�oQ�uZ]K�K�7�=���|�b�tW�b�u�����M��l���i�i_����kی����ѭ&�n�u��Z�/�����u�og\�W���v9*�ZTg����;��s��[�����q�~��7џOJ5�x���L���ڙ��	?i
џ7ۛv��f�ތ�=��N�a���g0�.$���������1]��sgb�߶���[��������L��]3��������f&�L���m������=���n��FojS��Zg��t�jJs����IY�V�?T��zq�۽o�P�9�5��J��?���r�g"���i�DO����н�(K���.Jwe�{~�wY�jYw%;�hg��^��Ϥ�/�۷$���6�������������QE�r@u�G�Չ�@U?oH�ޤ����/ܽ���c�9�����˄�[1�)���,kh���W��ћ�����t���ޮ��s�/�~���"�)��O�����+;��U�_���d_�]���w���|�P��?�Y��<�]���yy�cs:�3�c���������X4i=Ft��Vot?b$���6<k�Q��'��'��Q�?��:�*�����n���_��i:�R#��R4��j�h�����٭Ex[~��Q�y���9ڸ������:�MU�zo�}8�������vU_}y�W����.����]��Wk�B��_|�ﺏ_������/����l��w_�����E��������_�����{[,���h�����t�#%w>�l���~,��_�n���IN�]{�3��_���2���]Ϝg���kS��E��5�7=��ݼ���h�?��/Z���Jw+�k�}u��P�� һ�ᡎ����*�U1M�d�_Z�U	����s�ц�ɥ�z_�M7����9��Dde"[Z�|Br�ΧRף�o�?���|�gNw�{���*���*��ߓѷ�j}_|���3q
#��.��ݶ�{r�j�wy~tՖx���+����B�H*��j���JS�}�7���U�Lx��={6�i�!~��۵[e�~u�~��V���6�t���ˌ������i����jy������K�?[���/����f������Wf��Zu�?i��=���?i���Υ[�{v?��~�'fs���ڊ��$�����p���`��~����w~��x��������3���S}�D-#�:0�/7�w���U�_�e�0�3d|r�E�y5[F��Fyx��f�WC��B�ο�1y��ǺB%� m���S������4�[�����C{4�U[�԰D�k�<�,^���N�9s���s�ߚ�~���ڬΓ�|��=*��������|���OO�ޗ�3�o�p?a���j�����ѧ���|~j�da��K��ݻ-��Ef�����������?�|��͖����[�K��[���F��2��7���}ƃ�￥�Z�-q��4�$?}�0��|��������x�S���j��8%�qS�Ծ�R�wϖ��>e:��UY;-��+����Sg(e�c0��>�M;�y�M?�ۣ��{�WS,lbe�!���=U���������W���W���b~�6�����ů+�r�؛�þ�����0ǽ���?�Ǝ_D�m��]��&}O^�ؓ{z7��c���2m{����_Mj���~5a�K�k�O�-��+�k6����o1�m�<���}�,�K?i�<�����3�K�o���_��b�_:��xXl:/�����I���WnN�}E��{>vj@_�.y|r2�m-����R%�Ѣɢ!]V�d�6k�����b���ۭ��#�,�d+4��t٨��X�Ɏ�O]vL��l�duYHɖ�?w�%��:��v��c�����U9�����yx�H�GiK�l�R�|�n-y�'JZ��|m�v��u-�[����7�k[�~��m]��-�7����Z�㎧�׵�]�ͿemK�C{Ӻ��>tGI}󆒥��Z�Һտ�u����[?TҸe�֒�-��Ƨ[�mnY�v������?����ڬ~�/����XR�\�㎥��Z<\�K��w�ѢL�L�mӶ����-�e*�-N-�-�ۻ�c���I��l*=	�})!:�ˌ�\�K�+T�eS�K�u->�"$�+�6���^f~{�'��[7L�������V{K��;�X�b��-z���~�&���X�ki��W�Y���m����������UY7ιs�u6۩l�-������e�>8չD��6�0����R7t�A�C��0 �`�� t��q�1�v�z:`:�t���	�E�%�X��a �� V�`Xك8�aƔ�H���	�=��0}� �a��1���9�z`#�A8C��199
0�¡Á?��X��`��N�Sc0 �Bz�:X�z�`�!8cp\�����|�
���p`�a�a8�a:��7tA�M�V@��A胃��� �C0�p�CW �J��0k`za�a@�؁V�����:az��9�0��wP�p:nF�`z������ �A8C0}�c��C� ���8Ǡ��Q)�C�@�A/B?�A��л�rRz0g���5��M��	����y�a8G�}��/X
��=�=pF`:_�?�X�� t�&_0 '`1�������F���<����� ld���3����p�`��(O�1�E�`:oQ�p��B/�A?� �pC��(��q8sn%=�� �:a=�0CJ�*�=�Wz���X
���/QO�C0'`�o�_�8k`za����8p����H��0���Q^�'`�~�|��^�~hg�!8Y#�˱K������`��R?�#Jc*,Z�}X�_�?�>��0a�0�q8�����â�:���A��a F� �!���]pBŇ���>`)�A�zh�S�@T�p���
�+���(�~�A�!8G`�Ao���/��1��?�o�C0 #���YI<�a8 _�.��q�����`���A�~����#0Ǖ�/�.��R��~8`���U�҇����/X
��}��0 � �!8G����0���0�8���ć^8
}p\Ń9w�t�AXC��a#� ��8C0G����t�	�v����]��a �� ����Qr��	���aCt|�r�N��^8��8t"�O�t� ��a臞����������� ��p��(t�5���Ta:` ��0����q�.�HCJ����x0�����8�z`�`aA�7��p��M9|=��0G��0� �h)�C'���^��0C���mTŃ�*��?��R�u����`��Q��[ʇEt�@�z��� �1XT��ߢ��z�6B/�< }�%�0'�8�/�,�v��.�^�~�0�`��0�����&?��B?� �`���p�`�=��m���#�:�;�@/�>�A8��aѧ���:a=�� �#�1L�0+�%}��O:0�� ��a8#���,��W��a7�A�C0�*�1�v��E+�:�z` 6� �A8 C0cpL鳃w܇]���%]�c���ؽ}�C����	8�u�C't��>t�F��0 �A8Cp���z{�t`@�F8p�A�	��`zᄊ��>�����'iO���CJ�5�Q��7�c%����z�����g��>8��^���	ðF��C?�� t|�t��U<8��A�Că�p�`�C{���0]� ��a��J����*ҁ����v�a�a8����������0�~@<����`��,]M9���`vC���/���:z�P���`7��{0Ǡs�r�4����]0�� ����p�� =�cJ�<�,�聾Ӵ#8���G�yi7�����P��C�G�F�N�aX�z��00`A׏i7��a �A��0t�qX�?!��	��B�AV�ᘊc*>,ZK��:a�@/�A?� �0��8���E������ t�AX��F`7��A����.V�ᘊc*>,ZG|�Xc�o�'t� ��J�B�Y��q��R�50�����S�p��8������t�:~F}� ��@��n��`)�B@/B?�0�`�����/����k`z�8�C�9�ð
�c��s�5!�.��0}����B�^�>80��h#��0�a�าc�t��ܠF�N�,m&� >��n�C��K�U��т}��qҁ.8 }p��8�;�O`V�0��l��0 �������B��Ah�D>a)��z�}?����)=��a��B���>�� �!8�0�T�_��f��B��^��0 cp@��;0 G� ��a�h%�o�?� tL�}0g��	c���>t��!�#0#0�m�_�O��0 }pv�a8�����B'��>X�$�`��y�������c0��t����>��h��C�.8=0б���a=Ct��aX��1�1����C'�5p���',�s�g�euf�h�*�?�f+E�࿺���u���ڂ�O͟�T~���壥7�x*>�r��OON�'����L�.��U������I�	WO��>���?Wp$���h�]�g��L��Ƹ*]�c��s>𘦯d��׉|���EAaOvuA��9�JZ
��DT���A�޵I~+y��!��}��;��G�kү}�ܛ��7��?K/��og�'Q.���,��J���*(�XP\=����7�;*����,�����d��Y���3���\�,���W[��C^7M:A«,�@��B>���"�Q�eӤ3Ax��=����B^�<�"r�4�x	��H�=?�<���#��@~���e����pJ{i0��q�NY�����7�ȏY�S��hTx=�W"�~C��p��K��D8YynnAaMA~��);�9zy����{�O������7��R	(�@�������tzZ�s���6���D�=%�����Q&�1�^���=��:�
�ͬ�E�jz��5��I��k�B�?�=���w����;!���vaa�q�g;.	�Ծ������-��%�W����c�roj?A^f!� /A~�I>���BnǩB�W�ǿ|�?�ܥ2᝚����ѿ%���s�ϻG���z�7L���	�gwB��{�V�%�]&?���K�ߢ����Z��5&�j���u~����Z���s���j���µ������u�0��(�fo�=.���c��z��zL��ye����D��!^�7�zˇ^��_��w�K������Z�7N��į�ց+Ms�s�N�2U�^�W������+Լ��k�(��=h��]PT�=sj
Jv�,/��n�[PR�ͶwkU��?69�Y���5�����>�ݘ��#���p��D�	O����&�]"���ng>!|��=%����*(�.(Y�XS$ֿ�;jJO[� ?l��1ޏ��!%�L^ʾ��xϜe%��ꂲ�\��μ���-nwA��wuA՚��՚(߭W�<=_#�+^39Y�(��5�!<�����'�����5��A^5P���o�n@�Lv��C��%�=����e�"<M��wI��OW�M������K����sK����H�?8�d���,�n<�F��פ�� �5�q^[� _�f�yU[��ו�75�<UP�lj�C���x��1�|������1_7���3�w(A[Aa�=ȏ!¼/�^i.m���m�䤶�^������^���oO�A�J�%����k�O�S{T�
�>գ������b�\�U�;��tr���)���
J��t��t��S� ��p_J�]��n����Ʈ�6��"�9�Vgrέ0�5kE��;�����
U��_��$�TzEt,w���9ů:�P�ݽ"e|Ϯ����nW�4�_��d�O���w"w$�2���b/VJ��Hz�u���I�w��fy)��r�~�\=�;��(�Y��"F�{�&���w����4��C������XH��mC��$���]U��D��K�v�����ɞ*������r{�Pn1«�MN�5��XP-Y��^t"/��� /C�c����X��ȋ��a���"/4� Ϸ�V?�Q��X��8��vr��^�X`������WY������F�o.� �6���9Ӑ�~	!?��}���/]�
ߠ��������ĸr�<��<e���\�|T�=����{��6�3����;�<�-�W��|��z��Aʳ���P[��׉�Gzm�r#|��[w�[7�z|5��^G^'��/��/��{r�.(��=y�Kv^ŢmG��m�vw�1m�����RǷn�����zG��,��k��Տ[��!�{<u]6���x�9�S�s'���w>�~�QĀ����|�0/WHx��h�t�����< �33HO�u6�ޯk/y~`�l��ϯ�f���s������Q�֭����6�|9�ݮ����a���ۓ6�!�\�:�������=>������,�i>�>M���%޿�x�˒˻6ѷ�򾯠.���v���aw�������o����u��4���v����5��c���^��|���n`�A��!���t�s�ud��˪�d���ۍ�GzO�M=���"S�U��ސ�_�?�&\;�!��ɮ��G~fC��E�?p�B^D��Zȝ�/X��{�XȽ�a6�����-��}�B���Mr�T��K�0Q�!�����%r;F��,�?��k�>������#���K}���/���A��y�1���$W~�zy�2̗m)�s�?����O)���W$�[�����$�orn�l�+��7��[������/z�Ы0�ݣ��˧�!�Yԏz��hS���z�lS��$�ՙ���R	7�s!?�$��	�y��}zze�`S�7���x�=�⍳���	�nc�y����;~����S�3��ä�o������y_��sv�)������yߏ��f�����8�J(����z�hu����Of����F������=����y_���՜:=�:1&��ڃ��۟&\�?�����7��?zgл-��ɸ�'<ڜ:/"��<������s[Mok�x5�^]��Gjz��߬����F����,��ȗX�}��-��7������KZR�myqK�s�Q��[ҟ�NH��������?wu^ؒ~~S~�p��5�5�������uL��s�3wf<wU�U����5�~[K��zysK���NcjhIN���%��j�'��%��"�F��@�����i�o�� _m!����9%��z{6����5�K���,w-�۳Y^�@o��I;z ��M��-�f������C��d�������]��w���7��v^�^2�6N{^�������.�V���O����B���塅z�JY��~��z�[,�?,���L���p���yK��F��iI�.�&��i�����	ϴNP�V=!넁�/y]R� �{�)����-����%v�;�Krnϸ.E��'2�K�{��M�.�̸.q~���)���Cxɦ�u�z϶lS�$ ���ۀ�k��%�b*\�����(�7M��O��?�M��'�]?S�Q��vmJ�?���M��O����O yۦ��G�7|fS��3Bx�/}y�P�K��{�*<��/���=�W\r��^��S~��ӫ�������Q��������t�7��_�=��s�����p�4����ͩ�� ��ͩ�gX쥜��~�����.ۜ�?����-�?n��3���W�����{�4���r���j����;�9}�P﫟ٜ��,b��9}�(��L�u�t.l��Z|��c����fNO�U�*��-�������V����G�j��?F�{�U��hy����p�5}�~�5����i���+���yB��6�㲖W�/��W:p�|��������)���m�~����;�%�ܱ��-�?�7�S�w^ے~7*����8�c[���싓�����?��.��S翋u�������w�E�w���y�����/oK��"/���#/���|���B�@^h!�@�o!�|D�?e����-�?�LrU�Q�*���6c,�n��en���v:�R�yy[[�q;��k_[��@�ߖ~�vI��� �=��m��9}��n�~�m����jK?N�%<Ӹ�E�L�����<N�XJ�<�9=�Wٓ��<�%��E������?�5�8A������}O�8���銏1�<�~�V�9�d�8�C~���q�[����2��5��?z�<��������?���v�}%��W���r�ya{����Oy��R����K��YD~���OȣO���5u����=�b�t"����O����G�ޮ��B�G�<�Ĳl}A��<�v��v=�Mi�c������3��&ގi�����=���t]B�EKh�d��8���y����2��FV��z�GԚ� v�l��ܓ�N]A]c��+
VWԭ�[��:ŦrQٍa��fb��ɂ溂����ꂆ5i�j����筲�H����nMݯt#?�5�y���n�3"���N�����;1�OmM���pm��}�����y�3$��z����;�{B6���;!������,��%~��?�%r����,�"w#�6��"�����<�#_�uC�����������[����Dx�?�{ʯݒ~��J�������t}��j�9o�����_ub�[QЖ=bz�x��8�H|���,ǡ�g�jLÐ��'��m����1ɵ���Om�nϪ��K�v���ﵗ�w�*�	���#U�19����b��'Y_[�~��#�7"��~U��>�O����w�g~�M�3��b�,W߱j밨�O�l���Ux��O�/��S�{����O��m6�W����;�aq��Q� ���B~�#�>G����v��ǵ�#�8�s�n�������KՇ6ν���㜺%�c��� �Q�|����~�U˿���;��=��2&���G�U����x�����#���ϵ�w���Z�N=O�W��v��^�S���sk�t���t�-�����q=��3��J�SӸ�2��zϬ��8C}5nz�?���ךv�n�ح��'����?���3CoI�~�j��"�s6�om��>��n��,�i�,��z~0�ު�ci���_������W�B?�~�,������ߔҏ��ʨ�=���٧3��u�W�L�{���K�I�G!/�����?�:����Y�����F���B;�T��'���|=������gҟg�z&�yƠ�g|��?���������2���S~����ꍗ|�1����r��3�g�P�ڞ�<Å�{{���3�g��2o����7oOmo.�m�S�3��^�i�]����r�qC�_��NZ�c����G�轶]�g�4�`6���������=�ҷW'�U����<�7R�M�7[�@�Hn3Hx��=����r���~���>y�~��^�!���@�}3�]ˣ��;��,�껗�Y��w0OY��w1�Rϩ�w2�Z��������h^�������E��;��gS���M�O�=��g�ק��gS��F^�l�����-�B��BF^eag��B?���B����B�D��l���5ț-����,��G�i�gy����w[ȇ��[�G�ﳐ��� >d�k�?�#V��t�y\�7��Ԅ��~�,G�ڨ�:Y_���ۀ~ib�[ko	oK�����m�Eމ���uM�պ&�����$��V�蟙�~#��;f�?���Y菠�<�	���B�t��,���g��Z�G���b�������'��i�Jx��O�]����OO/��O�G;W��S��>���������\���'v�fq���.����;MrՇƑ�uM�]�\�}�k��6��{����.�[�?v.t���\�b�d;ʿ vꞟ�9nm�G����}~y��|�nyy������?�Z������:�~��?�t�r��YD��|j���*7??��GZ�%~��G���7<�z�R��y����a��UL��%<������}4u\�������f�F��,�c蟝���	��}_ax�I�u���U����C"�,~���w����"|��Lv�Z��eL����{�Wi�?����z��~]W`���}�uA����9N������ ~4�q����!�m��;-��%���cB짛?���p�����ݰ3���O���D�6�q���W��o�?rĞ6\�q�P�߿s��G�S;S�?)z���ˢ}=iq.X������7�6�k�?�t�����hC�0����ݙ�}�1ѿ�<����>X�*�/;S�8�_��� ��L=_����g:_V�k��N=_T���ϗ�%�oT�O�=�	�SϽ�Ӿ��?��$��;��������ϳ|��|I}��Pw�<k�%�gEH���S~�O�ի/�<K}7�jW�<���Y�Ք����Yv��w�ϳ��x�5���]�|���ݻRϳ�P��Rϳ�w������D�i?�����}���t����|�	�Y)O�&���S����z,���[�c�-�E�f��c̗����[�� _b!�"������Mr��7��ﳇo�Iݧ+��{��o�UӞ�iϿ��Z���lm��ޅ�_�f���f����P�b��0��5�������_�=z;Ԏ<�Ԝ4D�>�礻�����~���愲�����^��B^�|�n��#�۝~�p�:ܽ;�:b@�K��pH���x8wj������k�[s3�#�c|�=�uD�Gw[���������﷐@�ow�>mX�O�<��>�����^�7����79���n��r?`[�kK\;n��ݯ_�oW_�|���,]r�&�}�A���b�o���n/�a{F+|/t段ݙ�n�,I�$r?b�J�����z2+��ٶ�d��r��mKaC��3IW�^Y�[�Y��In�oQo΍d�<��(��D�7�l�g��)%re��˜������}��{��澘��=�ϳ��U�G����.G1j�7!�����!�7�O�Yk{vJ�Z�nW�����ϲ�tj�>��I�"�K:���=s6�zŸ���'w��3�zYn�-`̇݁�2���ĮQ�Us�ueM'���d�6��?"?��+�]������+�+�+�+�+�+�+�+�+�+����?�׌U:��c�eJ7��M�e��Τ�+1]��v_i_{��f��S��Q�u�\���uY��&v���[����������o��3�G����\�z�;]G���l~���u谱�ϬF��>6ry���9;r�g�߿���o��x��p\=%���eW���SW�q6������d�X���vf�X��������α7���l~��%�w�X�ߚY=��X/��_�z�;�|�g��|E���^1�c�+3�ǟI=��2գ�9��+�8�_շ������/�Y=���w�ۗ��N��W�q6�������;�z<�w3\�ܠ�-�uC��Y爝�3�����x}���t����t��t���z������o�u�Y�7���v��gJ?�����pٿ�h*��K$�a
��&�h�P�?{q�:����Iu��_UwUg���ba�[7���Zix����;�w����Z�e��^�e��}:�6���I���w���r��\��q=����W���?���R�$��C�#�+<(<"<!<-<'�(���y�p��RX+\%lv{�{��G�'�����y�$}�Ba��V�J�$���

�OO�	/
�z$}�Ba��V�J�$���

�OO�	/
�^�����Z�*a��C�#�+<(<"<!<-<'�(��-�
+���U�&a��G�WxPxDxBxZxNxQ��+�
+���U�&a��G�WxPxDxBxZxNxQ��I_�PX)��6	;�=½�#����s¼>I_�PX)��6	;�=½�#����s¼��/\(��
W	����^�A��	�i�9�Ea�I_�PX)��6	;�=½�#����s¼�$}�Ba��V�J�$���

�OO�	/
�^�����Z�*a��C�#�+<(<"<!<-<'�(������Z�*a��C�#�+<(<"<!<-<'�(����/\(��
W	����^�A��	�i�9�Ea��$}�Ba��V�J�$���

�OO�	/
�>/�
+���U�&a��G�WxPxDxBxZxNxQ�7 �
+���U�&a��G�WxPxDxBxZxNxQ��I_�PX)��6	;�=½�#����s¼���p��RX+\%lv{�{��G�'�����y_�����Z�*a��C�#�+<(<"<!<-<'�(��'�
+���U�&a��G�WxPxDxBxZxNxQ��%I_�PX)��6	;�=½�%�3��}-���kݸe���/�X�uˢŋ�}T��߇���m����v���m�Z��7,�غm���Z|���4ڴ��u[�m��n���f��v=�cC�֖-������o�S��6�߶������s��-�ÿ���MHQ�ҸοζhC�ڦ�u�7�mnl������k7t����_����������=�ۈ����DT�T����]��e�M��;����֭��k7<�m���u��ٷ̓�l|��Z���&�ӵ5,
    typename T36>
class ValueArray36 {
 public:
  ValueArray36(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36) : v1_(v1), v2_(v2), v3_(v3), v4_(v4), v5_(v5),
      v6_(v6), v7_(v7), v8_(v8), v9_(v9), v10_(v10), v11_(v11), v12_(v12),
      v13_(v13), v14_(v14), v15_(v15), v16_(v16), v17_(v17), v18_(v18),
      v19_(v19), v20_(v20), v21_(v21), v22_(v22), v23_(v23), v24_(v24),
      v25_(v25), v26_(v26), v27_(v27), v28_(v28), v29_(v29), v30_(v30),
      v31_(v31), v32_(v32), v33_(v33), v34_(v34), v35_(v35), v36_(v36) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray36& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37>
class ValueArray37 {
 public:
  ValueArray37(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37) : v1_(v1), v2_(v2), v3_(v3), v4_(v4),
      v5_(v5), v6_(v6), v7_(v7), v8_(v8), v9_(v9), v10_(v10), v11_(v11),
      v12_(v12), v13_(v13), v14_(v14), v15_(v15), v16_(v16), v17_(v17),
      v18_(v18), v19_(v19), v20_(v20), v21_(v21), v22_(v22), v23_(v23),
      v24_(v24), v25_(v25), v26_(v26), v27_(v27), v28_(v28), v29_(v29),
      v30_(v30), v31_(v31), v32_(v32), v33_(v33), v34_(v34), v35_(v35),
      v36_(v36), v37_(v37) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray37& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38>
class ValueArray38 {
 public:
  ValueArray38(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38) : v1_(v1), v2_(v2), v3_(v3),
      v4_(v4), v5_(v5), v6_(v6), v7_(v7), v8_(v8), v9_(v9), v10_(v10),
      v11_(v11), v12_(v12), v13_(v13), v14_(v14), v15_(v15), v16_(v16),
      v17_(v17), v18_(v18), v19_(v19), v20_(v20), v21_(v21), v22_(v22),
      v23_(v23), v24_(v24), v25_(v25), v26_(v26), v27_(v27), v28_(v28),
      v29_(v29), v30_(v30), v31_(v31), v32_(v32), v33_(v33), v34_(v34),
      v35_(v35), v36_(v36), v37_(v37), v38_(v38) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_, v38_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray38& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
  const T38 v38_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39>
class ValueArray39 {
 public:
  ValueArray39(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39) : v1_(v1), v2_(v2),
      v3_(v3), v4_(v4), v5_(v5), v6_(v6), v7_(v7), v8_(v8), v9_(v9), v10_(v10),
      v11_(v11), v12_(v12), v13_(v13), v14_(v14), v15_(v15), v16_(v16),
      v17_(v17), v18_(v18), v19_(v19), v20_(v20), v21_(v21), v22_(v22),
      v23_(v23), v24_(v24), v25_(v25), v26_(v26), v27_(v27), v28_(v28),
      v29_(v29), v30_(v30), v31_(v31), v32_(v32), v33_(v33), v34_(v34),
      v35_(v35), v36_(v36), v37_(v37), v38_(v38), v39_(v39) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_, v38_, v39_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray39& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
  const T38 v38_;
  const T39 v39_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40>
class ValueArray40 {
 public:
  ValueArray40(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39, T40 v40) : v1_(v1),
      v2_(v2), v3_(v3), v4_(v4), v5_(v5), v6_(v6), v7_(v7), v8_(v8), v9_(v9),
      v10_(v10), v11_(v11), v12_(v12), v13_(v13), v14_(v14), v15_(v15),
      v16_(v16), v17_(v17), v18_(v18), v19_(v19), v20_(v20), v21_(v21),
      v22_(v22), v23_(v23), v24_(v24), v25_(v25), v26_(v26), v27_(v27),
      v28_(v28), v29_(v29), v30_(v30), v31_(v31), v32_(v32), v33_(v33),
      v34_(v34), v35_(v35), v36_(v36), v37_(v37), v38_(v38), v39_(v39),
      v40_(v40) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_, v38_, v39_, v40_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray40& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
  const T38 v38_;
  const T39 v39_;
  const T40 v40_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41>
class ValueArray41 {
 public:
  ValueArray41(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39, T40 v40,
      T41 v41) : v1_(v1), v2_(v2), v3_(v3), v4_(v4), v5_(v5), v6_(v6), v7_(v7),
      v8_(v8), v9_(v9), v10_(v10), v11_(v11), v12_(v12), v13_(v13), v14_(v14),
      v15_(v15), v16_(v16), v17_(v17), v18_(v18), v19_(v19), v20_(v20),
      v21_(v21), v22_(v22), v23_(v23), v24_(v24), v25_(v25), v26_(v26),
      v27_(v27), v28_(v28), v29_(v29), v30_(v30), v31_(v31), v32_(v32),
      v33_(v33), v34_(v34), v35_(v35), v36_(v36), v37_(v37), v38_(v38),
      v39_(v39), v40_(v40), v41_(v41) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_, v38_, v39_, v40_, v41_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray41& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
  const T38 v38_;
  const T39 v39_;
  const T40 v40_;
  const T41 v41_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42>
class ValueArray42 {
 public:
  ValueArray42(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39, T40 v40, T41 v41,
      T42 v42) : v1_(v1), v2_(v2), v3_(v3), v4_(v4), v5_(v5), v6_(v6), v7_(v7),
      v8_(v8), v9_(v9), v10_(v10), v11_(v11), v12_(v12), v13_(v13), v14_(v14),
      v15_(v15), v16_(v16), v17_(v17), v18_(v18), v19_(v19), v20_(v20),
      v21_(v21), v22_(v22), v23_(v23), v24_(v24), v25_(v25), v26_(v26),
      v27_(v27), v28_(v28), v29_(v29), v30_(v30), v31_(v31), v32_(v32),
      v33_(v33), v34_(v34), v35_(v35), v36_(v36), v37_(v37), v38_(v38),
      v3��K5*���"~{����ۃ�&�͛�=�f�ִ�=���{�b0�l�TC�C���o0c��[�����d�wi�K��u��`�V�LD�^"��2@ۘqM���ȮF���kHOT�%U��ڌ�Ӧ���ڊ������;Ɨr/X�r��t�"ifÿ���
�������Q���'�s���5���[���1#�K�&�Ͻ��~ѷ2敲��ൠ����z9�-tu��7�Sh�-��I�a�F�>�14�
/�O���8H�kj��� ����:�i;r�,ܦLx��EO��	��3d;%�Fg�+�sL�fP��@���C5
�Kagv>�;�A��7����YЇ�?� <�o��f T_���g�
�9���n���>���ȝz�C/�P.!E�6k�Xݕb�����"��B���o� 8�9q,�e�w���o#;�@?J:ï#�d�ֶ���w�1�I����2V�Ģ<�2�ߠ ���vu0��@��&t�`�UzU���g�;~_�S>�׸�T݄o�կ:�`��Fy��[��n�����[c@<�j6ؓ,+7Jtq�+��v*�����-9���D�2�oȸ$�i5V�0�[��o�?Xǒ�
�>�WY��Qw���$�^��-�����GD+�F��� |�2V�ů�@����@�7-<�(Qi�{�ocu��i��P�C���&��WȬ�s�_Z�� ��u�����-N����KS-Uʃ�Ҷ��VݳʌWX����c�B2q���<lLcg���+���*�T�������.�u�b�i`:��Ry��,%�R��E���_���2KoၞR��wo��/���%ʝ�%�%��Y��]y�3���J\���yz5���`�ܬd��X��PI���k����Ԓý�@;��F�#�D_1��-�.Tn|W�1�t+��-S��g��~��X���J�~�ޏ�݉�c޶K�5��'��� �@ŞW�d�SczQ���en&f�)߿��Hy 5,�X�M�i���0����hLd�m��Yz��G���h7f��"�V����{���i+o�6��Ns��%�4������l���K��z�'�g��π�����G��^�޾���d�b�~��8�%��
�U��n3���rwM���y0w�WI���x��+oa����@3����o�x�5���ܻ����K��᳙k�Y�04dlo���ؗڋ=��nj�+]�N�43�'�����d��+��w/ito�Ini�D���8�mP|(hr�+|��n��G��4�@;��=������
u0�[�!�0��J�U_�wB��ǣئ��Y����k�����k�7�ܓzV��]P)I��G���m�<=�-��`t��O(6�#��5�ܦ\���?��w�����5�����9CѻX�cjeO�/ǟ0G/y��f�.�@�P�'�?�Xg#�h3ټm�x�`���uzRG��Xw�Z��{���A��'�s�J�+m��BGѦ�#����
���I�j'���6O���+��;|iK��KV<���� �v P<L��P�g7B��Y���/^�g�r�E���ȉި	CF0�}�U;{	�Ż9�|�%�Ώ(7��t�)��q*�9x���8i�x~,�?4g؏W�tY�8�mnK|���'Ū�~���@;4tR��4����L��M���[ԩ���� l�s��$����|�uW��
�ת��C�
�B#��w��d�Jb��m���W��װ����{��5��b�]���{��t6A�sd(�3��L��l�%���|1peth��� s�8�+�$nA�B��?�Wr"&p�a���$�t�q�Xm�KJ��W�G���~��KT+�^����@���y<W�y����]�x�Y`9�1g�⥙��M�v➳*�GK!qS�¸����y�+O<��9>>�I�%�='���"N����dM�q\Řl�!��]:���c�ݔc{;Vǜƌ0�j�#�3���;�E����І���C�Ϛ�@��"��N�.��1��j�{!��;
�{����8�Sl�A�M���h�� o|V����5�7)@�W��|]��L�m��S�V�*���=�w4��+����r�W�f��|���Q�v�a�i|���F�g٫��'5���|�yD(ne7cZϞ,��r|�s���۠_}��X��"ξq���hɬ9��9ڣs�2����~�*���^�r�䛦c���܃ػ��|����������S�a�?Cw�}``$�y	�־��=@�taF�����������6~N%�E����v�xk�!���A�����w���eqȹx��tx�������vC���ꏸ���L��Q�쁊V�'��ACo�[(oʨ�_�/�N1���E������[�<�[��*�( 2[z�2rڶ�@�6�FOc/��jCӖ��<�zFY���2	P��G�����Z��}�F�۬���X��M��)��Y�7�I��H�g�����j;����S�=�4���da�5��y�إLxZ<%���A��c/��"-����~�!�/��t2��|�Y��;�m�m���`�Gu/����uws�:����9�?��Y��9�9<G>�&�o��C���m�^|�m�:\�w=�^�Ea����/Y��1Т�|��ϲ��E7��A�#~�2K�҇�2)K�y�R�������ir���:a{��Ho����9v@�/<
μ4(BW���f�B�3��'����9ri�Si��G+XNǒ������ߨ<�\��2P���V������Ը�΄�EV��z�ӟ�%�g��ȩ�g��k�A�,��#�u_f�V8}E����d��fۡ�+�v�Bi�>;�ط��:a<�G�:fMV��s�r��H���{l��y����qP���"2M�>Ŭ�,��o�S���/����2�������g�P.���|6!jP�{3tz[@pf�	P�N죛跿�X������a�w���sz����B/���&���U�[Z�`�'�zܘ�'�JTU�﯆Yk��T�.�o���=���A�C�:����J�e�/A��bx�2�/��
�g������7O��7_I�Ǹ�6_�]\�d���Xbq�q�X�S���߷��=���G�E3#>�^�}�������w���/���[��wU���kt+�q���O�3����2ԟn|��U} ��Tٟ/������ƶۿ�������̥ްy���mO��;�b�w3���_�9�⃙��L���Ey6S��J�c���ɨ%�C�	��u����I/!7��I4���=��"!ʰ�*��C��7�O�g\�'��_���]鄽��.u�k�awJ�u��]�?��ũ��ᏹ�Ņ�9}�z��N�t��7�Jޝ�%���᭍��ێþ���=���P�>�)�<�r�~��X��~q�9ݝrV/�,Y2|�/vߌ�9��<9&yϲ?Q�	���ݸ����^ ^��G�E�9�Rt�lF�taWb�6�诔���a��g���ń_%�t�Ϝݠ|�(��v����4�"�V���7D��g��_��bY���ú�d�c�����q�o��"6N�Ƭ��D��LM��� �_1�A��wm�q�!�W�7�P�S��L�����n��Y��=r�|���\��
�����})�_N����Qt�:������3n����n�hN��?�A���X=W��h��滸��D�xT<K0D��%���fȘ�uH>���vt�*w>�+i#��p��C��u�8v�m��%�� ���r����h��~2n3d������՜w��꾊u�7��e�fu29��'��|����Y��ѽ.%���v�'p�IC���}���L>����ݤW:�񦚦��=��֬M͗�{�䭏a�"ɧ��.�h��̕.Y�/�3��C��/5���>Z���e�y�Chc<�ϴE5�k�'4ưxx��!e���~>u�+�'ɟ���N,�r�~���e�Cx3��C���\<�{��;�)E���q�Ѣ����^��h��R}}#�����eZ��ڌ������e��j����л.�w�������������ۣ�ť�����)��&�'�+I�~�N��L��WnV��74����''*�=L�do8Ȳ˭�5Ky�av�qm���g���,|���=�N_�7��.�/	^iV�U<�3�U��f����ۼ�]Y܃��dm�v6V� �]ąvO������NMo�y�L���xqĄ�p��ή	��r@�J7F;|W��n�����%x�s�o܏�H`{Ey/˙4X�l�[��]`���ǘ�
C��a���6�!�����U�{��*��6|��.,S��7�xŸY�<�7!� b�|�i5��#+����
�����e��v��!��0��ϣ���x�u1�·Ҝ0�mj%/�3P���i��_�]���6߉�c�̊���4�Ű��a��n+O5�Ph�o�r�#�?�j��i2�,����G�߻�1�|�bnd'���3Ӌ���KG�X����ގn�Ǵc�҃��5�w�O ��M0��K�|.C�E߂�uYf�emr�2aA�πɿ_V�Kl61��6&9�X���2dO���8��*��^��"��F�6���n�r�,�ǳU����t%��W��w�Cr<K�'��;��1�qL�Ē{���.��WL^��ǘ�s��}���Fe&�����k���<ӡW��+:����	�����/�����`rQd���u��8��~;�WBЊ=8� �T�	��0���n?B�{�D��QP5�`�}��ſHEMձ/��"�_$��-o�ߴ��9Oɗz�h=c�t]��������da�'+�t^Yθ�R7LH/[X���W�
t��!C�12)Yg��1�6>#w��>U�UB������y��>��IӜN]9�Q5(�=$T%����!����UY��u�JO�PY*O)(�,/�[�9�dIyQe��A �6i��ܜ\Gv�ɓ���1�?�)�t^q�+�(���S\���^�8m�L����2�/ʫ�t�+uXoX�4�Js)�|S�/3�畖���%eyf�PaY�9�9�n��_%���tQ^Iq���3�����K��\�\s�������esy��c��ّh^��D�4��l"=�U�6^AnUIa�(sDӹ��/.,v�~�:X>��dn^���Jb���ť�_Ee����
bi.c������H/)�\Q�����ṡn��t8p�K+�ԵX�Q��ln%���4_�M�G��-i�WH��%m(}~�}v����rx������/rG����J�K�Ǜ*���"3ڣ����q����
��O���A%0IP�y�~�		�
����1�C�,�ʹe��
���
\�������P	�H^�+����d	�J��*���*uФ.Ah���2**`BV��
�K�᜼a�z�,4�Eu���P��2SQ���E.���p��T�/[�ț�2�T}�Ea.��˴�PB��U��r�
������J�Bh`�˼����;H�[1xө�yH��r�`�;0�sm�S���r�s�y��ҍu�>/q1��af��%��Ɨr�(ȗЏ���
�T�+qQ5�0����I��2r�%[V�9�E�����a0��K�Ԝ���\Ԝ|$.�W5CHx��EwA��Ұ�핇��\��xJ�*敄���f�ka1�Wi%iZ�G�0~����܊9HQ�_�_I�"U���y��<V+Ys��3����b�B���z�׹e%ԭ��G��3~�tbEG��0X���"W�"���6�n�:?���\�ܼ���\��@M�:.!IW��.b�k(�%��!m8˰�<�[)��&��0?O��LwGQB~)��^��-��uŕeIIÓ�:G��zD	!��CC�aA�rx9<�D�!G�#CȤ 2)�L"�CHkb���:�U��Wk��V���Pw�q�dGR�`VqRB�n�#;aĐD����>��1-=aB�n~qeU�ĤA�䤡	���c���͛�_�L$��U��hE�H�����T2��?\7�x�ph���vkR��D���ILĜa��
&H�ӳuE�f%������J�uİ��	>	=�&Bm�����F@��2OI�9h�����v��V����D�}H�sE-�_����|��e�}��t�h����.]/5v4]����=��2W���ڎ���������������s݀뮻q��>	�]�o��܏v,}������CG@�Ȥ��O�&�����z�McƤ������Ǝ�pzj�=c̘q����Ǐ#IG:��M�8q̘�tgJJzzJ�ĉ��7M����YX2%��)))��))X�ԩӦ������c��sz�t�̸馜�i�t���-�μ��Z��׆g��W>�o�?�H��L2�i�_l5W7'/����Lt�
u�W|�͛�����ȏ��c�������Ƌ�>�����X�,X�;���t��?��h�eم�a����P��2i��/��.0�~���������������_��������>����?�~����������������������짼<����]Z��SxN��w�>>�]z�\�))�]��˫�,���g�n��*�n��Kuw,��I����[������,����;��b�V�RWMT{���%o��O���;�D�7���|��]�%�Z)����o��싗2��u�5:�]��7ȗޑ�,���-]
�Z�[���h�-Ճ?�EHݒzt:��Z���E�`1�>��'�i}������{ 9��L�1|&�@=L�������j򭗧��|@�s%Z��6]hN�R��!6ISʤ%���tK�%Zc�g*�j���zf*k���hz�Ј&aK��q�]F����u���t^��������` �Sd��U���?������xb��_����_��(}�����Qh��ړt��;��=.�|���O<�D���O>����	�)R|Ʃ�?;����������!�JeDf���>_��W�-�x����O��1����ZB�c��[��y��Ѥѧ���-3�#��1�f�O�����A)���αs�;�αs���B-�"|� >V����Z#1�A�E\Έ��t�:X:Xp�T�`/qqO����^{}�p��f�k��|pԟ���p��Ǧ��J������?�����M_GYKS�9�0^��o]���03�_��GSA�1�ߝc�}>\��a:=�����R�V*Ub��i�e����P�a�5p����>C���L#+?x*�~h�1�_�s�1;SlDW�/����7:��a�5��O���P#�]�W�DV�Р�ư�C�y_Y�Ǉm�65F.6���/gUoZ��e�jd�9��>D|k���pu�xC6�3���3��{3#ܢ�g�(f��@�u�٬噼���gf�gt�c4�0�9�fN�dֽlx��
55�03�G7;��h���eXM��F>qn͘v͈@>�f�3yC7t��8��>dR�Q���L�L*�qT�wff���-�h�TCd6�\VY�T0������yVD��l.%��raӃ�
��yA��D.��ƀ9F�y��أ;<�r�l��4�d&S����3;��ټÅ�g�_f�բ� ��5f���h�g���>�h��v4����f�Gf2Y�y5�@�1�7rΚYjŰa:l5�傭�(�3C�h�1�P�X�a̟i}&����
���4���̘�4fed�f�-k`B�[z���3������QF�I�L�������lc��Fa�3�lm��BC�ʚ�����όۡAa�LqZ��i�3�ɹ�we�cf�Zׇ�r6����f�af �#��:�rf��������6[Њ�_�s�QP�jd�9�d(���4^g&w<������l^cf�2��&����NJ�И��Rc�{t�:�a��PQ��4}���`��6�Ɯ9�\3�����7fFd� 1�!C�Pb�P�@n�fr�/cS�١{Δ��N��gs��8��\�g2���vmز���
�Q�mF����A�p^��2�.eZ�Ȋ6�)�+#*UвF�a��Lq�Ɣ�Q�]��w��݉��7k�-df��T�ꙙ�̏�����v�d��%���:i���@�
 k��~z�8�X����5ff�7���7rI�c��q�3qǴ9��5� ��L����k�u$C+�[���cUc�~ʚ-�l�^f��ڛ�v�l5S@�?3���͌��lQ1��<5FKdv�X���S��Z��HC���h �V�F����W�[����͌��A��F���4m���q�`�q�1b��a�fG�16����yz`G�$7G����td�3p��|6�Cch����1�j�h9,�����0H��q��e�h���LQF�vu���Fg�q�S+�3�6�е1�3�GV.,�V��9P�����F��О�lf�5F�Ԁo���$J�٤�C3��@�_lL��`�Cw_&���Y�"
�ff�Q%ffF�v㠳V�t��	���à!Wt��YcxsM�-�z>�3��ό�a��KF�o!�(K�,4���p���C��f�*Äy_fM�>���ӈ	(�DkP��[��F�A�,ߴ��*�ׁN����B�ؐZ2�ȷ��!صF>kD�
��C��-hl�������*3����0}c�j�7AЍ���vv(l�e�����>�W>�"jj�Dq#�e��4�#Q�v3E��Q���bD23bW�͙9
`�m��{��(s ٕ��gZ�!gfƳY59B1��&;3��?8�`R�7;j*-k4�Y�ly�Y�p$�ZH�*�\3r<��Y6ݘ����n�.��Vc�e ���h4��U�k3ø�QHfU�|jc�6ƢȡCޘ�k�a.эF��;�'/7��b���YJ�i�=�m�0�$��;�����(��$:K��c@g�����o&G�`c�F!^7�3yƿ1�#��Q/a�Uy>y�6�,;��)gY���.��+1���rSi���k��Y3�<�cVG�D�`�g��q�œ�6��1ʵq��k��U�}p�rϷ�h�7�Mr����-�e�H����n/X�q�+7N����2�6O��E��L-Y��ݩ��O9�:�S߲lˏ�Ǭc��lq�=v����j;L�6w�b�:0������x������u�O�|h��R��X��y3��!�=*����eg��ʕs!�߅d�e��>W<��s��"vcŕ'���������^�h��m�VϢ�O�l�R�<���������ǅ�ي���mF\�4v�A,eܳEO�lL�����R+aS�r�W|M1Ƀ�����@���*.�}9u�-۞��"G()8�@�롼b�z��@06��dGHJ�|��pwy�m�g����D����B?rO9~�\��>��T����}�;�>9��#Ve�J��ߚ�l�����1�O�<U����J���=_�b$+�O$c|괨̋�ms��\(��v�r��cuz�u���>�-#T�&��)��2�A"��H�q�	b��|�iObt�\ER�x��ݞ*!���N���b�� b2P�'"��^OU�E����AR��d�KӭX����N�I����$��s�M��K�[iVx���ż�l��A8�ݢoK�Jc�
���2��IZ瘜E���v��T���ܮ�opײ���b{��m��Q��𝹄/����r�íT*!�;!�Ē_��Z���m��^Sw�h�<����$oC> 9�J���؝%��N;�l�:�k:$��FH��`��6xPI��`����M��4]v�� �i���LD�u���ŘD� �`�(/�����^���d�����]"ujJ�}ޞO���%>�'���]�A�����gkuά����ǭ���ь�S�U��a��s��I���`��%���mP��۞�&��f�/`�����.?��6�Nk��e�6O�K_��|�tlѲ��}�c�a4_�/t���.��]w^�۶��%O(;�s
sK��lŏ��E�+[t�"J�����+lwi�	���q�:-υ(��"��L��Pۦ쯈�|mj�.BĔ��?�ݜZ(�/�ց��|A,a�b��Y� ��ߌ�R��؊ؗ!&�/	���O�vO��lXD"�jqoS
m�y���5	�P=7DSʇ.)��Y�㲄`um��,O���4�m4��<W��",�00�YZ�{K�mi�l(z�XR�5��ǰ�P�{B�0�\ơ��#;d�a���yO:�[����1���[�S��)x��Ǿ��'B��,%�5>t�B,Sí亘�u���^��1ԋmQ�"#fY��X�^�����lq��*(�*)0�NC�m(��:c\1=M9��m���2	�g��z�x���A<'{^6��<nMapSS�)�d�,1��ZQ(鐴O���0�1wE/���� d�-�������U�"X��h�\�{��X���I�������ӛ�5����bV�0L��x�wJ�+�K-�NV!���N���TXN/���Q��eTÔ�\���-�.̄�ǂ�T�z�fB�z���~�u�HzV�	��n��4�OrE%��R�(��9��E;l�w�t@$boj�h?�C��#a�}��B,T��ǰ���0�~�=����*)���-	A.�^�qNxX������^,�n�*��%���?�9<��9b&����y0�|G�/�>m���U��Z�H̟rd*��	��	�-R4kaP+�&�3L���E\��@�������9�_��+���щ�-K4ч�<�肌5�v��Ф�K�O�,�%,�8�}�׉i��I�IO�a���j�p�bɚl;0�*��]@^ �]���B�1~ᧀk���������$R�N�3�1���*���.!)�
ة ��e�m��q��k��&�Zf�i{A
;����E �E�䩖H۾�I�:�]oR����Tq��=��Li���<$d(�+mn���yL���ì��]��7K�z���a�	5���~ �
"!e��� �RQ�"/�d'1��~{�	%��Cj��D��

�����C����:���"CdĢ�Q��BU2Q/,<�T�I���C�İ��tC��9�UG@�EQ����<�kB�b� #��i�S���@0����(,:�"��=o�(��^(U9��I���Zt�B��)���(Kr(�_�zC��.�E:^* eX�Buԍ F�!_
G���cN(AG]@||'!a�� �/�\@UB�S�V.C�a�����G`B�u��ң�.�f&�"�����(�|��ʀ�0�]���h1p+�q <�+���3�+^\j�Y4$ܚ����x��%6G������dJa:�:�I�2��0��Jv��}p�'�<$�O��-� 41��w�O��e{��]�s� G\s!yׯ��9�L�q����c碍:D%pOET��0n+��L���Xj8:TE(A8��|ʰ'tLJ
xZ��r�R$G	F2�#��b�Aŉ�f?g[���a"h�Ip8r�%���疅e/�[�W�u@f�;"�႑] ��.��8����,�=؜:�1L5�c�i� ��K*sT5�GI0�DX����Z����u� �߽9 ͮ��&K�c:<j��2�/��B�R܈p��T_vȟ���^��I��i���b�A�H��@�S��xZA��\k�� �hJ�����@�6�.ކ=S�u��C����iɚ�d����3<���h�[�y�r#.�PVcr����v\�� �ruEvG.h�#�~G���$<��"!�� ��9��`P@��<ITn,''�g�d���z@q���:�U�c�rT�<3�lN!�C�W.e3�wi�S���J�v�:d;�y�L�b\�a���ڷ+���]I<B��^/�ٮ�e2%>��d�;>wS7���/_�<`��e5?�&�L�)�_�A�|�o����kB�Q��ʂ�f <%�D�GȈ�T+�P��8��	��"�:*��̑M&,�}�� |�$�4�5\ٔb^���A�Ґn��@���j�R� Ք�T�vlp��I�CHZ�D��'o�P-5�R���&� ��  <jk2��:>$�u^��ijtކ#L�fx��7ė�»MJ�$P�9x�e'����`d����IdLX2�gC DJ�@���
�0$�J�3�5���%�[�9p(O�����	dO{
��1�ܑG)8��Sh|�����㊀��n3r��ỵ�c�'j��?�^�3P���P��X-'I� ����N0X$��m�@rBh�I�뀡�B.yD��j�AvK��]�.��0����{p��bz`5|Ȯt�:1��L�c�6�X��5A����}��4�$����y�$�^�c���P�+@����C9/��LEp�8�W���q��P~�	�!��ӛ��[��'�R>�k'ܩH�!��9IHT����Iu ٚ�&�$��� l�ߤ�W�	D5���4�r��R�Db#ZZĵV���I�9R�V��ZtU��8Y�XtS��n���P
s�UpB�C�O·��#��Q�`�H����8`�������s��C�2X�D(ș�~@L͐�NDD.!��
q�>?	��=����Pky�f����%s���M�/Tnf��K�R� )�=J��X\͝Z��rY��H��a0͔�*\�g��8���Ъ�L|`V��p֡�lS�Cf{58�y2�x$�eӤ`��0����HS��1��y

 �P��<r�ω^j��&�����7�<���r�W	�
�G,r�ߩ�BEK,�+���J��U	���I�>�e[��y��� �xR$Qr�`9؞P�`�><�x����U��EBՙ�X���O1m��P��E�!��R�(��Rm����2
9����!�`ǸFf�\�/�����V�cT=�'ʼ�v��KV6zAȑk�6�����B<�KAZH�U�ɛ��Ő�9��q����O�pg�r�p�=��W����ɓ��X�Mʩ*����$ %_u����8�� 2�'V��kɨ������a�G>�㱠\pHڶ��� W����O�f�&:�q�[E3�ױ�R���� D�O)��3�,��Y�H�)2\��e���u�i�s�J]���F� ΅k�	�Q��R��uˢy���&�h��%7O��]Zv@���(� (}��ֵ��>�6 	c7�1GӚ�5�oR~a�����GyP.N�j�.��Ph=f�N�@��!� �%�u���Sa[Nז�j�ځ�zj� {���s�vt�K+�������0W0H��L�P���רS�Oy���^�����y���2�q�Sr��)�A��N$�� 9�}�Dw�%-��6LA���w���9�C�ǅ�sk�����[��V N"*�iPH������K�_sd�)��	�����  �t�J�[��]ske˂�q�	0s�ȁ�	�J��% �(&+N� �S]<
 -닎�P��SMp/!�H�ҩMO�U�Z�f'�c5�X�	�N`9@P~b�&���JI�CX(�\�%!u��)���Wt�4�9h9����0G��4mYA�M($D.d�b��Gs��ߡd��+@C�t�$!����|ل�jRƥ�s<7M,x--����J$�:Ռ�F�NQs*b]��C�&[��28���� \�O^#]�v����@ٴ2G�S��) 0B���:�XM���x!9��Cu�R���[:���.S=m���3�`XJB�2J���(2���ӅP�#߃�qt�b�"
B�����<��|X�$�?�"!�,���� 9�H_��Vl�2OL���TG
KK_�U� џK�Q���?�}�`q�4qM!�(�KKe�,=�����@�!|��X�@��o��p�v�a��]Œ%(���e uJ���2	�(:J�+E������kR��,� x�;��_j_��@������T�$-ّ&�%���aCP!���$��=����h�7U���A'q+R��^%�Tϙ��}����-��|�m� ��"�B�D�^�X��W����&��*�ڔ\D��}N�N��ͭ���Ţ�b��M�x^��V��l��q�,4��T�R n� (`ω�E&����0O���)�D���DH8�����~����9�谲�̿��y��a�(��*)gOy;]��Kz��9��x��DT##�qm�i���I�,�0G+~ґk��P(���yKô(d�֚)LP�GQ�t!O��Uk�5��eB�AU@~IA4�� th�3��)Y,�y�H�t�FYH�����_;wB��sYh-:p(�*�J���h�$���*�]E�R~�� f�O�q?�QUs��UL�H)�����|j�`,9%����2[hJ���D&�lךj��M�]���� a!b�!����%�.ʑ��)�#>o--Y�U�N��wGi�ΣDK����i��v�f���i�
!X ڍ�J��(V.d��"���F�4"�}��٢Zc�Cj�N֙��EĘG����z�_W�=���T�(f	ײ15Q(;0d������Y�-���2L�	�6e�1���� ��'�=�b�!��0C�q�0�@E	
�%-A�(qs���!\�"�&�!D�˫z�O«tM�O���"�k�u�N_g�XD���φ#��ɅX�9[hٔ�^��jN+:�^G���O��e�9)�J#�*�T@��X���K��ԡ��\�P�褱'W���)?N,��Y��Ŕ\���Ar�)o����)�]�=�Y0���3�N`�,<q�j �.|�vQe�Q_��j90q�1�,�X���X�� �s�T�%PC�mIG��С�j����bE�#[�PR��dH�(Jc =�?A�kc��
iE�lQ�w���3b�Sg�IQ�.[Q��a�sF������ҋ�G�F�� �.ຜ9�T�-�q�x
��N��b�P���h,/v9t�(u���>
�"��CO�cc̀��� *��ВZ��ԩf�U��ʏR�n�o[���]&A���#�O|�<�-%��a�Ҳ[ak|��!��6�A@)J:��쮋1[05�<���e��Q悚e@Z��q���\L�G����V(| +�R��z{U���$]�����,I��g��r�eO����4��+�wG�����I��' m=	�C0*R/ThѨo��:�+�;���9�ޛ߃=���-@�Hka.���0w"�k�VVw`ni��Drq��G�)�"�Bޫ�sD�N�
�<I�fU�����Z[YS��_�-r2X��y����"����"�:{�W'�X!fW�#I��u����I��ql7p	���)�����s2�q_	�e���'�����h�����y�'lp���S��V�$�VuR0�MD;�OÙ��OAn�i���{�8MR+��BJ���iĸ F������ī��"�@8nj��Aچ����3������q�i�+!!��1� �V��c,��	�%o�ז G�J��eě|�o*�8������.z�^qii�AQ��0[�I�0s`���}��ԈV�E/��1�����9�������zP��{ҍ�6�^�_Z'EV�2��,@T�B��z u��߯'�rщ
�[ڣIѴ�H��ݏ�mD���B'bN���i2�2US)E��S!j��6%�B!�uZ.p]�����IE���j')�p�S������BZJ'�p|��}:{N�$PX~ŧ���.E��5'}L��Ӷ�v)g�+�C貝,R��Ӏ�;��T$���%��M_E���u\��G�rɐ��6�D�a�] .m�s��!�U�4o��Q�L{��B�dqH�Z����3�ӈ8��1D��.T��h�L���
�9��S��W���	�J��`�h7�
��d���E`sR\��0ըI�bg
� �;�a��!�K!�B �z�piͶ��;'�^��O��i�T�0]�؈���(�Q�]�j���.�*��dΙ���-"T	MOKKo�r��e	%��B�je�X���K.U���kDdD�k�~ٱ��E�҅�S���#. Tܧ�4���
������'�1)�>E�d4dȑ�<�B9��T��o��'3��'(���X�9|��.	���ل�����PQ+ r����ME���R�Q��)�YPK��#g��dE�S��^Sr�=��x�wzzyMxs�
%CR/��8 ,��a$��dH���pˇ��`�	}�k.�P4�q���w�=�t����>���B�H������D��5]Z�]�ʵ��D��lJ�V��$�R�S�L��c��
j����a�k���J`3��K���.�9�δ�1�n[��-R���m������M���mIM�|.-6��ȣ݄�i��"�2G���>�ΰ���k�.�d��19��JR��3`D�c�,��s:&��E���֪�yH��K���f 
5����c������FV��Y�I'�$ϩ&F�#][���4@�%�F����^'�h�zڱ��d6�X#���͐�`О]�:z�pÞ\@79(WG���u���^���Ͷ�����J�(���1�zH���Щ,�A_D��*q۰��u抈����d^$�"�K� 9[Z�����u LZ�Ne⸵���F�'M�̽�Dصr�8�lQ������m�7��Q���H⩘��aDK�u�"��``T�
I�D��T��`��al�qA��+�a�dh�+��Iw|ڦ���d�2�D�t�RI��zIB��������YLK�K��>�l ?�����%NGE.E,��+u���. ��Z�X�%K�x`yT��fR�b�pŮ��P�-KquGy��u�\;��6���۴��t>���y�L���B��`��O�Q����@��:;�K*����
����I*01��vit��UP�L�K���z]ȔQ<,E7��ED��MڥD�2AU���&({M�'1�>u�-5�\_�ܵ�/����۲�Ꮣ�F�5r=?��?.=r�\�<v6<x"� 8;7�W)�AI[�f�Kۼ��&3&�<MP�yG���٘���(׮%�%:��M+�9�<�\x��Q+U0.�c;��n<I�oi��d�S7��UyS�؆����V6e�e[vh�&�	!�F��ћ�c@)0o<
�@�F�q���/��j�v��	u�sTˢ�Bw�ӛ��Cq'J�Ɖ�E�.�,�����Ԟ'��X'��}�I�-�����}��@Ҿ��p�(��à�٣U1��-B�ҳ���cu|HfJ���0 �x/$[B�dROq+�C��S.�;�<;�q�k��-k9h�K2����WCr���&$-�j0eJ��
[:��C����^�.�V�vi�4P:�&���BHx�RpM���酌0�I�:!��'�����mÄh ��je�z}��,�V:T�c	�Ȉ�h�ۮn��0�n���0a���^o���qi�����z�05n�~�ñ֩碑8߇W��}O���ZlS�#n�;�|2��lb��_n�w��ŀ?��@��)�dӕm�q�+��1h�/��V�$$�m�]D~�ص�܂���}E[�p3
�q�-`F�Mf�\+Ğ�$z�Ts�E��G�kM�Ǹ���s^�q�@\�����eA4��s�_V�z_<�����-h9�Nx[��� �B���w��u>FȠK]�*�_�:����K��|8KC�d�\�A����	(���'������A\UI��h8�?T�\��]�G�R�5{^Cޥp�����q'��y=�-h��A�C�3�5���)s�L��OjK(�	`�WhE^�K07-�i�&�M0����N�Rz��5��g��zx���!��`m.-�g�6C (�K:j �#�L��:�E
��<o#�@�u|���}#Zf6v3 ߖz����͠��|�٧��]���L�_��V��Ά�vZ:;��h}�d����#�L�֩�mn$�]Z��lt�F�>�M+jE�_�ܒt=/u�#=�Ng�mtEE<l;���"��d�M��h�X'Ћ��qZ"�e\H@ ��>�L��	e��\K���RꗧP ?о��}��[�0��	���q��F��j�w[�$�s��n����r�CPzq�θ'�5z]A����ݴ,�Чu#��6-r��J@���2:StDYNߓV�H��6��Q����aF��q��� �)C���~!�7��g�;�Bm(��t���%��C��a3v~���Dw!)��^��lԞ��W�������MҖU�'�<���������K(r��Ю�&�؝6�0A����2�5����IZSF�~@;����y�yQ-_�6�ȡ���Jk�L��v'D8�d�,z�*�+i��9��vn�����g����?M�X���:���@D쑢�gզ��>��SڢV�@VK���t����g�g�i�=�����`p�#V(SJ�-e���J��.�r�ڪ� �dW�p;�D���Y�����-�Y�%gA�ODp�����%�rhG�ԋ�ɓw�����5E���
�i�Jk�M��E�x�V��]�z��4��ǔ�E�)b'��m0mM�9� �?���5G��F�-����!"��l-�wk�t�hS7�H���@Ea)���dE	NQ��L+�I[+�����C�)�Ŝ��h	J�0���$1���kcn,��@h��p���޶֙��=D{��b�v��a/u?pI���-3�����|Z��4��7*�Y���Ῠ����A����T�E�n�3Q���$V�`�G����$q�"I�}�J�q�yt� ��>�U�9�D%����6�T��8څ��X�G"��iͥ]Ͼ#"?[��S��t��,Ed&�����Pw'�]�(�U�_Rl(򋄎�h�f��6�T�O
�pnM�&�g1��$�0K_����u"z�0����՘��ɂ�=�e	O��&�R%��Q�ށS����z(�-�N$��F��ikC��1bim�\��y��ȧ4T��?:�;��UuO���G���>N�i�)�uZѡ͕�^c�ҋ�$�M���U���v������h`�����g��R,�B���L�;����j�i�d�(���Q.ғ��Dp���<��٦�n;�����@Gܰ�6a��!�1%�ԣ=" ���i��B��~	|��z7�j/��T�ƴ��r�L�$FM��z��@7��ނ�]��7�D���M�h.v+���I9?
���ԭ)��'=�ʴ9�۲���4�מ$���3u�b�{v�AvU�ʶ�:��c�l/�w�+��.�Q�^ӑS�q`����#<�V�.��OB��K��jR�iȺv����<w��N�F�V �:+>PK-ukZZ�E/�k[_&#}��9��٥ܾ�+�O=%�R�ϡ3Y�[��.2����l��r���I�+B,��(�%��h�&H�t�����W�i��ށ�mIj]P�L"/��p9�����r�L�!�q�w�twizz�^H�n�<��iS2��}::�r>�qm�j%�a/sn� ��1�Nq��:��S!��N��s�/�[Ji���h�L���i�|�>jƐ�x��5���� �]�0�� `c�vH��������w	�[ïZ�I��Mr���#�VS�Br�ż\XY̧�C��N�S�\��^A�b�	��F�� �i�1bW�821A|J��NyEZI�a�O3�+��B(�"2�K�)Ei�Ko�d�1*��Q����hZ��*һ�悞Cv-�/p�E�)aZ�~a���Zv3������:	�5�����9�z��5W�vlB ͩ���4�J�:�V����U����`2���kY�"@�/�+p��G�pC2������~R��֔���DNDI��\a}�^W')/lA��{;�Z�����h_^=��«Dl�q]Z>��%Di�d]��|���� �wh�! �j�&I�=!��4w��6~��Ӿlx���fK�z���K�%:,����n��Go�݈�`E����%_k��2Jw��vSzy������m��rX$N��!Zv��%R58�~2��)۪�;pH�v�T�&-[��Ny��P�Y�)H�;`�)��ҡ׬�]�x��uX=��R-�t<���@y��w����8K�J}��Z(�S�&*�F��K/M�e��1	L��Z0�bя�tM	����_�<��"�&ꄠ��f4E{	�q���n�&�s���Ozl'I+���d��+S:b#��X�����v~�O��Ca\=�0 ʥNʺ,�~�B�69� ��.�o[��mF�<��:/�im�ʊ����mY��?�����n���t� ����&<ʹ�ڂ������C�6�ʔ�pJ�)�	-�$k:��Q=)�^b O���W����~�M`���M���-퇌�¼m�]�gI�#��]��ə��_`{.|0�06'�'2hr��U����#(-���/�@�H�μ&�h��@��@��r*h��Ҡ.O�C�5�l����Ş9[���TG���:�J�b���M�N�f]z��V]��6�Q}�cw�i ��=�M����RKR�㥭_���vW��3}@Pg	X�Bz����Ùs�)R���iO�:cZ܊�*�(��!�Q<�<���=�R��P^�fO�B���l�[H	���s�2mkTm�?����e&=2��kF����L�pu�����%;��h�+%�~<���������j0�+@Am�=�@4u�Q�Q�^���>�Ni}�[u���˪�6�1��$i�OݬR�G&k�duwE��*�s��&/x�E�lM��L [-^>��P��(q�sV�G�@�bZ40�:�C�j; �u��=�����u�>Q���A���(& ȶ�(����;��`�\�PB��T]YnY��<Y�`��p�y9�lrѕ}@Z��o�;z���^�N�~�@��S�=]��g�dj��)�V��/`R��XM�{�	����蟒������Ag[;z��P�&2�h;E�'sh���{�گ�n_�kF�uhM�^���:,imSZ���Pc,�zn�Fa���,Lq��}k�=7�����y����"��1�sӛj'���~R�	Z�\hA"�d�>�@	�< ��CS��!�ѫ�M�z���(��4��x������s�� zSa�޶��H�3��ei���r�>�&�+T����*�6�i點�����4�'�<���;�?w�u]K�)��#J�r�3@�D��Q��V�벋�HX���WF��5�\����F��-Ϣ'��E����P]�]��p�	���R��t�u4�I[�%c|.��� <�@lAj�D�Dkɴ=�R��H��Oz-��
A'���&>�hц/T��T��|���\ey�^Eb-��IQeMH�N�`��i�\�}))�0�տ3��~R�mUsk:�H�VE��~���k�$���Eڤ�(��T˲�	�)0�~�+�,����%e��?j��P��QՁ�	 ��JY#C/�Ve.k%�@��A�� ��jSVGo,�o�NV&K�c^�f����3Y�*�.�
�6Xp�8���X��.2���"fsՎi�v�h��XNB�w�T�z)�-�n��x	���ꊔ��j��ħ1?��WV�p��t4��V��B�����I�K6��m�f3��o��}�N��lz�YqX��e#���k����%� "3����AHPL�G�����d�f^���G@�%l�䋹�wJ7�x&��C(C�.�b��Dx'��K.��~궚>a�C;�αs�;����?��s�;�αs����̿\��������4gWG�+�����Z�poc{�j��a�ߞ�7���U7i�Z�Zh��W3k�ܰ/�C����r�����y�2ʫ��|�s�/������c�R^Fxf�h����w����=Ͽ���|���ifd;c���{>��0>��fp�/]�<�F�#��҅�2�^�t����ۗg�Y�n��l�G��WG�Ā�۵K�m
V� �cu^\{c�^�r��g�ܮnlf?�����Kl�d�����,��="�y?��ؗ���f�,�R^u������}j�d�Oi��.��۰��b{[��Vs{!�rI:}��t!�z>�Y� K�����}\i��.��.(K��]�]��|o5��p)uW/Q�6�����K�m����5�7���6�?c���sJ�`�������<s[��^ȞU���򳴥�+��>n#��^{�ޫ�(n/O7�7ϋ�����%K�~�t�qc��5L�����e��M;�]�2*��i�H�����˅lV��g��v�8�TJ�a�:_���&v�zQv~���|����v<'�ݸ񂲴�T��l/�Rq��q�`�.one�J�l�绷ݸ�Di�������ko��m�y���b�U��G#�Ë��Ջ���qՍ9��嗶�F�c7`��E�w�o,���U/^���m�Q�s���ji���V핶�K��*/�TGs��Z�_���t.Ia�o#K�m��/�Vl�S7��E��ה�~��b�K˨�y�^0V��]0C��m;Q���KuÚM�z���}��+��1'7\C)U��u��_t|t����s�[����e��W���?7[���j��T7��m������E�M��7��[ǹ V܈Ӷ�ѫ�ϱ\�T���^����V�rI����TG�K�Rr:�㶙K�s��y1��v|����6}�������K�9�j�"s�]����ׄ�/4�ۜ��g���҅�˶��6d�R�r)�}[v�z��}9���K��nsm�Ʒ�|�k/�(�Ջ�u��ט+���8�u���f�Җc�n��;UK��.K�^*]���v����G�_����땳�n�?����K҇��9�ۗ�z�e��$խsd����W/n=���K���n���l|�-��^`���{����Ra�%a�m��-�}�qOu��~���v��c��9v��c��9.�([��������je%�2�a���2��˔ͷ��y�<�@����r9{x�s��˃/�6���d]Ȫ2eƆ[(���A�\��.[��\��l�7�n�|S�5҅�#e+Gy8Q��
M;3sypk����˃+�^�\)y]�̐�F,�C^��FyXM�����P.vg(?��
s9���h��8\ڲ5:��A�6���|�G*/�Ϩ܏�]�x�L`y�T�\���3m�b���f�[XQx���c˛��#<H�5����(�lI�1(#2Wxfd����ˣW�1(L���\)|�Q.�x���rytt��������ؐCRTどNbyTq�{S.�U3��a����1��T�`���Q��R�AE�S��U-��k�&�],7�kd���*
���Uy�2\S�=��@��#�W�U墑/�����#�X4�C�+[c>� �ֈ���ЂY֘ݡ�,ῃ�St����i-�*��JVI������5����3PB_��V������Z?�Uu0/\2%J���漠~�J���u4��i�l^�dF\*���>��:1<7-4tдZ��i�Xvy��R��)2��ధ�����tb���%ݺ�2{�[���rp0q��*������U`���)>8| ��4�|&�9&-C!)�3�߰�#=1B9laL������P"����%�u�
��Ų�.�1��JE�jSk�s�A��:3^rXQi؏�s��T���E۱AJ��ڠ�+���Tx \C�3��О,�@��U��]�D������*���m˙{q�c���b���ߪ�GX}pC���Ѻ7��h��qp;Vr��9v��c{�b�c������׿s�/�:X���.��!���"*�a�q�W���_1�E�PD�#-�,���Ȅ, �1C_S{cSrp�\ƀ���M���Z!�'�;�����f v����v�c���8����X����_�<���LRGg�����>v~�w���yT*���X;�t|��TE=4V�)S��ܯF����Q~1ǿ=�o��O\�ȓ��K/��/]��Z-ѿ�wG�(������匜�E|~��ҹsDw����\;Rڵ�wKG���ՈK�Wܵ��N��O�����|���N��O�N��H��WQ�����w=]�⾧K�9��5'���5��gv�[o�K_:j�>�rG8����K�P/����\�w���S�	|��Ӡ��7�M��B��������	��$�/{;]�]��]�sǾ7����c���R��5�c׮��.�r���Wޱo���tՕ�K��.]�����}��2%��5Q�c�����:�_��*p��_�g�s�މ��{q�����^�k7��]��ݥ�-]�s\�ɮ�������o�wU�kJ�>�3Q��O��5W�N�s��t��k�:��ۋ�{�[���ו�/>7��*�ܴ�&�ֽ�#7_sӓ�^S���t}���5%�S:�2���(�><r���]��-��^�f\��M��CRq�5h�Tr��ø�(>��D�:����P���ңo*]�0>7���~._Gm��t�����Q|��-A���G~��kK�%>�~��(��R��ς>L����?�1P��Q���a���p�3(�r%�y�u}46�	���#�Ry\�(��9�y�;Q�+݂��)݉�nA�[������A�;���Tg���u�-��GyS��[�>z"~�[������z�e�p�e�^߻��=�����3g�Y�_}���
�O���3�/�����gϽU��nЇ~�칯�>���?@9�3_={��+p�ٳ�}�k��cЗA�9}��_�}�wC�W@�����Ϟ{��?9{�z�}�ހv@o}�!�wΠt��A?��9f�L��,�w�A�^@�����_=��K�g:gϵ�N/�g���o����-�y�ς~t�4�AH�{g�]}5�9�q]A;�m����e��ρ���o���/�>��*�m���r�/�����Lb<k����?h�����i�#�A�]���C�3�W�)ڃ�A?z��g:]}����܇����pt�e�g�����F�w~���YЫ��~�~�eЯ�{���0ЗA���`���@��Y���w��h����ym���-(���A?���|��+g�}���v@��	|}�_��oE���Ao��Q�����A����p�ݠ+�7��ٸ�]�#�]�ٻ�W�a��a)ލk��g�o�=w�4����w�qϧw)����g���=G����=_<{�ʂ�{��i���+Ʈ?�ϵ�������3��?On�������S�WM�yr��{t9�S�e��gPn�C���zދ����+�o҅[&�>3q��O]v`��]>�Ǔ��[��/�x?�g�UM}OQ��]��O_�K�/�M��%�?4�����[&��_����~��[&���7O���+o�����p��v]����&?�k7O����P��]%��I����5��ܝwO��7��:ڿ�&���蠃�����(�ح�\6ҿ[��_�����i�����n���/�=���Q�����=�d_nۓ��1��P�aßߣ������랺�|�;'o�x������y{�\6�����J⏏z��ó��1h���!y:m�_S�'����q����l���+�s5�u��6���yC7R���0���FƵ0������p`�Ǉ�����Q��OrY���ւXj�u�?��ۤ��uU.�w���P���㹗�\c��n<��=w$>^�u��[���{��u=��~;��B��x��u���S����ߤ�C�O��/�:���>a
�sk�O��)�]�s�Dm���Nt�?�L??G"���=���=u9�/�ܗQ�ٽ���6�������\�7�Ǘ[pi�঺qמ��F��Q�AM�}����p^�k����yಟޅo�J��^j������=t埛�2����J��ۯ8�~���8t~���rn��oЅ[��ߓO(�v�)��ߣ$y� �ӭZ��*�\��@�>���F��y��Ϟ�e�p��KW������p�gG�����>:y���ZN	=������1��mؽ/O\����įN:S�r3.�Џ����_Ǘ���mv�=�[�>e���Ȧl�eϧM��M�S���L{�b����+�s/�g�ݼk���e�]�6��=�}�K��u��ec��Ǹ�]\��o�?�Hnׇ�9����O���{�Gϐ>?E|�ܕwL�3�gW�nܼяP?B=? >�=֏'q�%\���y�}���k���ʵQ�G(��6�;8y�mY9���S88o��?��!�����+����ie���)k	�9{���{�������]���_�}��񊶳Ϡ��Eӯ��߿�~?�.�|���lFB�\A��.��+]�>�?�����CS�]c~�u�%\���_�N�}�����%���G�k��*�����'g�k�����|~�ğ�+��gP�(�o`����ms�@��4���?���H�,ڍu����S�qS��]�=�$=��� 団zy�@/o���_�5q`�k�� �6)�w�5��k���.�y?��������~ܻ�>�{���>g
� �?|۽��f��~�G�0�$[/
m|m܂6nA�L>��ww݃��ƽ�g��݇k�<�q�Ý�q*Gqߵ��F}����uq*�Շr	�����8����7rMr��ۍ����+�y������k/���w]v���[C?��K�jyS{p�@N���܍x���=GrG��2������13�O�C����}d�s��c���(����jז����w�o�έ{&f&?p����q��7Ξ��&��� ���P����=�羆玖���cf���8���4�{	�}{DN�1"����ܑ���~}�|M���=��_v��o�|��jP����������i���[��������?e0��<Q�'��i<�5<��=[��&�|�đ����N����O:��5)1���x6�ϒ,?w��[/���5q��� �G06���Ct�/O���]"m�~"��]�Į��h�G/�=��M��䌹��fzR�c�O~L�3���>pf�zﾬ���A�n���L�h�C=˨gmז��5y�e���TAo߳9p=�����sә?�i�KW������q?��G��߉����9{���=z��a��~~���)Ov�����u� ���?����?6���q���='�������|���wq�Q��>�g���;?���kčۈ�{�eo�u~S>�F(�M�?{��g�>��ܿ!�1��g���˷��wP�_v~`@v����Kg�-��C�3�;C���(���8{nbL��_�U���7g����F��c��9v��c��9v��c��9v������ݏf�����Џ�=`��3c�_;�����9�4���js���2��}��3�6s����3��Ü�9����1��9v�?�=�)�?2����smF��O�Ţ���K�&�\2�K�5�e�幂���t��П��}����w��_3��X{g�e��+�d8g��vd�����1��=�ǧ���/�x��W�������������k胆>n�S�>kh`h��uC_4�C_5��;L��^o��0�^C4�qC�2�YCC����������W�i�7�zCo0�����������5t��}��W��.Ӿ��z�����}�Ч}���Ю�놾h�+��j�w�����=`轆>h��>e賆�v]7�EC_1�UC���}C�7�Cz�����O�����]C�}��W}��+?d�7�zCo0�����������5t��}��W��æ}C�7�Cz�����O�����]C�}��W}��+�1�z��7z��{}���}��g��n苆�b諆^�K�}C�7�Cz�����O�����]C�}��W}��+?b�7�zCo0�����������5t��}��W?���^��?���/����=��}��?3�#Ə=��诜���e�_q�v��U{����7^�����k���w��?��R��6/��{�yS�\y�r��w��(������ܾ�~'��������f�C�6R�]oܻ�J����P.}>5��As�������?�/��?0�c�s��4ד��f9��b�{�~�۾g��<v?�q�������w����'G��8l������9.�o�������������8����c�s����c�s\|�\z�~���d�����7�8�\o���ߛ��\?e����k_�3�_��X��i��7������p�)�Ce�-c��4v��y<`�����?5v���.��7��w�=��!5��;5:�������GZ���%�����\U�0�g��w����O���C��>\9����?�����}�~
���?��T�}�~���y�R-��Ч���~��o���[�|���J���G?Qz��У�73��#ٝ�?�ȣ��ԡ���q?T�����=Vz�'}��g��A��ާ�<V)��㟸��G*����?��#ó��+�<Ra��������nT~��M�1�'k%���裺O�?���o��C�<�?���J?�ZV��u���
�z4>h-�7`�?cD�KQ�C4�P70��Ka���LH�a�� j6Z?F���߇h�֯�����τF�B��0>��
���B����0�OF?��������0�Og�����3�a6.���2��7�z4:M?C0*��]?��重��hNꇅ�T�j�q@�߄���8#
-Ì�~ �Scx�c`��	@��L0�)F�F�p�rf13C�o�4#V���e@̏�����H�����o��o R�v fC����կ 4�P� ��+�+Bi�����h�>(Bi������C��"���o@���+P�`�~+Bi���wj?:��Ag��gƢ?��� ��(Ox�ܽ	xS��?����AOT�:%j�r�U�mh�R�
(X�-���	A($�C�"*��EEDQ�*�e*�Tp��RP��"T�R��o���IN6�}������{��{C���=���^{���t��2�ц�H=��d�����$���kWS��������`�п/���������
��j���5�c����[�Y���x����q񯖍U�K?����\/�O�{MC�_-��/�������>��$��Ka���v��3>8�pV�5`�٣������wk��N\s-�K�_�K'����eėk��6?�p�w�Yև=����﷦�&�i�6�fӺ鞺��A�<��d2$[�>c\a�ܐl�;*��?���,�e�o<�I������'�焟~��7~��
��y��ɟ��熟~s�7����S�7~��,��o�^�����+ë��k�{~K����օy~����������G��~���)�>��aϕE[�͘8e��M{���d�Ƅ^7l>0y����_�b�G�u�}���zČ���-�>=���MR�/��}Zn{|��듊�{`��a�1Վ�߻=���b3N������.Og��F���;�#uN�?y��=>r��޿~<nԀ޿i�S#z�ϙݳ���7����;�wY����	[���Ua˪��W~���Cz��\�쒝7�׽���=�;f�uk��ظ�{�˛b_;9$���O����>��{c��&���<&���}��������[3h��'��\����)�xoYuǗb�yl^m/Ý��+�\朢����j�+KW��%kˣo�m��������6��{��l�p��k�MKﾷǆ�@���N��V5{��ǌ��������mk���G�U[�ͮ�����v�^kl�?�>�.B�	�1-Z�/Aü�|x���)������1��w���|�D��!���?��>^!���Y!���G������>~"Ry"�E��F�ä����"���z��<oG�?S"�����!ߧ"�?=B:��l�L�|�#����`�Ю}�!����"���1���|�������A�DH���"�[#���uEЇ��5B9E�à����U��G�#�������i�t6E��E���Hv>�>��{�z�!��#�sC�W��!�o#�S�G;���'E(���%��g��NZ4�]��ݑ�k8>�8��1���nct'����?9���bn���$�j��qǯ����Ns�x�'��_��E��00|���r.5�tN����DK�$�Gq�0�+�|��xQsx���rH8����8^�>>L�򩸞��&����4�0�#p�������y���p�ݪ�3��=9~?�8��'��E]~;>_��oh���9�J�;y9�
�+�_Og%A�jc{���?�S�8n9m���;��N��6j�yyX�9�竌�V�F^������z���q��z_��Mh����[6���^_�x��s�0�~��1ΰ4����y��ܸ"߭�?\O�:�������'](O9O�|<\ߞ��#��4M?[����|��������#��ߤ��c�q2��"/�E��k5}n����j����cZ�s9��c�-\nO���8ʀ�Z������3����&m���~y;���^Υ\�35�������2��5��w��#���'� K`����q�����^M�<��������Y���7c�k<�YГL�ns;��ֿ�v]q+O%���5�`	�����\م�k�D�w.7ή�!Moy���x���X�>Xxy��a�v��{ùp�����^���VHǫ����������\�\���h�K#ï���A�w������������n�ԕ��4����ߠه��|]��Y���'�w�fo�]M��M����tr5���5�����p�&gM>�z��~�ӯ>��c���
2J�c����ԡ�3������8���N�/,�:v\~6{�����ұ9yc������p)�cKJ�K��'eM5�8��9㳝%H��9���%�H9�!-(K�Č�܉9c���0sba��Pz���...(��/���+,0e�-��� c*E�y�L�P��9yR�xC^a�3�2�pr�a��|�� �A��;�hJq�3ېS������
���9�(;c�PX�]��Wl��e;!��YHfd�3N1�H�V��%�D32X�qyYW��I H�0�U0ilI�8�U��(;>�e<	�������A�2�ЧOFII�؂��̛�]��5v*��+�g�b`V'�/��YHB�).�d�h=/X)���8("�# R�ʞ�2���ȀJ�(Ι�U�p���2P�<^Av�3#���A���	"u�41����E�GA�
�W�t9"Ibp9u@�!0o�$�&�)cR��ǹr��2H�b
E �������&+��h�337�/{�/,,bO�ˉ!2k��S��p*#�$��%B(Ԣga����@��Y��y�Y�%��yE�v��ޅ9�_^�Y;//Hk�$����W�Q2elQQv�'��PX�19�8$�Iy"-";�TP������L'ڭ��dk�Z4�sAa�8h��� h��g!�1�f:�&��j��W2�p��d�'�V�IȊ�j��ٺ�N��qlVƔ<gn��,�*K����`�Λ�P������e���-?o\P�h'&{����,�F�=9�:��,,?��k�0��lh��B=����'u�3'a��� )2Uh��
r�Cd"i;��ةO,�,#�
�8EB�����փ� &Ġlg.؍\Pxa`������
��P�hs1����dƳĨT��ٺ%�œCI��LlY������Z��2RB=�ľ/Ok<T�Z]��S9�AU�o�� \;aW���6+h��\�J�%�#s��D{=h�}������A��Hgv~���w��r؟��Dq6k�X�y��3�'*`F�N��\�6�J�:�S���[�)ZK�V�y[I�m���(Ci�a�onK2LKퟒq�m����;�Ow�^�>�ℰ;n�+p6"��Ϡ{��ޅ��!��K1V��W�P����t����M�k����L��:����}��XU.��eyy���N_AtG�g�^D�c8G�;vp��1��9�*�J�7N;�D:�p�d���x7a�+�M��y"����d��������/��8^*��9^.�m����_*�Ǘ	x��7x'��*�K��"��������E.�����'�8/�ws<A��s<Y�s\�J��G9>F���x��?��R��r��
��՗�?�՗�����6ǫ|��|���k��^��&?�qñp����$�f��	���Ot�z��x�$�s\�G9�.�c9>F��9�+��8^*�9^&��ż����/�8�L�����ǫ��������~�7��7	x�f��$���p�2���:�[���� �'	xǓ|)�o�^�����g8^$�s�L�?�x������3Ǘ
x#�W
x׫�^���&ʟ������<�*�wr�E��7���Y�9'�e��g9� ��r<Y�7s\�8>\�r|��Kx���/�^/p���0Ǘ
��_&��_+���p��|��|6�UW8�$��9n8���q��f�z�/xx���q<A��p<I��q\�μI�^�1~�+�p�T���x���x��gp|���s|���8�R�gr�Z���&�8^/��s�A���x������i:!�G<�Y�Kyx������~�'	�	�'x����.�7q<W���x��;8^&�#8^.�9�X����R���J��ï�g9�M���x��/�x����*��x}��&�pR�w���/9'�u<�xo�����O�S<�,�&�z�9>F�-e���&�T�e�\�������R��e^��_+�Sy�j_���	��������1Ǜ��ㆿ�q�M�����-^�˟ ���I�7�eo�x��w���]�M���x��
x�N�����n��b��_&�<�J/��<���&�S9^/��8� �or�I�7p�E�7q���o�Y��8n�?9/�-O��Rn\�x�������R�w���	�@��	�0��xO�����
x�W
�T�����&�>��	��o�/8�
�����7�
�ws�,�q<N�;L��.��9� �q<Y����!��G9>F��x��gr�T��r�\��q�B����R�������k|ǫ�0�׻�7�����ë��)n��Z��q�����8�q����x��O�x������>��O��9>F��r<W���x�����2����5��J^�e�+�R�U�Z����	�9��x�i���o��9�"�f7���B�������[�������I�Ǔ�U����.��<�n9��������x+��	x�'\����6�����/ษ5��q>���>��I^��\�r�T��9^.��8�L�_��Z�������&Mn^��M�����L8�F���o��&��kr��8.�
�����{M�^��Y����,�'59�YM�n���,��r\���x�ǟ��8�$�=9.��.��r<W�/�x��_��r�'�x�/�_+�q|�����)���<�@����8n:'�p<N�ݚ�|�&Y���/��/�/i�<�~�^,��k���<|�&O_���(k��7��|�|�׼���o����x����&����7�q��7m����7��C�8�,�y?�.��#�U/��_*�;8�R���x����x��������~�����b���8n��x#��/�'x�&O?��S���Eޙ�e.q�B��s|��_������'�V�N�o��ic�(V��;�I�W���u�6����t�[����ux�T��:|�o��ux�Ѣ�!���A�G��x��t����$���"Y�w�����ux>\�w��ct�E:<W�K:�H��ux�ן�+���sy�:�2^�û���:��_��/���t�:|�����R��:�*�~�����ï���V��:�:�~��z���ޢï��cן�4��:ܬíz���7��_�ߤ�~�^�ux�^�u�-z�������U��:��^�u�?����o���]��:<A��:�����;����{��_�ߥ��/�������Ó�������_�ߣ�~�^�ux_����~z������_�߯����n���������n��w��_�����.��_����_�?�����E��iz���������O��X��:�����!z���C���Ç��_�?��>\��:�q����z������ß���}�$�:X�� {��Ԓn6m2���vWԧ=m7���R�dxB�nm
4��7�B�xj,PG�q�ѕT}it!+�ޏ4���D�F]�@ѻ�FW!PF�����"�7"�.X`ѕH��H'���u$�>��2�~it�� �.B�L�B��e�~itM瑞����'�)�/!��.F�R��	H_F�=�n�?я#ݝ�'��/'��~ �+���#G�}�W�D߁�U�?��@�j������'�*��%������;#݃�?�t����O����'�8�7�DF�'�O�~���?ѻ����'z�7�D�@�f��H��DW"}�O�'H���'�}�o%��~�^�?�K��'�O�B�o#��~�ۉ��T�H'�D?�t"�Ot1�w�DO@�N��qH�&��~黈�A�_�?� }7�Ot�����A��O�H�C����%�����?�W!ݏ�'�R��#������������[?�F�}���?ч�N!��ޏ���'z7���]H ��ށ�@��H��?ѕH��D���?��#=��'�M�ӈ�� =��'z!��D?��C�+�?���?�O!�0�Ot1ҏ�DO@z�O�8����^�ӐS��_�߽OuO�m�#q�m����=��=���/�����7�����0��$7���V_�������"��:mH~�������9�)�ݷ��5U�fS6�>6�V���^>e�6��l���}{��	<��q듥է��7c�n���e(m����4�>�D~\ePv�m5�Rz �rx�8;ڕ�TA�=۝Ӕu�<r�m�m������C�~/�BA�g�|K����-O���m�����Z3z�B9��⏠�w=����5�e�I�Q[��q��%<��,1_L��_'H��Yv�;���Azή���'�4���$�2�7zk��H��c\���7������ܐ�����$��FS��L�O�ޤ����K�]���D�QN���0I�����nis^�X�����y�wWi�S��a���9zS ��3�/+;e�Kc�Y�].�r�d_GY�Q �.��t�������7�I�Mٗ�Rɒ̩�=j������g1C?�%�bnD{,++^/�X�nm������eH�lR��� $�U�.�*��GS��Q�i��*��������9�}.�y���X����h�R����V�S�-+m��>�_�7�׻��'��W�zp�i�<xq�g��s���L@v��Z-ΦF��'M9�~s
�U�e�<�,K��+��ʐgmF�:۞��?��%�$'�]J�3��A>1#�y�L��W���ج�C��M�s��oC����G��M9	uy�����i����4������ʾ*�|�H���Z�V��8�ou�_��7�l[C��Q�ӮX�6�Q��m���̡d燂vՂ��XS�SH�o�L��}iVSPF�w�t�Y'$�z��6_��m�����r��]����}�⾩��:�;��eH��U����Ux'pTQ��E'��F�b�C��Au u/K��7��j)�!�T��ҤԵ���Дn��G�kƺ`�k{k��լ#xK�oJRZfaiXKP�H�4�Y�ϳ.%x��ds��k�J"0͟e�a��1�?͚ ��R,�\뱖��|]��T��Ǫ]'!_Y-����y�2ܤ�P���L9\�+-��rj�{����r��4���'�6$4��?��Jt�Ҕ��4�K�RkSj\������b$o6�obo��ojSh\��Cl�A�0U���%�ռ-꾌��{4ɻ�u��7 ٷȊת�E��S����+^�#y�ep���Ηm��}�͒�=��<��1�[b��oGc�v?���51�s@���c]���5�LDa�t@��zkMds�ָ��&YP#��vM��u������$���k���\#��ָ捐`r�r���R'�{>Gj<���Y���P	�m��ij_P=J��eߧTQ��9U9�'�bS����`�����4'��g�I�|aD���)9��#�ZR���~��}j��M[�O�(����[�>?�T���/3��{0���+���>�vg���|���y#Z�]�aW��%��&��6�vh�q`���ݟ�0�n�B*;ݚZ�X]��р`iJ���	Re�82
_fY�1��4��kLS�˾��"@�����mu�5稓d�u�u�<� �n�r�+���m�+pfەs��Æ+�+���m��@=NKV�h%�t��!�z�5}[��fl��C�j�_��!����z����kE�p�_dR|�l }�i"�x���3��iW��<�l�<� �����ݚ���h.�<��(�o�g�jHSjս'1���T���{�L��Cc���!�[��Ҽ1y�aX'{����,��9 *��6	��jɁ��
����ʖ`�n��9?�ö�t3�'b�u9�4,V�uv9�e�/iI�?}��>�"�rZVvȷ|c�j�n5I��Aω�J��ڔ拹�O]�#�?��iX��>K>FR�t����*�ZR4o'xx�����K��:��س�������c$����k�p��ZV:� $�jjk�����w�I?=������ɶs�`�c�N�wK�kX��X����zo�R9�Z���P��*��_��]-����4/��	�?�I�ۍ�d�7I���Y�۽��Md�l9JJT����5�8���>GWYIi�Q ����Z������[�5��5�o�ٕVY�-M��6�jf�Z��u��h�|"�7
���(���;��v�x���TK��أ�^ˮ8�	�o�2�������,>�wyw!/y���(;�MO�f��[ۜ�m}~,'��+�ͽ%FV�U����RMj&t�n��w�
)+_�M�v�+�ք��&ٸ-G1#fB2GI�
տϑk�e
t�N�EVv�){mm��)�n!	z��ܝ�C�x����r*x��([�������������.ɩ`�@���?ϣkA�a�CO�m}��qz�D�%�� ��6E�g��߀�n{�}&����>�H[�med{<�/�7dN���礭�(#�Z"��'{��0+ےS<v dO7d�9�.)����ܱ��-� �,J�$KNa1Hl}%�����Y `ǿ!��g=)�
M�A����HRX�w�}���ABc�<y�Kؔ�e_F�:k*�T��hl��'����f�ɂ*����9�ci>WRj͡�4�M�v�:��[��l9;����^9���`�����xE��?0�1�;�6�җ��X�U�����p\�LP�kiA��j��g��!iM�Ye�{_G�a��-C�[����j]jp�aqՁ?�׻˹�gv��!�>�}،�(�-��k����F^t�=��8�X�3|xy�A��HN�71��%��+����۲���d����*t�˾�A�a潿�<ћ�~ �:�I��)��0�o�A�Ov�%U�
��4��aJ��>�E�����)C��y������#�bm��]����qF��Z@��&p�iQW�QKy]��Mv�!:��2$o74�_�J7�	��>��|@�g�,�ʛ�1����ѿ���PfG���x�Ks� '�E�N�A%f�� ��a 8���n
��"S�t���%y� �[/v�U���m�\h��� �����I�N@7�K��9������MgC�\bu����U�3Y�%�}���4�����L�!�4��#��*�*�u1�2,Z���ВAJ�t-��۩l���!�ԫYy���˛��~�l�G�A�\�1C��@>&m�d�+YI4A�ʌ�`O@~�Ϫ��e����eԉ�[[�N0u�}`s�N`����a�U��U .p%	tm��[Z��v�!䏤�.X�gr����m!�rm��ԑ���v�2�C��P���+�,���u�A�b�$��	j�!6k�W��J�οFۛ���|�$�����]̥��4-/�4�&�V�jSjgR���똍)f��͘��:s�c�������3��n�-5�ې�~�=ؠ3Õ拶�l;,��U��C�4K�o�I����qt��~�ac��H�����u�׉uu�m蟆5|�A����$0)k������*���y�-�:�ޭ�%$�I�*,y%��B��,�g8���,%�"�J��βX�<!T���u)�2�m)�r�P�10G�kBoDY��b��l�/T^����;؀mF�?�t-�L�ML(�8?3l�r��̦�d�?
zE��4���++{�E�=�F��?��B��U�`P��j����l��2�y�,�5<@=�"�JJ
M�uF�KZ]=r�&�HN�3o����YuNI ��mxS���eQ�q�rL��"iO:����޿�\jS�5�b�ue�A����R���p=����t�,�u,���R�ڿ��T2˺Ē�O�/��U���@h�������i�K��	�����Ttz���,1���`�۬��*�G	H�B���yoZ�Q�H�����A~98vOP���h^��O�I��~�<.E��i�y��VfT?E����`�C���X���˷_'��4F~Ū��MH�u��2�\��s	��W��!6j�E(�o�)��5k���34��9r�.�g�gP��W8_v�����3�a�ʽ�K.K1J���3�ѧ4>�((Ù�ɰ�F��X��X1���}'��?��ʹ���x�<3�_���#rN�]6A�DS��=���F6�� +��R�4����[v�ɳ��A�Qvo1�o�V�6x���"KU�5�6Z�?S���rh+��=X�g��4)����z�ti��VT����R�|�f��C;?�TBhh}yC����rT{��[{Y���ʗ�FB/�9�_Z=���%����^�:�l�h����K{�|�T��l�j49���[����XS����T�z�,ٷ.Ca�8�:���4҇P�a[�Զm0�%Њ�
��-8EMs�$f�m�KlO�����#��h���dQ���͆�d��5���I�����8؞wU���h�lQ���9r[��������ĬN��p�.n���%�������n�<��ӥ&�O��e �3Gpj�zQ|�S���Xu��Jk�r�nYW�Ò�^�}]�褚��qݫ�9�
�ʦ
;�B.���e��<�S��p��4��	v���nPߞ� ���$��P�� y��^��6�N|}��c����ԭ�`��k�V'πW��7`>ߙ_ �G��z��_Q���m`qp�:5�؆�H���~���1��P���{qkĸS~az�7-��P���(��7�
��*�iR|TH��;l_��c�v�6��W�"Pվ�i��<���`�L���{p����{���إՠmO�4�'��?bV�Q�3��q�	�����*U�6�mF�K���V���u[��dl|�5�ONbVMg����l�C����R/����"bP�y62CnH J�u���Q��	���.��^��~�������0�֋�U�Y�N`���S�wv��N�O9J���/w��K�����J�n��{��Σ^ߣ[�
�]�7�⛋SweIc%~���~�\���޿78r'� �V���j�-��@;���7r�n�/����c��z�T�OI�I�O�K=�f��^(������!C2#c��B�<j��M��h�el�6�c���z��Rn|;8~ <�O�
ظ@��emW����O+��#��փ��BFp��z�/�>�R5B�U�l�:����1�^�:���i���JRG�$��-���������7���zlu����>�C-�l��4���5u��x=
{��^��
l�;dd�O'�.tt������6\6�qɛ/֢$���=�a��{������ݜ����6��ݔI�
eL܅�o_��+��TP~�j2��ꤟp��/��E��<�j�m��Ĩ_��s]��-�K��'ޮw�=�/�g�Ƣ/��ZŐTe��mI��*����Y�=�1N�I��-�Z��Q�F!r΂�zz{'/=����TnOg��1��@ыpQi���D���V�������mQ87��u4�����K%����4=�9�>w+t\���C8��jtm�^��cбw&��͉w%��%ٕ�!y�[c%O&l�>";J޵t`�,>���\O%�7)��QP3�g��aO�;E<H�oR*F|���M������{q'����g!6��_G�]&y���~� ��di�@�
}��.������]��;���~G�b��(ȝ��R�.�����+��h�f��B�oc����j����ϓDj|��9���t�@w�?���#Jn��՛~�^V�����ZC�N�Ǧ��?n\â����]�b�|��D��c�y�:G�q�� m��f�6�]��fT�E?�K$yp:���]�Z,�K���+A?H~ߜ��Ŝ
w�䬠��<Sa������I4�&3dm6ゎ��9��PXmݥu�7+!�l����o���LxWX�
f>ͼ&7e���.�p��I}�/��΂~���;v1�M�Z��7.Qo������u~;��S�����=|�{_�]�s�N�.eLv��#:}�`۸R}t�֞���?È�\�����P���$��8�O�%��8�^��S���~��yS��gI3�3�Rd�J l�'�t�3GX�&���άǥ�J���T�;�<����9&���ʛb�.	WVj$��v@_6��V��
.b�W^��@��p���Y��ٌ��Q������%G�$����;>����3��<�5�1ڤ?z������tk��MZ0"�v1�@�:�lp���b��'���8�	�k�5�!�6w+$��Qݴ�\�DSv|"���SU��\8[��R���n�3v��x�o�����D��1�8�RGs!W���f������.�L�q�􌥜�	a?���SQR���=���N�*��WUnߞU��w�J��ma�g�������V�������S��g����G���]���������m��[����VI㏧��_J.���h���Y$��b���Yi c���-���ds?�`�(���*��M|�Y=�4�����Kd�`�<Bg'w�E��a\(�l��~�w�!����)Jm�/��i
�w5��슾n���Y��4���١ڋoW�Z��o��	O��P�_����R�K-�?�`|0rg-�"�ϩ̔�Ԩi_��m!�Dr�w�K�Ov�is��%�o�Z�wݮ��5Շv,w+��8�f��~�l�����Y�jV�'��a6�06z�K�mKBI�٧���_���&��񒍯g��)�t�[C{����`<�%[�Tv��i k�=h���>Ŗ/|E23��4�/c��"�����Пv�/�#6&qOc���?�6L��_�d�m���́$�?�X�N�RX��va�E_��%;��EV���^<��hڐi�q1��W2F��kZ���!Tp!��YFnR�[�	�G�D-}�^/;�m|��^��w�ͭ���F��K�$i���̡�,�����F����$F�UGT2��F�dF�ȨtF����9����{�b�i�~�qcVٽc%oN�LC㸆��4~HOhߢ�i3�w��y�Jg��r��ff�]���o�MUV�rW�J,���2�@��W���p��m[�ОxA�U�X�K�(6=����
,��l�chb��,Yٓ� h!ÜLv7~����;�~��Ŵ7�ڛզ�-y��N������I��=m !L���_(�'�#�!�o^��2����;f6��A:������_l��M���F�M�U�Z�u9�o\1��9�V;�j�|��?g*����q��>��r$��M1V�i�L��+{1�|[��uJ�坰��Z���Jcl���.� ��|<mhS���	��M�V�$uqk������6wm��ծt�S�K�צ<����͛Q���f�;�Ѭ��nM�}��枏{〈�3r�֫�۩�RG��p%i�"M�tDz�R>�V�wO���$��*뿥��;е.�����W���R��;�|�V��g �"�������)���|$`r�CcW|:S�8.&kt��6���-�f�.U��xk�L����0�h]�����a���^A�I��}��G���S�o�*~�3�X[�@��O�b�F���T�9O���my�dG�$��p�T}�1H�=���r��}ƣ�a�Lۘ�7��Y�g��m�d�mF�n-�������n�X�Y� ���k+_L��;�����mf^�Y��sČ[�;�}�X%��n���Ӯ\c��}��C�ja-���_ʂڊrz7Vu��0��Bf]J/esJ�V�iʮ��oO���	��E0��ﺱ��wK��R_?1����7ƥ��)y�$A�7����X++[���0����(�ETB��4\��%!�	� �%/`pB��¦����a�#貮������g(ʙuڐ,y�A��7�$Oxȹ��cZ�E�����҂!��Fob5�	�x��8���+<��@טƂ�7Dp��6B�d��`|p^=_��zr��}���HԱ��I�!uM��Z����&�HӮ�ae/��ȋ���������Ē�uuP �&�.e�ؿSn9!J=�D��4ɡjL}�(_C(��)Ӕ����q�)u�a���I�j�a��E;��w��jL;\�����78��@�]P�1l w�]:Ovn����C�XP��Ơ)i���.잭���:#+U8�
�C�+]���W;��M:��G�Ef\<_��c��ѳ�)?N�֟�S|�wVh��A�u��k�d��hS#۸��]��ƨ���cx�/�.Sd�f��ޤ�g��}"m1�N��顡8�4��y-�u�y��-K�4tD'B����N�DJ=�[Rj�.��e�+ث>Y�<�t�1LՈ�I�Nc���������aN�S���֩3����#�yF�-zF��٦N�Ȼ���D��f�ѻ��JO�����84���8��?���y��^��>�O|��M�aY]��,��4_wƣ_t�@�)���qgcKp~
��h5�s*��Y�/f
ti	��-�W����$���-���U4�:6QoWF|���Wi˅�B�`�,�k�Q�٥!�콍�~�C2`@cei2+Ǯ�Bj��Qͪ�j�;�SO���HE��Md�xf=Iq�?�)(u�z~�P��!��Oy�ײv���gH]Q�IG~[O��
2S���ux{���!��P��������w]V�y%����h������O��E�%V�ֳy�ô���Ռ*�|� [���lm������H�E�9}���5����0�2@�Vg��$�wB������R+��;>��=W���N��~CqHsYT��|�z^�c3�`%��#y.��H�����ׅ�¤�|�砮�R����\Sl��x'�K�?���C7�[L��'�䬿�N�J93f�l�ض���~��e'g[�w��eA�:�+��_p��_LGa*ab��f�t�����	�|�^\�JI�:�+.�ܾ���K���Tt���Ɨ�S��G�l��<���a�v8�+�hy�(�R� #O���1�ZG�p�G�Q�
f�J [�H��.�1�R���D� �;2��m%�!*�>�`��F;G�>ߌ� �1����A�Bݰ������ཀྵ'� Yן��E�I��Z���'vl��O��@�q�gן����A{�s-۟�Խ�#$�����_x�`F���t�sM6g��==.����m�O����z��u���՝����I�BwD��V'�w��&�)����Q��E4�X��\G��q\r����{����&$b�{˗��w�o:uBe��.�6�g<�O����X�gӔV�wiVS���*��sj;PaFU$���X�NP�i�*}�I��=ݛ5xT����,����.b�Pc��5Ħ�GU_X�:Ǯ��jP*�w(d�C5_�u���e~[�d�گ���S��m5�cn�<I�[�Xc���Q/ł�9�{W�q��l&;��](�
�lH���\����C��a8��D���3����s�u��4G�v�#'��m�a��5F]���	�S.y��fB)a���-SHPg��9~?���X�u�6ާ����sn����!Ж�@�J_+�7�[�6ܻǙ���`�~�%F��5���&���p��-���H���V���ޡ(��k��G��\C��m�%�Q���9t>�� j�tu�7�b�	'$L4m�'*�1�O~~�9MV�)�Ռ�ӝ-�%8�3qD�ǰ4[sۧ�,�$�;N�|���M]�90��^�13�¬��[V_+u�iwG;��)ի��T���<�p�%]���x)��	���Ԋ��S?��KW�	:=����M���D{�������A��$o�f>~���﷒�4\�¥Z
��R��-0�X-��ߑ�I����7K�[�����g@?G�ޮ����9N��:>�w� �̂#lGĆV
4
]��k�&�@KX ;����9x �����Y�`��$�C,Twu+���j�'�ъ�����X�����������&i ���������ғ\�/��K\9��f��6�d���0�ǃ���yӴ�����ԯ_��>���11��4���n�[E�'�݃3~~��Lٿ��@��kw{���7\tu�J��qvR�Z�0�j�̝nY�6��Ǭ�;A��U�Ech��.lY�MS�#�7V^�W�p%�UҁQ5y%���FS��j[��A;=@���UǏn$ܻ�h�����2l`�!R�Q\�*h�J�����P���YvU���2K���,�,���S�ʼ�"������!u�GȬ���(b����=�b����x*a�*쟈�Q�4y�`m����
������W��AЏo#H��<�	����N�˾��3�㶄�w�� ��u�V0��>&_Es����4�X��X
�9O��p�m#��װ�Ù#�����a�m��'_����:x��2�Ȃ[�Vث�褗�t�B	,��덆G�C띚Y!	v9����Kq;��!����)����!<p��W_�W'7G.�	B�>^�'>f6"gA��[0�kX�.���*��'��(NNºW����ѿb1G2�^=��5�����alH�OP[�YNٞ��>0f��Th{��1�Lв����:��/:�v�r\�u���@6�h��с�����a�|�.�O53)�
���q�验!�v_J���H�w�2�T*��-K͘.�%��4� ������	����V�y#�N��=�L,�>��>���Ż|'{�g���q�w6z��8<��[���û�u9�w���w�opn�nwM�n�e�"�:��F"G��i�Ld�R������9��ny���X��{(I\&�}-0
��=��n�v�^?�n�r��n�t:h_��Y��T�ɍ�m������| �M���BZ��-/����:�K1SSǣ��pA�g�l����£Y9̗���W����є^��^��	�����c�L�'��3�������ǯwZ��Ϲ�}�;�l�S��0p���G����%QC1�,�g*���;͌WkHxn����{��E�^�c�C��V_�/�n2m~xc�Ad�{��x�ο�V��n?U��Z+|�>�e�Nb�zZ�|����bC�u!W��h������uD��߿��n�Z'�-�*��7x�K�X<����#�F��G�;���� �1˴y��4��Ԃ�c��,[�-�Х<���|:���\���+��i�9��
y� ��뜼p 4i���g��s��7��9<x�N\�o&��Y��g�K؋�<}�n��<��[���q�S��j�>�X�r��Gd�gP{��fP�4�x�/Ŕ�3�	`kb�~8�soN�AT[�-��Q|{�F3��q���)p`/��V;0���8J��F۽���(�/��Ԧv���s`zǲ�V�����9l���5u�7ɗ̆nK���a�L6ls> �xq��&�*���sstr�a������4Ik���H6���2���b���6�zvǖ�v�C����c�\����7��/�	��q;il���7�����4~�톯/�+����7��q����ؓ���;����A_����_H����j�+`Z�
P��
p�����`� m��	`��@mP}�C8��~]�*dR[?���HD)ޙQA��$�����m�5L�3P�;�o�{�������O�ߗw[�U���;7FC���b�FOtX���R�SG�?R��&�r<�2;&�O��b��/y����V3$��\p��vc	�*����e�:����{3fM�ɾ�p4��!���S/���!v�on|���l��G�^|����P���L�9���}�*��Y�7��܀IN��`��є0菻�hS��웴�aew�9����	Y5HqM���op7Ͱm���Q���h0m��dru��q�����_L;O��b�?p��xu``8�"��V�oJo��>�x�C�JcV�w���{��P�l�K�t�b 5��Qd�b 4���(����9�B���:$��v��Av'�K�E��r�"��B��Q�^Ė5	[�[V&S#g
^?d�NP6֧*T�Ȯ6�4$��<��y}��rM�Rpp]����n�"6��J���9Z^nג�=x_V��و/?�s�:��>::�Ńe���VhH�|#��ДJ���\�/�A�I�^Le���p��D�ql~2wQ�|n~���v�$:���S�OQ.Y��m~G�T��مc���������W7����|��)��7��E'�pY/;���O��K��<<J��U�[���,���F�q7m͛-�t#�lޜ,ya�6*�
ʰX���R!�}���.Hly Kv�>��T��$/'��G��h���:��:CXgS�j9�'�B������n;���HX��1wu�:û���(v�j��a�:L�%2��Æ��8���dnd��77k��R�v�v_K\Q�z��+��ș���o%��.�c�-�^:OO�s��Ðȫ�y�F��Al_������tàWQ���C^%Â�:u
�_� ������/HD��}���`�����UT~�����j�pl��W.��J��ܠ(�ܷ���56�V��궳���y��h�j���bW`�J����0�4jZzhwr��t���H�Fr��`�%Vk�;�ʼ�	ٙNK8�Nv��\�6X��ҟv/+Z��.R��D�\t�3�K���=j"�JNwV�5oWN�*?�iR6��>�Lg�.܇�nP��V����&���N�I�L��/c�w�3���L0�]�J�Σ>�ʅ�����7k_p���\��5Q���1u4�W�xV'�L@j�fڐ�폝k������;v��opX���}�Ĵ�P�:>�m`�*��Cڡ����x���]��~"���V__�U��f[�ﱸ	6i��
@��q�	��`ɒ�g'�;%�_G٩�y�Vtε�݌�o���	t��F�g[ۏ�T޾K�#��_�������kv� 3���gV�w`᳗��܀z�7M�����C�ז��C�[��l���JWkk3�1|�,;Օ�n�:���lT[ 3���)�]_���[Q4 current2_(current2),
          begin3_(g3.begin()), end3_(g3.end()), current3_(current3),
          begin4_(g4.begin()), end4_(g4.end()), current4_(current4),
          begin5_(g5.begin()), end5_(g5.end()), current5_(current5),
          begin6_(g6.begin()), end6_(g6.end()), current6_(current6)    {
      ComputeCurrentValue();
    }
    virtual ~Iterator() {}

    virtual const ParamGeneratorInterface<ParamType>* BaseGenerator() const {
      return base_;
    }
    // Advance should not be called on beyond-of-range iterators
    // so no component iterators must be beyond end of range, either.
    virtual void Advance() {
      assert(!AtEnd());
      ++current6_;
      if (current6_ == end6_) {
        current6_ = begin6_;
        ++current5_;
      }
      if (current5_ == end5_) {
        current5_ = begin5_;
        ++current4_;
      }
      if (current4_ == end4_) {
        current4_ = begin4_;
        ++current3_;
      }
      if (current3_ == end3_) {
        current3_ = begin3_;
        ++current2_;
      }
      if (current2_ == end2_) {
        current2_ = begin2_;
        ++current1_;
      }
      ComputeCurrentValue();
    }
    virtual ParamIteratorInterface<ParamType>* Clone() const {
      return new Iterator(*this);
    }
    virtual const ParamType* Current() const { return &current_value_; }
    virtual bool Equals(const ParamIteratorInterface<ParamType>& other) const {
      // Having the same base generator guarantees that the other
      // iterator is of the same type and we can downcast.
      GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
          << "The program attempted to compare iterators "
          << "from different generators." << std::endl;
      const Iterator* typed_other =
          CheckedDowncastToActualType<const Iterator>(&other);
      // We must report iterators equal if they both point beyond their
      // respective ranges. That can happen in a variety of fashions,
      // so we have to consult AtEnd().
      return (AtEnd() && typed_other->AtEnd()) ||
         (
          current1_ == typed_other->current1_ &&
          current2_ == typed_other->current2_ &&
          current3_ == typed_other->current3_ &&
          current4_ == typed_other->current4_ &&
          current5_ == typed_other->current5_ &&
          current6_ == typed_other->current6_);
    }

   private:
    Iterator(const Iterator& other)
        : base_(other.base_),
        begin1_(other.begin1_),
        end1_(other.end1_),
        current1_(other.current1_),
        begin2_(other.begin2_),
        end2_(other.end2_),
        current2_(other.current2_),
        begin3_(other.begin3_),
        end3_(other.end3_),
        current3_(other.current3_),
        begin4_(other.begin4_),
        end4_(other.end4_),
        current4_(other.current4_),
        begin5_(other.begin5_),
        end5_(other.end5_),
        current5_(other.current5_),
        begin6_(other.begin6_),
        end6_(other.end6_),
        current6_(other.current6_) {
      ComputeCurrentValue();
    }

    void ComputeCurrentValue() {
      if (!AtEnd())
        current_value_ = ParamType(*current1_, *current2_, *current3_,
            *current4_, *current5_, *current6_);
    }
    bool AtEnd() const {
      // We must report iterator past the end of the range when either of the
      // component iterators has reached the end of its range.
      return
          current1_ == end1_ ||
          current2_ == end2_ ||
          current3_ == end3_ ||
          current4_ == end4_ ||
          current5_ == end5_ ||
          current6_ == end6_;
    }

    // No implementation - assignment is unsupported.
    void operator=(const Iterator& other);

    const ParamGeneratorInterface<ParamType>* const base_;
    // begin[i]_ and end[i]_ define the i-th range that Iterator traverses.
    // current[i]_ is the actual traversing iterator.
    const typename ParamGenerator<T1>::iterator begin1_;
    const typename ParamGenerator<T1>::iterator end1_;
    typename ParamGenerator<T1>::iterator current1_;
    const typename ParamGenerator<T2>::iterator begin2_;
    const typename ParamGenerator<T2>::iterator end2_;
    typename ParamGenerator<T2>::iterator current2_;
    const typename ParamGenerator<T3>::iterator begin3_;
    const typename ParamGenerator<T3>::iterator end3_;
    typename ParamGenerator<T3>::iterator current3_;
    const typename ParamGenerator<T4>::iterator begin4_;
    const typename ParamGenerator<T4>::iterator end4_;
    typename ParamGenerator<T4>::iterator current4_;
    const typename ParamGenerator<T5>::iterator begin5_;
    const typename ParamGenerator<T5>::iterator end5_;
    typename ParamGenerator<T5>::iterator current5_;
    const typename ParamGenerator<T6>::iterator begin6_;
    const typename ParamGenerator<T6>::iterator end6_;
    typename ParamGenerator<T6>::iterator current6_;
    ParamType current_value_;
  };  // class CartesianProductGenerator6::Iterator

  // No implementation - assignment is unsupported.
  void operator=(const CartesianProductGenerator6& other);

  const ParamGenerator<T1> g1_;
  const ParamGenerator<T2> g2_;
  const ParamGenerator<T3> g3_;
  const ParamGenerator<T4> g4_;
  const ParamGenerator<T5> g5_;
  const ParamGenerator<T6> g6_;
};  // class CartesianProductGenerator6


template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7>
class CartesianProductGenerator7
    : public ParamGeneratorInterface< ::std::tr1::tuple<T1, T2, T3, T4, T5, T6,
        T7> > {
 public:
  typedef ::std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7> ParamType;

  CartesianProductGenerator7(const ParamGenerator<T1>& g1,
      const ParamGenerator<T2>& g2, const ParamGenerator<T3>& g3,
      const ParamGenerator<T4>& g4, const ParamGenerator<T5>& g5,
      const ParamGenerator<T6>& g6, const ParamGenerator<T7>& g7)
      : g1_(g1), g2_(g2), g3_(g3), g4_(g4), g5_(g5), g6_(g6), g7_(g7) {}
  virtual ~CartesianProductGenerator7() {}

  virtual ParamIteratorInterface<ParamType>* Begin() const {
    return new Iterator(this, g1_, g1_.begin(), g2_, g2_.begin(), g3_,
        g3_.begin(), g4_, g4_.begin(), g5_, g5_.begin(), g6_, g6_.begin(), g7_,
        g7_.begin());
  }
  virtual ParamIteratorInterface<ParamType>* End() const {
    return new Iterator(this, g1_, g1_.end(), g2_, g2_.end(), g3_, g3_.end(),
        g4_, g4_.end(), g5_, g5_.end(), g6_, g6_.end(), g7_, g7_.end());
  }

 private:
  class Iterator : public ParamIteratorInterface<ParamType> {
   public:
    Iterator(const ParamGeneratorInterface<ParamType>* base,
      const ParamGenerator<T1>& g1,
      const typename ParamGenerator<T1>::iterator& current1,
      const ParamGenerator<T2>& g2,
      const typename ParamGenerator<T2>::iterator& current2,
      const ParamGenerator<T3>& g3,
      const typename ParamGenerator<T3>::iterator& current3,
      const ParamGenerator<T4>& g4,
      const typename ParamGenerator<T4>::iterator& current4,
      const ParamGenerator<T5>& g5,
      const typename ParamGenerator<T5>::iterator& current5,
      const ParamGenerator<T6>& g6,
      const typename ParamGenerator<T6>::iterator& current6,
      const ParamGenerator<T7>& g7,
      const typename ParamGenerator<T7>::iterator& current7)
        : base_(base),
          begin1_(g1.begin()), end1_(g1.end()), current1_(current1),
          begin2_(g2.begin()), end2_(g2.end()), current2_(current2),
          begin3_(g3.begin()), end3_(g3.end()), current3_(current3),
          begin4_(g4.begin()), end4_(g4.end()), current4_(current4),
          begin5_(g5.begin()), end5_(g5.end()), current5_(current5),
          begin6_(g6.begin()), end6_(g6.end()), current6_(current6),
          begin7_(g7.begin()), end7_(g7.end()), current7_(current7)    {
      ComputeCurrentValue();
    }
    virtual ~Iterator() {}

    virtual const ParamGeneratorInterface<ParamType>* BaseGenerator() const {
      return base_;
    }
    // Advance should not be called on beyond-of-range iterators
    // so no component iterators must be beyond end of range, either.
    virtual void Advance() {
      assert(!AtEnd());
      ++current7_;
      if (current7_ == end7_) {
        current7_ = begin7_;
        ++current6_;
      }
      if (current6_ == end6_) {
        current6_ = begin6_;
        ++current5_;
      }
      if (current5_ == end5_) {
        current5_ = begin5_;
        ++current4_;
      }
      if (current4_ == end4_) {
        current4_ = begin4_;
        ++current3_;
      }
      if (current3_ == end3_) {
        current3_ = begin3_;
        ++current2_;
      }
      if (current2_ == end2_) {
        current2_ = begin2_;
        ++current1_;
      }
      ComputeCurrentValue();
    }
    virtual ParamIteratorInterface<ParamType>* Clone() const {
      return new Iterator(*this);
    }
    virtual const ParamType* Current() const { return &current_value_; }
    virtual bool Equals(const ParamIteratorInterface<ParamType>& other) const {
      // Having the same base generator guarantees that the other
      // iterator is of the same type and we can downcast.
      GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
          << "The program attempted to compare iterators "
          << "from different generators." << std::endl;
      const Iterator* typed_other =
          CheckedDowncastToActualType<const Iterator>(&other);
      // We must report iterators equal if they both point beyond their
      // respective ranges. That can happen in a variety of fashions,
      // so we have to consult AtEnd().
      return (AtEnd() && typed_other->AtEnd()) ||
         (
          current1_ == typed_other->current1_ &&
          current2_ == typed_other->current2_ &&
          current3_ == typed_other->current3_ &&
          current4_ == typed_other->current4_ &&
          current5_ == typed_other->current5_ &&
          current6_ == typed_other->current6_ &&
          current7_ == typed_other->current7_);
    }

   private:
    Iterator(const Iterator& other)
        : base_(other.base_),
        begin1_(other.begin1_),
        end1_(other.end1_),
        current1_(other.current1_),
        begin2_(other.begin2_),
        end2_(other.end2_),
        current2_(other.current2_),
        begin3_(other.begin3_),
        end3_(other.end3_),
        current3_(other.current3_),
        begin4_(other.begin4_),
        end4_(other.end4_),
        current4_(other.current4_),
        begin5_(other.begin5_),
        end5_(other.end5_),
        current5_(other.current5_),
        begin6_(other.begin6_),
        end6_(other.end6_),
        current6_(other.current6_),
        begin7_(other.begin7_),
        end7_(other.end7_),
        current7_(other.current7_) {
      ComputeCurrentValue();
    }

    void ComputeCurrentValue() {
      if (!AtEnd())
        current_value_ = ParamType(*current1_, *current2_, *current3_,
            *current4_, *current5_, *current6_, *current7_);
    }
    bool AtEnd() const {
      // We must report iterator past the end of the range when either of the
      // component iterators has reached the end of its range.
      return
          current1_ == end1_ ||
          current2_ == end2_ ||
          current3_ == end3_ ||
          current4_ == end4_ ||
          current5_ == end5_ ||
          current6_ == end6_ ||
          current7_ == end7_;
    }

    // No implementation - assignment is unsupported.
    void operator=(const Iterator& other);

    const ParamGeneratorInterface<ParamType>* const base_;
    // begin[i]_ and end[i]_ define the i-th range that Iterator traverses.
    // current[i]_ is the actual traversing iterator.
    const typename ParamGenerator<T1>::iterator begin1_;
    const typename ParamGenerator<T1>::iterator end1_;
    typename ParamGenerator<T1>::iterator current1_;
    const typename ParamGenerator<T2>::iterator begin2_;
    const typename ParamGenerator<T2>::iterator end2_;
    typename ParamGenerator<T2>::iterator current2_;
    const typename ParamGenerator<T3>::iterator begin3_;
    const typename ParamGenerator<T3>::iterator end3_;
    typename ParamGenerator<T3>::iterator current3_;
    const typename ParamGenerator<T4>::iterator begin4_;
    const typename ParamGenerator<T4>::iterator end4_;
    typename ParamGenerator<T4>::iterator current4_;
    const typename ParamGenerator<T5>::iterator begin5_;
    const typename ParamGenerator<T5>::iterator end5_;
    typename ParamGenerator<T5>::iterator current5_;
    const typename ParamGenerator<T6>::iterator begin6_;
    const typename ParamGenerator<T6>::iterator end6_;
    typename ParamGenerator<T6>::iterator current6_;
    const typename ParamGenerator<T7>::iterator begin7_;
    const typename ParamGenerator<T7>::iterator end7_;
    typename ParamGenerator<T7>::iterator current7_;
    ParamType current_value_;
  };  // class CartesianProductGenerator7::Iterator

  // No implementation - assignment is unsupported.
  void operator=(const CartesianProductGenerator7& other);

  const ParamGenerator<T1> g1_;
  const ParamGenerator<T2> g2_;
  const ParamGenerator<T3> g3_;
  const ParamGenerator<T4> g4_;
  const ParamGenerator<T5> g5_;
  const ParamGenerator<T6> g6_;
  const ParamGenerator<T7> g7_;
};  // class CartesianProductGenerator7


template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8>
class CartesianProductGenerator8
    : public ParamGeneratorInterface< ::std::tr1::tuple<T1, T2, T3, T4, T5, T6,
        T7, T8> > {
 public:
  typedef ::std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7, T8> ParamType;

  CartesianProductGenerator8(const ParamGenerator<T1>& g1,
      const ParamGenerator<T2>& g2, const ParamGenerator<T3>& g3,
      const ParamGenerator<T4>& g4, const ParamGenerator<T5>& g5,
      const ParamGenerator<T6>& g6, const ParamGenerator<T7>& g7,
      const ParamGenerator<T8>& g8)
      : g1_(g1), g2_(g2), g3_(g3), g4_(g4), g5_(g5), g6_(g6), g7_(g7),
          g8_(g8) {}
  virtual ~CartesianProductGenerator8() {}

  virtual ParamIteratorInterface<ParamType>* Begin() const {
    return new Iterator(this, g1_, g1_.begin(), g2_, g2_.begin(), g3_,
        g3_.begin(), g4_, g4_.begin(), g5_, g5_.begin(), g6_, g6_.begin(), g7_,
        g7_.begin(), g8_, g8_.begin());
  }
  virtual ParamIteratorInterface<ParamType>* End() const {
    return new Iterator(this, g1_, g1_.end(), g2_, g2_.end(), g3_, g3_.end(),
        g4_, g4_.end(), g5_, g5_.end(), g6_, g6_.end(), g7_, g7_.end(), g8_,
        g8_.end());
  }

 private:
  class Iterator : public ParamIteratorInterface<ParamType> {
   public:
    Iterator(const ParamGeneratorInterface<ParamType>* base,
      const ParamGenerator<T1>& g1,
      const typename ParamGenerator<T1>::iterator& current1,
      const ParamGenerator<T2>& g2,
      const typename ParamGenerator<T2>::iterator& current2,
      const ParamGenerator<T3>& g3,
      const typename ParamGenerator<T3>::iterator& current3,
      const ParamGenerator<T4>& g4,
      const typename ParamGenerator<T4>::iterator& current4,
      const ParamGenerator<T5>& g5,
      const typename ParamGenerator<T5>::iterator& current5,
      const ParamGenerator<T6>& g6,
      const typename ParamGenerator<T6>::iterator& current6,
      const ParamGenerator<T7>& g7,
      const typename ParamGenerator<T7>::iterator& current7,
      const ParamGenerator<T8>& g8,
      const typename ParamGenerator<T8>::iterator& current8)
        : base_(base),
          begin1_(g1.begin()), end1_(g1.end()), current1_(current1),
          begin2_(g2.begin()), end2_(g2.end()), current2_(current2),
          begin3_(g3.begin()), end3_(g3.end()), current3_(current3),
          begin4_(g4.begin()), end4_(g4.end()), current4_(current4),
          begin5_(g5.begin()), end5_(g5.end()), current5_(current5),
          begin6_(g6.begin()), end6_(g6.end()), current6_(current6),
          begin7_(g7.begin()), end7_(g7.end()), current7_(current7),
          begin8_(g8.begin()), end8_(g8.end()), current8_(current8)    {
      ComputeCurrentValue();
    }
    virtual ~Iterator() {}

    virtual const ParamGeneratorInterface<ParamType>* BaseGenerator() const {
      return base_;
    }
    // Advance should not be called on beyond-of-range iterators
    // so no component iterators must be beyond end of range, either.
    virtual void Advance() {
      assert(!AtEnd());
     ��>MI,����k���8Gj��e�s�&X��jJɇ�-	��q&D�ey�-�v��������'�җ���^u=m��o����$Uu��w���e���/�}�AA��F��R��A�>��t|Gv�#���	^�H��wk��(o��A�rkq�<f0Tr?p�{bi�0���y"���9���ݡw v���\�?�o��������"}��gb�ԋ���{������籜�"���/~�?�g��_��`�����;�O_��`�
�O���p������HD}�����\֏��������A"]��]DzKw�4���o�����e��k{#�o{d�?�)�o@���Wn�?,/t@�����z���\/�����F�t�Hg���"�KGa��M�5w��{���|OD�����=���چn�u#�o������=e��=ߋ�y��`�#"�`�m"ݛ�Wc�<��o�/j�u��+��ݑ�{?h�?^��5���(�w��2�O��X~h����vC�m������O�����[�D�V�����"��۲�p��=��7\�=��^*����ᇰ]�iI6 7P��.�L|����aX�׌c����\�ɫm�!Q7���4�U�M���MWb��LK{bu�/-����[���
﷚L��Bn����x�������cx��3�o��1{�u��n�!�ְy�8�K~�̾�������2{;%@L�Q���|NlB+B[u\�_���u�-�  ���'"OC�oM�{u׊��Qϫ�A�Yχ��}ۍ�c(<g��$���-ȱK��#WHj��{�v��nX���}=f�g�����1<�i��#�c��/¥�1�ugn}[�������T�te$��iۃ����P�$Z��L�~S��
���uװ�K���q�Eq��SW�qf�7���FQ+��ۧ�Rϫ��=���%�Y�*��~�E�skԳ���ci��>R�$����ғ:%��ϳ���V?�ܩ7����}�m�S?�6��n���$۠'�Zb��[NF^�I�|oe�n�m3�.�g�$s�G�<c����.Σs䛣� �w��,L.��HahO�����
-�A� �#���I�O/�_T�|"�������M�U�/�fӅF��\`��ǞǉIj�ר���>"�����>l���a�ѯ7x��VÂc?�[p�h6�H�c\o��s�9݂3���?8w��MȄ2�~F�uW��a�o�i}����������q�	�x�$Tϸ�h�%�u�B݀c�N�hd�����YW�Y�:�H��8���Wf/dʸC����O�|�Vq��g�݇j���ʍ��z9i�@O�r���	4���� ���D�?c�@�Na��d{]I�:�뿵�)u�2��R�sI��5\��XJ6�t�-�EVA.�BF�K�@ֆ�3��"I�A��II�Af��43��HFm╳�����?������,��E�{�g("�h��٘]�{�^	�#��R��|�<@�D��Z���o�t��t���1JE����	j<;k]ӳ���lw"�o����*�g��*�U=���~h�?m]��fe\�$�������xrcq^��DA��e�d��3Ht�?�sF+y;(����g�h�NQt�ub������8����N���H�X��C�M��q���G����`�d���X�D����7F�I�y|�����a�>\���@��}���K���Xƅ|���z�㮇����62����� #��K����ҩ�J�9�C��/����þj<���5�0&N��6eC�tk��.:��������*�����t{�~]�i��~���ʁ��m����������~�^,�,W+#A��������<ɀx<d�n(�ʷa�ؐ�4ls��l��rq�������5��O�u���'�z�I��/���u��D��u}�	����+�����Ǔ�О��pM���*�i�h���D,}�4��t�4�-ˉ�5�1fE5Ǣ�p�UK����L�C�E� ?	ܴpe�ɿΓ��ϛ4�>����rT��ᦰAt�	W���%����~��a���'J�]8��}�V�.>Rb����_���Fi��qc�U����t��E�'髖�}�
Bv�'gV���uhy�ye�eL��!B�W��ˊ�O��q?Dh���[��0f�C޲Z�.��*�/��������}�Fv��γ�����І���f#ϢO�3�F������,�M3Uw�kz>��W����L�:es�l�"M�a���-��9���*������N��!E��G�?���-�v���Cn/� ��Ha:�c.�k!6��/��V�j�X�W�C��n���*��t���| ��<h�fkNF��2�����g��� ��.h���!3�'��ʆ�[���%�f����
�1��cN�θ_�`8ޝrϘ�)'V�cK���BG(8�����q�,15�F�E�DaJy����P D�A�e�9p^�x�WR��Ʈd	����|�FS�$��k]��H^]�ה8v�:
f�Sl�^]����c�x_��''q��6�Z���X�2E��*��+�f�Nu���[�wf}v����� ��f�S;�NB~!wK�
>�Fٽ�B��)��&�u'�^`�h�h7b�^�z�R]X�v1$^�r��y�B���u�u�B�i�j+�w?����ؿ�C��	2{#O@�����l���|��Q$$�Wk=YD�x�i��8Վv�zG�/���������ըS��JY�\*�Y�`����'WK��䈵\-���j+/�����󏉺I��\���ߣ�ra�
�W�o�(+���&Kf����\p����p���zz�s�S���q.�{,�{,�/&�'�k�n�n��x�ʫ�z�)��
��V�m�ZA���g=�%�"��'�$�٦�lU^�|��7��������ܚ��о\��T������о���5N��J�G2�[���G\����dq)���x��_�m�Y�HL>���5T_}�����_���_d��#�oi�ٞ��|&b-��j��jy+��E`�C�e�ݵ����s'����6`M{�玂��v%+�K���m1�5����Y�O�V�C�S��J
v�~yI'�sL���H�5d�84p=맷&� W�$��9_���~3��iI���$��F[	���ٝ��M�A����+�_����cLW�����}#!�Е�Z�ٿ�s�9��P���s����Ǡl��mŖ��jf������?��ӛo�VEXԗh��}ҫd��5���L�\���	뫒Eܞ��*�A�U71�A"��D�����0�����$�g��J"A���IB�\Y�)xDK��4*�	<��g����/�6~"��v+��k �兠s^kݞ����U�� ]b}c!碌VB'�[X��foB5��+�v����+4L]�a�I�e�
(r��H����0��J��⽆�ɤH ?J�6&8�.l-��	\M|Њj=�:��7J�Gl��T��_I�&+j&5����<�NG�O��
٭#~�n�����~����s!�8?q��ȉ����١Ժ�G���oC��ArE�=U���z����c�t�����7#Ν�s�H�0�TГ��\k��-����Y���š^t��\�.���;��Uaw��ت�΢��[�svi�2^�Ï�|��kL5a�xV���˸/�7]�>@���2��C��4��_0���xx/��.0^Dj�b^�*����'/�0y�T����е6��`KHS�b�N�Z�R�i*��˙Ug��~�͈�B����enP�)R|_�3�CR�T{��kb���kҎbVbI`6+E5>����~���̵��^�H��C<E�]F�e��Q�f�z�w��O��t'"��
=��rC�]~���by��Ʀdh_8(�>�����<���2�?`�AF�����<0��k���`�	���h�m���r	=��UU�=�pS���x���Mp4(_��C3�ŀ�Y�l�ւ;������}�ǰ�u���6<�@{�B�#o�A�"�T�)d�?�	�z�S��������\��/�#�j�NC���j����I2� �ܮ�p1�7�biW�)�
���V`�D�O����j� �8��WE���a�gۯB���#�ϱ��"]����q�L���Х�㚞�a?A�Wf�?"}�}�"�g��A�۱�C"ݛ��E:��o�oY:J����.������#�&�o��v��Ɲ�秵d���s*�̩��h1��%+Rn�mz�h�"fF�c�����xeK��7������r�-k���r��ʬ��(�����n�[������h�OL�d��&��M��q�zs�B��d�=�v[Scc9]Sԑ��-!�&��&-����H� ������^�a=�7,��#wU_��R#���Z�����5��g����� w�^a���UU�/o����<>a%hr���f��	�G	��uqtwќ��t5Ʌ�(�eQ�͖��z��oj�U<�/�ǣ4:�6w`ӈ�+J#�9�F@�߯ӝE�vZ8�����u���%�ʭrx����C@��F^��/�K�c��)��ڈN-el��y
@Ҏn�+�?�b���E������Ol}�<şq���fh������/���>}�x��$;[��ͭ�'xih��}X�o ��%|�%�&_G3<�G���:qЬ���R2����A��W0>�����Wu��׊��5ri�>}�|�IB�;^��M���{�m�Z������2V��5 �4��.~��/�Ln����M��R��6�xaH���c82*xsY$�ɺ���+�㇞@�<�/}����C{k�6�K�"r*��Ȳ��:���A�˼QO�s���5�r��hq��/�"��6���/�k#�Z��c�c׺�h�
h!�8"����NH,���d��V���\1�}{)�_�>��O�	x.������Qݳ��,JH�*`�(�
fVȜWz�V���h������k�ä`���Iri��bޘ�4d^d��
��'���U�"�5rv��qS8ϙ�21~p���럑]�:IvW��af1�������Q��u��wt9�Z��{�ʢ D�н~��vF���������h�P�B�=4.s�����J������<�$�߱t�^��0�+��b�n�ko-��2��V�d�VAQns�q�Z�����.B���>K�ZICQ,����r��T�G��}·�}/�� �6�t����;���3�W��X:^�[���_��f�(�����~���,}D��`�m"�.K���0�_�?c������:�Ƈ ����(���FRQ�)q��ːE��š׶�DZh��M|��A޴���������v.չ*&`�G	|�����sx�Ezo?�i� ����D��q��RdN�q��.�d�����ǣ<�0����|����~��"���T��Gv��)ď�8��<ؓɿ����R��?8Lr�����}a���&X튯j���9�Ȋs��lWu�)9�|������s��<X���f���>[�^@�^
��K�8|����%v~���ӫ�����ˡ@Ю�/�=��_H�r��Z�}�1�k���fI='AڮǠ]�k��B�}�f���?���3�� ��b������"ma�V"��q"��?;Ok��,�;�{��Gw��8��꿋~�9�j�'|�*�)c1��}X�M�'}�1��E����A�d�1�{E�w�7����{��KYȠa�a}(�����[�F��>6�?��^�9_��b����2�O{��_�����^�Z�"�mȿ�w;=�;����V�{��q��H>�~�)��оLv�g�o�
�Ӿ��`N����W���6t��~����J�~k�y��H?��ߤ�	���+��hߠ�����������WWiK���u߰{��7�/�x�T~�M�����OJ_�5�� ��C,=@�;�tFP��X6��4�^i��ɿî|���g�����{�?�'�W�W�d��@��%u'ޥ~��)U8�d��tK������J3�N�uN�7?�y�
/ �t������#R����ӣ_`h�v?aD+SW{�\�^���{5~������3M%j��=�%g(js4U?I�̔<@e��Ϡ|?��h)��}M��BZ��˪�K�Nz�l�w���������Q�&M�7Z;����>:��I�2��A�'���X~j�>a�R)���C�'ނ�[�[�Amh���i�
|�Qe�o��	�!l��u���Za3h7 ��72~ꮷ��g<&@1����%��Ojl�Ʌ�D4v��ԁ}�<�,��>���~o���/��B�9/~�B1��d�Bl&r�5��+k[1�ϛa�2��Nʢőn������:#?~ٞ�P�-�쏵ylO�O�ӄ��m�h��t���1��.�ZmN������A���G̝�d�Q�sg�?S���ZU��}�]��n��?>��'��<\��xSV�o��y��U�r��	 ֩fuƠ��������l��m|xQ��֠�?���������ޞ��
ږ4j[fU}��ƮW|n.;i��V�-Y.�Rcy�Ѭ*�_�������A�
۵����%�<�E�_�����h�c�7hO��=����p<d���8@�yG��$q�o�ߧ��%�>�7_�k �y�b톏�]�ou�Y`����I�I��.5��C��kLCG��ROA@�b܁��;u�n#M���{��Q<��H���E:�
��*�-�;�*�e��mBê�8����{5{լ�/��,x��E�]H�#ޏ�W��ĹfQf�gw�=B�����/��ɩ���n���T78�s�zDl�Ԡ�[�6�������w�vއ���wxl�HS���#!�~pݠ^ �+��T�ҵ�_IG�s�|E��kRi��!+����)�җ����C
wT������� �1�w<!{a�֫��d�W��XiE��`y��F���ZYR�v�`6�}�$=+�`�X�K��0ԳRX�`�֮"��V/��-/�e�%��b����*����/^��3_l���|�9K6��ZO���׫Ne=�`=W�H�7��Β���=8�1�k�i�%:�������o��V�7L��TI�7\���<��d�Ug8������J�{Xf�+�(L��A�r�kz��L�;�`r�����V�$c9/�I�h{��z۪�X>$T�/�ǭ�W_��޲(��<�F�LF��>�Z~������/&�zG�ϸ�K��\��6O/�������&�cYz�H'���"}3K/i3�ϼ!���)�cnb�?YK�/Y��H���D�0�����,/ҩ,}�Hd�(���9���,}��Ad�FL��������"�Ű���ڰ�"]��g���z��"=����,�ӎe�����/��<"x�N���X]��������=s>���b��G�,?�B	u<z!+X�U'w,S�:��L����.�D.�f9�|�Rp������zՃ/�U��l��/ԗ'��宫@֯nHU+�<ݥ���q�0
lQ�$l?��?�Zܣ R�N8ψ����C4����%A����(�6��	� �R�+�w9��LY������2C\�Y�LO�v-�W��[7yx���� mz�jqa���j���}�c�Nx�Գ��,~�o�M�%�9��
X��X{�wi�4��؅���A8���1l�S+���F��o��ݵ�"���H<c��<�y��2Q`O����`L���ǝ��9��7����p8ׇ_()Γ������l˂�v�����Y�>t(J���J��;@ˡy��1#��_��?H�=���;�G�_�\�����Z.�߰@�o�[��n���?�#��M�g��ld�nސb�o+��y�<��3q�0�:���]�Ц ��󆽌�׳?�Z���9�Cq�imd.|�[v�<�YM'��훻A�o/-�U��_����}0L�}?��?�/ke��R߾پ���}�����������5���۷��:=?��?ϗ0'#���&�	\�w/���ފ�4���{�T�\�=)��>�8Q?���ݩ�B^�֯���SBlK�Lsm�5�޴@Q�!W�C�W��Hm���E����^�G���t$����ő;&g��Ê(b�6�ӃlȊb���;�`�A��.�a�4�����g���3�M�F�{����8�i>�]]�Ys��y���@��й�T��Q���Ʀ�v���Z�@#�hɏ��Nv,4;�h�_'F'VS0�r�l�f��h9�H���8�.�������n	q��ȆAl����K�����bK"�@�c[�\��ypU��?���og���b��C�#�\~Mրd�+2,D}�����KQĥu�Ox����X�V�E�jph����9A����֭}6Xs��-sw�sm�~7�����>$���k0\i�ϝ���0zq����Z����=�=ks�5�N}���mdg��9:\b �#�ٝ���=�a�ãJ�	����F,�ilS�ׄ���������������e��oa�ɍ�oFC��YP ��^�Uu't#wd��fc{JuV 1���1#ޔ6؝��Q:1鬤P���FRm1�tz ��*H��%$��9-w�3����k��( ^� m�	_&�/�軯L�7@=jh�	@�<{+c�Q�������,������}��$(����S:����(�3�_8�K"T4�\�VW�-\|�A3����k)�u�A>'�K���%�)�:5;��
�uyW�\��g�\�f��JɎ�~\�pnTx; ���4��C��<��ҵ�O���������p'	.�������#ՙC�\�xAO��nX���2_5�y��,�u`�P\��H����Ks��Z�̜�e����2E��Uh�vnv8������jr��z��՚MC��|Z����Χ�§������O�>���i]�Ok��Y�ӎ+xg�M;�͘Y�0ٽ���UY\Ly����T�,&��v*�O�� F�)����SM,���7�o,,5�LPI�]ؙ!3|����g���I����8͂p��J
[
b��Z���J�����(~�����B�2&+����f�F=��%/�/h�/�%/��n�Oڽ��b��;1��wU�zu�����d:�8:���yˌl(���d\�!�^5�K���;�Q��h�ނ��_[�(Ooz��t��r�B���
�TaOOގ����6��}�Y��Cy����L�k>�8|_3nQ�������6C��=SS>Ԋ���A~�cvJ��A{jʷ
�,�^�c���4P|�����2�p[��f�QQa��^�ռ����8�sh
���f_���_��#�zy�?�\e�h�dV�~����F�::_l��T�n� A�6M��#M�Qx��v�Ԣ+��=d.=R�{�I�#���z��џ�	�%U����|YE�ק�Hd�Z0��[�y2��q+�qƣ�2J�����ytE۸�Z�Iw<���d^,�0��;�����_8�Pf�A���ة��n��q������Q|�1B��6ڔ�C�N	�u��Mv����88B=$B��Rƙq�f��M8��I��7z���r�7��?8�U���X/f�x?�k��&��%➄�� |������0=��7$ԃ�c�؃J��ѿ:A�Jq}�'zՇ�7���ߔ��Y�����q�P�{^>�p�Q�1��Y��[����X����'�5�yH����Q�� �������L�X:yy��-7^�>�F�EX�������a�;��V��m��N�$�ƻ���o΁@v+�1�k!ux.�F~��k5&S�=�ܸ]�ޓUϏ�3")��Pl�uN�g��)fD۞��ǲy�<n����XM�n����bZ�4�������Z1���ҕ1����7D�X�#PM7���D��P�9Q�Ƭ��r�j��2��d�2�G*��%�,�����"�w1�<pP;�Q�O��b�)�������i��^��	�&�׺~��K��O�o-�f0�I��Jo���wy�F��x�&��{���{iO���,k9�ͻ�*�I�<�X�,;�W� {M߆"�yZ�L q��΀�C��Y�����.�^�.-�\	�<�9t�!�]�>����o��r�jӴq���0]�YӤ�����:zt�����rm��G�BZ�G��w3��}N��9T̝����Ib6����xS��R��Jl����	[�@�t
��}5�p�x�>����Rj���F|�����fE��B$5�>FGc�u�y+>��CHw����9�1r��k����?.�x���ě��E���+\mFFx�d�%�wzSL��K=9����W���+r]��<���f��m��?�L��W����͐9ܥƏ�a4i[��A�%��� �M�{��O��1ֆ���~��:hE�)��'"Վ'�#��N��[��s|ބ�ώu'���<SvF-pXa���V}��ܐ��j�w��sqSIم���6�?x���m׎.��q���G.H<y��&��+��8i��6�n��Q�*�2H��p@��H E�T��:e-����ٟy�e�R,���_k9�`���@�I��9�ż�0I���o�\�˗��r��.�ہ;[nCl?(��{f���*5��{�sL���*��)��O�~Ĥ����)��h�◪H�t���nYTZ�u�N�d(�|�B>ή���X���I��Jl�j��'0��5Y��-����_21������9o���������ϟ���/��;��N�M��,/�7�|�!�����I��K����f����~`X��I{�����*4�K�W'E��V�~�$q_�҃Dz Kw��Q���_a��T�<�'mRn`Fl\���HQBai�o0���@��T�� �$�� *>�uw῾�����
�(X��7�GiB�s�*|������s��93gfΜ�AI�^�rw����Ll�I�߈�7y�Kb�����PR�/�c�O�?�5)ߥ��IR��X����8��H�ω���x����t��i����)Q�WiUe��}kg{�����y��[E�q2� ���	qz��JN��"���!�pY�Nv���Ϧn����a!�O�#���r�~�q�:o]����¦>t�$Of`2]��I&����'�a2C���^~M+<��?�x��\�A�BG��:�u;�u�n֢�=�#��1Շ�:�z��X�' t�#���t�D��\�������lc�?�:�G��7���_��R�����f����60�˫H����q�lWXխ�t�<�Yj�y��섬oy�=���F{xV�׶D����Y����5䖷�u_
�F$��CX��=q�H|h ,ū��ip����w�����;�QVύD ?E�E��2#��D=�:=��t=�SXw� �}����v� ߌ4Tw�;c�"h �5�@�{,�o��,]�N�~�?��ˡZ7��8Q0DS�"�/'H���6��KJ'(&'�����vP	^�(d��DNv�1-l��˃߹X�@~"� ����n�<X�y��8a�+��#.y0�x��Y����r�!��ލ��N�|'^�T�R�ek���(����(��9����Ri�`���Oi�_�Bpo�6w|M��Gb�5=��˅5�6���|J��+Ԏ�e��T�y�1_J��)��ҵ	�͈7�&����X|]��\^�xX��PHs�Ɉ��P?H/����DE]H�|0���0]=nC�(�,j}��� �毄E�˧����Y�p�n��Jb�v%��P��ʭ���k�~�cY�=���p:꽦�����u�|t|>|\��	�OgT}��Wa� ���Y~4�`y�.̇e�{�rhh�bij��y�c���
���O���ѐ����Ԥ~܃�X����aa?*��������?��z���%������BU�FT��ƫ���>P��i*%��a�+�H��w��/���"��W�cÈzh�3r��_��F�_x��Q�E3g���g&dGJfJ�sC����^Y���x����������316�	�F���W��̅����_�yW�}����}�bT���~�mp���?��T�#9�"�ofI�r��Q�C���WՈ��taEe��s+w譈	��5�wފD���9�|T5	�f1�GyT��2�u\<K\�ǫD� ǒ��aQ?uçJ(���b���G��/}5�Dz�{P~���eº��E*Kb�H����IT��G��X������� �0�qϸ3�сgL�e\�E��hF=��K(?�dF샯xFӯ��/x�����x�[����<���VΊ�����h�����K���z�g���3~;��3�b%���b%n��X�v<�n����
�ܢ���կ�#�g^�(8j����E����s]��������s�}�t�W�_x����u{V���+�c:���m�C��Q��V+���h�~ì����"ku4r0w9�M��5x���0~��8>��r��R�Ղ�����#�~
��O�{��ǣ������}7-�;2�ƻ+偧&�^ɷ������9����!侟L�~���״6�;r�pI�O���`t�k��n[�w�a�B��K�D�6�>�����GúL����&D}%�==81��9?!��yBTqӥ�DԺ�K���lr磿�����޿oCRX�D|���nd]v@&�vBH�����j$0�;��z"O��S�<u3O]� ߞ���k�)������$�:�Sw����4O�n��O��~p��C�gI/oK�d\<���Nj�mi��/%F��TύZ��H��1���]��P�~t;���x�QT>��O�d�?܀���܀�>���Jt��?J!���iI��D�̪�3�W6U��dD��O�'%Q{q��%o������f�<�g�5��Po��~��G�N<��ǂX�F�O���� ��;`zL��?5�"y�z֗����DҘW����K���O������f��k�5F]-7�0�M�p|R����oX߹������'��}�7������)I������+1�������w_V���}�=w'>I���<z��QL^4��4�B�j��_�+yviL�X�!����<��w�~��m�":=q�UC�S�P�KK��J�����T�r�z����J/�	Um���^�P��;
�}Rt���E}m�]W���R�)�U��� �@��Vŧ)VF�+A�Q�4/��6ԞgfҜ<��j�e}�����XÛ��������s�9�3�0�a�Z�S��B�5<Շ�^�6<������S�t.big�r�W��D'���O�
��;̇�²�1D��A�"vV �U�~9Q����^�Ͷ?Z�4��Oe�t�ӫ0:�/�����Q����}�@��]���t!|�H9��9�**O�b�/u�� �Ȳ ��K�8� D�(�}����p���4�U� G�Tj�5��BE_�o����`�۽W"�j*�;>��3Q�أ�A8��͠H��\��@��1����X���T�E�Ǐ��!�{�������﫿A��3��ϓh��SG�=<]����S��Էky�5�vO}}�OO�o�<��yޤ����.�V��b�!\��`��#Aǃ�߅z�K�9{�g��v?�⻷9��#��ы-o'���b�L�X��ގQ�$(��/�(���X����C�mhժ��_��I��x�e�(�=��рt�׀��JЙ97P�X�_'bގ�Ϝ��/���xj��L(��`|s1��fY�o�x��H7�B�Î��i]��|�Ƙ�6o%^{q����7��z�x���Aϲ�#R��w;KPyfA�3�:�S+yj�t�x����tx��Z7!f�����,�C����в���YR��F(����f2߬�g/W��,�G�

x�k���b�.�� ҙ	�b15E��"{i5m��9�[+���JVʂ(�1��4�]�O}���Ji��x0�<��_�x@@�X+EoP��ƀ�=<#z+��-�9EX+�Ͽ�OU�������#Ha7���߬�݁. �� ��t4x���Zt{�k_�����_-��f��;r=�<�(�k��r�{.���y�:r�E�KW��۠*h>�1T��� �iǮx�����Nw��-pD�L,/���n6��b���l���2v���b�(?�ȷ���M(�B�|ޭ���}�`˲��`�oO�W���h��˒�6+K�(�٬,o]4��9997�����,��zƑ3=*����ދ�gIݱV+�R��k�fjE�!���.o��L�%�|����g!��@/s݁;R ���؟��b}%��>
�,�u�d,�Q�Edݶ�>���mTc���_i���X+mc�������lL�r0���E���OX�k��?�G�s��wj�C��<�_��l����.�	��(�X+�Մ�EQy:Qx�XB$�W��'�B/4�S�6B��h|Z��l�l�#S)�{��%?b1��Sa�hpZ��������f���v��"�v��.��@?{�Òm����<Z���Ed{���w�G��L�	6�:�g��F��3�( ���ͩُ�/+,;l"���i��(l8#�Zw`T� �-����?��$�y�V�a09'�x[������K���_B��HM�$W����;��5�،<9�L��z��T3Q�#a�s���@v�˶[*��D�����Q��F����,k'R��?�8$�_'�)h�B�j5��T�S��Qk�^�:��"��L�v����͸@��O �ze�K-
[V�,�9u.�p k:�.���ʹ��^5��H��۞�;e�%��;t���P���ә�)q0��9�ɨ��b�|��~�C�s����N��b{�.�9��wh���T{.q�O��E�~����Ϫ軅�]*��l�xw�1�ޣav]	�����~���c�������Q��/�D�+$�+�q>��c�$�����%:�8���A�,c�A���Cx�'����Ko�;���'x�;<��a��3_�������4��w!��n+?M$$��'����͕M5��N1��NTn������UC�5'��%��Ž��?��=���5�����[im������	�7봢�rnxm{�w�ǁ절��(،�MNC���E����M�b@EƓ�J�%�/��=��8'����`��D�Y�R�g�Ū���AS�fn�
;��� ��P�T�n�-YI�w1.������&�[���\��3y���W�fy0��!>�'뢵x#��[��$*��;ͼ�>�Jo�\XU�4�t8J�rw`�	ȃ���:�s�GTt��m�,_s�t��>�����/��>�C����0��u��f�Z�\]5x,W�.j����Ѹ[׊��nq�Fg�ݻt�;{E]�k�|�[f�=�<G�����\(�^�Sxx�dgA�~����`!���sp��Y��<�f�MTM��;��/���M�[�g{E3t�u<�&cA���U*�k��Q������}���{���7�+�t��bx�#���1���
��K����9�Y���~#)U�Sw�L:_��E9�����+������Y�t8J�}������E���
6�f�����W����;g��_�4��/ٍ<����B�v���E�\�u�h�ct��d�*l�f5���=��a�j\r���Aٮ�ʗ�6�a;��CD�n��g��l���	H9^��ۖ��ؾ�5���g��Qz�%�Y�Fi���לI6=���Z���}�I�?$uv�[V��f�m�r��� �,z/w��|#�\ѻ�Hc��z�܂�}*� ?�&��A�o���:o��m+�(��4|���\9}g���� ��o��G� 솸��\��X�<�(��V+cè���j�B;;o����'u�ߠ��m�W�w&U�:��C�ׇE��×���V�XX3B���G�:�װO#!�*��Tۑ7莩��; Y
ъ(�I�\\�~ <� �Tܥ4fm����?��aD���Ten���Mdz�i�V����
�;%�������FD��Z10j�n1��P�U�1�O��^��<������'/�h�����慫��o���Ϋes ���M�>�E`��7p��;�n���@z��[op�6dO�FϹ@�z�]R�� a�8
[�, &%8?ށ}Q�<�gi�{*�<�_�7*d�\����o�L���6ؾ�O�=0X L}q-@a�h��繖H�P��8ǆ��P���f\�,�r��qHe�?�G�{<%�����Ql<m�������'tz� <���.H��0]lG�<MC�@n?
���zp�%RR���𵩾8�G'��;�@�&v���d�^�/����l�ń�90����.�,���h{����J3?Z�A5P2H%d-'�A�%�gw`�����f^�۰
~1�m�jf4�MS�Νl'����#�����Z����o�5"' ��o*�9�퀃	��>�K��������{��tygҏ~�]�3wN�%����D.�x�& O��#a������F����r\t�El�=ѣ�/೼�Ӵ�Q^��mW�Jf�� ��8��;h�#�ԇ�y�Ӑ����n�Y,�� �u��^��&t�cp)�O�[��5��%�O*=b��(G���ţ�Y�ȍ��;[`�nwc���-�g���Y(*k�v`���$.�V��"L������qs���|���k֋�2|bn"}#�{�CZ��rR:�G){#*G.���h����;�v�,��o�HK,�"�	�O?������;��J�_� 	����H(%`��� ���[>߂/]���&1����[���/"!w �k�_X�!&�5��~��!���t� ��!����.6:WEiH"�!���	���N|;ڒ��R: )=q��]'z�����<�vn�.Xc"f�}{��C���i����(`�P07���5<i�_ƚ]źenms��E�F�~C��W�Jg�� ]%i�%A�����:8ǅ�+PR����}L��O���?#u��<�}���%D�q�N����7D-1@�t�(H�K��d��h����=]��r:�s��_8]��b�X�{���r��;��Hw�BNY뒟4;�������K��,�����9׌j�Y�˰�W+�{��Q��J�'��\q
�U�	�>q���_���w9�1��͍���M(&�tޣMv �F;s[2]ūhXb ��!w�]\�BCy��{���p����ȡ��$K�=E����|f����m�h�-����8�va�p���"@�δ4��*����~��b��sH������9�
�[�9�@>ub��/��ۋ ~+l	G��U�t��"�e�sW���F�Ԏ�z�����h��ly�@���� �HI��F1MJ-f�
5G�E�Y���U�����%��B��c�A�u��F@�A"q@2�^�PT����i��<%4�9�Ң^���%��mD�@$P&5�O��Ξ܈�:�և�r�`�Q	���c��##�&��e�)��lC�e�r�q��:�>H5r^�L��t�0X�E��Ք�
SI���='Ey^�;0 �E�I�?E�p^R�}����%�s	~<�;��<���q� WS��s��n��Ȕ����-�f�z��������pFg]�'�@��P�>|�ε��� m����H�R��A�_[��	�F���-��2����>�����̖㳛w�o����C���#��������;F��r8zv���y��2y�r��2�%�������WkN;\���F�\��=>�Z��!&��d��3����ѕ�Zfsot�o�����+݆��~X�|Xχ`=��~/_O�<���Ɲ�*�׿�r�B���*W�׻�Y����#a�/��+���\.?��٨N���״��Z�q�J��^�1���e� ��;O�[~��ٯK�|<������C�l�S�r�K��dk���i�'��J�s�Ë
`����d��5QD8n�n����:��(��y�;�2{#�����T��N5�nێ<g5'	�U���i����F��>�\��M������#�' F�f��5x;5�F7��[���H����j�N��{�o�k�v<���D3�ߢc�b��:��	�-ͤ� ~��F�$�����/�K�#�cnv�S.'�l�)�D뚬\MbhU�-�������č�^L��\��.�·�7�Z��<���#��l@�{^K�\��n{�C�T����I���_���W���U-���{
}����b����B7���9�n���Fd��e���q^dhFnM��=&���zZm�Q�@kd��m~h:`mR��vن�v�	_H�����6�>|#ZP�yG�O�_�x>�@�qW�Ȃo�m�҈
�R�>`OYW�s@�=�v/#҈�Ocە���gKc�jҴ�H�9F��
rf�H�"j���jqc|�E�ԁ�P/��Z�~h�)ܡ)?���w+ �'"��^Nq������c_�W�����>�^�M��W>��A#^`�����J�������H���5r{v����ō��߂�$�)��0��r�3����a؆��xL�>�h���`�wW?I�j�A���l���Ω�7��JCPi�?�c�&�p	/��l�M���Q���ǆҴ1�Z�^��=���n�7���5��o�1�W]B{��ҿp /��O�3����_��������?/x�������N��%a�?m߀s�^��[�{�v
0@�C��0���Ѡ����x w��(A���5�(�2�B�����[Y.���P�[��H(���5k$J7����ouP(Gť�W���"��]^A,�v���.^�>��#I! Gω�0'ܹ�5��� �Q���x��l1��KZ.�s\�yMt�Uyu ���v�J�)���r;� ���Wf�y���.�g6��ne�^�/�B*@h=�ٽ���Q��՜!��tM�y�/ܐ�;�g�3�a��l�(�����8!���5�B����(����u���ӕ��}x��HteTаFd�Fg�m��A����Y��-���
�B>˷��	.~q��d���7(é @�g����R=&�I�������~A�h��^�Q��f1��&��0]��.��]&��q�������'�L���`C�
[.b�F��責���A1~l	݅�t!�:���9aZx��A���DG��~��rt����� �YO�Ė����t_��Ռ'ˉ���x��I����<�4�o�����^v`�MѷZhE�&<��/�U9��,$L�g0��Fn��.:�M����2KQ,��{%��F��ПD�^�F�uË�6�d���E�7��z��=���Ȟ�|��ML ���ߧ�<GE6����� �@OXi7��_=L�)p��O7޾U��� ����������[�ͮE=Q@o�_��~�Q��ެq���wB��1��|OL�2N�9Q����Ed5��M��A��5�(��5����O}�z�<x�-o��]{���_��9Ѕ�m`���ȉu?Qn#w��=5jc _��] C��	Dh�Y��b-�@�����n9��_իw̼U)!����p��[xR�D^���g���� ��8�`�{�A����ڷ�����/�%v
=R�/y�Jd*��ha��[���ĵ��sz1��K n�;X�w��]f���u������+�ڠX_�!1x2Ei���D ��&=ُ�L�oO���^��_@�#)�Q��u��a����2�w�t�7�克}J���m��T�rk���N��"�w�#��l�GT���V�9%C�ݨ���G�,f��jT�b��� �r�Kΰ�y���
Em3�,`CDw`Ȝ�{`p@��!�f˃�wjjK�BͯݶWd#&���多.�,Y����Ĳ�̀ږn�xs�1{��v7��<�,�Ik�5.��-q7�b4 �O�.B�Z B�3���PHM����)��G��d�f&��TU�|/,��ak#�\��+9��ޗ�#�pX"��q�8����@��N�,���u��m6t;x��
	!�ξA��t/�����WK�	�rYd�s�����j�� �����;@�6D�����0s���4��4AU�2�Q�����~�^��Hv���_�)�l���Q�\��/v�]�H��A�K!�<琟2:mO=��)�2=���SEH A��D��x������J����}Z�tǻ��zC�JJ�����S9�.&Vb��7H�����b��j�@^�p�I�(��KՃQplw1J��%�0�4q�'�冒]�R�i�k�{E��ժ�#Md�E�ƘMH�E[�Q��.[����ؽ!-�n�W:��v˓1���h��gT�q�Z�K�D��K��x��뀝�᪉�"���"D���KGDy�O�x�s�t�ř�6�<�to:�?Շ�#��f#
菩��s��<�5���/�ɾ�$PKr��K�Kͥ4�|�m4�2����m�I�SHkXr\���k��!�'
d�?����H"��6���?qW�}Gvy�q��?�{�c\�j ��R/�󆘻��H��wO��(����N���5��8����e-j3�>Q[���^�;�z�O���ǻ#E���s��5D�1��ݛV5>��.��b�|�2�I�NKÐ�$����`��-
��S��t(̟�v�������<@�S�����E�ۍy���s�M����n�� r��ƹ�7Ϝg��9(�L2?1�t�T�A��~�(m��򞸙��5�z�) �B�[؊Ot��%B͐�J�O��l6�\��ڤZa=���!��Y;Q�Y���V�7E�J�Ӽ��TF!�m�Bd?�iY D 7���5�F����ӂ6���G�����+:�� ����)e�-��J���Y���Y�͠��ߣ�4f$��u�Aj~~�隨�H|A��^5���xN�5�w���y���{��\��u��w��*��,�F=���Y[����A��%���+�Nj���V+�Lg�:E+�*���b7�&�f5R<��p����B|Ź9s�ژ`r`U2hݔ)�u�����
�Gf��;����ޜ�RL�T@���wb�����{��xR��������f,��̖�#�F�-�J!E��x��A���Awx"a���8`�	���u�����R^�\��
7[�pNɚ�HX��r�c-��԰�3o��'p!����oa�6�%<����ݐ�b�E�P�}��2�����n��a}�!�L�3L�Э�$��������d�}p�����N����|���;$g���z�h�����d�.�r�d��z��߂���vCm�=��Ë�����3 3ao�����i`O�2�[/^��K f����Qh��1o�t";�hf�y�`x�`];a}������m9Éa>,%�|��0y�iV�����)3Z�?Ϩ�":�$RR����') ����;�OY�<Xdtg k�1K�����.���Kh�?r������t���{�#l��q}va`HMI�N���10�=�0�"8v;�uN-ۛ�����l��>��9���a}z�;0:��SSbo
�����=`��t�]p4@�S���>��w�!��q
NW��@�ó0`ne���?�t��C�`��vk%P��|��fr��(gX�QX�T�
u���s�����W)�JT�+����9�@ų�Jd�V��.m{�o���枤F�	�w����=�tB�W������ʁ�Qi��>cH�N�G�6���5�4�<����ƝL�G�������	�eg{��W[W`�L�6�w.�h�HV�̆����ib�P:��Z��Ѐ����b�c#R�;gm;�YR��YkeB<��	|��a1b5u�<� _��~�\������E��b��ϯ5:�f�}}o�8"���VMOl�;<��g�v���gC�M����1Dk����v����o9���	BT�o�ԛ��|����Գ�/L�b�����nU�T�w:���Ӈ3�"��x΢�yGh"67�q���=W��t�Ƥ�1�U�
k�_�l�~M\~l}�d���OL+�Y:M�8�\<y��2I�j�2�<ǃ�˫�<��c�4s�Tf�]6[��{JiY񬙳7L����#�T]�ү*Q��Dj=~h��/۹=�h�ڗ&K3�I3ō��̓�N�}��U2O~b���ɭ۟R:�\2��qq�y���i��o�q�;�]�p�{ho�$͜=�,n�:s�bif��u6q�0�V��y��)�+���M5�͆�ŭ|��E[SR]��ǘ�A�aR5��mX�&<&Q���Dvz��F��ާM�!��(O?k��`���-d*�.����?�`=��ZL��T��� .?o���RW�DY hd��/e��Ĉw<F���f'Dy����a��H��7.�"�gæ��f��-;i�O���v�<#��m��o�bx�@��Vq�@���gk8��ނ� 0t�T�Y9>9Je���b�(/Ŝ~�^�?�g��ߋ�8	E��(&�w���d~͎��kW��������E�;y5?�Uz�u���P�S~<�X��H�A�B�}A\��$�7R�:9��qca�N"��1]�I��J�8�$�E0����Ij�\ƈW��Qb��A}���e1��JkP��TOqU�2�c�o�2�*VL��+��0�>���Y����6����'K���撲����!�,	�#�=1�f�b(��?�T: X�|���}P�y�z2-�w���	�/��bR���(�2o&?#��<��xj8׏���O�W�)'O��z�*�^�p/�N�7�³Q��T�/����.��z��|Po)�t�lN�7N���R��u�#�sʿ�rΟtw��W�'�/�j<� z7wB~6�~GT��sr2�j�惉-ɑ˪��'$�m�yV��y�b0� �N p8T4.,Ew�z�.X�]c�%x���h:J_\�YM�;�6G�L�<��[�.�Fn\r�V��lt��$9�)l���;*��`�㔨���&ƃ
�A���	�A���؂z��*� ��(�b��f�]�k����.N'�����"V	��6Pnm4�rm�/������4²�)�5�K3:S�BJ��w�Q/z�+7<�Bq/�F��A�J��&�@r�+ D��F%@J���f�݀����I��R�'z�\�ƏƁ��`Pb��BxV�@6>>?�k�t�H/hD�{�^gFxS�>l�����;�H�oj�;4;;�����(�'8k��H�U�FNUkՆ��6��GU�'Ň�=q�7M#����/�?h�-�ĦSb�J�`�F�s[��93l��M(
2��Ȃ�	��r�Q��a�Sy���U�C��k�Q�ƅ��5p�m=5���(��+Nh���I7�;�a�xv�)M��7AEk}?x!���G�A(��n����_����s��(��^����)e�=�+�8�(�
�&O�&�O��Py�&�_$���>�����ẋ] ZQ�"��ҿ؝��xwE.��/���<����~�0y?�m�:>�fy�y����ې]�n(�ɚm�V}���q��2ɒ�%�"wj���QT��A�$z�8��L��;��VZ�G�Z���J�X��Ui�)�B��J�F¯��#�Vv�Jᜑ�S3N�1I$�s��&�J�8�%9>���E�V�v�wv�b�")��.�g�"�C.�U"�{��sz�y|}O�5,%eT\�Rz�5z�A��47eDv�EYSD3��ѿ����?K����N^�J�0�a7�K��x�^�1i)+���O��Q���̻)��2����>hN���R#�"K˟��i'�RY�T:�̗P���g(v�^�����e���R�7��y�UE������F��֏�=�{��CGO��dC҅�np����
x!����)ª����1�I|])�Y
��Y8��hC�����i����f�ז���(�w߻[���\��x)��IX�}�-ΐ�	���G ���ь:ّ��.�������Us; �3U=ol2V��I��?�M@2���0.j(�@�̿��&���ĘhXG��9F`AG�pF��$���|�[��_��%���f|��4J�a4�XV*�3��1/	cE�������|�p�p^K\�u}�%ƀ�Ǩ\�)��[F#�>��/�&�-�1yf��l�L�}��nП4qÜ��sPn�p���l&�rK�`��e |����J�GV�0T��ID#;��|6*iYj�+��'��������nR���5�r�d"첈��`#Ys� \#�iG$^��zpK����33ŬK=mc�N�>����A�Z�8-�T&/)U�߬
���}�{� Ko`7���l���)R�c;��<���v�iWb�\�"���e���%��p3���q�U����-���ƎlQu0x?=�4y'��4?Rx����+W��R4���cM�.���Ӟ�$��TuW���L�&������ŧp�t���r���r9���C���ݿE�SҀ���<6U��U��1΅^������WvTգmZ ���h߉���|�%F�}ĳ���d��(z~�g0��4���S~'�#���oA[�/¤��^݌���p/+p�Vx`�����"��8��>�3���o�-
�4y���^��
o+�F� �럀��l��$�wL��Q�$l��%'k����B�[�/9U�>p��
����|���qO6������H�\�Nu��ľ6w�dE������9��C��z�d�@�Mȳ5�B��������c ߈���U}+���(:a��3<Q���ɣgl�ٕ$�-C,�?�ǌ���f�%������N��m�,~
����M�E��}g��j�H�X��V����/����_�v��6*(�V�W%��#;3��$���ȏ��k�fb��T^Y8����դ~�Ƚ��M���T�Pi!f���˥�EB��O׸��Ĺ�m���a�͡@��Z+�0�k	�+_��Zn���������hnX��u�?.Q!�ts��L�����(c�sYE��ºʦ����fh+A�?R��GʭF�\-��pڙ='�՞رyST*���T%E?�m�RW$Dm����hB2�	�\1�Q6�X3~G[2�����+Pe��m���FoP�v���	��kAL6��%��k؅��K$��!/�x�b��1��l���6�#�PO.|~F�<�y l�jɳ����3�[9m �Hw~�6;�^%�P=Uu{���S6j�*>d�u.�i�k��Se1i�#RO�E����ѫ��j *��n#Yɷ��)�?��tx��}	`SU��K�@X_U��mm�Z(�
զM�I۲(jIӤ�I�R��
�b�23�����ৎ:*ԕ�H�Ogp�qCEM(H��5�9����$m)~�}?�$�{�۹瞻�ה���oV߲�����?�"U�ק*�=jv�>���a3;Y�0:���A����y�!�>�L��0����!2��o2�����t�X���cn9�0���~�_>�k;�n��9��k�ԪLMv'��2���ӎ$B3�+X��"��E2��1�[0�΄B@	���t��]�����b����E:�	�Bu��wva5�� D���w����@�~Tj�bE���,���d�-̶�C];�@n��W������7��B|�zQdzX�Fa�t*R1�NM�u��y�T�'�]�ʐ<��:�n��q|�^�52R�W�b�C
v�r�v�ʼ}���A�n}_�oV��Ik�>�1|�1v�G$�!���|����]Kr�^�2.2{Oc[GC ��l�.l��ٶ[��4�V�ܬ����O��Kޠ��)�����1�����͐D㻚�-W��"��푱mS Q�=Ǽ��yl�Y�A`�^�v���d��u�[յ;�^a�B���}���^����^�шt�Rd0�U�"����j�)��o�瑩X�v�D?Ԥ&��CFrx��}�}�g5�P�(?�*����TE�	��"9�mQi[������ډ���ܓh��볌�C�����9�m;̶�,���|�s�0'��!�%P���Pg�֧!���΢d��HRH�Aݷ�Q��KP�\^P��(�G ��o/������|�G���Y�B��
Y@u=Ğ��bc���h?
��E@��+P�_��w��kJ�̡�/����&߮��MN�����/�o7q����b��p[�6��
�d0 �\���A(�ob�܍q|����L��������.���v0;D��ۡ��P�K��� ��F£X��^i����r�\v+-�P(F(�4�6��J |��~��
<��h��ayz��.���+�2]���ӡԧ���IU���5R��T8���o
�`m���kR94Q����+�p|�搁.�l�a4���ӗ�벒p|�A�������c0�db��@Y�BI�˓�(fVo߮Ҳ[����&I��ޞ!lk-
��5�m�@ȇe�)I>�O������ݱ�Oua���d�0��B��}ۗ��t��i���[1u���ę-V��ӗN�_����fl�LI:�e2��fC{i���]�J�Um2&��-f3���i����Unq��vg���P���}�vK��Pvݍ�hTbTb��
�}Tm{��+���V�R���_`eۊ���B�l[&�wP��R:�ʶ���qH�ssBy����w�4��B����4��^�z$8��d�:� cx�Z��{�D�-ȇ�m�,Z_�X_E��P2�/
�Nq�.���F�!�EC��-J��������+S�^4�:��d�o��H�so��˟<�'��������'{ʼ�e+G���}nG�����V�˓Ʉ�K����w�$=���[ ��;���� <0o�����ֿB�B�@o���ª��������t�Q���%�m{^FLm^������'�������F�i@}A&?+���;w���������#S�0�-��H��~�,�9~؞�K�Ծ�=������&��+ί(!d��0b�k�6O1&#1}+鈱��1pu:b�q��@�#��dh��F�&k=����>�+��y��=՝Z�I�柉�7�xVS���ü"J�:I�=K�.����_���t��F�S���q��՝�cQ�,�Sc��(����������
�u�M,H�oW0J@����D���GDBrb'�v��6�z�����D�����MQo��d/��)�L���n�7q����[������v��h��m'4��B��%�m��N��\�������`��E��1*�ɋS�g�i�n�N፧q	��:��� ��m�D���d�et�H�	��e��+��:���j_�*��h8L�ǩ�֣�����]?�m��\���|�֢�B��w*�Y�%����8��	�s��	�\��J鄖����i2��Y/Ed��8�3���D7mM��%W�i�,$���ѣ;���0��
�v-�b���
=��h�?N3� 9�
v�Ѐn��1�O�Z��r~O8�Y�C܆��n��F,���hH&�y��r���e48�0x�
��%��q�YMG��0(:2�&���:2��3��::M������������gPJ����t��
�/�~���~�T���ka\�M�95l�D�&��6���K�ú!94�;������]�8PyX(���ǻ�z2�H�������/ڜp��XVP�'A�}G���$�aD��е�w(�����0���ۋF��Z��#CK�_/�g�xZ�|"��f	Ym�/����п��T�v�d0�(*�[��D���A�a��E 5T��!���.�nmn�jb�sTMDg�����R5�YT�P�9�E\����s��^�\�j_�Hl�m�b��$>Ō.�7��������=�xv/�ͮ�GWe{�H��g<�n�/O��\Fʓ�u�q8��x{&�{}�)�!�0��s%&��p6������]w�!���a��Tv����W����3�]�yK2`�dx����k'�L$d�¸͍����Ů{�De{O���lvݽ���=5	��w�K򼧮�@^�ӿh>d�ۢ�x��B�-�S��K�wzO�����Y�\^
������쟯�Af���X�w$KK��۝�]������y@�ܞ��12�핣}��-����O�z��N��X>��#~��k�rh�v�r�o���=��3�����|`�O	3i��.��]~�{�_�Ry����z~8N֩`�� 3o����Q�̗��J��]#��G�/�
���G~c����U����4_Ş��kßӹ�m����<um�{���3�>���=��Qy�S�;�xO%5�'5�c��2Ƴ�Rx�(��S1+Ӻ�#�c���ޜ�����[;�~��vc�߰[����U����If�������曕������*��v��g�E���5|?�5�v+�_���7����S/0�zNI�C��=5�6㘍�l_xT�>�����ܯ1ol�+�h<
���u�AE^o�ݚ����z��{Z�Qm�f۾�yJ]����h|���3S�W���^A�#���^r�_�
�Y�iqʇ��m�TAl���f#�	�ˠp��n�M�-�c���M�*G�_�{���%��)��K�Sz&ҕ��7����F�wP�H�HB?�$�������w#�		��Y����R9�#�#��O�#�	�aJ�ҵ�˔^��,	���[�>VB���>�}���F��z���n�]	}�� ���?� t�K�����I�i��қ$����_#}���A��^ �oZL���I�E��GI�-�>�?���+��T�.��|�Г�����A��@t�Y	}*��G�o$�*g���OQ��H7I��(���I��P��ϖП��F�_.�_C��+%�zJ�E��3Q����>��/�y�Ч �z*��F�'$�	��	��#T�ǣGB���G�[$��(݊t���2�� =KB�N���?���q��85�9uZr��n�N
h�)�yVA׉)��M��
��}��U�kr:����e�..4r
�sV��N���рk�鼿VuW%��V[��W4�a>`ݩ��nY g�^�f_�$�I��4����mt{v�*h�Y����ft���'��j|_��5�FDC&D�������'��/#�b��Ʋ"���9�[���z��$�\��:���k�R:����+���YN��A������R��L��v�
0�F<�/U��؍���݅2�U>����:K�QFgi!i\�.Nv'��Q@��b?/�-?��
������Q���Q�$t�Y��O�*v�|��pI��>̾0C]��rȺ@�ۥ�g��v�r0��x���=���MF꼉�ܣ;�sIq��5P�a�x\�<��������H���W���e��ɔ0=Jϧ��7�4��3�9	�u��	��/@��<�f��w�z�}�S�s,/oo�b'xr��H	�E��t_�Y�!#K�yx��:}B������"�0�?�����Ay��]�2����+����2@��.��%��c��V1w�?Na�h�w~�t#�A[V�2Ȉ�Nu=$����zʻ�p{(�8�4��!�_
-�M�O�W���<ݧ�;��(�(�[�ժ���gi}�������Uc�5A��`����a-o����8�����#�0�D�M&u����s��0t��ǉc�O���������v9�٠|�8�����X���n����7�B,��i�>��/��ΧH�{��&;���c7���N��v���)+�ӭ'K��?���7tK���4v�(��;~6��G������CU�aԥ@5ob���ǄV����rU'��7v!�0�x,:_?F��o��}ʶ��O�z�������T��QM�̽�kV��e<�f<ˠ׈��9+��N��z߲�רB��kL� �Y�A5�H�,̤?��Χ!bl�{%b�Ҝb����t�6���#(;��1�-��hA��㸥z-���P���y��Xf��dX����<GvkRd�nE
���K���%�0�K0�ߞF%)���=���ҿ�Y�f�cihȑ�W�d�*2^�e�*=J���(ms����/�p �#j�9�7�qυ�D9�$(8�?X��1@�l��3:_hG�7����M�*�"�GQE�H{w��<�-�HS��"K7(7A��>��	-��W?�R������#Ʈ������z[��(��^�}�]��s��H|2r�,(H�^a~����-���aD��X��^�C�Hg�CG�X��I�w*v�O#��E��bCv�A�I���#b��ZO�Fu!&�#Q�2f�|�e�҄8�,�u0��������<����t�HmD&-�l��T�#BE�rM�^�c�D��م�K6��g�tʯ�"���Q�)�T�!B�?��/w�҅�s:�6�̗��'Q�}ʼh�w��WS�j2���7��N�J���.�ʟSR�|Lv+v��|���6Ǟ��n"%�+�Q�@�H��Bf��{���+_8<�,�U����p�6$F}�(z�K>e������v`Wo����ɼq�?�@�̮B:�m�-�p9B����z�k_��ݒ����X�1����5-�W�68�)���J��sh�#�H��A6D��o<��U�=�w}��`���m#�X޷Ǽ��ى�!jv�̮6��j{|x���ٶ�����m
���(�%�Q��*Mփ�H�r�����}Y�0ޗ�ދ��c` �-��Z��0���N�~����l�:x�b-/���WVB���rީ�+�`�MF��y�{9��L��YA����mվ�PtV��z��qT�vR�Q=�T�S���J��]h����?���D:�t�,cR�z�?��H�j��o�����A~�+2�������h�_0�s��{�"�#ײ��`��U�����M�1m�� ��	�2r`�K����B�\��1�����6�'���2�;�
���/B�q�*�ٺ��X��H�IUU��2}~w��bv��Ѹ��3���2uOn0�������w3��e=�_\�+�`��t�zP��s�1l�C�?�!���Cd�I�a�`kwm���Ҟ.�c�v<��۾v�߄?��߈?/�_�?϶����vi�S��M�%��������4���'�
��MEȎX3�L��uh)bW"vbf�J3!V�ح��B�Ħ"�'Z�Ɉ�e��X����1b����j7ʄ���+�1��EN�G �Ć#�b�{1\��^@lbAl&b#�>B�Fݣ���݅�t���՞��P�+�S��Q�-Fl$be�C�1�R�Gl(b3�]�Pbxa*tbK��ňEl�L��j/C�8b!V�ؗ�U#�bU���o���U"��
ĞE���"؃���?��~�I]����4�'x�Ǹ2!���%��������2]��O'˾�O�`xu�����`��� ��A2��0��d�!0l�).>Cg�
�ׇ�l2x��[�5g��� ��O��^0��"�����hEO��k>���k|;X�{$�l2�����ZV�����v!�ʽ�{0�럑���*6�X��ԓ��i��y2a?K�佝�`�E��r_��sqwj���������Ɯ���`���F,1bCs"v����;��� bvľ@̆؇�5!�6bV�:[��Ė#�b8M���6!ֈ�}���T��<�nGl.b�3�J3�Lh�\�1�+@�Gi��L�����tĮF,����g�'u%�J'�����<-�D�#	�������o�<:B���� �Q��I�##�P��<"B�H���y%�M��"�:J^AȪy%��2BΥ�BVDȗS�U��!�d�����)B�9�dY��	%u �{�)����¡�����78Ɣ/�m�������J^w ��fJ��<B���%q�ˣd���ΙB�W���pJ���/����DksI�6�~�;WGL�G�Pr&m�ؘ���%)��zH��~�Yr�,�P����#!��Sp>O��7e��#�W�qZO�=<߭_?�~B�O��~In�ob�C���߃-��82�O6���&����d�#6���.#�1-��i��G���Ċ��G����.%��	d�#�B�?b���Gl���.b�f�� V��%��]�ص�]D�1���1�� ��M@�$��%!�DLN��	����_QOΨ���x��_	^u�Q��~ A����u�� �-�����]ѡJ`�e�F���ى���������B��Ļ���K<WcH�~=�,�ޒ��Au����`:�Oԯ��	5��E�S��~��
��\�!�����	��A�m��W��otbwl?8Y��%.BG���[eS?�<ar�ɝ�rgJ��ZvK����d�%�&5����zo/�Y�S�@at���O��']�¶��󾏺�u�2�N��2����U�~{0	�D�!Ǌ�aE��_ӋPZ�!��.�����wI�����,��g�-��S>4]RY�ǡ�ߡR�=�Ԟ���۶<=]�VE��B���J˗da���Y2�EђQ���
K�\h�x��'ާ�ZkO�n�/�-݃W33��g��]]XPº��/�0]�ޞ�l�Ux��͑��?e�c���V�'U��7(��Aw��A�]�?U��L-�-���J��VB2���'�5Y3�_N���2r�w��_������4�B�em��Ȳa�o9��
B���#]���/��"r̀���V�/"B�,�7�u{��AL9��*����^�ڭP��P���LXk����U�ڭQ��P�y��5��?'��HM�K����5��bEu�z�ا>��C��_.,�pQ�"�����u��{b��B�v�q�J�v�A�ⴏ,،��c���5�>����5��<��QYX�*4��+}F5*�>@,tR�C"~�("u�8�<��2x3�6.�d��l\ ���[�?y/��}+��HkP��'%�}A�lq��Fd��a5�u�����{�Oi�g��ş[�� p��7��
�d(�C���-
�Ɨ��Mh���=A!^J6<��ۉ��V�Thh���!��R�I壚LO���t
�3̃��2ﳦfSwCt�I>	:�_FX3��KA�����L�ӟ�6�Rض���!e�3�W����]����(����Bݩ�V�'�Ii ���S�ŅD ��/tk��
s0�;��2[C�Ge�+���(�YH�Nh���&S�	�c���>��B�k�i��1��"	VC��h����h&B��}��-��a4�q�	t�^HR�K�/#��}�;U��ҕ#y�l'��_ �}���5l<���$z�&��A��9^zK��aڜ0n�i}�V�_'���C{������!��e�4К�M��A�";��F���6,u���9��e`BO�@*�Ha�nA@�j��f�5Czu��wJ6O�M=�{�n�Y6͔EƮ�p)�R�a���[ϖ����O������|`53>X:>z���c\�Ő���z�i��\�q�2��է�����;L7P��[���;��'��T�E�;�2w�)�� �~^�
/3�_B������y���F$��$�R'�}��u���t�/�^&��&9i�^��t��춉�k�d@�������z{z��Qr��c�k�'FZ��7Z�F��s�x�e�\���3c`
Y9O��o�����l�j�#�P�;�c2pJ�:���f��18X�n�Av}�wמ&��6A��A;���/I��+�����ͩ��W.A�rd�����,��2��tؒB�u8tٚ�C���Q���&��&�y9��Ԁ�>>Rk��=6���Sj��:����>�M��L!���$~j��U���t�$�}Y5��:�.Uj����ꁱ,b��';��4i�d>0�(��7���}��i�m�E:o�<T-�(-OarާJZ#>_P�G�+��s��/��D�;x�����}w�Ӄ� I��Hǌr����Q�1�/���09����vj��)0{�?��)R}CB�����;7v�G��}ۜO%��^���ʑ�8|��mcRȖ"�yɖ"h+ٖ�z]*�����y��q��JG���3Z���B�
40M�saMje�:�V'D�U�ٌ�����C)R�R6��a;�ކ?/�.�	�B����\:�#�����5[�{Ǭ�G��� �h��̿IdvR��t��p����B�Q�m�1e�3��2	3�|C"�g���1̩���%�c�O&'0? a��a~;��A�\��p"�5�Gc��̣$��b������2;b��%2�H�%�s7��s?�)Jh�\=�Y��Ƥ���}L��d����yjg�X��!���|!p-2� �,�|��0H��X���1J!0=�i`<���|!�)��{B�R��a`������c�a!P��_(ŀ�4�0�,r1`9MG��s�����6�a|�Mw�-���bbطų�v|$�Mi�s�0}ˡ@�0%k�te}�вs��;�n�8��k�n�zP��픤�[NI��)I��zJ�7����攤��b��9
e'q���~7�B�� ����qb��z��A��}�/{"��I\Oh���E	obO��go����\5�'b_�փ�8Wv�Ea|�a�2"�|,�Et��eG�N:Vr{�/Z��Y�z"2هƐ�:�����=�]w��Au��'�2�����t��A%��#i��r�p�Zlhl_��[�9�Ӊ��wB��l��~X��4�{����D�#(���h�xS��ń�o����9��G{]�`{~���}�D	��x��?,q'�ǒ����^�&X��?as$cm�3�(2���ˣ>���g w���A�{����vTL����S~��C��� �Š���߇o���U��A��>��\�+�W[7i���xl�>�,:���u�M��Y�-R��h`�q��`(���ш"IDa�)��dJ�-�'!dMb����UM�+{�CTB�#���8���+q�f�_�[\[�F����1������I�J�P!�Z���7�Tdv�I8TL�����ch��y8O�����V!u��ԓ�y��	�ǎbNO\Cf�dB��h\�irMjvl●�"5���t~&���	2C�#�}� ��C0
2i/�tB���� ��g2�_!�L>V��bH%�2t�[R��%e��[R��%�;�%�yU*�Y��G�~-M��[R�Uݒ*X���vK�P�-���[R�<!0Ӻ%��$!0��BE��lH�-�N�����x��\�Iph��jq�����!�ǉ��� 9��`�~!0w�8z�#G����[*&c���d%���L�H�@���&�.="YE�i��;"�!�� ���A�������!�A�1 �s0:@
�=�O`��$0y~�i�xn��q$�djg��x_�d��#Y�}�����p8�M�y����~8�`饉�_�KW|��I�xIe|���%��	�RK��%0$�gu�.!�/%du(1�W�IjT&H�M��"e�$�!2w��q�4�P��-��'vnj<�%�<L|��D�Ϻ�xF$���M�y �')��AxZ��G�y6f�yB��\L�92���D�K�X��'2=W���<�$��f{�:E"����(D>��m{� �5�8A���k���7�߁7y_O·F(DDŶ� ��(XM�k����a�Ǝ�/|FC��MՓ����ǟ��+�<4C����:�8������x~�R���e<�>�J�0L�%v�3����u���_+P3��#����T��{:�Œ~:D550��:�ࢻމ��y��O(]t��^�1 ���i���m��_7%p͍��K�E{�d	5	v���阧��:Ꝝ
b��u�ar,9?�����A��D��� �:#|m�1|K��<�Ѣ?�X��Ai{NOdXJJ��Cg�2^&i���ҜƤN�����뛧HK7�[���Ɑ��ugT���e��{�{޲�~g�:��N�\�ed�����qTL�c�ȶ},4<��P�wP�����Q�@t�A)ɀ�G����H��kq�y;QG�~O��AV��<�M_��_ߑQ|r,����K�)fO�!ӵ�M��][��x������D?0���Al��S�P��Tv�XOn��'(��r}f]GC�1$�CC��+ih5�%�Ԑ����C�� �����3	o��#�#�����g�+��J������G���GTڜڜ�P�ڻT/0�@��]�����*�Qq��� ^�o�����oO��������l띌��0v�]#���'�e_v��񾯀_��W]O��s�p�&�⑚�o���nh��_��_�ͮ7b��SwxO��u�����i���{�{��(�*F�%9��r�p�7��=�#!Q(SxO��td�΢���[F���]����G��L�Gެ�����G���{��KR�Zd�{�]���h;��nE~ߞ��1��վ�ׅs-�.w� ���l�v
֛ܛ��_I�wo��|�:����W��z�v�F�_�n!Z&-O�;l��(^��$m����񧶒{��D<�{��^i������%N��P�4�o�����ПI�v*)��ⓑ�i�����H�b�����Ðh��}d��N�$�B��I�
2aö�ƣ�lD۞����}=t�
�.:'>������ -wD��s� ���������B���<�M�kݵ(�s�>�s��]�=A$�s/�̤f�}�OPM��F�X:R��3���$��Ϝ�����y��0���_-�kh���gc�CK�º%���=�����x����/�qif	�/�'�:SK����H1?i���L���oŰ��0y��w�o��`ҏ��P��%��%�f�(C�ȏ��d��rd�->�
pF�_�g��.�}�� �t�˙2FMN�٭7��}�����YZ��z���}�n���tg���e2�sn�]''���f�p<y�VyF�e�L����*u~�:P(c����;��`ވ��1{Os��s:���گ��+q��6c^{z��?�2�7����o��؛�6?���cq }�� �3�/��:򻝁����-XÀ�D��6B/ܘe<����1S>J�nQ�	�w9�i��<|%ޢ��C,(�V��j'f��{{@ ޙ1�h{yۊ�
0ۆ��R�>?�	v��d���9� >�.y����{h0�B���6Ӈ�������O���Ϝ��4H³y��:&�o��i7ΰ��3�M����8M�f���t��b�uť�5����8	6�V�����Q�rܮ(���D�.Ŕӯ���U�F����l�b�-_�j�q�1}0�HsͰ�-�zSKL:i$Y/.��h9��b5�r�@�*W�i��a��i��\�
���M��J�r�v��PV���li0�]v�
��V�c[a���q�ý�a����[����fN�f\&A����8�kQY�[D{�n����Z��ܵ����X�d�v��DC&C�IJ`�fH�nSɴ]����jhpEr�tW](II��B���m�u#c��]&Z��֨�T/���.�Eg1����B_[ZS],,�J�1��$qU�	��5D;�o$�oj288g��h�W�V/*ZXBBV;c��ƅ1�i.��g5ᛂ9}��H�����4�&L�7�1Ҍ(��er6���r�N���6�sf�����09m&+��d0r��PN7�:���Z!	�c�-V��yWn�(ʹ&#�'S=�,68m�YJh��n��&������K��j���06lX"1�����:�+H�����ӡzp@F*ҍ�t>�D�&;��Вn��`��i��Gh��N��I�<����Y��;��ВfH�D����+�&����{\���l���ysW�hqq4�F���J|ի�b�p�p3���.s����Y��R��o�(�D~1��`����$~��	��	� %�1S	���f&2G�f��]V�
,PR�����aw⨇�ͷtz�-Y�vA�nS��a5L����һ��T:�}`�L���6��؍n���2L��Du���nrڳ�5@��c6�P���c��|J�z�Q
��y�I+Z���Z�[�,i�b�eq��&�V�ȑNe���jB>�o0���ʴ�����#�G�y�n3�!��!����2��l�1�$�l�z��������[:�A!Wa�p��-'e7s��\R=����ڷT:�v�2������!2�H�+2�cͪku�%Sc\���T�~�=������ߺ��p`Zo8`:�wd�_�U�ș$�!ֿ��P�l�	j��,��	�W��b��+]&O�=K��F���9�#�:$:\���"Pg�4���y]7t�M�����4��lr� [=.)�X4ja�V�yfx\u��H�wI3!�$+��9�v0h�f@�0匴�Y���i� _7�ւ9����()�\i6�N��G��BY'X���shq��\�4;�D��c����.��Mb�3�����K�/4�5P	&�v�}L�9������U��AA1��6������`"-�I<?�i%��0��/0�����2�k ˕V?5���m��nC��b�,Z7i�~V���v�0�D{8Z0����t�F2r7F��h"+���ƙ5�H%qd%u�(��v`��� �A>��n"5�$�H,�\0�aLG�v����M"�1��{^���N:1�7�0;�?`����J�	�(�y��_���\D)�l����r�Y/d��X��	�ްJP���8&*����f�˘����G�Ҹ���o?�lf���o�<&��d��\_[\RZ[\���,�]X^�+����	Q�7���] �0���vC��e�K����5���KD��i�8\S8�i�屑Њ6�D鲱�̞=k6�AF��j����f�㘨����.�i.�[�e��p;=6�4_��5h�����P6��~V��&�ci�k���s(08�+b��.g�u�^�2�K��S�ڂ�q|D��څZ)/���l���*����|�^OmyNvY�h�a�_�V�J�6�#����L��frZ��J�V�����2��1FF�����Ԡ�Yk_�� �ަ�|��)A��DO�VR[���[,n��J��j�-�e%�%���&��7Z"E��-���1j�W�zl�U6#䀭��j�y�3���kJ���rmST����z]%A*+�o�F���5e�U%�9�y�������,h��屢:q�E��ԋ�*0�4[YUTc�3*�9iF�1bΘa1rQ�(����>��2��lrf�y��jm�N�g �0���`�D�����%��L]^�-�-�Ui�Ac�W�z�m2r%`�W�&|ŵ�F_�[\F;GPI[���0�3~HUi��	����d*``�Z�v���,�D�4��z]��%�Pz��t�D�j������`��*q�D:�nWE������V\ܮr��F�U ���e��V��ơ����r���)�[h�+k+i�jKh3T/,�Ư��iM�h�@�kt12�����a�(K�V]��D�_X���L����{lT��cu[��hbDM�2�T���1�����p���X	 @d(�*��3�+!k�*�հ*�*=3�a���t�P�W}��%Wmr�9!	�ɑ
͉p�++��H?`K����e�̻�@2G蘤��rf�b]_[�k�����覂�r�t�E�D�,�2�v|qq%�)�Q��h��J��R��/ŨU/�홲�r]ME��+q��RF��#�P�&
SV][S�@ f
��zFMԔ hbD�B\Yi�&�c������������<�ZR[����H���Kb��k+�ZI�t�\�IhrmU	��^Y!mI��B[�YW�)�!F��YEkݍ��q�WOZ��8�nE�M/&�O�*ΊXò��(��";N��͝�Ϩa�1r�ҜٳjuŴ�aIC�W�P[SQ��j��X�S[�.�-����D�MS�J��gf�J�]�+��*�c*a��RgCw�@�fa�y�MZm0�	Y0d(�7{z.-^I1-y��F���H����V��3�ҺT�u%9�1.+�545�v�6�o��xl�ԥ�d�����jF�d��ٴ(�����)�(WW/ �A���J�T+��4�E�Z����o����ڲ2�XZM�sଁ�K�#���!5(�=�^��*b�N��n���,���f���IBd.��ɔX��ō�=�w��H5�%U�2-d�וUm��M��j�)��8���S[]��>`�\��i�)sDʜ��;<Q����)ZHV��;��s�"�������"�^�13j� �a8f�늪�ż��\��ti3�r,*�-?oQQV1u��.�97;'�jl��\]Z;;{ΜZXi2��!�#W�<V[�-�K'3�R��N���V�:C�赘��ƛ�M���R�WW����5BoT芈g�;+?':%�����`��Y[
�PS� �5VB�7��?�nͧ47��5�fG����8Q穛��8�J��@m���DW�+R�k�e��eu�0=�P�,VWF���QU������0��hc�͇�xn:�i5�9@��j\�MUmQQ_K��9V�f-��Հ�-�t���`�U	�M��5mmeE99��O��c�fr��أ7�I�]Pn\pZ�n#'�ِ�%���b�{�v���U�	V��%����<~Pg��fđ#+o������D���a���L�:���%|.�ۍ�	�̠�DfA��L�����6q*�pm!R�?,����9������h��|z���G�.\��c �#OӢm{����
J����T~P��>�/�@�>I��e7#.�3����6��x�$���9�9f]�Ś޾5R/,��ٌ�U��Ŭ�,��"��@
^�h[��X㖢��Ϥ%�n\�I�x+���%�!���Ru�������#'u��M���MMPG#u�$�
@n!L�M�
=�̪s8p̈�V	r�jO]���ns;�V+N@0�r�{�ݹ�ˀY}*�<O��b�E�5j)�k��23�|�^��bb+48���lr��j��=9�b�]q>#��	γ�d�]i����.6�-�C�Cb��>(��4�j��lNYTt���MEJ�MVK�ō�a�~��<�:S5�Q�x��N���26�)��-�	}�ׅ��`2�Xtp�)�%*\\Vr�		�}�[ml\i��o'C��b�� �8����`wZ`\� ^,�I&p�JHjr6��g��i_��e1rU�b3��F��@|j$qu�	}�ϧ��Ŷ'*�,ܰ�L0�9��#{���s � � � �  k 6<
�<@�>����p7 �x� ���9��Nϕf �')�C���1r�h6���/3v���	�^6��I��)W\��vUz�ԫ�efM���3sV��9s��7����
u�z���Ѳ|���fw��t�=�+[Vݾ��[n�]��/V�q�]k���mm[�~����������_������w���z���<��??��O�e�S���3�����_�ۋ/��ek�+����on����o|�������C�8�}���:q����O?���/����ްw�-nzLE�9��c�[���Sa-��.:��pϥ�f�\��mJ�j��/��![���U2�d�����/�/��V]��iqP���7�T*�4���mH�2Zm���e�+y��/�,��臺
����g �(��Mg�=�B����7��,�m��2���Z�M}Q��:��:,M��fg_�F���"�I$��C�Up�$���LKb�:�ɤO\��M\^*�5'���Ɂ��B�I/K�yV��$m���^�tJ�(Mh��c�����V �a�X� ��a�Gb��������8��1P��5@m��7@��M�
�R�����Y3�2�O�m�7bm�?�C�����`�JV��U�D��1Xi�`S�Qu`�6�d�Ұ*�s�n�X�֏���+��_n��vC���r�@���} ���(,���D���I�;`ښ!GPOI��쿊i��+r)8��lh�X��O�x_���b�x���9��#RX$F@�\�'.!�`8�aL�p�R`�Ez�DD.cp���,6�<�S)&˄�h�	QX�HN�������'��9�w�[]�6	�G_���s�t���o\� q.���8���}���;Mx��t�^���84�eG��L-�@�d��/� $��v��[c� 9,���E��E��tT���h17f�������N�����f��t�?#��p��_��g�;{2����5H��A�=D�:_�E>��^���Շ��L3�
ΈڼT��q`ε3�6U����J�����+5�1:/�#V���۠N���X���Ѝ�GI��+�z\�&F?��JǶ��.���q��h�P?����������eo����f���F0N�y �%n_dk�\�hrX��t���n�����y>g�d�E�M<y��T����!���
w�.$z���˅'��
�$.$��>��7o.$E����SJ��.$?r*{	ȡ셔�����>9W� �4ׅu 9�\�>�"��I���g Bd叇�����^��O8� ���!7���z���y]F��׊���dw�|
௷^ �t%,����t���=����z]��]�DO=��G����$�L�v�g.�[�<�Kor
j��׉�\�rk�:ܞ�3(A�x!_���(yLQ|X�eh6�82�+���<��ƛu��T��*#��X=�|��A�UTj�����A��b��Ż�A��� �@�w���dP��������a\踈�:�F\�9w0a�~��oFZ�L�A��b�l���F�ņ���t��\�'1�F��|%�7�J��6*�Է�e2>uL.�3lz��n��nPWR},"Y�fr.;����+?MG|��������>�n�0�߄.Z�|�������;��N�x�]���K���������S��Pe��K�#���n]D]W��I��yYA���ڭ�4��^��l�	{UQ}14��A'K,�E��b��C�޺K�ѣ05��Ɇӿ��G�>��;�,6z��.���#l��m0�o�|u���톦\��>� ��#+�bm���V��t~6�\?ۦ8V$�)��8�.Y-_��kh�L��46���Gtɣlu��y`�[j7s�l�[�y�r��ʛ����eu��o�����s� ��k�&W���A���ĸ��n��J�σ��n���V����7\}g,��S W�	<�-���{���'ВVE�/��
��٫������[V�]���m���5��߫b�E��������p�ʾ�W@�&�8&�����x��������:�x3��=P��SȻIR�� G1������9J{_RGQ�����}���hK��%��_?�z{�<'�k��7�<��k����	@@
З�a��p�}���5 � 6�t ���������~�[��!�g ^x�C�H���7R|��  � ������_�L�տ�� � >8 �#�Y��y��; 6���>� �~��o�;@� j�x�o ��A� �G��M �A�~�� ~�n��=���7���P|�zÙ 5 c�u �H���`��硞��_��Wc�ǿA���F�H�y?�56M���+�2"�����ξ,�q�/)�g@����b:�o4/������� ��21�D�3_��Օ����З����_N,��帴���(��3/�<_x1��g �0NhL��g��3}�M?��ًB��풴���D�n_�W���7�e � � � @2 ��:��}  �<
�`�^�6t�	� �7[�� �!|>��y����m�_�% � *�}`�Z � �d � � z����`�f @@��G`	��H��	4�O � �!���Aˁ�8�	�a���TVe'�}7���($��@�.*A���X���*|�7ܵ깗� 4����ޡ�Y�u����L�G����P��$0 �}��<�� � 8 �Tdp � @7�`@��'��wi��5�� Xr�!D� ��`��� ���p� ���C � n�z������1 g����� x `5@=� `"�����CP��?	�z O�{v�8p�B.@+��酼 >P��~��e��!�	�� ���~p` ���{9�݉כ�z�ˍO�����N'�79�Ld��\y2��zK3y����bL^;��"aF�o�����,|)��s����-���\�fs�4�� xH ?.�j��FP��!�gx�,�.���p�Y�����B\��}Ф�{����U�N��ϗ���2���|��>)vN����������pI8t������'�OH�ς�V?��"�MNśd���3.���8ZငqxL��4�?��2.���6��?zd(`�y#�Q¯��i�o01ͦ��p���a(�F)����"?6q�Y(��F�����h�ԛ�3�}:��FM�O���U�{c��"�RB�<�)lt��z�Y=�][���G�tǋ��Øb^E�����B�5��[���Ҭ�F�I»��z�
�q;<nf%�&܇�Pr���IC|S����j��0��%d�����x�C���E.�F[#�2MD^(V7k�ɝydP|��ap�hƄ�%��W������	����~�>[{�i1�h�D�&�D��[�\x���z������Z�΍�C4=6+gw��}}��CM0ne���ȭ4a*!IT��l��0=�3P�b�#����"��e#�/ �A�k������7|�c@/��c�&�=X���x| SHɎ<�j�Mq@y���h:|F�h��ox7�n�\���:&�Q���ə%}Y��B+�rj����Scr���e)��p�BS�̀` c��n� rJ�}^9s��EFd�Rr�S�D�!>��,�m |[s��(/'�O�����f�~+��0���2�b�G՚��<,>�݈W��.w��o}��AA^���EGn��(Z(P��l����G�=�o�38��f:1Jޫ��΃OCi�]䁬՚<�-Z�p/��L��v��'@.@� 
�`� *�	0\ � �� �T�QÆ�?�h���6
��q9�Lf	�yl�&���J������ұ��f��p�`����Q�(uL��K�|Uv�y*S�(�U-�r���`b��nc��3��1.O��p�+'���d��F�	`350nC�n10��֩\ZV���9.n9�
o�r3���Ē	�}I8�(� ��p8��/�S ���7�KiR��� ��÷�Iܒ8�BgHh�q�=7���o�����<�7����@\�$�2�7�����6���h������7�>��[ �LB�ϓ>�<�)�w,�/�J�KΓW�|�4=�����=}��[�k��X��p���L�z
��k���ΐ�cW�j�����`�B�5R������VV6��Ƀ-��\�E���O�_+�Q��Y[K�qZK���1�|�&��q��t�qE�Tf�`�$���2A>�c^�?�R���ưļ*=+KX���5�T4]neI�b�
�xk�l�����V�6�ܵ6S�[Z�A�&C�Q���翷���� ^ �� ���n� @=�M � % �fd L0�8a�|�	��v�
�<�� 9�p:�� � k��Y����� ��x�9�' � �K�� w � , �  ��d\	0�P�1��G��� �R� J
 � � � �p)�% #� ����I�n��!�4�� ~ ������v��,�� 6 �	�0	`�p �D#�#�� � �`�� �<	����K ��X����s ނ6~`��r��x�1�{< ��dL �t��� x`ˊp�� ��P�	0`*��
��� ^��s*��3���(�;Z�C�{9�P�.��0��a@�>)@�>��4Á>�� �!n"��`.e>QL�ХL@~+Я`n%x-|�Bxt3S�|��xS�'���dH5�?W$|-s9�b�.g���
f�'��Z�q�^�1q�q�:f<�����~�8��_~���9�$H5	~��I@G�R����{3����Rnc(l̆������w2��_�)L*|�~9�R�4���"(S�ǘ����4&p�4S!�Us|F�FȦB܋���1�˄��L�̵1��eղ�ZY&s��u��e]��!��9����7�l�a����i��91��˲��e9�D�����ό��L3�y]�C��l��B����9@�es�r�9 ���1F�YE����F��r��-C\�Q�3�
��8��Hcd��=�H?���0̓��ț(����>�s��U~/|~������I?cc>o�0�Cq�������ߒ=��!�G�#�8�Y�ifޒ�Tb�d�4��q�G�>o�/V�C�(�|����/�oȥ�N� O����?��4�e�����2K�g��|7��+���W!�~v�~q��
�lٗ�+�_�S���!1���/�_��!2����B����q�a1�=$M�r�L�����|��{�4~d�yb��eIS�YJi���E	���%�+�ɲ�ɖ�r�9I�X�[�C��)�sX�*�ҍK��Q^	q� �ay��ky�\;>�.�8�S��)S�Ay��K.��E�!�E&�A^p�"�gȏʏ�Gk܇W"��2=@�2C^����-�����U�G���eq�?�M��IV�2٥I�'�%i�������O�|*ᩗa��$L#�7�}I�I��$�[�dH�S)�7�}c>|�ҬU6��U^�4/� ��xk�G��m��K���>-I(�K���M*L*�$i�=�<�%�eE��)�ޤ_'Ic=	�MI���N������{�IQtߧB�����2� A@��E2�� Q	�$gXX�$'� ���%ɂD%	��(�` �
�w��w�zy|��������TU�9U]]�{�T�f3���������#�~d[�V0U{�F"UY��2�(�R�Hֲ9l"����D��`��4:���s�
��-`w�Z6���U6fRa�FWa}���l;�U����q��2���=;���xS���G�3{Ȏ��|=9��c��ٗ\��J.�h��l�����[xu������F~�Ρ�>����D��tr�U�kx�
W�#�E��2��j���r�v fc���h�Y�2���,By����RU;���K7ظ��{�X�����2�w�]�ez���}Q\���}������}&ʨ��Te�����;�tޝ��HO>���+�cT��q�D���q"�<`=yA��)=I�X�d�&��to�_㪞E0���6�
i�O�\���S�
cT�`<����S���?�#xV������t>�b��=\�I�����%���C���Z��v��>6��Ly�C�i��F�1��U}�(�,��ք�21L��ۈaM������vޗ��\�'D��7�1,���=��o�Um�(��+��w��=W���I/m��N�������Q�(mr�D�!ϡ��~�6O��M:A{����m�jG�'�O�
ө�m�6F����"QP�y����"��T�~�m�c.V��bc��W{_[��B]�%�P+��j����r�m�6GkHE��܅Ӫ�QMl�Ъ�J�4oB��.^��ЊrU�4�]�/ğ�Mi����K��f4�����x��7��<���[Lշ��U�Ӭ,kEA��.�D�j��"��~˾agQw��`��Qv�b7�l+�6
Q�:��Pn�Dv������n�.���'�T�����V��~���Tm.���5Ѧ�=f}�h�#�&�.�����6�Y�T11, T12, T13,
    T14, T15, T16, T17> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7,
    T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15,
    T16 v16, T17 v17) {
  return internal::ValueArray17<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10,
      v11, v12, v13, v14, v15, v16, v17);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18>
internal::ValueArray18<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6,
    T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15,
    T16 v16, T17 v17, T18 v18) {
  return internal::ValueArray18<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18>(v1, v2, v3, v4, v5, v6, v7, v8, v9,
      v10, v11, v12, v13, v14, v15, v16, v17, v18);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19>
internal::ValueArray19<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5,
    T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14,
    T15 v15, T16 v16, T17 v17, T18 v18, T19 v19) {
  return internal::ValueArray19<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19>(v1, v2, v3, v4, v5, v6, v7, v8,
      v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20>
internal::ValueArray20<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20> Values(T1 v1, T2 v2, T3 v3, T4 v4,
    T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13,
    T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20) {
  return internal::ValueArray20<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20>(v1, v2, v3, v4, v5, v6, v7,
      v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21>
internal::ValueArray21<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21> Values(T1 v1, T2 v2, T3 v3, T4 v4,
    T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13,
    T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20, T21 v21) {
  return internal::ValueArray21<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21>(v1, v2, v3, v4, v5, v6,
      v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22>
internal::ValueArray22<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22> Values(T1 v1, T2 v2, T3 v3,
    T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12,
    T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20,
    T21 v21, T22 v22) {
  return internal::ValueArray22<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22>(v1, v2, v3, v4,
      v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19,
      v20, v21, v22);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23>
internal::ValueArray23<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23> Values(T1 v1, T2 v2,
    T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12,
    T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20,
    T21 v21, T22 v22, T23 v23) {
  return internal::ValueArray23<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23>(v1, v2, v3,
      v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19,
      v20, v21, v22, v23);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24>
internal::ValueArray24<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24> Values(T1 v1, T2 v2,
    T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12,
    T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20,
    T21 v21, T22 v22, T23 v23, T24 v24) {
  return internal::ValueArray24<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24>(v1, v2,
      v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18,
      v19, v20, v21, v22, v23, v24);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25>
internal::ValueArray25<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25> Values(T1 v1,
    T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11,
    T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19,
    T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25) {
  return internal::ValueArray25<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25>(v1,
      v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17,
      v18, v19, v20, v21, v22, v23, v24, v25);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26>
internal::ValueArray26<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
    T26> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
    T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
    T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
    T26 v26) {
  return internal::ValueArray26<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15,
      v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27>
internal::ValueArray27<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
    T27> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
    T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
    T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
    T26 v26, T27 v27) {
  return internal::ValueArray27<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14,
      v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28>
internal::ValueArray28<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
    T28> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
    T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
    T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
    T26 v26, T27 v27, T28 v28) {
  return internal::ValueArray28<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13,
      v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27,
      v28);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29>
internal::ValueArray29<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    T29> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
    T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
    T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
    T26 v26, T27 v27, T28 v28, T29 v29) {
  return internal::ValueArray29<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28, T29>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12,
      v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26,
      v27, v28, v29);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30>
internal::ValueArray30<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    T29, T30> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8,
    T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16,
    T17 v17, T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24,
    T25 v25, T26 v26, T27 v27, T28 v28, T29 v29, T30 v30) {
  return internal::ValueArray30<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28, T29, T30>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11,
      v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25,
      v26, v27, v28, v29, v30);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31>
internal::ValueArray31<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    T29, T30, T31> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7,
    T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15,
    T16 v16, T17 v17, T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23,
    T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31) {
  return internal::ValueArray31<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28, T29, T30, T31>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10,
      v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24,
      v25, v26, v27, v28, v29, v30, v31);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32>
internal::ValueArray32<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    T29, T30, T31, T32> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7,
    T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15,
    T16 v16, T17 v17, T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23,
    T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31,
    T32 v32) {
  return internal::ValueArray32<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28, T29, T30, T31, T32>(v1, v2, v3, v4, v5, v6, v7, v8, v9,
      v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23,
      v24, v25, v26, v27, v28, v29, v30, v31, v32);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33>
internal::ValueArray33<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T1�e˖-_���[)~�V}l�V�o͚��[�~�'�����o�M���Z��O��yQ(f��� ��{�+���� ���P��O���>����p3.�q������02��˂���x�Q D^K�n�W�Cd}M������Ar^�2���٣q�Q4QZ�/8
�X��ŨW�*r��Xc���Bd.C7,�C�#��g��4�sS�Q�)��6�e��"j) �e, �`=| 6�QI��m�v�g��z��������2�'YIY���
P���Jx-z�bO/��c����\�s��?���DOg���A�^,��}����ؿ���_�4��)ʨ_�,"����/NF1�ǘ�1?�Ȫ�"T��P^���Qm�u�ԇ�k��4�&�n5��w#[���o>�e��O��W"�@W\��q��@O�T�7�A�F?��r��#�?���_��g�o1���r��s�i�F�å4�?QB��~�K~����V��ҰP�+�ɶ?�S����e~�6�G�߷�ß��mtnq<:_�-��d�k	����l�T���k�-��x����x<��bJ-�߀Nn�#����p�MR��A��,� 9	_�/x�	�a5�������9�yỌ̏�(؍[�~8_����hY_*��p��ylE����e.�y�.��D&�Qݨ�,�i���-q�#�p�ʏ��>�p ��5<|�a�N�O��D�Ͱ����>�y��H<n��E��~�c�)Y�t,�~N4���p����܇�$�!�x��"��/�zH���7�NHN��L���L��A|T����9�{�+�غ�9���@��蟌�kQ�f����A/���_]��ؿ�l|w�Q�&��KG��Ie~�����1~���C��*zN���K�1Y���ޱ�����\N�~��/���ό���O/���?��Ư�?\J�?d	���_�G�XKi����?X���������ȥ6��Ɨ�A�o>,��{>"W|z1| �G��²�)��� ��/�;x�=.��p�u�rX+�Z\������W����@y�-��e^!|{��C\'|	���PX�|.�0< 쀇2gu��I mb�P8�a��c��̼���(b�(!��^�F��j�z�v����7x�Ն��4^�+�X�W�ִY��jѲ��Z�iۮC�N�����ɆM��oܼe��;��ݷ���}u���c�O��EK��p�y�����b�q��o>�i#����}����2��D�<h�%1[B��� qI%+U��B���u�Ue˕�P1o�'����s3���s���gg�;;'W�\��c�vP���g����a=�K�"�'��4��㞀%K?�ཅ�/Z��SE������S�{������|�Ҹ�Ɠu0���Ѱ��c6�Ba��DO�������w�������xu����d���j����P�b��������2��-�������~���fx�L�oL
��	SY�^�6��}���p�#��pm�ÖS���{n�p���6r{�5�Ј���}�"�h�K���נ"�4\�V��k��x�9o�jyv�w���FtVx.�pEjP(<ߴ9b�_e�2�� �2DkE+��˚�Gn`�_���DG*>����GG����c��	��z ���ʸ�;�1.wl�'K|�l�sx}�@0�3W�<O�͗���~�H�bş~���J�L*�\�y�Q	"U_�V����ָ�8��hi��w�G��ݺ�H��+�wZ����7��O<��#Q��@Y-��0���]V?"O��P���G��b>_͜>n���J^�}%�.��ݍh��i�(�z��p:��w!b9N�te�7#�_8���9���u=��W�_���#�����[E�ų�%괒w��u=r��B_�_�+��3�ȋ�r̐��t:fl�B��l���f}q?\��/�g5�{�~���>t?�c�S0n��^��`|S��rx�^r��?u?|�g�+š��Ǹ�K0^����U��~X��<�<��t?\�Wp�;����?��Ȃ��|����Oc|�<�X�,'�_q:+.�o��M0��;��w�����~ؗ��ևq�����4��t�A�Uv,��8�7b�7׃�M���y��ă��;�{n������-� ��y�A�Ɲ0n��^��?M�"X��b�>/��i��W1^��簼�S�1W�1���{U�5�[�c<�⃰/�;Uz��q�[a|������0��"�b����0.T�A�=�����b���8>�ˋq!�����xc��%������5�qU��3g�v�)�(?�Pd(��@�Q2�$3I&ɴM�iڔ������i�4��%-�[�Q�da��� E#V���\,ܨU�k��-�x{�jŜ��y�yϙs��$�.׷�o��Z�s�g�����?����� ��y(��V`/�����х�6�z? �F�p�I����J�s	�݁|��T�!`	p�x ]�N�`10p�L��`;�4���ߍ�!I�{)�F���H����#���@�����&�i`7�{�����X
�����R� 0,Y�z'w`?���i��4�.�{ע<��8L�� �Ez�p8,��ӊr ;�M�^`
8�� {���P.` ��p�����
�`�� ����z�'���>0��������'���nB�Hz��N������~� p8LlA?&��W�^�Q�i`0� ���;p�܁�@o�K�����P_�n`7p�L��I���LmG{ KE��Q��$0��z�	�,����L ��!<������$�D��Ey�A�w�%|�&�}���"^`���:����s��n`�l���ϣ<��/!\1ڡ���`ɗ�߀)`������_E��n�0�5������L<�|���?`�y��~��A�|�K��psQN`)������O��z�� �L�8���\����L��r܈����A���v�;��zKP�WQ^`���ρ	`/0 v��~�I`�	���#��������,���͈g�-��h�[�ϷP�A���9	���G�{�9�x���.E���� ���wP^`��(o��#��	�a>/C>΂L�۩���9�7��B�M��4���<F��Xrl� ܁���� ^{�;v0p���Dx`	��z�@:�p�.�{x5x`�5H�vLÂ�� �!�Q���4���b�LO�sa�TA&���#_���O<�XT���6l5���R@��G2�[��,E��i`�X�`70وt����_�6��L��i�0��E�&�[-�O�'p�,Y��F�'��ߌ��K�i`��N�G�S�7�K"�zȫa����`O=��/N���I#<�8��=�7 _�d
� ����(70�� ��q`�J�f���ă��^�E�D;��r�}��:�/���؉��B}�ψv��n�������@�"��S�0
��$0	l��i� ��_�^��n�c1�}� v��A���a`�H' �����=hg�?�t����Q�G���	�w��Ɓ%���@/��40@620�u����3���2��N�/�>�����/���߂�L[̢�R���o�n���̚i���tu}oT�jY�߈����9�˄����iH�PB"��S)��> �2�x�=Y�k�WgW-�[M����tBkh�L�R�D`��B;B�hǔ�(�65"
�'�A�D^�Lx�dv��n���ZG�x�OL�*_Ɏ&�O�h��/�JQZ����Ǩ�����vx����.O��,(E���SC�d۴jѧx.t�DIH�PfI!��:>���^��zl�U�/"�ݞK������D��Jt�W ɫ�E����\=X+�1q~â�3��Ϯ���G�i�~�i��	���N�',�;���M��&����=Z�
��Qͺ�M}�8���Q��7۔{�W��H�ޚ����_� �]�aٳBz:Կ�;��?�c�e�~F�)fw�J�[��b-��;O��-��}�r$O�*�Eڠk��J�t��v�{�5�2a�E��K=���g2���̅X��<��Z�.�;>Y���m�o�ب����C���w�wE� |�/G�����*�tVp%,���u�H�D���������!�򰩑�P���W����k�?)_���Rj	k�MQ�R�ݢCA�A�?�{�		�T��с��POPeHmy}��X0�[��������3���뱓ʿ��q[����'+0do�֩��ƫy�m��e�m@�!�;j�pU�����C���QmV���E��Wi/=��q��(�K��j/�����e����E�m6����O?ՋVe���U�o�2�5"�4�m@<��0��bQ�,�Y��^:����[��COB�w)��
r��������[�=�R`�*1��`��J
��x���|n<���H��u�w�������2=9U�nͪ�Ն�������Tm��/&���x��3�d����rOv?�`ֽ��O8�Gnȧj&֫�(PaR��"Ej{>:�9���&J*�h=��Yh��iw����H���
�D�	�	ߑ'�5��=�t����n3��S�Z�g�6)�e�iP�n�5w�h��'"Ƽ��,T�=�qWi�'z���yU~�ע)���џ���?����U�Yv��f7��3v�,<��jg9��[i�|��'=�@_����fT���P�f�<��>؃�~ĳ�=���&Փs�V>)��1���L������|U{R�����G����Wbb@i��u!��Y��Ě�U���'�L=A�/<��S�|U�����=�y"�}��EG(.�BK�0�Bz��B���Z̝'�L�]D����o=W��߮�/j6]�j}9��4�<��%XC,��L���?�����=j��j1��pg�6�n1����r`��͖㈯�U���3���,К3����bpf�¿4����}`&�|f0LL����3��z0+��3�|x����q�Ƹ�Cg&�T�w�|gکz�'g�k�����K]�j?p坿K�'sۛ4�g���{E��/�c��Hg:�Gr�9`��6td�#\�J�W���`�u����\����rij�v�q��w5��|v{f<Պ7���Ա�on!փ�Um���˴Ki��r�ϰ1^�#��k���r�ש���r|x��?���t:S����yn�a�'�_c�l�w�*�=2����s/�1Q���H��!U{V�3����m�a�2[�s�f�Z	�AJ�\�o�{=P��Ry��n�zߗe�f��b<�U��}����_���v̗������y��Y"��,��<3&���獪�VF�������p��[S��[�|������2����[���-��ع�WU�
&�g1�v����t׋!�b`%�6���[�� �	����E�ӗQ,+�\�y���(�'�Tm�>7�_dو[d.�*1WakE�2*w�;�x~�Lb��� ��wJF��"�Zv/��S����~����wG�_�"{����/u��/^q�睯ǿݱ�4� ���My��H�p1�'+��f�M�8�k� ����f�����Gg�p�l���XYk�>�+��o�����FT�iW���ReC��>����aK9Ȟ�?	�J{?�=7����&���uY�����{ߥ����?������;��+�� !�e�Zg��tc��$:�|�����}�Wv>#P����|V�c7�i�S���Ls��o��O��|k�>N���
>	~��og�/��F���}U��U�.k6ˤ��G����~���/p���䏃?��\���a����+X�j-�Ӹ�J�Z����eHV�_r�#\�nt�o����Owg��VK[�XVRܞ���C<�jUk�~g���]�[]y���8{X��e���w!�E�w���f�����/�`Mv�7^���q����;/���8���Kk��� �/p�G9~'��s��/�H����3��P��������]�Q�2\���e8O��D�rys]Z��>�w�T�gY��s�c!u�e���?���^�oF�|��s������ܶ����/�B�"�'����5f׮��,����#\a��պs�1��
�3�����U�Y��ԛ�5CQ���'(�Y�[y�G���z�1c��֋QqU�Ӟ��.sNR��X�k�e{��f��Eq�����#�l���a�]����<���S���X�e���c��n������ĝ����W8׿t'|*����^)��R|��p~�������|S� -+����r�O���������s����~��uq�nhԒp�e�F�x#�_�H>/�"���.A������6��_�(�n�������>�^���ڷ�)s�������&��Z$�%"��`Ȍ}��ӾᾭL�^�2[s.��znF|��T����qW�3��Z|y_�Y����	U��k�|�"�J��}�h],��m��?ݩD���?泏�ݵ\�냚<��S���ÿ�� �����D�n��پ�J�پT��h)�Gτ�c�J+���{��"�nyP����A�L'����8٨j��w�Pf�;z������/�k��To��7 ?1�a5{�z����u�u�<j����>��_�a��!��G������9��_`�����-
�	/�/� �Z�v`��פ�������g6�}���D, ��_į<XLD�~����;�8_y��}v�'˳�zn�t����?�YRr�#kTm�Yoa�=�r��6_�j����;�W��wк��Awv��|e�Os����u����/Z�j¹�\g����Pg��Ә���/���t��^ԧw�➇����)�?K���ߙ����<�%��ތ�a�n��y��Ү����͔w�aN�ڿ�vaԴ��1���s9݅˜�nS���Q?9p�~7yY����f�=C���;��S���WC�;��Aڷ`~�x�J����)N����"q�|Ƥ��9}���Db��G/�n�����md=�������_�v�/t��<��g��Q
w�M��U�y�n&������h��p�nx����p5����iW�w�>ZA+U:[C��O�8|4�T��2��&�5F���KL��*��/�*�~|Xվ����QR#J�EI�(n��Y	�<�18hS��Z�V��*����A�
��ݱ$s��#��n�VIGh�-�9����_�6U�w6��4��Dͳ�F0c,�����j}��(��׏p�k�}��u��5�ٔ������%����ڡA�Ý��o%��ڡ�ڡ�h��|V��Y޿�u5����vv�{�*�"Y�fpKV1��.A<��vx�8�]=d���q��}�5�8��{��1I��[D���l��'tҔ������b}�S��Y�%��V�%S�K̰_Yo<��C��.U����)��sac�^oę������Z_a���C���Um�{B;��pN���W�R~���q�F���#�(���7y�C�[�H����xJ�g��J��2��k��_������Oe��C߃�,��>���$N�A���u^Rf/���{�)���z�x�\e�[�j�f�Ei��tS��Y�e���|R����s�|o~/�����9���r�'�:xj��k1��_����W��0�
zm�5������;֜���a���>�ݱX�[�z�6ý�*ȿ���LA�da���_ܭj����"�s���+�$���"�z�3l?�C�_����g��C�o�t]1�hbG���d��ѱ_��3�R]�Cw�Ɏ���q�rQ�N��>anңZ�WH��������lօW�����F�槄�J����i��z��쫯MR�-�j��V*��
�z��`��)�����ʌVIo���[Sf*�2����X���sL>���w��*#Y.�����(�~W'�?&�����g�8��=�r6X�_��(���u�����<*��EqBf�vYJ����Ԣ��~W�g�\��^U��o�'h�5j쫘�Y����X�`zZ`��|�Ɵ뙎�9@mވ<�?(9���z����G�T�'�I�+J����3z7���ׇ���x�cAc����YiQ�,�*r���ޯ�4&��~�p�Nw�E�/�q� �t��6��sY������(L""��r�T��|S�:
���Y&����ʤ�	����[�$�3f�nm#����/��ߕ	�ۑ��ѝs���N8Ds�Q�u92A;�d�G�C�`�,�N
��ٷK,�-���|۟�_�z�C�([r��r��z����Mxi�Q��5�x����ky����/���݀�.���N_LMS����=��蠪�E�~�+U�n��p�#k��2	��]�n��vv�b[�I;y�(�D��X��On5����y������K���2������=��+����c�=����	{�U�{��:Z퓧~e�%nk���G	�WU��n���ZZE��g��D��|+���pI�8��3�Z�μ�ӆ�߇=�v��T��t�jt�E/����%�}3�_�������O�(���Z�e�z��닆d��w���:{\}X�T��By����yv��N^�x�_�:ڣ�#��Ϩ?�p�����&��[=%�������<�~)���yA�? ���f�ǟ����8:rm0����>>��|���i���N�B�>����bN�U�;�瘿V�ɳA�j�f��r=w ��R��ʵ~]n_����{�:�E>�DQ���[����������_��^+�G����r��iv�w��f�C۔6��&��=ʭ�&��ś�TS#�
�	��|���Fy30X�y��Cv���_���FzJm�k����w��p�����+%#��L��,4��%���������d�s�X�?,�����^�B<}o���K>1��;�\�������ϻ-���-�ߓ��Je��D^0��YA�7U�:�(!�W�����7��8��V����l�O���|���#��VD����_������5�{t��(�xٺq�����R��6߃^�;=�2�4�kH�u��V���������}�1��`�g��ϹE}���uY��'�t����P��8�6��'�~���~7�[�*��)�����\������Q�zG�yV�B���v%|%|%��+r�1�s�΂]��җ�oC��T��@���
��}�����"�_�wL[>u�U��N�s@k؟�(bL��TW�n�fړ^*��ў����O丗Dw���F�q5���1�=}��z�y�������ݛ��K���4ܯ�����B����g����'����~b�~0�Щ�Yku?��)��˱R�#W�k����}8���f9f����3f�;�g����ސ�^�z˂1l��G��.�p�Y��'�?"\����|�}{�C����纯:
�%�Ӧ�w�fv�]�r���I�Y*B������(�y�1^��7���x�2ϩ#��1(��[i���]�h�j��?)��ǲ�{�r���~���_9��c���Aߤ��o�4�_i|�J߮���]����ޫ�0ϣ;_��ƴ�<��)w���G�΁�E�x��A�n�_�X&ҥ��6��(��,�{7բ��Z��ߚu��[%�e���|=���|�|���u�v�]�O�� -ӜG�z
���JxK�d\�.Ɉh���H��1�9��i���z�����wDE��W�+�.�
&�P��g�>�it˼-�?A`�Nğ�tLۖ#󑿦<��B����kט�F�j�e/9�"�h�(^,��|�P4�?Wb=5����Y�4���5�{c�^�!� ���]��zܹ����E�%)R墕�3O�@\��ܔ��S��Q��L^NZ���q~����G>Z�˾�K߈�G\�~�~���|_hF$�?�ӹ��BS/4��i��q�����d�ˡӂZytP�7�q����߾|��9~������{����?Z%�e�~N!��"�3(��=�N�oZ�i��M�k�򽶭�-���.��2yȟ��"TMN���H ���c��)�]�N��g��2���U��?4�-��wn�ݞ�'O��#��]�%�J`H~GG�?���1m�������q��^�|���术��o�]�=��1��)y�c�hz���c�m�������-?e��=�*Y��7Xu}tL�S�u�R��|)�vL�^ۂ\�?�'�����K�v*��j�o��|7�"�,?��6�]���|�|��}���{�o�w�np��ׂ�5�/n˞��?�����ͮ/��j?~i�s�r��P�������x����r�K�`�\Q5C�o�����1��-���ʑ�]�MC�k��q�1�} ��~��w���O�~�O�:�㫐��Y�e~�F�,Ւ������≗���id}Td��|{}P���Oە2_�����v���j�ﾃ{�8�Wn�O�������*�[9���)��Z�w���$���VT���d�a��ǴC��}曖r���0��q��7}�/�z8.
����b��~����{��w�$��a�g�'�����o &��-��`�����:�o���Iܳn��sj�|lG|]ƴW
���0ͯ��e��6�e�v|�K={���]g~g~g~g~g~g~g~g~g~g~g~g~g~�����xr���x��5���)6~&˯2K�_���Jcyڽ:gI簜zHǂw��8�ϴ���^���h�_�ӛ�h��od���x'����5�"��2��/g�Fc��n�71�GO��9����e�y�s�����O����� 7�K!㇍z`�Ct����̇���X^ɘd~�2�f�#�z�a~'�b4����1�e���x�a�#��I�_�~p���?��0����Y�a�d�����r��3������2�-��0�t�˿g|�y��k���f��a�of�d~�̇Yn`4�j�e�����g;�?��?��oYv߯�'�?˳�o�EY�����R�W1�4���w�b��Ǚ�8�݌�7:���k��_`� �C�{�?����E�}<N�9�g��W1~��',�2�2���5��;�Y��h��y�������?Ư�����ߌq�|��>���o�e�O,Oa�i��X���y�?�r��~��|��oa����������0ڑ�}��7��r/���d�F��~��!��-懙?�������t4���E,�u��W0e���a��q��F�[ٿqִ��>�g�s�?�h�{��1��?f<���,�9��������
��|�&��>��E����%���W��r��)�M�w0�s�W3��1�|'�O33�G�2���A�����,�f��SS<�2���>�篍�e>������� �Ǎvg��7���k�1�3�i�s���q�h_��l��w̟��o��r=��{�奌'�_��fƷ��b�i�?0����0�7�?g����'��=�%���Ӷ��{���5,���'����xʨ�;8�?3���'��|�{O3�e�_`��1Y����a�̏0�w���Wd���._�8��m,n��������3o�����f�,�Qa��,wp<������e6�������w.��X'����k��b|Sp5ˆ����{Y��ec�mb٘�X6��՞I��(����8��`�XtNߧ�ݰ�f9��s,�U�\�r�qÞf���o��j�C��{�e�n�<�=,�e�nx�ec;ʲ�'�,��x���r�?��բ�C���Ş^A�==������/k���u��{�\��/m���5��{�U:��{{.qȫZ����~[���!ok���n���{��!z���u�o��G���l�o:�o�I�[x��Dz�ec=����lc}�T�'Ʒ������E�|_h쏰�����4�bNrF��_��4��� �~�_8�>@��������Ӽ!a�9c���p���δ�3�e>ˑޘ��?���F��dy*w쿱��v���?i�!xڥ�ohe ��˟f��/��"�-a(i�נ"C1NgA�lbrI�h��$�+"� ���"� �)
A��(C���0_�y�0�"�M��.���<�1-x�~��~y��\��\���mGO
�h`hc���&�p�����f~��qL��5�c���lc{z��1��1�6ְ�lbw��]�a��c�cm�a���`���г̏a40�	���ul`[��m�bC�̏a40�	��ϋ��ϳ?uA�o����]L}E>�xW������ͳ�o}������ȏ�� w�_�w��m_s��x����ӂ���"�~"r��pS䟼���2ٗ�W���;9@�J��""k�c��g�7�_ �J~�|'��k�wK0�����G~ds��t�}I�j��b&ji;cY�m/d�و��~�42Kk1j��KY=k��W���_��J�R-Wʹ�KUK_)����|!{>�Rά�4=�Q�l�
�e1R�ʕ|�(��3V�
�{ ��
UM���o祾Rr^T���o���TʚUSӭ\�.��V2�-��&�r����K�0��N��`q�j>��s�i�;�+��"��s/�/k�{;����X;W�*�n����O�M�s�ێ���iP��[���G��c����3Ge{��}��n1���[hV����W|�}ƌ�����n�1���ȹ��=�����~���H�{�u��zhؿmL?Ǻ�����d�����(}�ljJ>~F���S˲3�|��{E�-�^������^S���~��������Y6�y^�W��f��[J?�F@�#��[鿹���|��w~n����6���ǫ�C��H?B?r����������V�'蟠����������s]���'_�i�>*+�ԟC����X�g[���A�GM������]�~��?��/�^{�O���Aѿr���/c�����6��+��pӧD��>� Z�E�xڬ�|U�8>I�%��-Z�(hѠTK�H�&t��y�`�B�!i��*�P�8�.�~w�]w���]�+�- jZ-�*EA׊�">���9��$i���������̙;�q��}oֺ<���`�Kn�.������ii�2��X�|^!���¥������[r��C����6�u]���F�x��=����"����|7C1�m�ۢ��`��ۅ��f��_��u�O�#ݿw�o�i�^����4��2ڻ^�R�.ߖ��f��	B�3��7�_9�ޛ転d��!��I��	����Fy�M���Ya�C�7���	���x���r��������Wm����wuҌ\�m�8�v������ �����&�s|܂4���8���v��^���w�����>���'#�N�h����O�i,d�Y��:�p��w�1����T4�6~�G�_���[������6�K�+/�����o�wL�-��3?��꟝��#��w^�vϢO�3hǗϮ�7k��\}�(��{�~kdhɒ/>��}��珗?�ǎ�ڙ>��ߝ�ws�o��+l.L�e)�[�8|P|%t���K�������h��K�g��Ï_�]�%�Y}���_��W/Q�/Q���O/QϱK�_p������������˗���xN�zz	Ţ��0�I
�7�8���oX8|����(�߀�w�;/�__���S|]������O��2���c���v{�/�����2�|~�%Ng��OƸrJx��2��o�|���?�ĿY�W��G�s�^���|�K����{�8/�g�z��X��
���Q~�Q�O��x���(?Ԩg���ߛ�xX��߿k��1���b9t������7Y>@(��ը�Ѡ��'��r����3��[R�6����*r�mZW�}�x�g-q�������3�(�<����qx�9_S8J��L����t�1�M/��%�l9��2� 1ʇ��L���]�?�c�/��\k�_R��C/+Y�[��WR"�,Y��'�x�K(q�(*Y�hŢ���-Z1��`����Xp��E��ş��V,�
,]��N)+��(W�t�ʕ�V
�KW,ʻ�d� ���.Y��J_�����<�Z�J�C���.~�Ļ`�R�,]�p��Т�J�?j�+-2��k��X��z�{��cmf�҇Z�d����G�/*��Ĭ����
%n�y�<�î�}��BE�J���k���%˼��,�AGW,Y��2�C��p/���%���M_��V���E�@�-xh���Q�&�d)L�E�$/Q���A�4�'�©1gp�²%+�o�E�<��-��)xPx�˻�����2|��rQ���/�uA6��xK+]�w���].y`Y�ari��%��~xţ	j|p���8�^�p��DL	��r�*]������������_�hiI7~�>/�\��e�V�\��2a����Z���x_�W�%�.�-��ݿr%_� Z��ޠ:��MB��=����Q7��9~�7&~yӨ�u�ତ���������#~�b��P�
�����\_��p>�����%�{�ES�K�JI���y.�w��a��X>Ui�g-Y�G�0�y})T�_Nϭ��Vv�Q������>߀�t��<�+��i�Gw�|l7��g8\�o6�s����Tt�7��u��6�o����j�_��r7�&��|�o�7��>.���n�|��Pt�zlE�Of7�|��^l�s�.���s��n�i������x�o>���m��9�~�M?2ﳍ�iI���O֐�%���&����~��I��I��$x�d�"	nK�'�{&�'�ӓ��$x�d�*	��l�$�{'�7&��ߔ�*	�b�%�_N�g&��&��&��I�d{�!	���5&�������yI��$x�$x$	�?	~:	> 	ޖ�N���������/�L��I��K�e�[�J}h�u��R#�p�mWW�7v�ۮbC��'�:��޻)6�D���/�m�_q��k�����oi�4Km�fJ3�"�Ϝ��k���n�G� �1�������z�i�p���b�\y��/��$uot���
M����S˷���o%�=��UV�3�m�X��d����G<�ײz*2_�암�1���T�2���v���'͕�I�I%��o�3�z~�t�L�B9$E���Y��C=��
��ͱz�1h�G^%�x=q �˫T�����X��3��<�xO�e����;{�;�Y�3�����mW��h�{�U�o��~���>��(��y�+/���5�=GVE��ѺzY�f�U��{�{ٲ�g���M:p�]�����49e� �� �ܜ��+o�M�CPP�+��쿜ո��>Eղ�����V�-.�G��uT��#䅱;��p;*~��-^(ߔE��]y�|,&?�p�v�������"	���uD�ڄ��[0P��)���W��>e���G����s^��ˮv
¼]H��Q��`�?�޿�2�~'�_ۙ"�����DٲW>��ˆʞ1*������׷n�'PL�_/+ƫ�P�/CMXw��0�����7u+ ,?\؟G�@;�D��K�J�~C�=��u�2�8O�G� M� |�Xe�뮂b�w���w����,�#�*�`/[Y �F-�f�"p����9C�6oma��5����X�

��>u��jkmk��5S�*@k
�����lN�w�S��B1����0���`�W���T�����ْfa�6��5XM��j�ɚX(U6�j��'�WD���o�`SNXd%l6�=Z-��V�y+;��,p������ټJ�����/\^��7��3/��.�& ,[5	>^�>��o�j�L���^�^���U����V�Zlզ��ݡM;	�������<��͟o��&V������ü}�`�m��������k�'ћx/B=c�z��,[�F��zch�_+�Њa�=L�;c�M8n�~��0�������v���u�A��s��v$�؎6��i"�Q��V��{�ɬf���;ޅ����@z;�d���B�HVS'�:��l�ĚYM�A^e\��{V3]f$RɲC�?"��}���O��URv[�mE���X1���M��C�����bYm�� 
(�*c�~�q�mȅR�cSr�b�.䳏�0�zς���쒻��>!'�~�?Zj�6��j1��j.���EşKJ,�Ku9��o�(gA��R��� ���8��>�A*�ÊuZ���z����n�B�a����S�#-p�-`� 0<��H!���h��xBF�%Yv{7]�z�Ӡ�a@��d*��:��m�o�J{/V�1"y�|��/{ �^�
��5��i�X��
D�5<����4h)Mo=Ot��qG<r[|����
ko.��-��4Y}G�/$�o�HU�J�y�6��&����|��@ДH�X�,���F�7Ə���tG�_<��v��? �G� ���q z�H���;�S6��0�Y����t���Ԟ��9����q�y��E�\R����WuR)X��l�kPĩ6���6���d�5-�,&��p!T2[�w�5�m��V۽���9�׏�L�z%Gؗ�6�Jha�'����������yߕԿIVM~	[������F�NzN�6�_���_��O��|��o�TQ�f̜>E��V�x;��ePHi�ί�,?�+�&��������ݧ�f<Qd9 ž0� ���S5QF��u4���`�dV��- ��[%2j��|4��Y��q�(b�Z�}����hY��r��.�y®~�=ѭ-%Eg�/��M��L~n��9	^s���"M�׭�66Arhɰ�Q�&�H���tA'v�n���Q�	�c�S�	E�w}� 'w;v��ԌGm�G��=,�Aw˷�A>���3��p9K�q�t�h��zP}5\V�ãM��QP}�	�P���3�C����������������
���x����Z�,�:��L�XA+���m���=�@t��ݑO���������C��-�*�}�TvT�޶D[��|Ţ��JׯP��X���e���+�/!�z�P,Җ��
[+g���ڗM4݅��.�G��בw�����r�����N��#�VگVu6�������]��m������3�G��e��k����I���V^8�`�b"�d}�?���������
�B��&��c�M�m�n���-t��y��m�o��i�	�#�W�W�^h��0���E�J��G�z�E��z����$%���%����������7*y�=�Z��2�s��!��,��$��`-��kho���Y���T�'�eg�|Z�2�"-k����}����c�9W��U������bU�:QR%��'�](�Yua����3�=�ÌK���K��˝����t��+;bW�kl�ިe\��M!'E�^َ_�N]�.���Y�6���iwX��ݡ��V��R�����m�H���K�/�C+s<�.Y�"�O��}n����W>�U���<ji���Ҽp��P���2�'���VL@�ֆK�w��!U�ǈKO>�EV���>e�[Ј9
n���4Ǒ�m�����:P�q:����T�&�u�@���T���Մ����j;��m�Q{b��<LWZms�V��˔浹���i����<�AY�e��)�&�c
4�]�F���w��h�㝃\��bۥM�8�X+i�o���h�V�m�H����h�z��[�����rT�'�A�Bc���ģ�rz2<��	��H>u ���?�� ?�L�8��}*A-!%�Xq9Z�G:ն�q��q�uj�z��D��E%l9�%*`�mn?���/�J|U؆�&'��&9N�3�*]H���=[?U��zT�C���)�uҜ�`��_8���^8�
+Q`���������T먋l����b?ݡ)6�Q=��Y���:â6@�Ñ��_��0t9*?��P�!�a���q}@�f��|эJt���&�z&�I�={umLVt�\J�`�`�hYW(�`��8-��IM�lY�:��1X[��A�{�&J�]���H�I���:����݅� B8�L�*R��b�iir:�����@п��+�
���/�'i�1���|",+��s\B!2�s��\P<��z��}XsLy`ƪ�+מ�OTh�vp�Oz��Ň&����c�n��m8r�۰�7	�U�I)���H5DHc�՜q�j�AY����������0�����TP�T�r�W��C@x��S����/��T�?q��1��w��M�^������D��/*�g�����G�w��i����QU��} ��;�;{|+%m��Q.��TД�ڗ]�r�G��V�� S�5�(9D;��}#��:C�5��T����E>�@��e�3�����z��4%�C�=���5yG�����!�VMu��g� ӏ���.;�j���f����vu����>.z�)k���KԦ4 ��/�|YM�+;�5u��ذW3e��_��P��%,�+�#��A%�ɠ��Z]a�e�Գ8oR�`H�g�þYؒ+C��y=j=��ZУ$9>&i�:$m� �#�i$<�@h:ձ:q��c5�b�7���{�7�Ѝ4��B�=?vjo��]��6*�)e6h2B�IK�{	H��$���Xi|Y��\�PH/�~W�Ķ�Ub2�Z�B���Q��t��������o �ÕGk��p�ѣ<��q������Lb��|ª
z�̊v�c-ܗ����?[R�����S��*͹�e�EG _�l��w3�ӇEA(�2T��'k��k��d����:Y�>��g���՝8J�VV�5��h�	�$��1r:a
����0��߯g�B�h!� ��e叇�����&.�C�=��̴*m�ن�i�0Y��ټ�V����:Y�]������O͕��g��)��i��N��o������,�B
ٻ׳��)X�8�@������HX
0��ϫ�z��=ܮ4�4��Z��Wq&���g�
/�[��@�h���W��	;�0:�缩����<�s�'���7�k<~r.���9���E�G�O��_��Ϝ#7h^,zU2�k9��m�x���Nb�l8_��I�:�MV�ە�����[ȏ��1ZV�/Dmι�?��r�p�^��gM+��\1Jd4q���	�><k���%�x;��`�M����%u��tf��_�r��U*�����o��f����u6����{��U��5hO`�#������ݯ�ֲ�ՙ4�1X���XxuD^4M�8z/���F���"��	y�@IЭ�`l�4Td�9|j�LNK�,t�bU��r�hP�2�@�FS�|T��t��Q0������D�à#"�(5u���:0TQ�� ��a5��[�^��V�F��ę���('�c�� s�;Bl�鈭<���>��|��h��c:S�/�[W�<t�"i��O3bS��*��|�h;z������bt�D��-Y: q2�;��J�[�©)�겢(B��82<Z�]�Da�I��W���=��xǃ͋��ZM��v	���o2Z�1�1�l�K�a�k�4?�����r]�k���	�!��}��ۉ����:���=���������	�ͥ��?߆Ke����6N��� ��QI�|��;nO�S�\��C(�w�Le�(2O�G�[���O�z)z�O4{O�>��y�:ǌ���py���I�JBe��N�B�@{�Cox՝Xg��\4�QE}+�*(7�S�?Z�N2��X?Б���b�]x��t;����%�tpN6p�Q��e�nq���}�JD�oϢj�A��pY����Z��ٰ�,S ��A�V�Q�@���P��㝶	�q����ӣ-�_��[���
�`�-�s�g>��Ls�>C�1�rs�Pځ���,��Mځ�2؆1)�_�68s�ڜ���V�O��2|k��N[�|��z��<�llK,�!mP�c��J",~^^��!,F�.G�J��َ�^����D_M���sV��Ǆ����R�J��Ǿ1�-�L����7�+���hb��=�n�i��?�<jx���q�%��L�l�����/�;[�.��~�(�}/X�缕��a��N^�!b��c�_�M����,�n�'#��#�*��lќ�`Y� z�M��G�b���J�Z��U�9�κMR�e8���>�K�F<.���a�?O��IA��Q;x��Xk�M��1C���BD�jB�lm��@���je����@4eK�Q� �G�ӕ��>5ɟ]o������ߚ��C�0���M�!/1o�vs޺TA���af�����`c[��x�oD���1�@m��*�V}/Z> ި>�����h�/m��&��I<��ٖ*i�rdm�&�6͆�_�vP!����c�5�b<~�q4��c"�/�pvmBz�ΰU�O�p>�5�IR�� ��(}�a�w��N͙ߩw�F��o�4��IShO�4��h'�	��m�C��$�R�?��g�-uڌ�Kj�]��Q���`�P�"o��	�)��
��ei�Y�t���Ǭ��5_(�@{b%y-�Ų�<����b���w*ZG-�`؁���t�1�,��ك;0��Eډx�;	�0V3�>o����yH;���<J�Q�|��^o�	atX�sឧ�QdF_�E���ڬ/1U �Z�Mri�/dˑر�~�V�I�Z�@��R�V��CZDEP\�A*.�:5�����^!����,���}'y>:Wc�ۆs��G:`�@A�
6U\�/�<ЈMr|�{��$"�={�|S�ۏ&��WlȐTs�Ļ��=�@��#h��s��#��ڞ�� 7@�Y�3U@wv5#�q�)7 �PwQ2�[��H�Ks�G
����%�XF���#y��`Z�<Iab�X���X�T#�lb���	U��F+�M�Y��鮼�u!�N��3]�.�|��q���<8_>E
|��Q/?n��G<���)�5��E�i�Y�<��W�ۗ��l��8���o�qTy�۱�ê�+ct�g������-��x`�[9�V"��CE9���ar��I,PdA��?_v�_v���F�s�m�z���_��;b5G#�I������7
Ԏh�.�f�#��������8���1�pPl��9��|�y���ަ�Wa�-6b��{T�=ǃ�zY��s�g��rh.�J����+�r2,�1�a^n/g��Є[=�Qu����0Nk$�<N��C|���gR�i�'<)��Zqp�-�1M /�͋n.�l�>v,>>�z�B�
yA��z/�� F���
�p�&N��ХX9�W��+z�$��T�������Da���X���T#��9x�]V�`������X��z��cT�\�mz�V�R�f�!&X5���E��Jk��x D�#��"e�>$�]���Z��pKED�<�@r�3@�я"�%��7�D9�!�>rڭ"Ɨ��E����w�=s8S$��y�������e,��U;��)Z��1&2�¯+��j��H,5.���;�@C�ϴfR>#.v �l'ޠ�{?b�]Wp ��I`>9��)m�Y� ���JܬOØ�2{`�.*��g(�~��4�-�UF�D�ґŪ�%M+c�ȍ VO\X֍τ�܊i}N�Xi�^fU�����6�
L���N��I�J�� ��:j���ZfHFV�F��x��ֲ��	�R�g�0����/�*a]K�4�� �anM&bM�X�-�iE����G=�ɳ�_���_=+
��I�Z���2���s���<K�Me�^���[JHpya �-ad�s��h�^�F'�Q�#ӿT��#����خ�>��YIw�����#��e0����n-cZ^Ӥu�-��zV}�E~p�U�>�Ǫg�8ulK-�㖺��Yu�c�}�0���u��|%��!,���-a9w/�IS"�a
Ry��Vy�F[A�|>���<8� ���(�G~�1�P�u 뀀���\�>��bf�`Znm���T9VPQO\ugy��s��z�S=����9?��hZ.E�*X3�<�g KM$��0�A�pV��6�;˥3� u� v�_�N�b���*�ͬ�JWb �_#�׍��������B�dP/���6��a�a``��Y�L���	�������b�^MA��rr����-���������?��}�P6�����9���J�y!�1a4^��*���[I6�&�$�a�r�#�vk�I��m�Es�6�.�&W�>m�Z��IlsmE�+S����;��FN ��jgm�յ�Բn�j��H�E#���@��:�Q[τ�tx3�c�gUw"�f�h�7��]���c�C��ԉ�R�im�+�E���:�gJ�.x��U���'�r�^XnD�>\���ta���%����r�.,�i�]����<{A������˽qa���#j��M��H�li��8��mLy������>��f�����$�	s퟈��!+�
���m��x��q?���k?�߃��vM�gU�Ǉg�u�z!}��Ʀ/:G��X
�~Mc9������ET�)˧���E����5/z�?�5�d��=��At��<g��m9,pO;�z��U���
v��Cg�w�.Q��J4r�Z�Q,�?ʎ3L�N�%TXga�R,0)��j�jQb�Ɵ��\�2r����~�S�fU�pѫ�!�bA�?S֞�|���Q�� �7x�k�^$���Y\��������߷�br#��&�U���R��2.��ע,i������e��ꥥ��6:���������Ii>�xs�+a��=�&u:p��X�>
;	��~�I�����9��F��C��R�������2d�Ѭ�U�oJ�����l��&w,�1�Ns:G?`Փ-џ�2�R��8m�nC�Vܶ-�����  �ק�b�X6Hp�M!���6��F4{��0HOl�3��1�m���X�|V�|砘�4^��e<��&Ǌ���Ϊ3�ֵ�eU[�> ��\k��Kg�k���U�@�ZA�OA��y�s�XY��շ;�}�X�|g����� ��= /�a��l!���u�:�u@�-����s|^��m���^���gY����	v�s��bg`Q���F��YD�K�+�D��`�ׁ��0���K��k�G}"#�l2r��j��O|����GG�ad ��8�p��Sm҆W�w�Hg`8�C�.x#T��[Lt�F���� ��&��>C��M+b�rUO�(�����k�ۖ��
�n���Z��3���[�3h��h��W�8�!��6
�ɠ]� ����v��,]�2J���ԣ��J��Y�i,���P�9K����p�bu"����6w�k۱S�~���)����Ɋ��އ|)0�����?H-c��tN�	G�u��2G��\BkH�k�/�p��x6�O��L��K/���B�(O�Tb"�ꍀ� ��@�@K�=B��s�E{�e�\��w�Z�����UbR(�����>�e*O@vD����W�XM��Rq���0iA�\�)�PIm�@�ݵ��B�kBY�rL���⭌V3����/�rl�����gp�B��0�o�գM]ڤ3�'7��}&�y�ȟ$����|n'%�;�|�A�a0��:���T�ܿ��c�� ���*�J�*�ڹ{=ږ�Dm�]F�����R��<�P�}�I{@�*�Y}�.��,`o$�P�Êy�O��P��I{��n�7�����bp��=��|�>�(ڈ������+�f+�d��#V^l�Q�q�ܸ?m�G�`9�a����v<�A�kD�=�c4DKhr~Q�Y}Ŏ�z�{�qJ����!�FO^��u��}��`�9��K��w+�!�7n��:՗�'T4�9̿�]�׋D]���*�y'em3��l�^������e��+Ru\��;^u	�a{��lj�A����{T��vjJ���սP�i����$	0g��8E��tXd� ���ư+/�U_�"���U���c�-ƶ$��S�����Q51�?���Q_�oYR�;C�i�]`CވYK��C�۫(�ݤ�����8���s
y��@�p�'���N�|�\T�t�����ħ�>���W��^L :`��%`�4�j�����os��wp9��k��^
�����Q�R�	��:Gܥ�;�4[����Q��y�}�[�Mi�P�}9<\GS�ܡ�HF�fZ9b7��{<O��[���F$��\�,��*�j�*{�����
`ƿ�LZ��x>"��*(M�e_B+ ��+�3qOn�>�ir�.tCW��a�@�\�[sٰ�LW��({J	��˝j�P��{w[��VJr��|9k��R��|���6Ԏ>����պ�����뛅��Ҽ6J�[{��Վ�+EJkΚr�vC*��Sa���tw@��)��gH;3)�R)}���
C<ڒ4��N�.3�qa�=�~�[���d�bzد����~��cRe>W��,��7\�բ.G����ê���cs���}�;���Z�㳐��&E=j��P�Z�QO�4�g[x�_����Z�Ԥ�8?c����Ď�-{�Yj�Â_�iV�m4���tLv����if"L�t���9��#DF.	�Zҋ�0�
k�w�;b���x��5�=:@�z/�ō<�Ϟ��O~xmy�W��Y�Tx��+�k��s�2�RҀ5E��^R�e���9��ōR�9^���x��'س�ӱ�{��	���C�<����+���O������J=����|� �U �7΅E	pS�7>�)��X2@����j	ã(pU�G^����v����NW����%�g�B=&�fm�-��f\&��	�:`h���`1�i){�H`��Qq�>�{Z�~���އ�o�G�E�hi�~̝Ú�����u��#Pu-k���Y枬~N"�"9a��n�����fDf�
C7B;���IY�u;�}�]�Ag�#B
�8(EX�n^3Qv�	<�&��S
Ξ�>ο���>�X��~>��q�h�a�Θ�+.��]N��yt�f3x�KƩ'�f����C\����Ȉ99��\HJ �3=z��p�p�(&8���Z��Y�@oN���&۫�����^�Q|	�SX�m���X�I����N��0�	�XLRb53;}�j��s�S8u6u����0P�eM�*R�*���T��V�l{���g-��lC+�,�V�{ɢ�>4�7-�|܏�x�����>KJ����AΧ���6����ՄI��L�3�V��zy�[�<E�:ՊOs(��IL�!���Њ1@=�U�w�f?��y-Z�OȖ��c��h�4�r���v�t���%�	��ڈ��@��ɹ��ڀ�5��O)\�B�KD�Oؑ �/3� ����+��'�z BM�&}������o1�f��QO����q�p�ۑ��!ƾOv�2mM������ԧf�G����U؅�M�����7C��ݨ�'���#WH�zs���^O��s��1�o�6������!�����$-"�=�0F�E&�M ���{D�I�*o(dJV�:��-:H��[���1h��*@��4zQɭ���x[_��ԊME��]���g�(����I��y�����B䗤ARjEA��̗H�z�J�L��sa<e&���E�lԻl��bSӥ�͋o�\�V���a(���♨�#^#�����NV=Þ��Y��\{�",�g+	�IZ�)� 8^}���4W���!�	sj�:����W[�?�*W�����`��ʞ^v^X�@����	@t��4.�<Z�������8Uf���l�C[�c�T%"��G���Ƹ^B�Y�m��K|������r��Q�+ئ��Z���b�o�͟@ �8��m{ח��Z�r�T�硝k쾇�i���п3�PV9S�Q9��|�l��k��`rF�\�G�~[��3��
��K�=B|!H=��Oқ�[�Ī3�p��V���k�wh��2Xk��\��S��3~@�.�>���et)�\hۣ-��Rր�&�O��~�w�)m�d���i�_�L��Z�ʿ�&��l��U��H�z�n��t�R,|�N1Hx���P�(�i5��e�}ߕOo6������:���
����L1UB��$vK<��a�,G����#V~��pY���m���N���du�}��l�b�"Z-,X�U�kY�щ�C!��|B+��y7�{ceG���JZ�G��qF�Vʱ���u���^�R�&�jP�[�5�Ҫm�,�:V#������z]�?���{X_�> ���B�wZ�O����l�C�0�˸��_	��'̦E|�O��H���|d��M���a������]�,�k�~#&p�Nz����yV����U����-w����S�'�߇z�0Y�#�й�Q��J�8��'�9�����W;��0'�؜,Λ�]�Bӆ�_>åX5'�ɑ['�0�:1����1�0�rn�m�C����?����ߋ�nz�ōޝ(�ȩ5q��Q��6��=�`&�.�����������~�Q樄gk(V>�[�1K8�釠~���x�W���nu�>�hΆVW�!�)V��sV@�@��2Ԧ�͢f��K:x�?u�W�;�9��ֳ� gP��.�RY���������5���7���F��R?���OÍn��ىj�9�,x�G�{��&[��+t�'�s]9�!$r%�'��B����1��-���E2t.��w�"�Ҧ���x��B\�Ӊ|���E�DP	�D�GeYL�-�}g��L�1*Ƈ�iM��-�������0�@u���'�یy ��F��7��� x����`�G>�;��xyY��z%��Yr�5y��w/�O�&��4��}��}�s��j�%����(*�|�D�Z��43����ڸX�&j�#<���g�c�bw�|,z 1�zHv�T�O��"��W�8퉑�w� kK�hÛ>09����)s�J!��q�>Mc���%?��)��,�����!N*��;�p4�s�-�ѫ���I� 2�[�ȸ�Ϫri���d���1�nΪz�`P�Yn�T��ﱹʹz�b���9����lL�Dd�Yh#�=���VcO��@�~]���38��
ܱMl�?TL&d�a�PyƦ�=�^u��=����%=pc-�*�v1�l�fb-ͫ�`\�e�V�$9�/$g4t(�!i ـ��g}�)\�հ��`=������'9³-��ҏ�R.��,��ڄ�8@X�~�}�ZXł�[-��?Bw��ەSR�}[�Y�P��\�eu�M#Y>�����E ������ �BX�X��(箄6{��X �΍ٍ�^�]YgH�^�����������ח��T5:�Ý_E�z��@<��:LD��O֦&uƅ����wv�GQ"�n�S��擶_�=9E����6�f���YF,c�M�K9�UY��^m�٫u2n0X˞�t�bB�ݨ�BAb9�u�v;>2�⦞k���,��Z��^$V��p��9�dze�ހ����^p:�!�^�n��N}0�M�����3CC�"k����E�e]���`�1��+\��'oW���:�s��t�2��~44!b}c�Y 3�H��1���<i����#A�?�L,o^��V9��1v��x�B.�%*�"��i3��h�ZX$�o��P0ȉ�6��?�dd�
���0H�c�5�s9�s� �&����gU��'|�r��싻>`��w4��I
�,v�bO}>H�B˥���a�J�1�c9&�W��PnS�ɐ������++-^0��������6�`�q��6�T�������S(��Tϛ�7q�1b��5���9��p�	7��	�A�k���~�g�q&��	�e�ƕ,g�AJo��s2O�{�1-u=�2���A;)�����v��ߞ�$u#w�O,�H/Ӕ�z�ۄ��u��k�$Uw�B���t��ge	�M�A�ɫux��H�4*������I���e�1+�G_ �&���~ģZ������;��:{�L���[R���5n!#Y���Υ����M�N9�Jۄ�<y��+Wv���n��i��v�k���=qܑSh�;�<�_����_B��:�=�m�Ui�+��͐���WY+��}0&m� ��鴆��8�l��Jz�`<����m��y����0�wx���%�$��0�w�& ��$#���V?b���~�9�Ɏ�)_���2���L�
�T�n�վ��M���A�� Wk���H��70n�DiҲ.S:lL�JK�Ȃá�`�o 
�͖:+���q,�;~,��b��]��~��U�ϥ�:�:�7Z	#Ȩ����R��#>K�2�p��p��q����ߋ�n�O$I~0���y++�et��� �gj�O�����G�o�=< �������>[��ߴ�����J�	���k�h����y\EX��)������!|k1N���Q	Ȼ)Y�θِkw���K����Ne�6�ϻ٫���!O��
�d(��ek��ӿk3U�F5�7���BՁ_zr��1ï����P ���,�x�"�s���?�G#�l�"W9I=(���󑃇'����N�{�䷺�ˤ|d1���)fB�q_�Ģ�׫�d�����R��
��=;Iࡣԥ�v<�"�[�]/�kK����t�������	�Ҹ5"ȑ
tC�(�c1$m�9BړT)�"��H�F�m���:lE��8�j�a���cb"��R>��È�㰿7��/���݌�[y>�M��3��dW�hC��6ru Hz:�1�Z�(�ېQ���Y���,����͛X��;ڏ�w�4(m}�Q��M�C��D,�I���ͭ�L3
�O�v��Dڨ�.���t����	V�����+(P��)~ήa5�`�x��"��W����g�P�N*+F/k&�;V�p�r�q�<��8Ty�O}yG����SF츞�iñ�����!"���Lg�6�y;��3UDM���Z{>�c��A�G+�=YՖQtdO�G�����y$<�g�Y���Iqqx�I�,x�(�� f5mJl�ځ
z�)�q��~|,�6FUc#Y�ّ��c�Af�B4S�<��1ys���@_r�x�F))�|�Q�G�w�0j��.�Ü�0|ɀ6�w��aF��T"�Z�?&xU&�.k�м��X�֑��o���L^���俲����l�7�Az�nXw��X�dh7���|�4�WS�)������ŭ�G:ɥ5�l��qx��,���OuU�u��l��<���rh���U?q2�ͣ:Ƕy�|P���Js�'���!�U����OP��ep���kR?V�@��p:���AcW|�����+<���^1��� �:p���!��U �aE��&�c!�?�98�ۂO=v�g$eǔqN�(� ��p�1\b��]��|B|0!�"��-�����O��,���,�6Y�t,�,ӣ�����a�1m���� Ȍ[��\Z}�1�dE:���RFf����.����5O����f��u�8�0�����a�<C��9��8`9l��!@���������E�4:�?��32I~
���P{g�m�HDB���T�q=,�ji�^��!�H��b����}JX�� ��q�9슖���F@?�����0)��Ƥ��l؇%]�6��C��o�`��@�|ѣov�ň+;A��wڌr;IA�$��p���G�Ѩ��3(?�h�>#�k��F6�g����� �s���#5�ƕc@H� �k�x�͛M��Z��&w��[�ylIsa����i /�l�esY0�$�Z�c�K����~0��t��b+����+�0=>��4�Do8G��I(�v2z�΃b���#��@Z�p��ގ:�W�P���L�B����<3y�^��ē�P�|^LJ�����$�O�1D��ó{Y������$�Z^^��o�7,��X8x^���Kc��S�&����P��Ӵ��F�cq����	�A��*��!)�Z��3�ő_����eqbL�{������x8�����#k2�i��EVXMO,��:���y��|�xr7V�L�e�NH��1��1"C�`���jd�=c�Js���1Ġ���p=��4���C�c'��I�T	_�����^��d�������H1��"��]�6����Nǻ���� ��u�����Y �ۻR�Ar:"-���t�<�a$���mI�jd
�F6{��?𞍰^����(���+���1����8ow,�D�'fy�ND�Fm�"��Pۜn<t�lvj/��FMB;��4}���D�C1G)�����O���߂���X���\o�h�[��f0�@��rra���[�����E��3`��TѦ�����?2)œ��|�<?��m�7<.c�@$���)g���W��|g:�i�7��\���(I/��-����<)�ȇ��q0�(���;��FGy��Y��2���HO/ѫz+�ѭ�K��3�B97/p��$�L��kǕ��Yi�=�*CW�^w	`�ᢛ��U��Ƃ7��f��x�G�K��a�@�p�i���q���	�b+x�{1���o�qߜ�0lw�Ɩ)�3��s��?��dV=��
�NGF�r�
\���[����9� �����-��} �~��_�wc�}��μ�BK���U��A��}�vϓV~o����=��*k��R��� ��}_6y`]�ەR�S8��ι<+����I�G�t\t���=��6��8:��5�a�.�YJMR&w� ����;��@0z�̂[�BΖ�bh҆"֒��ux츟K	/�jy�@R��%'�M�\�6���G�⪃�KN�v@>$���@�.� �ސ�?:GC+��hڹ��&��0�)����!���%زfO���"���V_Gz�^��Gj7�cw}`���Nbt_����ՒI�3����P�q��E��d��L�΄�l�ΎO�V�W#Gb(7bd:X�C����w����� �K? 6�9V�H'����Z+�}��[)!��T�[����q>X�e-�����Ŕ�:�t�m���.m��e=7 �o�A'&	>iϧ}.�od�Ƶʑ��bJ��i��;6�Ǎ�4����S���V�%��53�]���D���~]���:`Ͳz��d���� SO���뮣L�W���;�=��G�;~����1�0VC�Ӏ�ʣi�]�`��a��A�Mn�í�� ���'}x��V�� G۬�fO�6\�����=���v<�$�F�[Q�ɂ�$��|-�� �=��FP��V��j�J�ߡ�X :�t���k�M��I������
�n�0{A����K��X�5�o�"w���ڣ�a5��'�B%�E���LOn��E����z��@`�z�G�'�%ړ��h���[��ʝt�;�d��Rj���3��d�F<�&d����6��0�3Hr��ʍG������W�{�a�X���k�W��Tq����N��cHiuw�ᐑ-Jf��6�Z�oj��f�
� ^�Q.���k��o>BEw��
��m�ȡ�v��d�r��`R��8�|�0b>��P@�&b��Sq0��MHʧ ��vB	����ӭ�m��_"��͌-�*ʡ�XVb��'�?H�eK�5��G�����"���%AA�y��V`���Y�33B�<��X��F�T���������|��i�셫2��V�|���^Ȟ>�uc�����s���E#�^�z�|�Li�C[new&&?�I��v��c7��Ԧ�n�Ċ�݋�7����L��.�^r��t:^�����p	�Yǩ���⼦��l9*���k�c��ŭ��9�2Ƌ�<Ġg��P��]���7���K����Xf��@���,Ƒ�M��l��~��� ~µ�Ó�I$��G4�y�%�Y=gp�mF���ɴ4��ѠN��$~f�#yaM\�^F�INƾ�1�еs�	��5b h�����+�L��笱X�֕�i�����O��~VZS�
��@cS�w���8/��;�P8���+�@ߤ�<�%_<�+�����s��r����c�gm��\��p��?�x|����];r�Iu��%[�M����%)�j]`��/UK��~���[YM�[{ĊP_�z�S<�쳢�u�|��/RI���P��)(���_=��R{z��[�H�J�F'�+�;JQHs�jũj_���FA΁,�_�{�w<��n���=��q�󙶁N�/��#r�/��A]F�j���5����K1�\�T�n�z1����QghQ��;T(��߰�b��q�����O"@r|�?��8���"�=�.x�7���=�Z���N�_�Z?�2-�nm���bM�����b��N���M�,�Gh5��uu���A���ݹW�UE.�q��T�\#��V���jd���h�q��c}�l~4۩hOn��rz�x*������p�zG���l3��Ͱ��x
�χi����P<]X�,��.H��i�.�����\Z��4n�|]�i-x>.�0��p���:��A[䵰9�94�o򨭲
�5�V�3¸�8/|KQ�����0,Hs���X_�p��3BZ(8L��8��Qy$���x��NAWY�C���gzO�P��.X�N:����D��R�g/�hsg
�4<p縉y�z���[[i�|��z���C��Y؄�]�"mP�&�����V�ĩH�����0����2���Eih���O�\iLA�M��"��.H����j��"�O���)�W������0_�0�9u�P�Čf��e��?@�?�լ�9ΰ�zR�/����V_gl�y���m1�p8R���z�%e���8�wT�����>�)��ᴊ��� ��^GX5@=�>���o�ܟ�|X`믌%^v񥓨�MU���ǭ6�"m"Leƽ�]3�%"&)WN3�}���b��4���c+�q�[�G�ֺ�1Њ��PȀ6Y{�f�aD�X�=XH+��5E3����������V�]�j��`�a`��s�5I�77���v�� 9p%�S�oQB���d�{�1�����x[(�n�~\"�	(�H�~��"t��u��Bx�G�����t!���싧C�{�B�>bG�O��=ۀi}
��`�N�<�U�{�ً��߇#B��]��Kj���z�1����}c;��ȗA���nd�P�I(�UGɛ�lsx\�jc[��a�a%�pv�7�z����et���Jʗ=
��W*1��Y�-����`̗k�f{u�s���2����:��c;�h����?DTC)Nӕǝ�碟�O<��
���Ќ��;�B�"��!+_��s#NK�'w����#Щ�UςW�ls�� GmE��I�À�	(��Bˉ�@�GK�q2�xH2	�I3�ԛ϶�L�-��9g|���H47 tGy	�;N\籄c͘�q��J���������T���)%�=��[�_)�����t�=�`3�!X�=�[~jw�A�t�X,?�������cDU{�~�6��\�7�x�A�=�`�}_�����}���x�|i�'�ʎ����sv�9/t9g�ؼq��G�P����I�oS��6R"��[�����d¯7A�3�Ε�-ٚ����Pc0��C�
φ��I��tX�&ٴ�C�o�m����\��o(�K�t���J��D=n����d0C���',�=|kL�4���S���|�M���>_?�}$��<Ĕ��Aj?���1�ǞL�W��iL�q��:{U�8qoWu�ZN>�z�ZЀJ�ck��urީ��k*��rq�&�����I;��&���fq�v4�`�v�d��wtl�m Yn�� ����wt��\���
-E�kx����v��g¢� ��؞d��Vtk�p>X�d�|�c�� �I��G@U+\��R��*���+IꆹhUG�b��X���5����9t�Y/�K��j�'ܰ�Ypq ��w�2�J����a��@#� �(D[*Q{�){0�%Z�L�s�QP�Y�S��;�v'�RN�����֦�xx�H���8�v�o:���o���9'���P�����:B$&�4����|%�W��d�F�A.f�{�i�B�B�(���c�����'�����q1������r�] /�G�{�m��~���+Q:�~ۺ��w xm^c�cXuV��&[V�y����MFw�W$e���㋄���N��ol�������Y�7vE_�C��_c8{wt�x 4�Bz�/a{��n5n���6�=������+�6�r��+9v��n=�g�h�6y���F'��'#�H�tMd��:.��'�x �gvP<4�6�P<4�&�+@���w�@x�L�O�;4;ӥ�gq�תm��=��R+k�ߤ������$=&���&����ڤ�Y�_��ED�|��K��g��ڤN��kt{3�KSC�����m�	���I��g6%��4�b������\����9�zsR���/d|�o]J�����}��:���s�B�5���r�I�Ì@�������̹�Z�Y�ղ��0�⡣�����`Z	��������S�����T��7)�Lk14u��5������XuFv�����ɲ�c,�o�	���ǌWx����Ċ�/�P�meX���>G�]k;�j��X�pB�?�+�']_��&
Å��Mu:r�~�g	����W��I	���]�k�@���h���=��^�t�#�ƅo��&�
��hz<]�30#iO�G�F�5�W �q�Ԫ�����]�*�๩�苊�eJ5�����X�x�#��ݖ�ܲ2��T��4���v�-���[m�2!� ^JD-M��9�I^��y��=g� �������+g��<��>�s({����B)��	Ŝ}���:�h�\�*s��:њ�5iy�s"�˘w?IƘ���hk|1�Э�;,�>&"�;Nx�0p">o�Sn�J�r�����
����յ�Ҧ4�|��"�~�X�����ڼn������z��bz�05�#��_�p��£b	G38h�Q�x��tg��T�e
fy����1��DSG�R�0E���46�%��ݘ���ZL���ƌuO&�[��v���J��$@���w�ǝ�q,X|��]�b�t������v�{U�G���c�]
�4��.�JrC���:�)���~�bgqH;М�|�0�6L2�t��U��A`�^(a�@}%�]d���W,��W1̻�����7|p����$_c^o�H��̷�WS\��q@*��P]�n�4M���[��Cw|lּ����X�J
���υ!w�i3U5�������s�PP�zI��C_�M�/ "�95�R�\��dwYU3���hz�\�t�^��E��'h��^��X��m(�-���jY��`��-(��
��&�q[�y3w��-���C��ׄ��3�w�_����:_�]�Ȗ��*���9��8�����+��#眸Cm0����يH/�Az�LP/U)����i#��A��������G�W��e�F������������h�㟨|������T�9a��(���T��y�ZVgb����4_F�bL��}t]rrj�b,��^*) ]�Xq��f�e[f�����I�Vy��c�܆<#g��f�V�=y�6ʙ�њ���y���fW�^����_-�"�.��=k<">G(�zq�ɫs�-X��0�i0d��-�1d��e@���}A�h��պc�s}bo����TL\��gX�M������9��g����?Hllv�1���Ӳ��Чv"���oˮ��%�ஷ�AL��9�r���6��w�\�٧��:�N���ْ�Np�<�.̢�O�q3�R,����Q���H\���  ]}��3���IN��t�1��+�t�;�le�[�
X������Hr��X�b>0,�~�y|k�|w�d�y�!�l�d�]�������s��#?���O�-�9��濢w�B��t|�K�9��K���R��H����cF�:��/��忛��]�;�c�b��� ��X�:>�Hw�l�9HD6��Y�dTͧ^w֓���8Z�(��^E�0U���c���{&V�/�|"�	|y?��_�;�1n_2��Bq/��a��Q���$>u�:;,���vO��)7HrE�j���1��W���fF���`P���Y�~}2������1AZ�;�����B6-�Q�E��6�rM/t��I��)Y�w#�I�0�":�EfK)�0����!k/>���^� �K1z� �?c��Јg�;�-Ud �W�������w�"���\�I�rK)��C�D��w����i+?��t�k�.pU"�!�r�}E��E-��7��ᜑAՍ�ݟ(=����\����	��2�����@�CL�qB���T$�ȸX�Pi~G�;.{��BI�e�4`�־K��^���-3+�����V�aS��<�?�w<hQ~����vl��S�m���4�N�F.�����3:�A�d���?���J�/� ��F����*=_q̌VrW�O]��_f�l0��h�t�+����).�@:��߁6�`1j��Xc5��_��U!O<���MR�1�7�';s6H��w�ތy���Z
ί g:��|Ǚ������չ�L�����ޛ7�����+���2}����x�o'P5}N��Q����em�?
5/�L�OPT����|I��^�u:�KDZ�$��S؝B;�f���>ӹD������-��"ԴP�Y��?����oW!�Ӊ����%��!�+�sQ���"6�u� �#R����B����Q�l��}P#�Ǭ�Q��9���@�t�����nN���C���+Mⱒ����)O2I�{c�o,���1��M���)/�ʉ�4l�1�lp��Y���W�{#)�ʜ9i:��O���o)P�ws��xg�nR=�UO�(Y�\��E�#m1��N�w�v7j��[<���W�>�w��sc��V�����`������.r��$x�P�_�ŀ��"��Z*e���Fk�U(p)x����o[4V(sw�Bk�k�V��@�'(�<e*�'�ȗ�q�U���3Sس2d�x{�����C>Z��lPS�ȥ��	��w��9q�� ��m�ݜX-:7���������ӤW��ͦ\��Hh>+�F�c��}��CSO4��E�s�{)�<&������:��G�y�4u�h
%>�Ť��p��&�u�#��G����ٲx��IjV������X����&TJ*H���	�`��G�r��K
��Q���W:���A�%#�%��r:\d��i�'��ҿ�f������]�"s���\e)s=5�P]�d�̓��5�;���J��%O+�x{�o7)XgYX�,�`���2<l�po�G��4����j���&����T�3L��R���\�f���B��L���j%1ap��ăt�n%�ݝ&4=��(;�*�R�̵w�����j��~�;�F����3R��{#?��[�B,@��`�ca��p������U#V�Ë|��2OW+�<��)0l�xe�9@8���%�^U\A�h��!�Jq�Yxb��)�i��}���O2ACooH--ذBH�o��vZ����㦈��Rބ�eA�I�	�D�Gr+o���󛮸��ND,�~@Ҷ� ��Cs߼�YB<'�Z�/Z��GJ�1�F^��G��1�7U�!�O��&��\�XHA��K�œ��h���t�d�e�y��t%��,�;����;W�Ԥ�1��3j(g��8�ygRye6m?[��g����xQ�!�ȟ�"���3�����/�A�D]ZO��_ɝ�D�X4�u��g�p}W�Ǿ*�F��V�d�̋J.v�~"�,��ٙy�PM�;�Y$]���ޔ�a��o��� �
N��`(>�8P�EXDA�ɤd���ޓ6.Y
0�9r=����Ksr,R��a���hl<�����=�l��{��x�C�9��^c�w�+�?�YG�2NG�p�E�"�*�E�7�7��S���d�� V��6��{��ګ�b���%�}��g����$�3���tZ��^�5��L*��<f��un?�@`�E-�"����������@��`� ǰ�8�a����L�'�[/`������ȼ�t��w����^B�j���9��Q�:[�6���}�yE��r�6#�y�=2��\O���!iPC�Ƨ�;ȳ�q Z�iQ^D:�=̷Ã׳/�Pùt�z�G�oANz��/���D���@;׏� �H
�)_���O�h��m�ٕt�_ଌ"��62�<�#�5�)+�-��E.��˅Z��#<�_<p#���ۻE;"-W_ZB��P�U�<n����<#獑�L�P�� �!!��U�����r;�|=�����E�N�E
xUJ�-f3U7�:������%f�J*h�+e��g���Y����b���r��� �}'	N�~�p�)�B/���7�ھ#3j���'!߫p���?�
3�=�z���:�&����Ͱ�G|g�M�V3��7��q
����kuKb1�Q�o!���шglI?c���	�M��tN͓��x��Мx�����w������ю�(�Y��B[���>ؒh�u_η���#г���C��pj�:A�A�����ѯ��F��+���{z6)ę��itdc��rU�������
�$��I��m�x�݁�\{ ����l9�c��aH����xu0��	5d�y-=(k"�<ݒZ]aȘ06�r��QCM�6�y���s�|�R̰^�ԃ�Dg`�5]v[g`
�8ԡ�E<&Vŋ��(?�U~����Dk�j^����GE�l�f@���8��,�f�إ��e�u�
��^{�K� ay�[�}V��(��;i��a�ȈH�#^�&�_�9zq�y�r�1��"���ْD�H_� lc\2�A�Z���C��{��t�۠f�-Ȧ�gB�*o%2��&e����.����j �
��+ �;��z��x��#�1a�H��j��	oH��i_����̌�g���8ݕ�-o�qG`&ot�pP(�"����Y9�v�x���|��PV ߄�$Y�����Ѝ��Q�wv.��=i]��E�,�|��@ڵ)�.�:s�}��X�s��Q0�ֲ�����G�}y�e�1)��³�s���!e����C�%tAl� �߀ыf��F�\�4U��X�N��D?a������$�����p�H)���	?+�ء�&�Ve{e �ث�HVX�1 s�B�*]DDO�)�7܀n���+R'l��.�pKt�f�zF����+FEU<6�\�4��S9V�YNԗ�&U�W?�Gne$���T��s����C7>�?B��yS}O<��ǀ�͹ro���b,��c�d�={�� �J�V��vO@�Nb�{$c-��[�0w�<h�x�g7�m��/b�Cނ�G�C�-ᚲ�(��b�7�0���{�-<d
�h| [�E3�R��AA(L2Z���ȟ ՟@�G5����y�w��\,	�4���	�Q�k�߷�ӎy'��#����7���l�ϼ�	���V�,27zQM���9hd�A���1/.��ld��&�¯���3��b��(��C]��v�ń:�2��S��J���GW���:�VY��p������S�N��~A�|R�ej<��<���)�+d�8��<nv�{��gXHI���Nb0���aN��ĊD1�\[��2�s(A�	��}$!A������i�YmD�l��cp�z(L�A ��ǈ���x"l��=C����Qn�E`�<x����cp�~$��(~���"��NQ[�-��f����@�3(^��l�$ ��ܮ{Ձ-�8�@����7� ��3<���Ժ���x4ǣ%�$��C2���b���=2 ���=�r����o�$}��s��X0g2�7�5Z�T]nP��p��<��X)����"�h�-*Z��t�=�I��x�ِ�%�zUB�\[���c}M.JIs~�K���4��ա9�� '��,���/��b�/�E�E(Fu'i�N���mO��i���oV֚�����sG�k`EYƳ��Ί�y��՘�=�J�G��}1�a5:^�w��a���V{v�7������w:���� ]ɼ-T��4f˃�2�X^�������Ntʥ�F.Y��
�
��Q�irR�z��.����Zg�e����d�:3�[ax3]�����ʊ'�(�(��{W��.��c�4mέ��_1���?�e�|�3�e����'�ت����J��
/=�<�����/�դ�/b�T��cب���D4��~�����w��s���|t��$ O��1�
Iv6���m�G�{/��+��[YQ&/)Њ�ԌA��Pz���e	��;F-H,S�nZ��\���)풋ŰN�&�Q���ߝ�w���+�.�~w��_"�~J8�Pـ�[I�8ћ�+�x[������'B{�J���Ua�����F���?�#B|t�ډ��t�z�"qZ��F���6lh�yǣm���|���a��W�I��c���}�K2֠�s��/�A��ړ�17�t?�1~;�߹��@!�	�;��܀����*�g�JXU�n�B��=7w�\�pϦ^\����<���c�H��m��XD�J��2�o;��E_^�E�<c[EM�v���>�θv�l�w0_Qh�x��w��]Ֆ}&ީo�Z��2��|��)�U)�qz'�~�L��]�LG8��U���k��o�������ʽܩr�`vQ�,��t[h�^����������z7�z6Ŗ��Ʊ4�G�Q|�s	�H�~Ϧ.%�_����ԩ�����*�PD�7K:�JIޑZ�$)�m�{���(�D�N��� �$�P��
̿�x���+:�F��*:/|�u/y�����&7P>Њ��������J�P�x��SK8��$>�Jq�Oԫv�g&��祂c1W��;<J%ߔD*y��T-$V��Wr�i�&^6�I^�wBs��t�?
�1��E�$�f:�2r�G���u���rC�u��)'#&�/�?6IUA9ccRN"�	.(�VN�{D��tW �(��ኗ�^-�-8��lX�kC�Q�_��>�����<��f<�@l��i�V��MFj�SjB�4���rE�(G��ȴp{By��|7�MT�M�<�,b;���O��F{`J�n�Z���x���c�MiB���=��G���.�hj)Ͽ0�������N��Y�����
�)���N܅k��z aa����$7K��������F7���#W�����H��CM��O�m���Dt����D��#��<ȼad��#FWJ4�)�d���� ���=�,���~�Y��8X�)-�J�I89�I/.ƍ��G�K�j����ElIΒw�!a6
|���h�I~t������\B6�N���'����$�0cIJiBݠZ`]n��*�.���$e,wcT�,�f���x'kH�ʋ���L�4��N���%����34��C�l�
�HT	�V9{(+���l|�ș���^�}�g_w��d�hb�P��qn��y����ґ��U�Y��/WCf�Ze%���. ~�L=l��l��4(�H0z.H)K-�4s��eD���cI�
X���D������{~`R��&N0;	���P��I�2�#��N��s-�����ph�m�|In�`م���Y��9{�k��邝�j �N��R�p�;ID����5R_X�ى��+0 ��Úe�5�?p{ݪ͆�iF^p�9\� ���Kx ��[꾟*<+HGqc�@��!Wj�"�	�Ҭ�������|��n�\��,�B�X>\ҀBc�y5�"�xJ��XG���Fuy�o��K�M��q�:����n�H���D��-��<�*�j�Ƞ�Ptz6�a��Mv9��~�֟?=�W:��6ۘ M<�.�~�P�	��@��C��C#�vy|*���J�K�o�I�\�K� �o�l�]NT,��*��f�w�ki�m�W�k�V����a&��,�ʵ����x������S��|��<'�����-�8�<h
y2@���:�2d��d���+��V�F�����8+%�_��'�5�&�V�H�8���e�c�䘰�L����~(�z�J��,���C�����8�)3�l�pΘ�y�I��V��i�In�����(<
N�9�~QqE)��	W�J���R�Z�p����eBc�+��P۱C���8/{:
 a��s	_]L�sLG�>)��Y*���ᶼ5��+���r8	t�X冔&н8�{�7�����Yr�g�9��r'��o��J&V���ܳc쵄�ۯl�[9=󝾕�d�O�:�s��������=��F$�졋�%<�]�>��ǥWI��<�Xy㼮^#�K.�K�bv����ĝ�X^U�ˑ4l��M�1+ͺ\��cN����}�D�i�����(��}QE��+��f�aY :I���b���Ǭn�\��=	}�x�%8�,��R;�(W�~?�s� �~�uf_G���JHp~O$<���T,p�gї3��u�����vʵ�b�z�.��#>Y�7rE6N��'�|=1�N�-�z5��_\s5�O��L�A����I����F����x��w!f�I�C�T�1���"[^6��}=![2��r�[�� nS��8�,��u:E�x2�]C�k�ɿ�'�_C��CN�Vp���YL��d8v��׈��k4�c��)#aU�[K0�&�ۖ�C��Px�Y�����a�2��3�Q�5�t�L��^5n�+[4	�ix���l��Mbǘ��tm�8p�X1�N�un�^�.�&���L6$mK.�V�۳)^lV����i���x��v��ɇ7j8󾓆J��1`)[�#9o�R���˸s�>�m�1y'$���<��0�>�ZO�L�p#i��g�
Wm,̲`0hTn������3<�3�e�[]׃<x~�s�y��S�'܍m��;�T�����u��5|�_#�ڍt�Z0��)�.��"����0�Z�:p��U?|{�p�7 F`,,�l�7�0s�G��Zx)�\Mq�j\�R�mzE?n~g�o���Mǫ6�8����2�JЩ�2��'Ӏ�uw��������I�~/�N�{�]�}�]�{���{���)�S� e��Z@���>:	��n#g~&�V;���_���x�h����{R8��=�!�o;��h[7�,�2���^��_���.�M��m���H�s̶�49���v�&���>]`�g[X� ��Yg�B�P)G�RR���3��o���=x�?�.wF�J�=`���r����w�7�*�X��FC'�^��a�.7)�¤�k�k p#�o���y�uK�'�K�"F�GV1i�dp�����r�6�߯ҍ�ϝ0fp��zK�˺��S��#66iV�xs���5�a����A[�[G�J���"��V���b���q�uw�4�s���.����@��S���7�s<&��@�K���84θ�.�9��u�{�'k�9�Ų�{LQ%R�v����)�v}[�:��<��o��wRƁ�5�:<9�e��'�mWj0^����ƽ��*�v�ۚ��Av#�v!��X� UGJ)�30��G��q({�Z�� �[�`Z �[���
� k�&�t��"}d���!�Lף:v=űE�0=0�����]�q��8����w������@���4������ڋl���/6ښ>o2GlM�� P�W�7�9@e;�Z%�j�����4������N����.��0��q�r�4�a��X�h�K9��!�N�&�5��@v���NOƾ��q`������=�r�?gu��K�\h ��sp4Dp�<}$�\W8r�p� �= ~=��G�O�ut8�>��7\O�����g��H`�2�h����fK�=��|H��o�ɧ�Y'����T+��П)�O�����8mf�ï� =�
=����R4�\O�F5�k�hܐ� h7Ҹ�� ��{���%H���뢈�;�4!�E&��o�A�E` ��y��G5���yP�Ha"J��$��`�h�=�Ӵ�m�9���K��ŎQ��OX�k,��6�[�5��G/9�-ǹt�,��a@O�0�w��n�,}3L0���#wR���?;F�{i�p>�qA�%43�&~���"��?}H�F#�ӏ�N�Z/�`0��I�M�!�%�F�Z����n�nz?R��
�Fh�V��n�[�R��=��E:+Z�WL�1�h�qMtcO_�����֣ t�m�o�~ptC�/�еǸ4��{�ZM��Fg�Z8�M�+��������Sfr8�_�'�����pz�K,p�rT�Xa�udpin0S�R��h�T�K5��vZ�\)g�����u	!�;P�l���D��κ�>�K̫��ܪq�PϬp�u��0�l���v�M.��g�ۑh[,�Rm���O�9x)S��{f����E�����Xw/��df�s�st�H��Y�Q��>zN�т譽��X���"��S��I�`� R�042Y4����ZV���$� VXw�x�tw������'������Qʪ���MM��ļ��X�}���Q�+�yy����\��p�Sͺ�Q}���%�~K�;q�W\�R�����?܀3���xCT��K�:N�б���=���;-�3�9����S�F�3� �[�X�ћ�Ⱥ?yp5���E��5�|m԰>����<$<�PA�-�6��Z��!���H��\�$�Y�5�[TH�V�@dO˵u��@2�������7�o�q�v��# �y���F����-Q��t�qƄ�R�K'4}ً/:��&'��� ��� ��,=�/\�f�ɼO��u�/���/G";�u�@..�e�jF�T3w��&@q1�P	ɐ�*YҤD�k���`q:���V)0�%W�(aK�+1��'ryn�a$%�h^��WI��7%�������=� ��7lF_[�Z	�B~t���?��O">N��u�u�<�2O�L@��vQ�沘,Z̻�Nw;��t���8M�w�}�8����4�wH �N0w��(C'�{ i_x�a�}0�Ɋ~��f�zv\�k��/���C;��G�g�M�n_��5����1gkp9hm2O��j
�F��W�)��~>ܥS��E�i�����2��
�ۂ��h���{Zat�p;�gA��+,�C�ȁ�C��?[K��'�pk����rٯ�#����R�^S4k?�+V�oA����pX�����FO3��n8D�n\��vڞ���ž�܊Xp�w��'v��7p���=��zRhOZ�ߛ0�k�J&���|	�L��(�?��v��"�����C��~�x��g��V�wo���wo7&(Ň: �Ku|�w a$�_�����8���qXO����p2S_z�@�G�[�#�{_gJ\��7�]��ԝ�=��=��U=Ի,��n�U]+���n�9��{�@R7s�`qno�bRV$���VZ�/ڭ������M�;2m�FGShoࡹli֯���gT�T�w���5�v�gX,tp����1)ѻy����O�����iȏ\�&a>vVt+��I�#��G`R��8���n�J�I#�˱������8��3��.�� ,����q9��&V���1�����/͆�j�j�}����O�!RY�M>K����i����]G:�:���`�*Y�m�Ď����Rg�D��� �;�����)�F��Y����~��s��ja�T=�i��}ޯ�b�T�j��S's��q�!����n �$�z��_X!rA��nr=Msԃ$~d���������ld���6���댳��l�r��y�Y�=�/���$a�qf[\��d�͋ok�׬`�Fnì@�J�Mx��),n���W;�+���� f�"p�9��5Ze���o��Ն�9U���y�P7�*ږ��#��(�A�У��������+8C �LD����[i1��\��B�n��'a���G��!3wWA�8a2Ȍ�M�t�VB���ʯ;h6��F�,7Ӯ�����I���l�\�%WԻx&y��N�$_�-�#�g5��1֗��	��΀%�I'�-a�9~���;r �wd�\l��a&�@�Pe�-e$Gb&!~�3[R�7z�
jk�XD�>�a�29H���qւsoS*W�օ��('���Cc���H�H�^Y�җ�&!}ҁ�{!=�w;!}`��!]g�Wn�@�����ϡN�C��t��H�7i���`[R�9"9�O �p^,�1�@�ǺD�p�/<M�z�8���G���?rq;0��v����U��2��A�ւ�w������9���F�[�wj��T{����WI��$2`n� D�C7���uqt�0��ѡL���"tP����(dX��@���N���^-���L�$�x�gMz����Ee׸T;A(�����6�=O�Q��8�xS��R4���������5��y��)���N�;���2/a�E�D�A�+�򕿛���X�2�A^�F��Xs�9/�)�Q��ʾ�x�N�������'�I��C�G���A��e��h��J��$yJ�$����>(;ε9�ԃ�);y��4�0��O0xzO6�FU$�+,�G���� :pZ3���Z�db��l�u)g���7sʥ/]�;R���{)c��W�5��
 ����ސ��N�!�*���YrE�(=A�.X/�8P/�
E��7��}�0g�z�H����Y����#O�+?�{��~�{���M�~�7� �֡��B�,��dB������R�z@KÐI;�a*3b��V�A�#là��j�@�9tMK]SH�ND�^s56�YM{�<Hɪǖrj7�S�n10���Zj��Z�l/����w��u��5����\�_t�r���� �h`�G�j���ܰ�$������dΏAH2�|9��v��w��{��{�n~�Fk�����j��\k���q��a7�U���0+���(�5�)��G�g�w	�-Y�!�eh뱄���.~�B�_u�*|x�y��Jə��߬ã)G�i��-�wY���+�-0�>[~2��29Q�I�R��v8	����\�R�J㸂V�2��w���=���]���J���sm��>i�;5�i�.��S�5C�XV���؉�>_��%���a�w�e�[��e9�u���<kn�pO��Ht�
m�����
�#A�L�h�O)��a;5����V�{��U�Y{���J�c�~P��ڒn�NNKmW4�0�T'��jZ��?k'���T���K��x���5�`t2���C1���Ei@~J42Od��yS��d�j��C��3�i���6����%W-�Z�j�\Ok7%�d}`��T#���*e�G�Cis�!�<���Vu���]y����w�<��E��L9�κ�������{��F�����%�cv��Ë��;t}oaE������EI�=>������s ?k"�����T�~��]��FL� ,����������^S����P��Q�'oR�Uu��!*jT�b�#�ч7���O��'��'A[%���?�[%�ɩ�qA��h�����7�B/���i�/ ���I2���w�
v�y���Xc�O �gV�^O��Z�JQ�]܈ќޡ�{]�+�Z�lU\F�.�=�?�9P���w��ܻ/�Ni#�ʻ\��l�t*��Z��yk�n<� }�%�>j����-٠��؊�>7}���f��#+��������Q�4�h�|��	�����f����'��]��R��vॢL��˔r��n��)�y�Pz��V�ż�����я�h0��W+����^�	��E��`����{���M �w���d��R$�OEnx�۔�0��^i��u���?�.��m�84���C��T�N�ūY�z���������U�x=����Q�E��mZ�>���i٘�,�p'�˼w%	י�am�� .J˨\ѿ7_�u��mxL��o1������b���ѩ�I�pؑ�M7H�h�CED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)

#ifndef GTEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_
#define GTEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_

// This header implements typed tests and type-parameterized tests.

// Typed (aka type-driven) tests repeat the same test for types in a
// list.  You must know which types you want to test with when writing
// typed tests. Here's how you do it:

#if 0

// First, define a fixture class template.  It should be parameterized
// by a type.  Remember to derive it from testing::Test.
template <typename T>
class FooTest : public testing::Test {
 public:
  ...
  typedef std::list<T> List;
  static T shared_;
  T value_;
};

// Next, associate a list of types with the test case, which will be
// repeated for each type in the list.  The typedef is necessary for
// the macro to parse correctly.
typedef testing::Types<char, int, unsigned int> MyTypes;
TYPED_TEST_CASE(FooTest, MyTypes);

// If the type list contains only one type, you can write that type
// directly without Types<...>:
//   TYPED_TEST_CASE(FooTest, int);

// Then, use TYPED_TEST() instead of TEST_F() to define as many typed
// tests for this test case as you want.
TYPED_TEST(FooTest, DoesBlah) {
  // Inside a test, refer to TypeParam to get the type parameter.
  // Since we are inside a derived class template, C++ requires use to
  // visit the members of FooTest via 'this'.
  TypeParam n = this->value_;

  // To visit static members of the fixture, add the TestFixture::
  // prefix.
  n += TestFixture::shared_;

  // To refer to typedefs in the fixture, add the "typename
  // TestFixture::" prefix.
  typename TestFixture::List values;
  values.push_back(n);
  ...
}

TYPED_TEST(FooTest, HasPropertyA) { ... }

#endif  // 0

// Type-parameterized tests are abstract test patterns parameterized
// by a type.  Compared with typed tests, type-parameterized tests
// allow you to define the test pattern without knowing what the type
// parameters are.  The defined pattern can be instantiated with
// different types any number of times, in any number of translation
// units.
//
// If you are designing an interface or concept, you can define a
// suite of type-parameterized tests to verify properties that any
// valid implementation of the interface/concept should have.  Then,
// each implementation can easily instantiate the test suite to verify
// that it conforms to the requirements, without having to write
// similar tests repeatedly.  Here's an example:

#if 0

// First, define a fixture class template.  It should be parameterized
// by a type.  Remember to derive it from testing::Test.
template <typename T>
class FooTest : public testing::Test {
  ...
};

// Next, declare that you will define a type-parameterized test case
// (the _P suffix is for "parameterized" or "pattern", whichever you
// prefer):
TYPED_TEST_CASE_P(FooTest);

// Then, use TYPED_TEST_P() to define as many type-parameterized tests
// for this type-parameterized test case as you want.
TYPED_TEST_P(FooTest, DoesBlah) {
  // Inside a test, refer to TypeParam to get the type parameter.
  TypeParam n = 0;
  ...
}

TYPED_TEST_P(FooTest, HasPropertyA) { ... }

// Now the tricky part: you need to register all test patterns before
// you can instantiate them.  The first argument of the macro is the
// test case name; the rest are the names of the tests in this test
// case.
REGISTER_TYPED_TEST_CASE_P(FooTest,
                           DoesBlah, HasPropertyA);

// Finally, you are free to instantiate the pattern with the types you
// want.  If you put the above code in a header file, you can #include
// it in multiple C++ source files and instantiate it multiple times.
//
// To distinguish different instances of the pattern, the first
// argument to the INSTANTIATE_* macro is a prefix that will be added
// to the actual test case name.  Remember to pick unique prefixes for
// different instances.
typedef testing::Types<char, int, unsigned int> MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(My, FooTest, MyTypes);

// If the type list contains only one type, you can write that type
// directly without Types<...>:
//   INSTANTIATE_TYPED_TEST_CASE_P(My, FooTest, int);

#endif  // 0


// Implements typed tests.

#if GTEST_HAS_TYPED_TEST

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the name of the typedef for the type parameters of the
// given test case.
#define GTEST_TYPE_PARAMS_(TestCaseName) gtest_type_params_##TestCaseName##_

// The 'Types' template argument below must have spaces around it
// since some compilers may choke on '>>' when passing a template
// instance (e.g. Types<int>)
#define TYPED_TEST_CASE(CaseName, Types) \
  typedef ::testing::internal::TypeList< Types >::type \
      GTEST_TYPE_PARAMS_(CaseName)

#define TYPED_TEST(CaseName, TestName) \
  template <typename gtest_TypeParam_> \
  class GTEST_TEST_CLASS_NAME_(CaseName, TestName) \
      : public CaseName<gtest_TypeParam_> { \
   private: \
    typedef CaseName<gtest_TypeParam_> TestFixture; \
    typedef gtest_TypeParam_ TypeParam; \
    virtual void TestBody(); \
  }; \
  bool gtest_##CaseName##_##TestName##_registered_ = \
      ::testing::internal::TypeParameterizedTest< \
          CaseName, \
          ::testing::internal::TemplateSel< \
              GTEST_TEST_CLASS_NAME_(CaseName, TestName)>, \
          GTEST_TYPE_PARAMS_(CaseName)>::Register(\
              "", #CaseName, #TestName, 0); \
  template <typename gtest_TypeParam_> \
  void GTEST_TEST_CLASS_NAME_(CaseName, TestName)<gtest_TypeParam_>::TestBody()

#endif  // GTEST_HAS_TYPED_TEST

// Implements type-parameterized tests.

#if GTEST_HAS_TYPED_TEST_P

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the namespace name that the type-parameterized tests for
// the given type-parameterized test case are defined in.  The exact
// name of the namespace is subject to change without notice.
#define GTEST_CASE_NAMESPACE_(TestCaseName) \
  gtest_case_##TestCaseName##_

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the name of the variable used to remember the names of
// the defined tests in the given test case.
#define GTEST_TYPED_TEST_CASE_P_STATE_(TestCaseName) \
  gtest_typed_test_case_p_state_##TestCaseName##_

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE DIRECTLY.
//
// Expands to the name of the variable used to remember the names of
// the registered tests in the given test case.
#define GTEST_REGISTERED_TEST_NAMES_(TestCaseName) \
  gtest_registered_test_names_##TestCaseName##_

// The variables defined in the type-parameterized test macros are
// static as typically these macros are used in a .h file that can be
// #included in multiple translation units linked together.
#define TYPED_TEST_CASE_P(CaseName) \
  static ::testing::internal::TypedTestCasePState \
      GTEST_TYPED_TEST_CASE_P_STATE_(CaseName)

#define TYPED_TEST_P(CaseName, TestName) \
  namespace GTEST_CASE_NAMESPACE_(CaseName) { \
  template <typename gtest_TypeParam_> \
  class TestName : public CaseName<gtest_TypeParam_> { \
   private: \
    typedef CaseName<gtest_TypeParam_> TestFixture; \
    typedef gtest_TypeParam_ TypeParam; \
    virtual void TestBody(); \
  }; \
  static bool gtest_##TestName##_defined_ = \
      GTEST_TYPED_TEST_CASE_P_STATE_(CaseName).AddTestName(\
          __FILE__, __LINE__, #CaseName, #TestName); \
  } \
  template <typename gtest_TypeParam_> \
  void GTEST_CASE_NAMESPACE_(CaseName)::TestName<gtest_TypeParam_>::TestBody()

/* JLBC: Disabled for MRPT due to "..." still raising C99 warnings in GCC (2010)
#define REGISTER_TYPED_TEST_CASE_P(CaseName, ...) \
  namespace GTEST_CASE_NAMESPACE_(CaseName) { \
  typedef ::testing::internal::Templates<__VA_ARGS__>::type gtest_AllTests_; \
  } \
  static const char* const GTEST_REGISTERED_TEST_NAMES_(CaseName) = \
      GTEST_TYPED_TEST_CASE_P_STATE_(CaseName).VerifyRegisteredTestNames(\
          __FILE__, __LINE__, #__VA_ARGS__)
*/

// The 'Types' template argument below must have spaces around it
// since some compilers may choke on '>>' when passing a template
// instance (e.g. Types<int>)
#define INSTANTIATE_TYPED_TEST_CASE_P(Prefix, CaseName, Types) \
  bool gtest_##Prefix##_##CaseName = \
      ::testing::internal::TypeParameterizedTestCase<CaseName, \
          GTEST_CASE_NAMESPACE_(CaseName)::gtest_AllTests_, \
          ::testing::internal::TypeList< Types >::type>::Register(\
              #Prefix, #CaseName, GTEST_REGISTERED_TEST_NAMES_(CaseName))

#endif  // GTEST_HAS_TYPED_TEST_P

#endif  // GTEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_

// Depending on the platform, different string classes are available.
// On Linux, in addition to ::std::string, Google also makes use of
// class ::string, which has the same interface as ::std::string, but
// has a different implementation.
//
// The user can define GTEST_HAS_GLOBAL_STRING to 1 to indicate that
// ::string is available AND is a distinct type to ::std::string, or
// define it to 0 to indicate otherwise.
//
// If the user's ::std::string and ::string are the same class due to
// aliasing, he should define GTEST_HAS_GLOBAL_STRING to 0.
//
// If the user doesn't define GTEST_HAS_GLOBAL_STRING, it is defined
// heuristically.

namespace testing {

// Declares the flags.

// This flag temporary enables the disabled tests.
GTEST_DECLARE_bool_(also_run_disabled_tests);

// This flag brings the debugger on an assertion failure.
GTEST_DECLARE_bool_(break_on_failure);

// This flag controls whether Google Test catches all test-thrown exceptions
// and logs them as failures.
GTEST_DECLARE_bool_(catch_exceptions);

// This flag enables using colors in terminal output. Available values are
// "yes" to enable colors, "no" (disable colors), or "auto" (the default)
// to let Google Test decide.
GTEST_DECLARE_string_(color);

// This flag sets up the filter to select by name using a glob pattern
// the tests to run. If the filter is not given all tests are executed.
GTEST_DECLARE_string_(filter);

// This flag causes the Google Test to list tests. None of the tests listed
// are actually run if the flag is provided.
GTEST_DECLARE_bool_(list_tests);

// This flag controls whether Google Test emits a detailed XML report to a file
// in addition to its normal textual output.
GTEST_DECLARE_string_(output);

// This flags control whether Google Test prints the elapsed time for each
// test.
GTEST_DECLARE_bool_(print_time);

// This flag specifies the random number seed.
GTEST_DECLARE_int32_(random_seed);

// This flag sets how many times the tests are repeated. The default value
// is 1. If the value is -1 the tests are repeating forever.
GTEST_DECLARE_int32_(repeat);

// This flag controls whether Google Test includes Google Test internal
// stack frames in failure stack traces.
GTEST_DECLARE_bool_(show_internal_stack_frames);

// When this flag is specified, tests' order is randomized on every iteration.
GTEST_DECLARE_bool_(shuffle);

// This flag specifies the maximum number of stack frames to be
// printed in a failure message.
GTEST_DECLARE_int32_(stack_trace_depth);

// When this flag is specified, a failed assertion will throw an
// exception if exceptions are enabled, or exit the program with a
// non-zero code otherwise.
GTEST_DECLARE_bool_(throw_on_failure);

// The upper limit for valid stack trace depths.
const int kMaxStackTraceDepth = 100;

namespace internal {

class AssertHelper;
class DefaultGlobalTestPartResultReporter;
class ExecDeathTest;
class NoExecDeathTest;
class FinalSuccessChecker;
class GTestFlagSaver;
class TestInfoImpl;
class TestResultAccessor;
class TestEventListenersAccessor;
class TestEventRepeater;
class WindowsDeathTest;
class UnitTestImpl* GetUnitTestImpl();
void ReportFailureInUnknownLocation(TestPartResult::Type result_type,
                                    const String& message);
class PrettyUnitTestResultPrinter;
class XmlUnitTestResultPrinter;

// Converts a streamable value to a String.  A NULL pointer is
// converted to "(null)".  When the input value is a ::string,
// ::std::string, ::wstring, or ::std::wstring object, each NUL
// character in it is replaced with "\\0".
// Declared in gtest-internal.h but defined here, so that it has access
// to the definition of the Message class, required by the ARM
// compiler.
template <typename T>
String StreamableToString(const T& streamable) {
  return (Message() << streamable).GetString();
}

}  // namespace internal

// A class for indicating whether an assertion was successful.  When
// the assertion wasn't successful, the AssertionResult object
// remembers a non-empty message that describes how it failed.
//
// To create an instance of this class, use one of the factory functions
// (AssertionSuccess() and AssertionFailure()).
//
// This class is useful for two purposes:
//   1. Defining predicate functions to be used with Boolean test assertions
//      EXPECT_TRUE/EXPECT_FALSE and their ASSERT_ counterparts
//   2. Defining predicate-format functions to be
//      used with predicate assertions (ASSERT_PRED_FORMAT*, etc).
//
// For example, if you define IsEven predicate:
//
//   testing::AssertionResult IsEven(int n) {
//     if ((n % 2) == 0)
//       return testing::AssertionSuccess();
//     else
//       return testing::AssertionFailure() << n << " is odd";
//   }
//
// Then the failed expectation EXPECT_TRUE(IsEven(Fib(5)))
// will print the message
//
//   Value of: IsEven(Fib(5))
//     Actual: false (5 is odd)
//   Expected: true
//
// instead of a more opaque
//
//   Value of: IsEven(Fib(5))
//     Actual: false
//   Expected: true
//
// in case IsEven is a simple Boolean predicate.
//
// If you expect your predicate to be reused and want to support informative
// messages in EXPECT_FALSE and ASSERT_FALSE (negative assertions show up
// about half as often as positive ones in our tests), supply messages for
// both success and failure cases:
//
//   testing::AssertionResult IsEven(int n) {
//     if ((n % 2) == 0)
//       return testing::AssertionSuccess() << n << " is even";
//     else
//       return testing::AssertionFailure() << n << " is odd";
//   }
//
// Then a statement EXPECT_FALSE(IsEven(Fib(6))) will print
//
//   Value of: IsEven(Fib(6))
//     Actual: true (8 is even)
//   Expected: false
//
// NB: Predicates that support negative Boolean assertions have reduced
// performance in positive ones so be careful not to use them in tests
// that have lots (tens of thousands) of positive Boolean assertions.
//
// To use this class with EXPECT_PRED_FORMAT assertions such as:
//
//   // Verifies that Foo() returns an even number.
//   EXPECT_PRED_FORMAT1(IsEven, Foo());
//
// you need to define:
//
//   testing::AssertionResult IsEven(const char* expr, int n) {
//     if ((n % 2) == 0)
//       return testing::AssertionSuccess();
//     else
//       return testing::AssertionFailure()
//         << "Expected: " << expr << " is even\n  Actual: it's " << n;
//   }
//
// If Foo() returns 5, you will see the following message:
//
//   Expected: Foo() is even
//     Actual: it's 5
//
class GTEST_API_ AssertionResult {
 public:
  // Copy constructor.
  // Used in EXPECT_TRUE/FALSE(assertion_result).
  AssertionResult(const AssertionResult& other);
  // Used in the EXPECT_TRUE/FALSE(bool_expression).
  explicit AssertionResult(bool success) : success_(success) {}

  // Returns true iff the assertion succeeded.
  operator bool() const { return success_; }  // NOLINT

  // Returns the assertion's negation. Used with EXPECT/ASSERT_FALSE.
  AssertionResult operator!() const;

  // Returns the text streamed into this AssertionResult. Test assertions
  // use it when S�s)��~��@%����gt5`@}rr�ps����g.�AI��0����B�'�A�p���35�t�jW��j���fWon�Ȏ�����]]��c���%���2������wMIh����ܷ��UŤ�OS,�룚���B���˻�f�m���k$���H�$��:^8�� ��䏠�i��h��f�{FMc�_0���y���2.��I���� �QaPfD���TH�jmr� T�=���:�#t=���)��y
jT��
r�Y�*~ �b�#�	pM]s���j듆0y%���F<��Z#�W����_����EC�����[F>nE̋z��K�cJ�*h�Vs�5�'��,D����o�"��ٖO?�l%��x�sv��
+��X���T71�x"�X�l�;�nf3χ &�,V�|�e�?9��+X��t�dO�|�����U����jĻ#����l��F;��y�v�k�pX��@��Y#���-�-��Q:(��ܷ��ن:�8��I��S�0��8�6���Eh�!�31�$�̂*�������~�C�jD��#��5d!�#Tg����|����Sk���h*��gF���lU��}p��J�!7��Q�<� ݨ���U�}��� �;Y)�&h^%\�9�Z���O��M�/�њb�wS�pqp?�JD�m�2�p�n��",KvQWi�C!�oX]�=\��#�5H����ڐ�+?��+U8�J�4Y��Sy����JI���M��Bg?
���y���*��\����0Y�a���|nX����&!1���0�M�S�f�����owZ����W��C c�PSv�휹�㴞Jި�qE�c����x����af��W�G&z#���\�'xpu���>�MPd'��t�y�G8V�����N�����\��wV�+~��v�zH�D0u��C �y���� ��\���Oc���\�1���$�f^
�,M����Y�*��JS��SX0���p��fr}`]V�"���P/;�W�f�P@6^���Yd?�u[��p��H��ͳ�	zj�D(��P��q�X�)(
M=��N�_x��OE�Y_�*4�W$�[�3�
�䚐39� �"ӭ��-�zR�z���g=O�4�[���f��;�%7�1���p*�%�I�O�49	�ɗ�j��l�{���՛%���D�e`��]���̸}���K��ף)=z�d����'�B�#���腪��������o��[�T�NJ�Ѱ7��>%�p��%�4}B�����i�(l�*����Y���7��{m5��U����J\��������q��y%�p�#@��W�#� ��+�c<@1�so��5:�����G�n�Fu�;��u���f�U���ق3w� ��W�)��?r9�` �\��v�\	s���N���C釹�	��z;	��ȁEy�N�DC�㟘`I�M�L�L��_�?�����V;�[�q8	"䝘VO���;��i�;Dڈ�NpK�7+�?�D�qu �L�Dڶ�3��X��A��#U�5��^'<hq��.l��}���O��w�$w ��a��;�V���@^Ak���V'�3d�o�O���9�!e��3�����ҷ*����5��8�����<����w_�&�ƴৄ�O�?����0�&��厥�9t��mr�泾�:��xe|�����⚙�a���6oep�&t���a����������Z$�7ir�-�q��3��z-=�σ-����:���~���q��@�7�	,�"&p�	�2�&0!�J�����W��\{{uT]{%�=w���-&������t �h§Qj�����G�� "��.i�Q�HEh�s\���`ޗ5D:�M嘘J�.M��p
���x*y�M΂m?�V3n���#(�-�)a|� L�g�h7f�M��!If� �6��^@�d��GAD�DtL����ڜ�M�Ͳ#bN��1ϖ�C�Q'&����`|j�Y6����#�"k�6˵b�bJ,"3r9�q:c l��"���zb�Z���;�%�08��mI���8�.?�-��r�z9�w�N+� ��Y���a�R��	b�q�+�]�7yt��_��yLW�	9�PJ�4�����yT��
ӷ­r�I��W�,�>�U�b�Ց?����Qb���B8�`=p]�A��J^����'� XAѕ]u�E�=D]�A�K¢'�}	�ݢT��>fR�X�U���*���։�dq�C@w1��D�vS�i�7�#��CB��a*Ip`��&�\����]h��<��+32`�)c�1�S�͗�H���)�ia��{�l�����=dN��2,}�!5_R����y�^�%3#�K�{���"/�����E��Ə_�����t���0��޹�������j�J�ne�����#�xN��w9�y�x:h�y�_���7?ϑ�x"�=�Q���Y�a�Y�BϺ�7�ꇍg�6�䢫�j�������(
G�� ��"���$�5K�ݚ��w����U/	���>j㛿��9�x�ְr��s����������+�r�w՞��X�G��¶�����j'�:i��O�İ'~�Հ�i��	�P�kk�w��j?��*n�$��MA�}Y@�K̰��	���P��R��Y�\�oG)���֊�:���]5�#�U�/'�<g�o�hP�¥6�bf"x��	{K+B��5�Dz�.�D��W�!e�<iIO�U?��l��O�,����կ��z7sʉx��Ԯ�g}6m1&��J�n�'�h7���ؗr��T6/�����|PY=��ͨL�9A�Q� ��8m�����4���_��1���?�I�I�D�>������N&�!>�УSg����r��K�S���߀ɨ	ܴ\w�0��iIxj�܏yR���;x�D,�ǆV��y�R�g����,���%���yR����������%��k����5��h�j=(���`��X��Yϯ���׷��SYsRKQFP�$�Ӭ�A��Z(a�ɣ8�j붷�j�=�;>�Z�%ki�;?��+���vN��7|0[�P�A��K}�za�Y��T��j��/��4:���;x?O��0�ָ"�����s( ��l�S��F�IyD�8<Ɵ�@oZ��xsk��B֕����
mx���kc���<���
Nf��af} �*�
?��z�P1{<t���.�`BT��}:�}��Z �=��`b�@��p��^z��r��~>��}pmQ'�����b�c���q��0��]��6�O*�~��lz�������#Y����OⶰSh�Z��`����M�	s�s��i]�?ǿ�O�)���~��԰h��G����C���c]�����>r�}/����X}Q��h�� �D�B*�������2
��"������������Y�Թ �z?�~�m���}��|��́&���}B���i��F���D��)��`���o���j�4o��g�oE�t�[ƉNyIm�s�)�"M�1����
��^��.��9��/���&o�A7��}��!Џ������4��5-�xʡ��C����Eʡ<P��n�@��_�G�s���}�H�5�n�e/�ċ���im�(�~�}��#���4�`�!uJoh�[D��օl��J4�����۱�ۭTn�i]K�֭�6Pޜ��0�K�Wܝk��b�[k���t�3�A���*�(c>"��JD��(�!�_#9e�u���
�ѳ����_��O����	��:M��u�}����� �۽Rqk�FO0����C��i�Hu�����77�<��
���6w�v��+Cl�1���zk�:�5�7�Jp[zKl����ؘ�>i|�d�"uމ�6�ܻ�Y�?=����3O<�]9��p��zW�e�����f�����'�s����u�����Ð��n��'�>4۰:⠝�2�r�tX�*���,�E߫5q�oP#�y��|���~E�6�Y� (b���	�Ȫ���h�1˞��N�Nh0�읏8���yRrSp�pd���x]TS=�`GrB�G�\�z���P*��[�7�'`�^^�*��w���Z��q���{G�ϓ����P�B�:����3�2��Э��1<�`�v�\�2w4D5gI�������
6�F��cJ�����/��lh��k�9��i��2�yfPC��f�!�����<��r�/r������C�r�_եM탭J���ɢ�oNn��3Ǘ���yc`�{&Z:1�=o��t<�9+b�FP>�rW�|Egm������<B��5}�����`Eo��`?_b��s�2�d��sG7FR����D+	>���A߄����{Z &pQ����"�������o���K�<F����q���.�+Ų��r��T���\��R���T;�k�.�k���5�ߥr�M�\���o�N�;�nJ��FW��$�-Cm�w+ׅ��4Aʰo��K���yM�ֲ��j�S4�	[��0k���)�!r͡7urͮ7k���Ik�}1�p������TI�&�B~TSmy������?�5mXQ\�`5�ڮU���7N��[#K�}�������v��9@�r\�H֋��@=$iax�)�'�)���bL��	�#�e�{f1�c�B��.�Q�ͮ�.�]�
�@aw�p�o��n�{_k�r�:�yJ^�L�}�&��?U�񰔘=��=���{Cg?��ڳ�E̞�wD&�b�v$��e��� �'�l� ��S��zE4����+Zgݒ�m��B��>0��'a�nroɝmBwF��XҺ����=_���#)����X�>��4�xl�� �i7�FA�gՁ�zO�@��1�N4�|��l+D����|  �ެ�9� �M����x����FuOE���%s�ߦ��2�;�;���]јy�j�Σ]w��y��S�#��Tv���D�*@Z~W�>�|�|�F%�W�F��\�Z���[�ݓ��}>���nRg���.�w>�:��W��+���@��K2f9��ʭ�GU|�P'�ws�*�V�W��Re�?p��Aת��r+ds[ݬw�ZV�圍��U������k�5�[t���ϫ�MwFU]��O�S^�����T^�;�w�d�^c�H����0{��qEu�A��������`�ș�%�YU��GB#�y��f��խMz�$�,}:S�U1��������^�.Q;��ȼ��e)�j�%>jsQX���Y�ܥ�2�y&�U{�7��γ=9C��w���Y����^�����6��yݮ=����BmH�j��U�ƅ6�u�t>�Ӧcf���jO�-��Q��p���k!i�B Q�L��sƅR��q�h&'���03󞾢#�G��zq�^8'��*U��'S��������P{[���H�FUyQ�Wm�����uY��4�7:�HM�k��A�i%�s�B�6�Z�5��6�p�8�HC���/�3m��?��o?����stH�������[a��ں��Li�@��pGjK4d�59$͓��{�W4�_���=s�x����c�J�Ow�	󊠻f9�e���S��EN� �%o���v��K��ʯ�[���tkCe�i���Q���$�,ⶈ��_r�[m�R��F��Kէ+�H��m*Y<.$A}�Ұp�|�4t�0�4b5@םkN�Q5-t�SV�Ұ����'S����@j����������5�o,e�!�X�0�G��\T�ԣ�5;:���Ab���#f�&j���4	�����m������[&/ݮO�ap��Rb��y�	ڿ����xC���RzA+�]��)D�󕖝��z�Z2��xo�u�а��������Wt�O�^وg�{�F~�A�j��V�9���E�y���D!5O�'�����`<G݂�y*�9��H��N�T��h�a�C�L�9s0Ex�7�����u�h�"�;�{9�QՖ6�f\�v��a ��At���ɻ��f��3�����N$��=�S�-�X}�q���=bg���3�Z�p� �m����f�~&�@�0C`�׊�)�� �1B7\�t;���d��7�-��)��-���0�:lo�"���*ɣ��A慽i�O3�&z� o��.�@��9��y(P��I�(��SN7���XB2���F�}NzCԶ��6w"5y^Gff�"�^ȮM�G�3��b��\>�(1%T���Z	A>�M�9��}<�Зh'�JCU�tx�m�3�f,#��EJ;{���(��LV�4��$a���]>��ݿ�����3j]����>u)�TYx�x�&��P�!�� 	�w���'뻏�6^ �t�E��h8v��y���R�Dk
t��_��x�����å���q'����5�<��r	���Ff#6Vg(��\�ڷ2��%���DJ����M�l��=��`#ղ`��[�*�5WW�4Ґ�5�4��Rln<��x5e��X$].*������j6��y*�8vܟ�uܿ��±����H'�N�D�H��#C�}Zx@�4�{@��%ZJ�޽�{��5�+���%|~蓰\U3^'�btVS�{U��@�Hm�9,k�\ߚ�V�wP�s���w��_f����Rw�W��5*뷇(;���u�����1�v��hO���so�-Y�y,Ⲹ%��F�=�7B�����~r<8_��p�l�d�U��X�����Ək�.r �{h��]��L�GÏ:���h�Xo��eFs 5L��Z�
;kȂ�lA�*[������0c�-#ҷ�kN��.b�����޻f+MU�J�Z�W�����I��Q��Fb�.a��4^õ���czeP�dXM��93kn��EP��Cl��U���l}b���J���_d	K�85^9�4�-[��+�YF6*��v�i������͹,�tr%���&i5�f�%y'i�[�������a��n�mW3��a�)�����?z��N;;M��ypDr d���FG�Kulԧp�^��ǫ��%��$1{�r�M���*�~�������#ɿ�n�	x������H��*o͵X��%H~7���|uN��W12dM_�2�ǧ�a�2V�G8X�ؾ>�떎��C:R�	����0
��%uI����xy�.1V]9��[E��%�W��g��[�N*�S<.q��O�<,� �U� �����,mY��	1�1?��nv �7-țI���i������������|�Z�?�_�韟\E�m<[��B2{�&���o���y��������P��&$�]�\wP.�	�^e�+y56�y~��ݘ��ߩ�7x���<K��9-�w0�5yV-}�[����3�;��N�ؚ������>�`�d-`��Xn�=�ԐyZ0]XfU1.�.�m����-E:l,��7�	
�)?�ET�i	�T�b�SP���y���ųtO;J$?ӂ���X7�I�ݤ�lB�Z6G�����-�P�"�y���t�X�>T����la�T�O�zE�C���Q�#���(a�*wcqFy��f&@��HX��4�ƕ%٬�Wh��ݏ�=l~� ��TPo@�&J�e���� ��ʫp�ȥ񾇧k9z�mZnq�Q���h����qjؙ��ř2���V+�~���a3���-j�:����o�J�!��K~���ϣ3l�ʑ��P��<�b�D��¥ҋ
��*xH͹hL�I15�Q��yQ��;��"���\4g��GJ�kӟ���*`�����%MxE{Rɱ��"��0����P���a���F�P�ΨE(ar0a��$���xϥQ·�I��;C�[�oJ�[k����V�������X�<_�Z(�z��<o"���#o�t�ȁ�>l�������)y�/�IPbD ��c�)��ݴSK�~�Fqz��U��c�Rؙ� O]z�%��z����G1o|[u�g�~b�Ϥ��JP�|rs8-��_e	�_[�.-�K0�E|���)�l��B�>���^L�!���׫���nB�x"�kdk��+�`����q̻��Ç8�e>�1�!�\�Cܑ��Vx��:ě�C���'Xԕ�U��Ռ�0��b�ZAycP������,�OR�7G�;��#��i�D.�|m2_⳻�?-@irp7�h+��%��^�q���S� RU_�
R�h�C�}�(lj�F�M�H���y��O�蔬팏[�Ә1]7�����-���MC��&r�~"M�wG�����B�t.�����'�{̥!]Q+u:+Ruө���h�)�N�n:ϔ^eM7�M�S�(��$w�9��OsX<M�C���Sts��s��,8�O�_e�us�}����L��l�J᳹�?!X�T�R-m�Φ�~6�l�^�����b$�r�s�/�Q� �P�&��`)Q�gG�����G�y������d���d��J�=ͷ�$��_H�3Z��60|���ΉC�1��<ݍp�I�}s���1kK�$��,�kR�[u2;�Q��~s?,U��$�p����<J�n��
��_��J㏈/B޿�a�D��I�T�?���&,��6:ugL�r	f������� �6�X^���֖z�3�I8���5+T�<q�uVx���N1�LY>;8^�tF���.�f|u��Bk`'-^Xyb�+�_�Eq|���I��)��P˸�7f��qr�P��^��Q�i�_��<���l���`�s�[���/��肝O_��*��Ė:X|���j��>kԹ�e�A�.7�y���x����E�%}�^�sD��B?��k�OB�V�[�����)-f��	r������ί�
7�3��+4�y�hx��7+#���%0l!��],�g�ޜqF��[��b���	D����v�Lui'"5P�w-�8n2+�0���1OJ�{Qp's?�1�~�!���,WF�"郵�K���[:4�M��hX�x
��x�����@����G4�(B���ʉ��"r&0+���OpC��(�����|����z�2��Kg=��<T�f���KrbއN���a�vIT����{۫R���X���b��l�Q�I:�����A{���Ui�ד��0�y_�Q������~(���oj��P[�01�>��W�+6��p���_�?�����Z��o����	9�E���m�!��\��t+�����O�n��7Z�)��Q�#�y����Vc���Pl]$61�J���<r�xY��5�{�h��W�q�.�ggk���s�� ;���z������$�.w�+�I���i'�+��\�2z^GI�[�1o��i��RÄ���,�����v�ja��W����io��
7*F���0�O����ϡ�g1��#�]]�z���z�9\�N	�o<��m�4��EQ�c��)sj��x�z�Fscz���!B�u(�@]�'Q:��7�Г~^����5�}8@���~ �`Q�z᥮ٚ����d-Hi��i�|�9VQ�Nvj�E��6Tk��^����&i�߼k�$�R����L|0 c@�EQ�K��B����D8'��$r͞�F\�kl���=����oEə�*�|��>~̐���٪���^�ϖ�e�{�����d��J���L�	�����7O���F!�o���eզ̋�دEG������*ҝ��3��N��`���8��I��6H�Љ�4�4�%K�ߟ�#�<��r���F�s���{�N>S��~���0&����w�׫�z㉤3�5`����o�a�C$#:�:��H}	���&�cl�̻�iT�ƛ��DM�xX���:�<�W��[��.��O��=��^eJ����y\�h�"?���]�`���;<�3Ǔ�d��"�5^"d�H�}Sgub�eU��pd(��U�f�^ќQ$!W��|���r��RǪ�ۿ'��R�QMT�8fb(U��~� U_b��/�5 �:��I=�x�1���;M@��i�1;pT$�H�Nr��P��C��.�,���´�A;��,������>�$��#���*�٢$^�/P��T��=����|A.�����A���T�)��{0��5	�v�����m���qwL1�8�+��䚯,=M�.wW��u@MV��1-i�'��!%KAN�z��?4-L�Ϟ�f��b����k���J�3� rV���ɰ Ƴ�����T�|��S�{,�D��ք�%�Cs�?ڋrZ'R}��k*U�>�F����_
QyI���ּ�LQ�7�wG�֒q?��2�EZ�X��ƞ<K�7xB�S�L
��Ddv��_��^��L)�B��z<�׍�N������x�yJ�JӐ�ta�Wu�{�	�ܳ��¤V�C��	�����/�����hi��� ������T��\��v�`������I�I1�$oF�Ԟ�2_\��?�8�}�>��`�b�����,�Ҙ�����iZ��CF�p|�H���4,9'�Vw���3^�Dy	7��3�8.�=@������'t��O�=���3T|�.��b\f�\�j�W^�Tݷ_]=͕�t/���<UB��j�{���2���e:���«'������|������2��D*N�[��;�
�ʅؒOh/D�c��JT^����>�q����������'o,`g~���H��'��X�k0ި�@ ��H+�һ\"��W_p�Ի�3����ı��R&�wU�Dz	��%��Ex_���\�n�J���Ȫ����U�Rb)u��yp�j���=qM[΁=x���[�1n��=���@?��g�³�����߽
wm���?�䔓�yj�3�`���T����eLW:�������`�����QE R�e<K0���F �t�?�����e�2���sf���[��]|���QWx+\�JtzJ�G�oҋ+���1ݾ�[]��,���3��n_�O��?��?��1cxj�@�>̟���?Vmlw��ƨ�n{�\s���J�N��5��V�����ϻ��,1?>MÚŉ4��D!S�9�%�\z�-X�&�i�n�2�	=�њd^["����zm���fzjI�e��w��Ǹ2�]1��������g#�z��c��*p�<��`�6�zq=-�����9ޯ�����Œz��:�,���Ø1�!z8����3���h�SJ뗣�ֵQP���g=*���Y���lf��HW���R�ϞY�s~��X{G�jҚy&����>r5��e��p�2~D爁��ޜ�̃�x��ꗮ�]�Wt�u���o�������?�ᇒ?���X�,��� ��y�1�Z�����1��ש��!�;��nAM���T1ZcUkT|pjÐ�s��_�ÿ́oR��h�p�������[t�?�P�:���^3r܋�0��
f�hH#�����:�*>�W����>��ҷ �_h�{��_!/x��Q�JG�^ \(�����C^���F�ؐ?��3'�<�Ր��_B����6����H쓼6ڰ�۱ tt	82�"��px�V����}��ϰ�qx;wr�٢��(��G��X!x��N������*RH03���<uF�>���>8��w��w�H��0�v��j��&��o(#���+8~��9���0�b*������x�����*����olO���Δ�ɟN��FMО�G�3`+jg��h�yKp�/�Q�W�'�t*��e�b��z��� Mۆن:�aCr�4�w��/o��Δl' �֡�H	Pl�ހӷ�����ʒ-�,W,&?X��VI�k�x
]�mi弖�-������(v�r�p�2voz�;����������f�~з����4#7�yk�\�]|��{?'*g�PK���F��w����������u���8�[��`L1M��^4!������	�9z�}��mc7b��2�%��<ñ�H|Q0�d?`b��L��(���� d�B䋜����c����{���(��{5u��Sʸ��,�m��ors�2W��W�}D���}.Mh�ʹ��.���Ty�"�y��М%K��%�^�y���<�.ϧt�"J��������Dʳ[��e�FW�/%
Gַ,�䊆�I��:+ˎ����z`���v�>�2;|bm�TD�����|W3��RO���[Yn_��9>?Bϋ#E��Tne!��f���RSp&+,���3Z�.G�K�@��Qo�z�zm� �߀��4 5��o��c�$��D��b��H���e:N�;��v�V���[;�T�Og����{��Q���zߐ�V������\A��h~;�e!���7�/[7��������v7��K�h�`^6,T�4��|Z���/�*����"j́Cj�-^���.9ǉJ��V��7�qV/�e�5�d��¸�w҂�QḞ�ڴ�>J�QP%����(����a�Si��_؁0X��_ư���h�}����r0\~U�.����C���O��?iX�׼\�a��B;ف�$�.�*��L�e��'I �6�׷���=�jP�kb�^��6l�\|y�U���;���>
�"�gn�|�s��X���$o��L�����^��c����T�P�]N�S� ���~  ����r����o�f���^_$����Y�}�$u.���?(J�H�_!�~���R�S�(�?�v��.'�E�V����7\����{�)��Ҏ Z��a �-�#1�L�y���!/g$�,;V��<��X^-)�:�Ǳ��6��Q��r����; k�̴�����(#J��CRvq}�p����ǥb�@s����^�(��G��t>2��&"f�2'���ʲ�:~%�&��Zp�e�w��#�X�ᩃC͟�5�}*Ĝ޹�6���i� ���i�0��U���G��:�6�����wJ;i0�)k�D��b����0<�E�,���b,����J�I>��t:�D-�nR������GL����=Tr�!碦�S$����mӉ�����Ӥ|�;�&��%����1�L3&
i��@���Ø���ƸO��$ke�N&�6kDr�k� nCO����Rr"��z�(�*��G=b���lX���h��)b��`B6�U�u>����	U�-1:��9I̾�	X��N䛫M�G�D>�����Lb1��m��@�(��mM�����cI='�z>i@������C
��d�sݕd�uu�+JZ��'�K��Z�OM��&���TE��;��ܬ4�}��r�.`6��b=�ΥRa9V����>YD�J.s3�����{g}�^'y�AD��T�r�b�GH���m������� ���İ5���b�ﬅ�S_��u/�wQ��*�,��H��L��x���O=�����ʆND��)x0MG���e���-ΰ�h�P�����YV�$���);�K�� ��&�����Thz��&��Z��4	^�YVNļK$Ww�|󉽐����4�6qQ(�"4U���%=���B��U#x8���b��q[�ny����	r�$**���e��p��g;Ⱥm���$�⊖�3�z0��x��'ֻ����Q�>�[��(Nd�W�c�:i�y�=��X/���Q����z^ک�\%��>��-�-��Kn���`�<�Y�@�7�C�ÀJ�7��oAf8oZ@��ѕz6^�ȓ�M�vt������0�Ո�1�Ht�\DH��������+�<�~?�{z,�B;�4J�/�q#f�h?�b@z���@6U�|dD��>a� ]+�l�)�*Q����h,,�Llw����j�1���^�u>!%0�����5��G�KŴ�I�_4���7/L-U1�e�0���#_�2�s�TXa���y���	�+.�h]z1�ֻZļ 
�W�_,�<�x�?n���G����s[5��09���qX�U���g\��P����q�ɨ��'�'�en��0�Bziy��E�@�& �S�**�� ���#��R�~ "�\��'��Ϗ���d���p�-<0m�� �=�W�Q�Z���vج��M���:<N,$Q�J�qYq��`�
�W`��*/s�ǉ�}�a�!�_s��%TJ�����f��g�.K��[��)s�[��3��Jd��g�zf�
�b^Ԡr+i!U��hz ��� #�w+����0�]~�1.x7��a��7�5X����"���*,�����:�[���KM��a-cp׫Ǯ�Z�yWTR���u��$ > ����ɪH�	��'�V��J��[JEW�ה��o�	[�CQ⧀fc�#縏��>�!����My�\�_���&[����;�G�^�w���Wǥ�_�5�d�J���W~*���AUR>���<�-Q?ۻ��$VSFtJÄa}� ��*����?<�pvIvdᵭ��ߜSU�]˅����ɠ<U*��$_�V#9D�5iU��@SD���m��m�9������&��|Q�>~.��H��")����� 1�}�'#��$�{VMc�uU��%��.6���*��#���OC� z�*��C�)�ZYR�ݫdÍ�l=�H>�L/�ן8���_�sHhx�c,�����B�)�H䔭f���J��dC!��bIk��h{�0�:WH�N����z|��Rn����ߜ����ӳ:�59%�ص�Hݭ��
�Q��	���.qM�{Q��**���k/ ~t���;���> r��Ѕk���S���'�j�Z��=����w���B��ugm�oj���P��:���:��$���$l�(�G����� �����>����ZZ��4':��/���L�g�Wk�0��Q�Zq��5������__ ^BI@�	�HJ:�Ɏq��<T6<�g�g��ȗ�<�����J{Fah5�D���u�(�#?`�4�b�Iea;(�	0�Saބ2�)@���ڿpnߜ�l]XK9��?����lt�ʹ���S��9-Q̣ ��a�8�F-� U�f�&�NF�&���1�&_}��������%	��s6r��w�D�K�Evߠh[Y6�2}�*�g-�M �/Ly�4��B����_}�WC�\6�em�e+,.��>j��6�Fu��r��D����[3��z�?C݉�ҋc��.�ѽ䋸�o��ِ
��$(Ra��ӗK1s��6�>��[Ջ���$�FB���g(YS�y�� �o��`TO�w��w���<�P=cxUR������hȢS�\����<�g�I,�Rv"��-"�[��#B�z�#}Q��Ճl������䈸��8��4RE�̯�ɶV��/ p-/}⢞�P4f)O�G -��2��`�$[������}c8�n���F�7He�_
	�?�������8��h�X��)��|.ŕIr%�F�$���3|���U�I��Y���Ѱ��&��+[W��;\|;���.��u���H���73l��?�<>o >?SE]d폎�;a�|���x\��������ڈ��J�r��������O67u�@�1��κ��o���9k���|.��o8��K��g�� ��Xi^X��A{�=h;���B��md:d�� ��yf��Zkd��w\]ɹW��$o�3���堑X|�URG?�C'4�����xڤ�{`��8���	ΊAc�5�ࣲ�Z�(;����(O�64��Z��+��مL�E�>h�Zm��V����6	A��C�"@�d��{gv6������s�y�s�=��s���)Yuz�~�0u�'W�{\��>Px`�? ���!O��񫻫��%a=�˗���ķ�����0IN<d׶�h�)�w����|������?XՑJ�� �W*����*<i�3|���|ݝ�T�;���%�=��?0��W9�;DV�#�*��)x(_n��
&���;Vކ@����㑔#�_|
�l%�L�K�����m�������pw�*'� T��}����K��]6]�N�����Sˠ�VY��@N�<n91��%ǝGRAv��*��+��U-���d$&�
��]#��6�;V.i�ǝ�@����Q�cl�y��>��Ҟ����X�Ãd�z���w9~�'�|�0�(+�fԪ�����C�Sػ􇆼�z�hUdb�ㅆI�:A� 6T��4~�R��V�G.H�wcbԴ�Z'�4i� ��T���RI��;fԒ�h�j���*��e�9��i�I��$96�%�߁h��M~�xd�����>�&I\P���_�+�_����wIwJwIw�E ��`�wN`�E[��@�M�&M%<�����+���b�ĥI�F9$��A����Ї@(���,'�K������8)+U.�PK�/9,ǳƆ<0Z!��T�-Ǫ�j5�%F�ِo0��U�~�,X2�?_V?*u����5�6����%;ea'���3�SA5�.��r�m
v���k/Uݑ���`t�u$Bo�`���tO-P􏛐�\�@$��\O8KV��z��$'c|�`|P40�S&�W,)��  �4@�P���%�g7X�7K6�@��Gv�Yn� d 4@͓d�Ȧ� B]�P�r$��>0ڶ��L��FjJ������/��~�$)�e��/����˰��ҋmj��#��p�ǖ*��5Nӆ�!M� �E>9����K�϶��*u�;�#ǃ�>�S<�㎐z IH����Ρ��U��jb����1t��	�`YI���{2;_W�*�H|��5!|��Ի�[�<g��f�Aі䄁Rr t\95�����{�V�Y��v����R4w�Sr�v9>ax(~s�����[X/*��~��n.��o;YZ�m�!F_Gv�:��r����J��Tю��MϪ�G�xJ�}�a����TMl��Z��$e����m^�d���y�B��eM�-	g��x�	���+|9��v�ag��yP�2���_X��l���o�q�p����p��qe��bO�A$;���؏_r�VT�l�M�	9��/����3��Y� ����9Ɋ$5MW�@lL�YO�P�P���u�?~x�|9�S�~H>qt]������(��	�ЈzyK�:!���7�������w�$�]�P��r��%+5ni�����%RyWA��㽊
������W'��Ueǎ�R�
�.�(>���]���	�.`�R�u'~��Pնw�v�.�V͸�6�	D#��j�\�mB��f4b�������~��/%�a���z
�ټ��-�M�?E�a:�cӑK�X�k5}̏raY��s���\�B����d��i0n{�|�b�]&?�,4�m����Z�º�]n�s��kD�'љ�v �^��P�&`��r�s7���&>��8|��<�b����4�퇍��>�[������?��a�O��e��*1��$E�y�s�]��r�w��5E��'��G�q}3�m6��O�@b��gN�ش��)��Rq�~�����עء���x� ��w<x�~���3~�_D�N$�
\���A9����o�7%�BRW_H���J�0������(�r�ۻ�%���<-rb�O�^M��.da��x�Ub��av����L �`��;@>vj��:��q��=��pZCg"8�8�K��k�Һs��D���L���&FW!2��h*�g�B��wة/���tYz�P�j���\��x����B[��)� <�A���+�Ε)*t �]Q�!�L���\�-./��X�t�-F/�ĥ_�OIA���K�� +En0f�_��&
0�'�p��hSć��;�_�h�s P�^�8b�D��O�r�sd�v}p��+��tR�C�1�Յ#U}S����p5�"D��6��%��9=ra�T�_��`k���cmM�i�ʳ�8�DU�9^�n�qF�l��0g
�h�����kHj�8��os��F�>�ّ���E�<������:�[�C�$��Ѣ��G�֛��e�B�! �.�a��[�9�X
��"�ye��w�ŧkd�p�;A9�5r��ߍN���f���}N��t��IIX-�'%�5�A��[s�����N�c|.��yw ��>Δ�|}
��= �7��:���� U��_8��:G9��Uz���;a���+�?v-�3)4S��m�˔�n1ZI�� �p���#=L�ؼ��1)���^6�������P��2������l��]�?>=?1��c��������b4P\��� �;���i!q��q�l`�Y��QS�-���CO�2%&g������Ь�0�_Crc>��5�Uou7��[U�_@�^���XgsPx�х#=t&<��(.=�LB����g�q8�����-�DD�|��vY���,���������Ʒ�z׍g�	YGtnP6��I�,��m���E.[�3 W<��b+%�1oG����3��񉣸@���{��N+@�a���CZ(��{�0��%�G����B�	9>�Ɉ�R��Q�w��3�Ar���d]C�&��"�i����ȇq��7nm��;���9=��s���2@]>��y�E��ʳK+:_��K�%��z�Я���JY�7�Vq��N��k͸��Z�+��	�|
�ql�j!��t�=5�}��X�	ĕ��`'�Ҋ�uv�v@��Z�{"�5|����:a9[�Yֲ���h��o�$�#Zzǚ�:.t�j�'��I�ߓG �u�Ю���lNqaf O�"�m%^{^0�1qe��9J�_n+˓�?}��`gIk��N���e47�Z ��� ��b)	&q��F`m�v���`vΑ �^K�D� 6�2�5�ME�Í���v���6�yz q��9J���	��43����	z%b�"��@��:P��:�a�eE9" Q�3 h�&C�5�7eq�N��'��9���?�Z)Nc(W۪n��Ҳ#��j��ĕ�E�1K%elY���Ʈ��Ŷ�u����m��/c�Vb���;�c �M���3Ak�e�6j�U��)�[���V��@��W�]�+$��U�Jǀ�!k����ֽ�5Ya�qNgk͵�ƈ�VU�B*����0�U�+��*�'c��1�J�Z]Z�m�ö#<^\٨t.*�"�����%�!AbLA�l�B�!�4���s?�6�����/�uO��{i�ԘX���궗6�s�r0@�z� �Zm�e�PO?��n�+s%0���w�����v�û%!�b�a8�ĭ)oUlc�	>~H���jݥ֗�G���������!0wP�>�D���/scc�%��;jM{�z�Z_������"��ap�g�*L^��U�gv;j��������ه�>��a�|pNN�8H��h��	�������$'���w�-i(+�g�3⊼��;]�𥉉��jY9(�+�,�����?,�x�k�3CL�︃?���П�Nti�����$���kQR��6:>q^���5�N��d��NF��+`rk��|��l�]�/���Řg�o�Q��֪r1�"4�ڪlc�vR?���?00JmV@=!)_���߰i�zZ�Q�_����q�-�VlB/������C0>Η�$�%Mm&��H�H�0�%���f�C��D���� �2_.��-�m�̐�(`�Kۓ>������R�F��N����� ��\rȯ��O��`�ۑ�n�p	?���.F�A*̞��v�_� �1$��L��)Z �"g��+��i�cI9�r���~X��8{D�ܕb���8�֏Έ�	��'�O'������i�'��G�b�A��~<
p��c��*e��S>&����Q�����}���C��#XRW>�>@\<(��0Z�]ݖ���r
�C`��,�-������6P���|��N1�������n�b�j� �4'F�!� ��)L� e�j����QVl�s�<��W�c��'8@�zd��2�CWqq��2Ԛ��� I.IIj��l�՘�|�,I��H��`��l��)�RN ��Q��!�Tc;e� F#����Y�MJq���zXU�ӎ��Ү�2�#�x�R��`�6��߃��|�z����=.�V,�8>���8>��S���gvq~a�A1/���t�Ȋ�NR>pl\�L5�� �p+��Cl� ~ED��ݣ����AP��4w׻a��ubhǫ�:��re�ڀj�Zk�I1�]�~&�
 T��$A�@�]���c�s"��yӤ}��x��k��ca0 9UE�z}|Z#���"{%�d럜��8����p8��N���s��ʹ <����8Pb,m�ߝ0��=�7;�H���P	�@@ ` E�<�e�y:�~�	>N�����_@Pbl	!��2@*��<�,��P\Ine�C9�sZ�M ���Q�i\���@x{��JQV�}a�@p4�2�A�y��#H���	��Q�>HQ�	|d����yF�w���֗u���gQ���؋�PH�S%ˬF�?�%�����%e�Q�_��3��@�@���8޵v�xGz����_I�M��!���:;����m��N���j�A�?0�m��.�ZR0[�Y7q�̦2cE�!���TH�5�7m,؅���v�n��1��:#9�#�D �۔c��g�X�77K�R�~�^�a�s좰��H��Usط��!ؕ�s�ʈ�����ue���iCX��]I[�/����*���k=�����hc=/�������6){ە�� f�,�A>���o���Ş���N�7�q����|��eʷ��`ie�JI��[��o�f�|�e���ϙ�?D�՗<+9��3�)1y�c(˙|?�f�N���څ��B�ʻ�K5A2�>B�s�N�6������O�V
zd�ف�>x"y��˼U�Bz��vA�ʙB�^�^">��v'�#����<Zzq��,�^�GY� �5�S���Z-)�|�R���pI?m^�	!3:����)��H�{���;�	����� 4�o�)�j���c�A�a��l�]�Jq��ېn��>���ZM�TDX8ۨC؋A|�h�`m{Q��iԑ8��dv�Y�Y�Y'"���8�J���x�0|��4e�����Qs��#�B�ύ����X~��iğ1��o����(��W4�ۚ6��m�~I�?�o�'�@,��g�k�����#����,O8	ƀ�*��D��?ڂ�l�V|�)��z�O�P��;z����ڿ�W�����7	:���/�R"uSh2��*�;�h�&s���	h�h�y|�46�!=ǥ�����B� ����V���4L���1��$1�)�{�y�A@�W?G?V����@C)�~P�����p�D��Ք�O���D�Qss~�b��=qF�Y�1�3�ކ�p\mQ��U�G[�3vT�p����V�>�(mү4�f)����6�D_�\yl'8sÇ�c>����[ɇ��m".�*p�~���Z�B�w�u_���*��9��q�}\R�����2i�-npOou�y($���~�[a�Y!�b�<��#�_�ϧe��`#-�n�-��l�9<��1�N���H��P����"�東d$:�&�c�թ�:�M�Lff0��k����e@&$f���Vn �J�2�����1���JC�iR�>�ȠzR��W��.��T��u��fh7�$q;��wv.w�L~*F�Eـ�j���Q�,b]���V���Iަ՘�_���_�����bb��I��9���Db�>8;�w:�c�B�k$KN����b�"�nN3�v�Ha$��P�	8.��@�m�U�	Gą̪�e���Lb�b$���h�k>��ܠj�aF�c�*n6��vM1̱CH���[_X�d'�����E@X-�n=���<T�H��h�QtaM�U��?�����|%��������h���эk͞v&�un0ē9n��D�v��h��66v�C}l7�GL�dOc�0,���|2�͏Q]b`m��X3��	��6S��]Vh�0-/�N��]}I���@_�?lΓ�&��6KS��X���$1z�[a��5r}Q���h�{Dv���Y�p�aC�lB���͜���6Q|S�h�Tm~;��X�|�Q2&o��*2���@��	�b�]�J�?�F��Ąb��̗��*�Õ���[.���1�0Î4ݦ\�3�O���/��"u�QاvQ��[�uf�a�_8��E|\�487e���[��`G9ԫ��8w����h�Q�J9��Ѝ��pZ���}��sŧ`��#�r�Ru���Rz� ��+� ��)7�����/O/���e.���L�W�T ��9�m<VL�����^&��ך��mwfܩQ���?�� � ��1s�!*J��Vz: 5������<i+�ͮ�F�2�Q<��n��n�qA�^����ڴw4N��1yIm�yt�~w��s�����ޓ��}��� +3�ߥq��te�uf�۪#��,�[�Hq����b -Y��i���$��)�\��G~����)L��&P4
z�g;t����du
�p7�ND�u`]N`�3%U�*�.�2��-��9�ݔFc��k,z�b������<���0&;���|k��'Ѐ���@���Q4�L`����f�}
npځ�&�1i����G�anw��%@�f�9� �S�2c�cԁ�� �*�=�!�9a�!=����ߥ�ρb ����+�.�<�%Rƙ��?&ƣ9E�8�&'�L,`��É �g�l8�q��*���u�"�,K<��������u�.�Bz��r�����2�L7�����������,����_��>�LY�ʍL�M`"�y���S&�������H*H���0�  ��f���/��~I_�g������}�����O��L�1vi�����5�0��ߦ׷�&��=��j����X�0�GH$Z	U�qBG�#ug�e=�o�W&^�\��[ G�A+خB���mC���&��і���;L4�~JC�8�?��W�]ɞ�G�D�'v�`!c&߯P?a���k�.��t��gt 	HJ��Pz]E�H�B:�mҦ2�F�#�}�`?�� :����Io��N��Il�G~�v�/5��KS�'�_���n�z��M?>l2�`3�vj?~���)�Ny�~�f�/�B[�K��x��A��� �3/���+��<���y��������U�� ���%_�v�z���z�� ���\"�=���:��^����,Z�����oNtpcL�f�alXu������1�1�.���_v[�=��ͯ���=�i��+��Y0��K��{��]��F�j��BzMmD��D8�M|���تW����!�/}ٵ����(FZjL����C]}�S�N;_�w�{����s̯�K�/�r��K���v�¿��%\�����՟?��)׋H�W݌i "�P?6�KZ�5��$gM����3Z��·H�ɱb��d*�a��@��|1�2f�����XYX�_��g@��qHm2]�>�`��XS�>rU�����q�ԍ��>�1���m�1�S��ay�X7�4M�0�W��P/$�{��b���cCj�3��S�@̠�Ȗ4������>qE+<d-1��ֆ��cU���y��C�]0�#�YN�r>{4��x6@="�_����Vc}�t�4-���mkrp�����v�ً��y�a�� ���Ą�Ҿ�l��('�P���qم+�Q�nگɓU�^�ܖ���(������UmY�{<���U�C��PIf{����%��'�����x�����K�"UL���ڋ:�ˎ,;Ɖ+��J���b���,�D�9������4����&�gt�����+�&�n	��W>�`��x
�|�A�è���QU
$�z	�hG�rGB2/$2��h��!���r�?X��lk>�0����y������,#�����(o�R�)�[ѝ ��2�U���+IvY���r�p���N�%����G\2[�)�����g�;V#q���#���JYH�ky8a�s�+䏀�+�kF&m�>5��^d�p���_�#���r��i�|�����x�-��  ���1��7ߜ�_�(cg��C���!�𲓶l� g�����E(�h�p�G�懟�q�9����K-�)�������v͕V�юl����TC%�����d����-H9S�)���zY�_�SZ�z�C.��D'�������U��9���{�'f���{�x��7.��m�b��nhr����qs��-��NA���rel?:�h�ܳ��j��Y݀�˦ �4�bY���)��t@=�,9>�Ӛ��MՁ���q���T;ʃ�L]P]�݋me2ů~����䒼e�Ј�߬���%<�RI�)*������t��T��G+�rZ�(��Y�Ռ1vo6M%��	;A�S�m,�ß`���}%)(�P��
Ѻ�N���R�q^�u����Aac�i�V:��n08�����ߑ>�-:b\A94�3LNvL��('"�<����_\	�$��!�N��c����v=��]� tu2�%C0�q�/𕃒DϣR&nOQ��cPX�����` ���mK>(�F|.Q|׎�oc�H���a��-.�W$u��U��ڼ�@��r�-<h�Q7�0�5`r��G�/2`c0�j¬�Y6W*]��W��T�+����BCo}NK�xgN�:�	OT��l��f#�T���icW�IH $Q=��֣\��,vȨl��ʜ��l�p�h���1T�)�L���tP1�OH��>�Y�9�$@T��?�T�)|.S�ҋa����~
��A����P�M<$���� pZ�Ic_"���P/��.�ɂ�`���7ռ�0�1~�O�ǁ�Ҋ�1֫T�B��hk��$?������������F������w���n�Y(��~j�@h�J�G��L���(�̓D�^�������p�� ا�0���o+*L�c,��>�4�Cq��Slx�k�~���A�֏�W�>0d1�ްD6���ڔ@^^H#!������nQ��!�T�D��XU
̎�o;I�Eϐ�q�h�J�"��f�2-��id+��#ͅ�j]x=��P���m��� q�p��"��I�O�nG�Dlv�,��T}X����Y��Z�n�Շ���@���U��5X�J��!�M�J|�2��:5@.I`ҾVݮX$U��>%_����bŕc	��w8%a���S����,r�_�2����21��y���,ħ���exu'�i�� o��E�$��E�F�me�$����T�t�A�h��-��[Eu�����ׁ"rzL?����о���9��i�̸�%w�ZslB@0�D���jρ��zAYmaeN�{ϖa��W����RetY����y�(��y�g1��	�)��yĕىb�u�A�PU�t:ְMT��Klf��H�����h7֘��D���j�;?/������#U�
�BXV�=��ݫO�V��P�E�+����&$gO �������,#�������׮ 
 y�:@ *mY�ug&T���e/�@�W�(9-x䀾~4?�5�0u.�xf3�.��3�ΊN�Ձ��4 &t#�c�L��gcTՃf�N��
��x2� ��n��T�`��M��zr+�V��m�VNs�Dno`4p�N�֕���mU�a�p;<�-`�@n��;L�gf!��m6|�>�'�Jh'ȭ��(���A�H�-�pQ��4�����]}���܎�1�ŌT����6cZ��/]vJ~����������!N���Q�W�{t�9���/�+S�w�V��f�|g�#\Ѓ�#|g�9����6{�.��N��+�w�u��bt���O�j�${��tG_��6��%*7��g��{F�c������X�J�c���~��>`~�'�BD讜Y���M����cC����]^�"6�[N9J���szDwB�w4������;la�(1Ӊ]y���X�Β�N�1��r��M��č�f�X�FHM��|_�\G|�:�2���8��`�`z*L]j�h
)&�y��7/��%�s�[������!�_J��B���
�rb����i�r�ء�# �1��z̐�x�|/+d� =nӦw�������(���aý�L^��bj�$�����/�:ɞg�o� ~�d4s���t�xst�3�[�A��Iw�}w�D- L���U���j�z! վ0�����f��0@�}���wj�J	�C;�>��"�Ý�����~�����EV��?kN�z]�X5[`w��X|�|� RD8��@9��l��wx�$�D����#'�s�)7�e|�`���r]��9$1��a8e^�_�Ⱦ���Lj%!R�	�A�ȉ��5�<���:<�Y��-��[�y��y�k�����qe�R��d���,<���E�t���4�#'d3�&�i�otgS�����S�g��>G"�s�J��<I_v{����j��YGJ�ӷS&�cLu�Oq���V��Z���I��@��:�q�f�;��d� E������\�6UR���e>�.u-Vc���ʵY�Qf'�a�����h'��'�q�7 ��ҕ�h�?4�:@[��xl	�QA+�ʹ��W��#�\�L���L�t-�n�x� ���kYb�mN�"'F�i��6S��R�.�?M=��ô^�j�O���՘Z�o�{H@�
�>�֓��_��I�BXҺK۽����6�O�
|�s�3Kd�R��צ�%������D[�;x��O��"����P44j8���KO�V=o>��6�� �ha�c"	�0��Zf@+�g�&�#l�q����IZ����6R�������'���A�s�ʊ<9~+�'����.Y�(����/�E���FAu��� ��Ɵ��.1x��T��k���ug�·��!�S�x��!u�O1��7R�c������ò���_�9o�|���3A�N`~�,������+_|�����.��&oC��t��'���.g�F�[�\�7oq�~�R�zlw���iS~��k=�Od�X��W���!>i�\�s�������m��|�OЏ�����������m�WI��&��|�#���n�t$�l�T�5�ǑC����������M^�E�p�li%�8�7����Y��~�?�:j����Q��?{k����'�RU`���zB���76�N�1�w���vRM{�֟H���3�]�}`��Ŋ��>H�����W��e���q9&�����.�!�ewiiJ��ez�E6q��y>���H;�?	�Z#���H�1Im��,$�wC(���o���_��륊��r<�z �MJ���W�S�Ź����Lb�+i��+F7��ӏĨ��w'��ٌ=ۖ�p�C��^B؏{j����DΨ����@�^��\"F�`���_,FǾ_)F_M���Pv���K]����wW��Rڳ�%	:=t�4��r>*5��쾉��H	u��R�A�=�z�M�^����m�ώ�~�XB�Oʹ9�;��;M�Tk�OZs1��;	��ؑ��l`��l��c��f�3'��O�5e����� �p^�:�~�&O@'�<%�Чtb�'�-:�ʯn�	y����M��R5�����-1��g[���
v\!Ƃy��.v�T���NQB��^t�t@"��<k�1i˒���,�(\>f������'��Pe1����9t�k`�^�����8���T�"��@�,o��o֕����kٜ��}C	�yDPj�j5;��m�k�7�b�{�����M�5]Gb�?�i_�����0�Ӹ�;b�y��Jy[�ƈf�G���r�2J��Y�9��'cUo���0��6��M�f��zj�B�5��T�`����̏X���y;&�N҉We�X1:���}��xl�0�-�����p�����~KG�E��Y�	�f�&��,��W6DF� ���l ���eiK��5���� Q���3������D���Sޯ��>��]̈���q�ư�l߉�zs�oEC䩞��0�����+�����)*)�!����b���?�n��Z�f/�W-0���o�M����hw���{ۍ�Yd�%��?6����;�}�oM�UpWc�^�p#�LdSeAg_��U��]���>�*��y�2�F���Iܱ��`�����>eSė�mjK�&*�5��o/��O�`�г>�ެ��N�^�=����h.��.���`-��`�q��>;�`t�З���?��r�O�E�N;Sz���+h��.7ם��̀�@��0�	a@8�����i����<��L��~�z�����y��<����\HX����H�<�WiA��l����YŅ�w��A� � ��Y�&h�[։������H�6�T�y�eV�y�e �O���Ld��ٟ|����i�f@ /��h�����r�Q��� m�6R��޻P%Pm�Y�M`��4#��Vƭ�'k��J��F�/1��V���t�X�~3��a<@��k�Є��C�}��{k�)�D鶶C��K�z�57[�s>)*i��Y��s��7ڭ���P2\����ߡ�k7��I�7��ױ��`�[��2��I� o�FW�3���Hox�>`MgbS���"�x����ض�[�����-l�F�A��İM6��XS(���� �(*<"*hWq�ɸ7���1c�-�y��_��w6Q�Ì�����ER��ymwD���f*0i�C�J����k����r ^�6���럅)��|z�>=��0��Cj���6�*�sY-�F*�|��P5(-����e���?�Z��`,�ŋ�����AЇ�*����8IS�tn�݉����Ål��(v��r|}b��X���yK������,_Qze9�%�M� H�qܝW��)�� =i� cv@�WT�+�nN�hۏ�1Ҫ3K�ҾHأ��S� �l�6H��.���$q���$��)�4hRf��>(������8����#K����m�i�Ӑ�Ժ����~7Mk�q�^�x�8���hr�x����%h���G}/CM���^��7�k�;O�����G8�b|�'�d���稜��[`����Ԗ�A������L�'O����#�ӟ�#�G����d�L���~g������J%e��,|�?��H>sR���Yݕ�����)Oح-x�ܒ�4�U#�A����o�P�RY�u��=�Yr|/�{F{[���ɞ���=��T���z��Z��o�
��`kq��`��ݱ�7i�����x��S��nL;���.��ɍ���IR�ǧ�1�>>Ng�T�}Tbz�Dwe7���!ݧ��j��w�9����}��{��րw�r"��r�WO@�Y�qVl',�a=D��4^	Kw�9+y�v2[�&�/$�*ل#�����
�+\�-�6G7�ǸC����P���ضt!V�,��89�����{��&�/e�.X��%��*�4��z��K�m8gÛbcP�����m;��=��R�������sÀ!��7hn�E7]G����V�[{k����-�	��P�^��M}��zB��7l]5L��5��9�ꗋ����r���1�f�_�K���+��%��P�ڝ���4�� t��l$b��@���2�Ǒ 
���9��͔@�R��%Ш�>����X��ph3��D�b!ob�[����~@i
�y,�Ou�[���G�,۟1�x�y�Y�HI�q��ɉi����0RK*S��j�Y�}�.˚�) ��K�\���u&2����_$��Hh(���DH���Q6�x�<����HYY�g.��RZ�NF��[��a��QƝ�b�4�N��H�FY�r��Q�ZC�����0L���-L.����Ex����R�L�  ��N&��/WNu���c��Kz���v�sk�?�W� d ���>���Ndo� �"���@{Ř/2�`ᛸ�9A���s�ETv����J��.���,;��8wʗO�7����'� �F1~'������c.�`م�^H�Ǆ�9�x���-��	���;N;��@Q��;����]QmqU��\:!�cm��)�#*�[:����9�گAӵ��
�<��U�S�� �@z��U/O���V�Hc�fy9t�Ic$�r�fW���b`#n��W�g��񣀠@�x��6�@�.��J�]���9Hl��d��G%���&phO����|�쮴��e�J�o�J�6od��}�f�Fbc�E���~�m;E�Ϡ���+]����W�<�F�b|	�t���iZ�K�����	��M�Q|����2����:~���G:"_w�-�_���;J$ q��t2��m�7���{7�*��l�6,r�g)��k����E>L/�U�ъ4��Qʕ(�>1��
�Z�S��.����|k�O��OI���x"�Xo�h��&\����i�����m�%����ڋ���%4�*i�E�*J�6GV:wF�6Gx\���8�v��~��|��ȕ���%�8���d;-�9�C�q����;2���fsz�ʭ�v�T��;H�%�:���Ym��$��L�MW2��V}�|pc�4u͹t�gں��D�)�D�w�ώJj��k���;=�i뢽�� Fkp�G�r�uq���Y9�S�{�:̻�^|���j�ذ��H�,�|���Ãq2�IVW?K�F�����0��L��6}c:#&�L��Lz9�Wg2���L���B<�-}^oP;�T@�Ǚ�W�#h�G��v�>v.��l�Og�?�g�/֧�>}��=�����*/c|c9�C�s8߃2�~r]��'�sJ�L1��W��K��[	��� 1�W�!�,
����82�\f�s��G4�O����0]��e���8�";n�Ι�Y�hjצ�Ԧס�|i�t^T0��A�!���d���vm���zt�����;�?\��_��K�H����z�o!,���L��c�V�@1������cхGK�;�변�bZš?�=�]I[�x-|5b��l%57<�lA���/��)4r���d�Ȫ����~p�5�*�0���z�G�K�.s��A�g�a`Hڲ	y6`�o남�����ٸdة�i���Yjg��.�3N0�1�8�	J�"���9��(��Pi�洤��we�ŕ�ù^��zqy�^<�"�C:�z��_���/�t�����{�:қ:�ʹ��':2�{���`lN�ڂ��%�hx :�~�^���H�̊��g'���a�N.�Az��z���?���L�:=��`�!1�a��p}�B�6�ҐG��B���2!P��FXNi�t�;	!���������u�4C�%q�5����w݀���݀��x���yk��]���L�_�&���~*F� _�o��z ���v���x������Ch��Ì[o�2��Q.��/l	{�����6a-���-�_m�cG�*]�1�Ȼ�޽�`ӮE�L����	��6Է�~;BD��|��P�N�ڪ���4�(���mt꩗�b�v��V�nmE4���b���|g�Q������nz����ȍ����0�t_�����t�b(����Ң`[u��O�<�4�q�>�-�����Z�Uڲ�������Kij��*�gmYZe_i�������߁P��A�[�=�]h��B����d��������������ʱ#��v��bLw|�,�$b�o'M��
�/HGM�+qu_'�~��dG������HKL���@|},e\M��Ֆ)�Ǫ�.�����z{���%�Lo��l�놭�h��̸A{~�UO[�u�,���V˼��),sB/�_y�b�����c0x���m^�ζ#��iD��(����5[yD7���Z}�	 �Je�,���G�����p22X5n,�Q~�Y�g?�991~s������a	L���dv0W�����T����3�}�.6[�]}�i>߄�D~�$>)}�@$A8�3���_�j�~n6.��`4f���8�7��5�u��}C�iC�ߴ�R���T�e E��QK|b>��[�����>�2��]=Ĩ����{JWk{
~��Z��;=�[�/��/#������.�Պk��N����U�f���h��%�8�J��?�Ɓ���*�� ��� �E� P
�g����l5� 2��2�̦�?���G_Pfb�F�m��6���Y��ھ�8λ$vI�*EH?����~+<�3��!T��E�����eiU��l�-��Q�3�
�2���{�������'��#�J��
ki����u�Z�U��*�(�~)�*W��{����Xl�C!ι�R���������Ӭ~�i�O�1���9���)�+��p���񒳒Q��B�_fx��~-{Gr=@<!���Vs��d�Z��]��ռsm6�^p-���7��Ewsr-ʢ�C�Q�5�Z��7��r~�[й�|_~q��|��mO�<�W���5�ħ��ǚv�e���T�k3X�OX��S��z�����>[�A��W��6s���
O���Y���z�	��:���;�n���Yc=9��ۻ��6h����h��������)*S�5]��+�Az�?�k�2x��ɰc)�pz�ߘ��|�'v<ev������w�ħ��-�__�q_��>�o'�'΃��UEn�W�a�eM�qU8r�}2M���/�y0���N�y�h��v��fox�)���"Y�Q�V嚻�-{/�Vq��}R���<��4�������L�.�t�4�\���s9@�=utzG��I�Q��k
�U�2TS�&�Z�L����MpJ!����6�c ���ެ��u�qRf)b��Rl�����~���"�t{��T�A���v�}(���fg�2c����ᇽ�p�(�M��4�
.����Ϫ�k��N�C�h��4[Ma,����g���g�%��$�Lm@H��Ayd� ���i�䦾D�m�n��g9���T���цv����6����&$�
�)�}@W�_����"����O{�����:2���ξY_�UL�NE}ɑ;�vd*��w�V^��p�/��ʴm�i+{=7��a]{:�2�&��͞�,fސ)9'礢�������2�e�ۜ�P���#~$��<Td1e̆8��"%���ŷ�4ҁ����E�b�Ɵ���A���PGB�Q�X���2���^�8O<��=��ŕ?�L���jD؉�����!�k���SB�1�}�Dzs�,|�Mj3�����j��b(����|<�z��AR`��&D��c�b�7�㲅s%远�ON�7"�
�j��b�f�lx��\_��r�Wx�7�i����~9��V���Z3Yt�Ň��4��.��9�*�� _�=���q���kn`��n��"u�׹��?�%ǝ����R�$�sI�!�}�|���ve��]���t;��`�W���Y������%�\J�P����]�����e{�nv�}����
���Z,����F�WKQA;��$�I��5���nz�d�Ota����d�]��-�/���k��)��
\��+���J�x-�dLI������0�Zب�9|�Ct���A���V�N����|`t���LE�h駼@���X���eF��a/|_�q�G�濃�M�1�n��!����+%&����ZL��� s����>����O&W� `ӛ�B���k��w>���"LoV�v.��[�;��g�W��*�������W�����\��P�4�Һ�V�u3��Ue={\���&��K���RG���,F	L�SR�I��5��ϐ����1j���du��9f`a��m���mZ�jH7�F*����X-�>$�S�1�%&g�{�"p1�8�r����z�	�0v���c��:u��σ��&�#/��\I�@�A�L!�N���؍�<|麿�E��I�`I/�%ho�ۅWS����w#ƢZ�x�4�z1�JŤE�5�����+XE����i�+���ϓ��j�\Rkj1�Q&�'�DRui����t#�A���w� ���~	�CB�9!�2Ҡ�z.��c���NLn�;(>Š��%K��-����E%k�dRx'Px7�x����Ĵ��?�a��q�Jp�i`�_�K>�p`�g4����;@�����N�y[��$Y9��+^er�
�x�,�8A��hM7 ��]�פ�&�/��4lΤ�t
������e��)���&#�ȇ�Z��U잊�{�nu�lq�,���7����"yqe�ҾH\r?~^�wNa{�<��I�S[3�ZS}0�u�L���������q.��r7���i��IY�LE~�, �t�TT�F�����1b�gCq��oj0�pR*a����ۿ��{��M��{\��r!
/���ϳ�P�`�8��L��X��
��������ΐ�6c�\C��2X~>�uLa��f�1�!���t��
��j6DQN؁~�f���>{)` <L�+t�˟��e�>��j�� �|>�%F��R%�s����{ݰ�*Uo͕ԀK\���� Dy�}^$ŧ8M���S�Ǫ0�p��NA|
�WHL���֏���+�ܥ$�o��/Q�q#�C=e��_�l`���l,���	�Л�>0�V!ȋ_�����P����ng%�эto���!��ǹ�>��3��Շ`�}+yIm4&o�v�3p��n�r�>�R��n��g%��N����_Y߻�[�B�?��c!{&jhA�$�5zb�����X�w �Z�&�(�[QN���]��̌���ހ["M���[�����x��F�$�$��T�L��/�0mP�}�x[u�_P�ڀːo#�0�R~�&����K��ؙxh9�?�bKFJ�.ہ��\�=�t[�_х�h��n�m�Xq����q]	��lh}���H;�]ڨ,��r�Ζ�;��4o�̜:.J��]��L�L`�v�{�s��t������&εBIX��Fb3���v?�Βؽ&�R����L�k�s���`�MGR��� ���tr��6�+���p�yHG�<+�����F�l>y�_�E�<39��T�IW��lQ�$:�6�R�DM���	\ǮF���f�-�o�C�qg�$W��b����������O3�~j*�/�؟���k��o���X�yV�)g{"�5S˻ާ�����o�9�w����E��� }��;z�q�'����N-$�_���q޻l��Ԟ�|e�Gh`�����5Ai�E?\�J�#x�qךR�Ir���ө��Ӱ���:��ش�4n��[�7�q��e��(�hك����g�v�@Ҳ)�w��G?9Pv>�G|������O0�Wf���I\E������}�*��z���~�b���7j���{?��]x��wMt��t�t��b}��؝M�u4���E����!�y����:s��4���m�l�a�'��X!�1�y���h���y~.����@ڢ��ò
a��j��eW�>kn0i���	KZn0��Q��q/&���LDĚ�?6@h�=�O�"���S!��R��]��T�,�u��G'����咉c�k�3 �K����,m��
v�zy���9�\��b4��D�`�hX�0���Dn��e��	ԫ�!Ue�ʓ���R(�i@�D��ܠ��:���4;��
/i�X!��2��{M#O'��㗯��T���6�����)Qe�����?�#�;u<����:��f���Co�����`�.a�3��09�4\�w8��}��K����ߒ�~���$��?���Ƕ����?�1���'����,�ʰ���V}�gMe޹������)�[O����o�q�$]}�~����җc1���_\ce��콲���e�˸��|x�=�mr���Iz_NÉ�m�R)Vm��wL��^P���n�yTG��e�V=��x��2��g�#k�ª��e�M��q�M<����`4?��"��Qwᖁ�����.0�|�O�^G����̴4C��+S�7?ӷz�%��/1W�/K��Wu��f��x�u��:�!Z�͹z���"�e���*3i�Ц~����t]3��L���N��뾹��m^�J�n�0���R���I;4�0謼�jN5�!i-*�����|�(	yF��t����V�a�:m��LRC��g��F����u$n��"h�$k�w���В̙kK_C�7�m�:tJW�s�g�m�T�2s]�<������	����4��p#Ge�c��Y>�eF]vSj��q���X��n�u?Oor��m�gyF�jx;�����=�V�ޛ����5oH�/�rR�[���X�0��hd��O�ƅ�d�H<pZ�ڸD�����YC��F8o&��������T�V3,��}Yo�{l��7���i�y��b�Ƭ�=U�;/��=X[v�N��3��eϝ����֥W8L�ߣ8��7���+i}��d
���9��S��i�=�_!����U~$\��;��J�^Ө�X��ܥ�����7",��_i�0+)�Ϟ0��{���������ʧ��~�W�O���]����g����/�R�w��A��7j��/C��L�X�s8aU��>�{st��=���MnA��q#`�����0i��)�zH�^ϗ΁达U��w�3&=�1i�a]6��s�lL��^�L���b���/���5��<��I�ʵ?�]� �},( C�Q<S>/��3ܿX��ts}N���i�<���J�ތ@�������Jq��z���z##��s7h�6~�u�mG���ֳ����=-<�������[�<f�����3�du��ePkY��M�z�����ti˾������w{���𑹖��r��jI���2�\S���t�0b	o��N7�S�j�]K{�'O����U���iT"^c�q`/����L}�P�[_��nz������-E6���>=��(Ա��A�6U3�z��S*��˯�Z�}�W~p�5ul+g�w���vAZaǽ�H���#MCu:��k\v+��[M����׶�1\/��\�)�k%[�����J�}X�`tHk�n��Q����a��>�:��|�a/31�G��J�a����J2\47��^�eF���$��j2J#��o������ʠ��\�
%��T��r��	�)�l��J� ��+U��t���u��Fba�?��m�mr<�$�!�!u���m܋���պ�})��Q��q��K�I��<X���/g�F��l����T��䱀�	/uP�Tt*{�X�?�\�W�������M��J�nq�=wq�)rX�̽A��Td5�H81]���1�@a�9=t���?֚xP����/��I�QiDG��~���BgYv@��V�����nH�_�y8���|����I�+��1љ'F�X5�3?>�o[�g%^�������t��⫏�ّd�����A�e���=�;>�g�W������S\�$+�e��-!u�<���k��u[J/�W
����7����yyP�1�C\a&n�'F�7>1漐�(6�	Yx�|\�㐰�/�pI�G:|��I
7F���Z!�t
wDVy�{���1�vI��x��%XX�Q,���eaW�Ud���T:�ƻbs��c�z���s/�10��� �K���XH��&�lc$E�o��aA��������Đ�k�f`�H���΋��c<� V&��Ox��s�Ȳ��%��?��8t��dNL���>�~���\�%FL��D��%�=�~��E��ކ��dL��M�(�����2|��t�wC'�vH��XѰ�ϴ�7��Е6c;}�7[�g�['r�&��א
��-�XY���3����?��[%�&Pp��	���#S0?�ٺ��#��!�W;�Z�1H�#���}�����Y6��礢������g���	OX`���)��<��Q��EvY�y�f�W�5���Y�b=�"�u6����ťv��8ё۱H�U6�p�'r1��������J�Fò���+<��H�Y
Ҕ���C�zC:�[҈��C8���2�8�>x��X��Tj|��ų���1x|!"o�cx=w��O�nc�*�W s�ss&�b슓�l��3��z�m�FVX��I5���7�o����4��)XD�@������m�����*�jE�P�����%�(*���<��B��P*�=�ak�Jm�;��;�;�$����������]�=�=NL��7O7'���Y �t
�J��}Q�x{,�Rf�h�l�"۫�l�`�_�"�`˅ܡt��~��Y�5���]X��e�����GN��T����<�s�]$�nVF2��w��͑��ā1�eE#�ĘN��'CC0N�γ/��hH'�cC$���A���2�}��=T��-���N������n�|��U.Y���^�T�4 %)�~Q�EQ�G
�bZ ��w�BU�2�<�E�	�.a�O.V{��>'f%j�=��Mpި.kf�)�3�V�B�sҖ��2�GX�A��~(8�HF#�6g �
��3�3yT�Oyq|Sl�P�.����L���ʚB�B�:,�Ω"��;t]~����If������*��T�"��S��/�V8W95ғ�Y�.-5����~\����R|[oKl��c�%�Ť��k�R��v�������6�`޴J햖��|���j���ݠMk�!?Uj�����K�H˭V�N��H�}��P��Rm�a������?F�Q�w��5�`��>��}�����L�0�KK�DKm�s����uoȷ��5�I��z������3��{��~]=oDK\h��,v�J��;����^m�Ѿ��9z]π2�9��ɏ���4��>Ѓ��tOM������N��?UO�6�;���Qe���[���8$-�"��!gT�+0t�q0�߷	�-rpx~a�┓��ݠ��A�;A=ʛ�%� Tx`�zC�LQ%�~gEZt���`�#¼�ٷ�M�X7ލ͖��������p�r��'�{��X7k�}�ت�v��C�6 �b��W��H��2X2h��c�j>s	�x�*K���(~��
m�ǳ%�,��C�� C����XAf�7P�&�|*�r��%�qt�H��R��c���A%K�f��QOo}+�� ]��
������ �m/��q
nm��1��/�;܁��DG6�XYʤ�蒁O�����RV��S�l��mU^���/l��%?�m{��NĦضNx0c��ѱ�<4CT�R.����)
4ewp��Yym-+�]���ٳ�u6+��T���
�Pz=��J�R��w["3m�M3�ϵ$ �Y��X��J�.����A��1�Z�`A��V���`�<��
����<�5���];���]�O�)<0	gQ���R��� �TYk����U���ۺ5�[��U|}�iQ6��\����gˡ��~ ⵞN�@U��l��;�cxyGPn�l�4��5�+�4�'V3m�T9҆y@~�}���\������/8#�}Q�	ex�H;��K/J��8?h����'xC�l];=2}/oĊ۸K���QZ�\��N�H;��`)r�:.%����|�$V�����c�����fWk�+������:�����ɃJ����&��&�Ì.ʟ�Z�.r�-giu+�Q;"	�7�,=���S�Q�a��^*
�҃��Vo��в��F�G��n`��N�&��>2�6,*w����c�+��'X��l�[�-�_�A���j1Sf��*P��C�0i��BĢ�ȶշ�y�����,uz�[-+՝g����k��ZPeB��g�
zz��DX
��EK�H��L�#J��?o�6,��M�A=����m��aC/��!K�R9A��P�y��CA�=�t[�H���zץb<��n�d���?���/�[<�q���Bi>^]_�_@����G�[.���օ��b��R(U��b�B��;��sFA�k�}ofP��6�����S�
��[;��= ����}ݘ�w(��BQ��2v@�/�O1�Be�A7�7�-]�ߡ���b������T��e~�Bbkh]�����7����G�=܁5,�g�"|G�Vq}`�T�	ݻ�#C�wbֹ� Hڻ�`����EXbH��`��m�3k�/q�5��o5^��dG��@�&�
�֍��ֵ�Tt^I�SW�qr�4�j�
.q�n���7�nO��m:��"��x{�1��;ae�䔖�PVΣ�:Xρ��[�g���Q�o`����h���ΟBQ�Ig�Q}4��1���˰�_ŲJ�;��bX��N䅆���נw���Y�E��?G��N��'���g+��1��Ǽc�y�'(����Ӿˑ�	~J[�t`������F��'�aŝv{[�-���`lUK-$t��uo��9����^�618������m��]�h��"k�'x�-�)�n���1[�Ǭ�&�8L���((�Q/U�{._N�Q�l��R��s�T��^�������I!��ηЯ25�`{���=�0�㥰�)K�`�6�%�;dC*��>c�I��eΕw��L�JT4Q���ˍ�I��SQo=~	a���T~M;:�V�jDy�75Ѫ�f0�����M�� ���9s�t��M�c�{�0�؜�l����(vs��FB�!���*]Q��N蚈�� �% �i�06Y��Qu�%�b/?���I�a�v��mE鴏T�`zr:}�u��ABՖ���_g9<lS<��D�9���~�<��r��w�h$f��X��䈚����~M`�	Ph�A��h{Fѥ��Zt��$�$�ht�X-�lY+��f�A��`H���f�� ��K�p�����n�|u��Hi͍�ū���� l?��y@ķ^eL�W��e�J�z���#̹����p�3(��~�?��.����ϗO�Y���"��R��hKMs
'�o��H60dZL@����+����Q�\�܏Y�-��I2��-Q� � ��� �{�A��p� �� �#����B3�w9r�_ҲQ��)�VpF�
iB�w�]�T���WF�a�R�	@�Nq���iR�X|��Q������}��~~��nB�l�x���0O�l�M	�nvS�6[�ˢ͖`��}Z���X�~��/x%*rMe�ޗP�L���bI$fֽd3&�V�7���IB�f�`S,��v�K��[�9_��t��l��34�s��� �9,<��o�&�q�?f�Y^��g���J��̄��EA���R�^4b�9�_a�$�w*pE����Y�(g�(�l-�u��
+�(�7�#/��0�6ږh8����U{E��Ņj� T��mUm�?�q&�Tf�U�s-Jc�%?��m�|?R�W�1��������c�`�R�ʇ�G�d�_vw�Ү+uu̦+����E�ϥREw�q��C�'�NN��?���l	(�ZE*�A�0���E%�崄����
w fål��M��":�2�yD��C�-��U�AԻ�8�5GX1Ni���k�uS�U)��<�hF�!��LU��xwT���^�9���z����{f
�%N���S��}I�i���2U�;�av^��}�s%�3R��,ۍ�Z�q��!/\n�F����>��C�4O��:����ƽ�Ƈ��n>�~�_B[�m���V��������:F�ϋ.#�8\+L�����s�k��W��)< !jSn�|�1K4��VQ�%�,(��~����!��v~V�m�ӧ�b���G�P��/��T��@�/��w�6�����g�0BR�\�3*3A:�O�6#���E��Ũk6Q�Q.!�)�jY��+}	��]~�FE9V��Bq�_3mY�r�z�ݻ^�|d��S0�����b6�Άӝ<�*�ZtLdB�	� m���1�D-���:�\D�ö��3�o0&�3kxL��w��Y�(8B�[<ƜlM2=cr7�w��1���Ye��U��X�qL��N�X$&�
�m\t_��n�o��;�����3b�o`��k'9L�IbȞ��$�T������$�UĖ�����Ĉ������+
m�w������_�h�k~��x���� o����[��S�S�����@���U���N���1/^�1���0�]0	�Y/`�8(>��&��&fzT��Ǒa:�1��Љo�̞50E��;��KZ&�� ������Pz��PQ/���I^x�&��MR��������h�J�2��>7c���ΦU�;en�!39u�C����!�ʧ�!�E3�'���NF�c��!�?�3����V��Ds��^�����{���_xC���3�e��M�nͮ	6����������1�s;ۣ���<�?3�ʿ
�Eo��%\�to�Ӎʯ�s&��=�p�;Q�Ϫ2TI�?S��ИmA-1c9��#�Ɂ�$^�k�^�i��\�G�X�h`'�5�t��'�Q��7`4�0��u�n�4��;�E��4D�a�Tw|4��jB|�SD<.|��{�v��:���V�����>�igg�W	-Lb1��Ό�L�nk�e,���) k��W�۩X^#\D�%��Kc��!��D{�'{�SS���"�N��s�g F�	�ըu�z�r|:>����aEG��s"���O��Cf<K��O���hF�y�?xgsy������C:�3�A�|�Bl�nb�/V<?� �k"�U��fM	�X���bx�޻��4�Q̿7���
ӫ��z
���N�]tE9z?�a�Oq�|Q�U�+>pqS$���S�'�4v�3P�l�xA�f�{����I�:��IS379`w(M/%��St?����f���.��$ɣ�>��$L��tѧ��J,�#��Ex�p���rE�iw4��������� F�[�,G,R���S�h�M)uzÏHK�l3.-xB��{T,�T���C�1�+���0�m���������uXǏ��^D�0@,������	�VF�ayO9�)��FEs'J�(-ϋ`��R�mͮ����^�Qk5<�S��"/�*;�C-�{�f)-H�UmWs)���Їz�cg����G�Q�*�X��p���1�r��_�!m���>n":�dVW�����7����餩xቢ��v��~���7�L��.���Y�C+�&`bٗ�4�Jc>�o[��uS��B����܈�E)����>�D��x�۹&`R���;|>O�:X%&�5\�����D��_N��D��,������8i���\љFz\�QW��~��vF٪(0%a�|�s(��O��b��gEu�ʻ	f���9D*�{e凨"-�8�1\�º<�7ᄚ�;��^�J����f�[5��.T�P�w3��VA��(�=J�Q3T�x��(w��<�"���1&D�f��:��mb.c�����������m��J�,�3m��*G��J�(O,k��K�<�= ���7��6&�h��%����J��8��U������V��Jz	~�r@��Q�މ�N��a�5ii�M�^��$�yk5��j�B�2$_#ulG����\m�$��������ӑ��o�1a���j٘��:$�yL�7oZ��nR�u��>]+����֋7�t��Mt���g��z���y�eG����I����y=�ӓb}�̛��cDqx�`����m�0�R��S�"f�)���d�?�!�}��ԭ��9��̹��8�!�H]���%�)7�7�C��z��:'�}O��hj�Tߙ��"�:�|!���r�Py��'�M�/ke��˄
�S,������ź�{���f�Ш[Z���f��T���9l�J\���d�'|���K)J��T�ZT>����Y�·��luTpg���ť�]XW$Š�+�Γa�Z�]���3�$W�J��)B���E(ࣉ�@y���y�����Rs��V';����^BϮ�7���?,BZM
Wr7�'���y�=�؀�8W�k/����N� -<X��|���.`ᛧow�E-��^�o�i�c��'��^�K�$��n�w�L��8F������	���|m=y0��V�����Ƣ֘Dʺ��x����NdĻ�%��)qY��ar=^�$�����q:�00n6Y,,���RL���)��l��fj��̊J�O�3�"���zV)��$�2����Fe�-�� i&ނ���'��1�z��	J�ƛj��W\V����F��P�̛萔�O0Q����Ce�P8ECFEϼ�"�B#���$�h���r��~�Bh����)��_�X=MM��?^��2n`�t��{����"�3pD�wD�=.#�1=J�
oP~����̓�V>�g ��7�1�z��i��Q��V��[N%�A��My�!������[S\�"�G�j&���D�t.��9ws�7<K�hI)�-|��U�]��3pL.�8�:�43��c�e�Ֆ� �x6v�(;��*,/d"e{h��_�o��A��u��i,�W��6��Q���r��B��K�!�d�؆�
6m\Z�<Wl\h��z��=-1g�ץS����E���I�E�%Z��]��s��8�A�K���3`9��YX1S?f�c��3)�%�� a�P�����A�W�e.�)b?���|����lm�)��f�ڍ�p�!T.��ar>�n�i�s��.6�(��Ug9EHi�51u�i}�iR�9����8���Ua3�6΄MM����E��hKn�"ņr�i����r	����=W�)M�{���|q1���r�*�>��M��v.��3� Mq�;�Uj%mS��lye|���Y���)��>K{�^�Z��Wǽ��U	'4�2�On����ޣ�f4R|�n��X�գxc�Oq�z���ԑh��S�a�������tУ��!e��Bf�Uc�d�ݕzf��w��|�0N��w�Ŵ��;4�V؊7�i�<>I����zG�%�̔6L~*ߏL^��r�t̥
��Lv��s����u�~�&� [ lѼ����ve஗�`08��m59���2�q�� <W��<ͿVlTań�7����\��躂&~��/8�{�bu~n��PQB�ba1;Ŷ#Nǻ��0wd�?:�&��n�r��Z1��>�p�3x���z���t����ѷ�:
(FR:�^�0��r�cL2w��6��`���Y���*ӗ���0���AQ��i ���=Iu>�yi� ���<5S�(D���z*_�� [_���Yr��~\,�O���+�T�Q���kĿ�q��|Jv�X��V��Y��8���ˏS��'�+�NtH�<67F��B ��Ԃ�Gy�&Rk�`l����9s%M\w�;�n%����݋�LǴ"t�+�Q�dC���V�C��A�蝹�Xv���?[�֝���h�����hS#/�~�1A5�_YE��*P��/���Ur���)ɕ�s�
Z
 �X�,D+ŪJ��Me�?\�|��������K}y\�)���"� �������uJ����,T&�Y�P��1��F@K�fǞ�C}��f�}x���-v���X/��w��	�1f���|Y3��w7s�箨����a�e|Ώ�p꾣\Pf��f�(������w m��̏7�-��e����0~�_�s�4;��E�]g����q�V�G�R���I��9�P��č��N6NK��G�8:�+��(ݏ^e�7�M��8v��`���e������B͚�=Ò�цe&�i65(�Kg��풎�2R+���%����6�#��
U�B�z�ax_M���(����|!�RPV�?��&�0�� uo�|�X�|��)Җr7a��>t�?�Y�٨�4_�j������E�#F�aew�4��	����9�{�S���n0N*�z�7E��q�=p�D��zsʋ��R��-�$��	�-(k�Y�d-^A�������`à�j{�u�p�>�_X!3�1uJC�)U�Y]�������ghx��_/��h��*��(��t��f�ʑ��K�h�s��Ƹ���`�%f��ա��,��F��Ύ���x8�Xk��������Ϥk���� Α|]Z�+.�:�"�ۍMC�im�k����?��Oq�%��o��r�tƻ�`7�_�G*D��v�/�F�g�����h��Q] -u����O���@���xL{�c�Z���1)#�ؙݦ`�ˉɭ��5�jP��B� z�Sqe3ϡ��J�mQ�?��Y�cz�.���])E&�5�Ã�����Ħ��I�9�=d������JΙ�t%'��4K��+rkf���3|�J��N1*fg+,�W�n�R:��P����2MW�
a��w�I�c�\��<�&�y�=���L�c�yi������{�Q��`��c�ǼsF�M!���:�������I��}}xab'�'���=Cu�i=�Y�	~����9�,:�CV~�v�ꤐ��A`�ʟ<p�qu�I�<�F32�~�}O���	
������R�{��CBC�=�c�p�T�&s��Dͭ�I�Cnа�1��
H]� �L��?��*�({A�R��)�	�xS��8k=9��Ma�`�u=��0�{*�_;����^"|�j�����C�%�݃r�l�s~���ӏ����1_T���-�0��a.��u���,R�ƴ���n�O��Ҳ����M!%�]�26.�;���	C���L��2֎/��y�����&�y_��)�)���7	N�G�YG�3Ys#'(�`7*'�$�6X�ο�8�v�N���k!��L~l�0�������ǹ�e���^�!�&�yYr?SV��a�>@���i?On&�e�d-PÅ����/��w�=09Y��Xm
r1���6g�6c�d��v�A�<ŧ�%0�g�z}K�i�
�1�M�q�
�0p���*�w��}Fݒ͖�9V��u�(7��o���-��i��f�� �?��?$�Y�I�:}�����(��?�:����n��/����L5v�%�Bڨ7� ��������i�G��E���^㩗��G����ۏ��b!�9�<p?KOS�8��[�8X,M4��Oյ�(�'�9�*�1~, �+��G���X��hHU�R՚!�s�`Hmۀ�ԭhH��N<���^Kf�㛢���QQ�6 �Rc� ��Ch���Pn;���	$ۣ �:5a���=:��B�9�iJP�=FK=_�0b�!�!&9Ky�	��"̣�9�'����n�:9�ף�b�s=3��i�bE^�`������W�Q"N��1�t��b��[R���������5Օ D���O%��-Kx�n��&J�v�ew髻�kX�$b),���!6�ޯ�h�64�k�P�ï�,kN��K����>�5�v���?�~?� 灿T�������į�N�W΁_1S��6��nH��:�ͤ&	:($�%�G)N��i��=O�Vـ��]�����cm�d�k4T�uĲ�f����T�J!�� ��]�Z0'�s������oǊ,i��l��ݫKJwK�j�����^`�)X�Oa��x����3�H����(cb�����~M�z�95����;bo���i��݄�1���vG�)����Q<A�gu7^��kwbJ�{��uY�;�A�E��.��n:%�MhĊ�d����B�����V�$�
B�9B�3�����IC�j�_�пJC�wpTh�`�R�"����e�<SoP�o�慭�3�9Me7&�&S��v>��K��B��u�����,�D��CH�{����L"�ĢY�Ҋ7��7�1��Y٫�R�Z�Ԗ�s���'��s�Zh������\�!�>�b�<�Nq�{*�䝊��=׌�$3�����fl��G7c6o�>:�-�-��^lĥ;�a��ע���̽��E`l��I4�uj�1y�Ќ���t+��3�?)Xi+0��G�a	u�^$T*'������F�ˢ�{���
6�y� k*&TS����wJ�HX��a�顋�zu�G�3�eּ� zQ���##�)ݲ'Z�8R�J0K�&"p�X���(��t�ŴJT����f*B�Ľd%
�<>��Z�>o����OF$-�����a�t�Xm��I�3� �p�v���v�ov;�7Œez#�!����I��:�h�Կ{�(�f_w:@�ǘ�b�kb�=���H�c�&��gE4��,���~u�7&֒T3c3<�r������8_��?y����O�I�`��I:*�x�V�35QZ����������X��-��B4��y��ʿ=�X�{�C;���2tmM�.a{�ls��h���V�Q?{&�Y���z�r��Mm���-2���0�RDE$YZ��DLt�b���$��B�E\)��݆܅Ą2w1�$W�9���d<���t�wsA�q���M]�oLST_DISALLOW_COPY_AND_ASSIGN_(AssertHelperData);
  };

  AssertHelperData* const data_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(AssertHelper);
};

}  // namespace internal

#if GTEST_HAS_PARAM_TEST
// The abstract base class that all value-parameterized tests inherit from.
//
// This class adds support for accessing the test parameter value via
// the GetParam() method.
//
// Use it with one of the parameter generator defining functions, like Range(),
// Values(), ValuesIn(), Bool(), and Combine().
//
// class FooTest : public ::testing::TestWithParam<int> {
//  protected:
//   FooTest() {
//     // Can use GetParam() here.
//   }
//   virtual ~FooTest() {
//     // Can use GetParam() here.
//   }
//   virtual void SetUp() {
//     // Can use GetParam() here.
//   }
//   virtual void TearDown {
//     // Can use GetParam() here.
//   }
// };
// TEST_P(FooTest, DoesBar) {
//   // Can use GetParam() method here.
//   Foo foo;
//   ASSERT_TRUE(foo.DoesBar(GetParam()));
// }
// INSTANTIATE_TEST_CASE_P(OneToTenRange, FooTest, ::testing::Range(1, 10));

template <typename T>
class TestWithParam : public Test {
 public:
  typedef T ParamType;

  // The current parameter value. Is also available in the test fixture's
  // constructor.
  const ParamType& GetParam() const { return *parameter_; }

 private:
  // Sets parameter value. The caller is responsible for making sure the value
  // remains alive and unchanged throughout the current test.
  static void SetParam(const ParamType* parameter) {
    parameter_ = parameter;
  }

  // Static value used for accessing parameter during a test lifetime.
  static const ParamType* parameter_;

  // TestClass must be a subclass of TestWithParam<T>.
  template <class TestClass> friend class internal::ParameterizedTestFactory;
};

template <typename T>
const T* TestWithParam<T>::parameter_ = NULL;

#endif  // GTEST_HAS_PARAM_TEST

// Macros for indicating success/failure in test code.

// ADD_FAILURE unconditionally adds a failure to the current test.
// SUCCEED generates a success - it doesn't automatically make the
// current test successful, as a test is only successful when it has
// no failure.
//
// EXPECT_* verifies that a certain condition is satisfied.  If not,
// it behaves like ADD_FAILURE.  In particular:
//
//   EXPECT_TRUE  verifies that a Boolean condition is true.
//   EXPECT_FALSE verifies that a Boolean condition is false.
//
// FAIL and ASSERT_* are similar to ADD_FAILURE and EXPECT_*, except
// that they will also abort the current function on failure.  People
// usually want the fail-fast behavior of FAIL and ASSERT_*, but those
// writing data-driven tests often find themselves using ADD_FAILURE
// and EXPECT_* more.
//
// Examples:
//
//   EXPECT_TRUE(server.StatusIsOK());
//   ASSERT_FALSE(server.HasPendingRequest(port))
//       << "There are still pending requests " << "on port " << port;

// Generates a nonfatal failure with a generic message.
#define ADD_FAILURE() GTEST_NONFATAL_FAILURE_("Failed")

// Generates a fatal failure with a generic message.
#define GTEST_FAIL() GTEST_FATAL_FAILURE_("Failed")

// Define this macro to 1 to omit the definition of FAIL(), which is a
// generic name and clashes with some other libraries.
#if !GTEST_DONT_DEFINE_FAIL
#define FAIL() GTEST_FAIL()
#endif

// Generates a success with a generic message.
#define GTEST_SUCCEED() GTEST_SUCCESS_("Succeeded")

// Define this macro to 1 to omit the definition of SUCCEED(), which
// is a generic name and clashes with some other libraries.
#if !GTEST_DONT_DEFINE_SUCCEED
#define SUCCEED() GTEST_SUCCEED()
#endif

// Macros for testing exceptions.
//
//    * {ASSERT|EXPECT}_THROW(statement, expected_exception):
//         Tests that the statement throws the expected exception.
//    * {ASSERT|EXPECT}_NO_THROW(statement):
//         Tests that the statement doesn't throw any exception.
//    * {ASSERT|EXPECT}_ANY_THROW(statement):
//         Tests that the statement throws an exception.

#define EXPECT_THROW(statement, expected_exception) \
  GTEST_TEST_THROW_(statement, expected_exception, GTEST_NONFATAL_FAILURE_)
#define EXPECT_NO_THROW(statement) \
  GTEST_TEST_NO_THROW_(statement, GTEST_NONFATAL_FAILURE_)
#define EXPECT_ANY_THROW(statement) \
  GTEST_TEST_ANY_THROW_(statement, GTEST_NONFATAL_FAILURE_)
#define ASSERT_THROW(statement, expected_exception) \
  GTEST_TEST_THROW_(statement, expected_exception, GTEST_FATAL_FAILURE_)
#define ASSERT_NO_THROW(statement) \
  GTEST_TEST_NO_THROW_(statement, GTEST_FATAL_FAILURE_)
#define ASSERT_ANY_THROW(statement) \
  GTEST_TEST_ANY_THROW_(statement, GTEST_FATAL_FAILURE_)

// Boolean assertions. Condition can be either a Boolean expression or an
// AssertionResult. For more information on how to use AssertionResult with
// these macros see comments on that class.
#define EXPECT_TRUE(condition) \
  GTEST_TEST_BOOLEAN_(condition, #condition, false, true, \
                      GTEST_NONFATAL_FAILURE_)
#define EXPECT_FALSE(condition) \
  GTEST_TEST_BOOLEAN_(!(condition), #condition, true, false, \
                      GTEST_NONFATAL_FAILURE_)
#define ASSERT_TRUE(condition) \
  GTEST_TEST_BOOLEAN_(condition, #condition, false, true, \
                      GTEST_FATAL_FAILURE_)
#define ASSERT_FALSE(condition) \
  GTEST_TEST_BOOLEAN_(!(condition), #condition, true, false, \
                      GTEST_FATAL_FAILURE_)

// Includes the auto-generated header that implements a family of
// generic predicate assertion macros.
// Copyright 2006, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file is AUTOMATICALLY GENERATED on 10/02/2008 by command
// 'gen_gtest_pred_impl.py 5'.  DO NOT EDIT BY HAND!
//
// Implements a family of generic predicate assertion macros.

#ifndef GTEST_INCLUDE_GTEST_GTEST_PRED_IMPL_H_
#define GTEST_INCLUDE_GTEST_GTEST_PRED_IMPL_H_

// Makes sure this header is not included before gtest.h.
#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#error Do not include gtest_pred_impl.h directly.  Include gtest.h instead.
#endif  // GTEST_INCLUDE_GTEST_GTEST_H_

// This header implements a family of generic predicate assertion
// macros:
//
//   ASSERT_PRED_FORMAT1(pred_format, v1)
//   ASSERT_PRED_FORMAT2(pred_format, v1, v2)
//   ...
//
// where pred_format is a function or functor that takes n (in the
// case of ASSERT_PRED_FORMATn) values and their source expression
// text, and returns a testing::AssertionResult.  See the definition
// of ASSERT_EQ in gtest.h for an example.
//
// If you don't care about formatting, you can use the more
// restrictive version:
//
//   ASSERT_PRED1(pred, v1)
//   ASSERT_PRED2(pred, v1, v2)
//   ...
//
// where pred is an n-ary function or functor that returns bool,
// and the values v1, v2, ..., must support the << operator for
// streaming to std::ostream.
//
// We also define the EXPECT_* variations.
//
// For now we only support predicates whose arity is at most 5.
// Please email googletestframework@googlegroups.com if you need
// support for higher arities.

// GTEST_ASSERT_ is the basic statement to which all of the assertions
// in this file reduce.  Don't use this in your code.

#define GTEST_ASSERT_(expression, on_failure) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const ::testing::AssertionResult gtest_ar = (expression)) \
    ; \
  else \
    on_failure(gtest_ar.failure_message())


// Helper function for implementing {EXPECT|ASSERT}_PRED1.  Don't use
// this in your code.
template <typename Pred,
          typename T1>
AssertionResult AssertPred1Helper(const char* pred_text,
                                  const char* e1,
                                  Pred pred,
                                  const T1& v1) {
  if (pred(v1)) return AssertionSuccess();

  Message msg;
  msg << pred_text << "("
      << e1 << ") evaluates to false, where"
      << "\n" << e1 << " evaluates to " << v1;
  return AssertionFailure(msg);
}

// Internal macro for implementing {EXPECT|ASSERT}_PRED_FORMAT1.
// Don't use this in your code.
#define GTEST_PRED_FORMAT1_(pred_format, v1, on_failure)\
  GTEST_ASSERT_(pred_format(#v1, v1),\
                on_failure)

// Internal macro for implementing {EXPECT|ASSERT}_PRED1.  Don't use
// this in your code.
#define GTEST_PRED1_(pred, v1, on_failure)\
  GTEST_ASSERT_(::testing::AssertPred1Helper(#pred, \
                                             #v1, \
                                             pred, \
                                             v1), on_failure)

// Unary predicate assertion macros.
#define EXPECT_PRED_FORMAT1(pred_format, v1) \
  GTEST_PRED_FORMAT1_(pred_format, v1, GTEST_NONFATAL_FAILURE_)
#define EXPECT_PRED1(pred, v1) \
  GTEST_PRED1_(pred, v1, GTEST_NONFATAL_FAILURE_)
#define ASSERT_PRED_FORMAT1(pred_format, v1) \
  GTEST_PRED_FORMAT1_(pred_format, v1, GTEST_FATAL_FAILURE_)
#define ASSERT_PRED1(pred, v1) \
  GTEST_PRED1_(pred, v1, GTEST_FATAL_FAILURE_)



// Helper function for implementing {EXPECT|ASSERT}_PRED2.  Don't use
// this in your code.
template <typename Pred,
          typename T1,
          typename T2>
AssertionResult AssertPred2Helper(const char* pred_text,
                                  const char* e1,
                                  const char* e2,
                                  Pred pred,
                                  const T1& v1,
                                  const T2& v2) {
  if (pred(v1, v2)) return AssertionSuccess();

  Message msg;
  msg << pred_text << "("
      << e1 << ", "
      << e2 << ") evaluates to false, where"
      << "\n" << e1 << " evaluates to " << v1
      << "\n" << e2 << " evaluates to " << v2;
  return AssertionFailure(msg);
}

// Internal macro for implementing {EXPECT|ASSERT}_PRED_FORMAT2.
// Don't use this in your code.
#define GTEST_PRED_FORMAT2_(pred_format, v1, v2, on_failure)\
  GTEST_ASSERT_(pred_format(#v1, #v2, v1, v2),\
                on_failure)

// Internal macro for implementing {EXPECT|ASSERT}_PRED2.  Don't use
// this in your code.
#define GTEST_PRED2_(pred, v1, v2, on_failure)\
  GTEST_ASSERT_(::testing::AssertPred2Helper(#pred, \
                                             #v1, \
                                             #v2, \
                                             pred, \
                                             v1, \
                                             v2), on_failure)

// Binary predicate assertion macros.
#define EXPECT_PRED_FORMAT2(pred_format, v1, v2) \
  GTEST_PRED_FORMAT2_(pred_format, v1, v2, GTEST_NONFATAL_FAILURE_)
#define EXPECT_PRED2(pred, v1, v2) \
  GTEST_PRED2_(pred, v1, v2, GTEST_NONFATAL_FAILURE_)
#define ASSERT_PRED_FORMAT2(pred_format, v1, v2) \
  GTEST_PRED_FORMAT2_(pred_format, v1, v2, GTEST_FATAL_FAILURE_)
#define ASSERT_PRED2(pred, v1, v2) \
  GTEST_PRED2_(pred, v1, v2, GTEST_FATAL_FAILURE_)



// Helper function for implementing {EXPECT|ASSERT}_PRED3.  Don't use
// this in your code.
template <typename Pred,
          typename T1,
          typename T2,
          typename T3>
AssertionResult AssertPred3Helper(const char* pred_text,
                                  const char* e1,
                                  const char* e2,
                                  const char* e3,
                                  Pred pred,
                                  const T1& v1,
                                  const T2& v2,
                                  const T3& v3) {
  if (pred(v1, v2, v3)) return AssertionSuccess();

  Message msg;
  msg << pred_text << "("
      << e1 << ", "
      << e2 << ", "
      << e3 << ") evaluates to false, where"
      << "\n" << e1 << " evaluates to " << v1
      << "\n" << e2 << " evaluates to " << v2
      << "\n" << e3 << " evaluates to " << v3;
  return AssertionFailure(msg);
}

// Internal macro for implementing {EXPECT|ASSERT}_PRED_FORMAT3.
// Don't use this in your code.
#define GTEST_PRED_FORMAT3_(pred_format, v1, v2, v3, on_failure)\
  GTEST_ASSERT_(pred_format(#v1, #v2, #v3, v1, v2, v3),\
                on_failure)

// Internal macro for implementing {EXPECT|ASSERT}_PRED3.  Don't use
// this in your code.
#define GTEST_PRED3_(pred, v1, v2, v3, on_failure)\
  GTEST_ASSERT_(::testing::AssertPred3Helper(#pred, \
                                             #v1, \
                                             #v2, \
                                             #v3, \
                                             pred, \
                                             v1, \
                                             v2, \
                                             v3), on_failure)

// Ternary predicate assertion macros.
#define EXPECT_PRED_FORMAT3(pred_format, v1, v2, v3) \
  GTEST_PRED_FORMAT3_(pred_format, v1, v2, v3, GTEST_NONFATAL_FAILURE_)
#define EXPECT_PRED3(pred, v1, v2, v3) \
  GTEST_PRED3_(pred, v1, v2, v3, GTEST_NONFATAL_FAILURE_)
#define ASSERT_PRED_FORMAT3(pred_format, v1, v2, v3) \
  GTEST_PRED_FORMAT3_(pred_format, v1, v2, v3, GTEST_FATAL_FAILURE_)
#define ASSERT_PRED3(pred, v1, v2, v3) \
  GTEST_PRED3_(pred, v1, v2, v3, GTEST_FATAL_FAILURE_)



// Helper function for implementing {EXPECT|ASSERT}_PRED4.  Don't use
// this in your code.
template <typename Pred,
          typename T1,
          typename T2,
          typename T3,
          typename T4>
AssertionResult AssertPred4Helper(const char* pred_text,
                                  const char* e1,
                                  const char* e2,
                                  const char* e3,
                                  const char* e4,
                                  Pred pred,
                                  const T1& v1,
                                  const T2& v2,
                                  const T3& v3,
                                  const T4& v4) {
  if (pred(v1, v2, v3, v4)) return AssertionSuccess();

  Message msg;
  msg << pred_text << "("
      << e1 << ", "
      << e2 << ", "
      << e3 << ", "
      << e4 << ") evaluates to false, where"
      << "\n" << e1 << " evaluates to " << v1
      << "\n" << e2 << " evaluates to " << v2
      << "\n" << e3 << " evaluates to " << v3
      << "\n" << e4 << " evaluates to " << v4;
  return AssertionFailure(msg);
}

// Internal macro for implementing {EXPECT|ASSERT}_PRED_FORMAT4.
// Don't use this in your code.
#define GTEST_PRED_FORMAT4_(pred_format, v1, v2, v3, v4, on_failure)\
  GTEST_ASSERT_(pred_format(#v1, #v2, #v3, #v4, v1, v2, v3, v4),\
                on_failure)

// Internal macro for implementing {EXPECT|ASSERT}_PRED4.  Don't use
// this in your code.
#define GTEST_PRED4_(pred, v1, v2, v3, v4, on_failure)\
  GTEST_ASSERT_(::testing::AssertPred4Helper(#pred, \
                                             #v1, \
                                             #v2, \
                                             #v3, \
                                             #v4, \
                                             pred, \
       ����$�z:Z��a����2Y�n.K�Gn��z_8��z�H�"y.�.D��}ZcJ���z��yY5�	)7M�\ez����E�(O�0�fR�y��a�������/8��%�<F��0GM�n�LT�*oi
���[4�h���{��%�cQcy�����%8�T3v�"�®F�"�kQp;����Q���L���y2��f˱�D�a꯿����XW���_,Z�b��[XO�S��GZ�ُn�߮��Y�7�d�s�G�����aNs�7��:¼EI$tz�CN�N0�+�@��Cє���+�8�[��C~E	�������8j��C`�JM-i95�!v�����OR��\���$w�'D�x� 0a�=V$w�7H�'�\vܝ¢�xz]A�w�F/Ǒ]!�ǣQ=@fM �pT%W�`�Y�����J	:-IG�/6ڛ��V�\?��֦\3kӭ�:?)�|�@wfs�mi�l<'�����&ݽU~-϶Dm�#��8��&�D��Pr������(���7e6��~���fLRmG�� ����������>-w)$
��xu>;i��H�{7ԇ壃Y�[ڏ"PG�[ܚ�#e7�!q�#����7��� ��)�׍�ru�uӁn�����9"�w��iǦ���`��M�J���9�mpw����aM��Ӓ�}[���ǐp�f4#�¬�ݖ=لx	�`���,n�nՀ��e��I�E�����}d�`���G,˰���D�����@%+�����BW:հis�lGPe��Q$c��P_po��eo%���NE�Q|�@А�4��1Di3�K��^Ȥ�t3���?G��X'��[N7SP�������$���d��"��@�.-i�Kg��1�ɐ`����hU��ހ7�m��ߥo���?��,�X�Z<p�u��x��Ħ��29n�~`����Y����0[�T�!L�5zxПCF͹�����#���$��#,�(t=�Y�.���ڏHc�p?�`~��Y���\-��B���FՆ�:q|F!Bڭ��h�P��&�,��n�қM,K�������'�,��)����_�?pؼaO\��ɱ�P�g/fa�W�A���, q����Q�-�H�#I�tԶS�l�o�+eW����'#�\��.�t�"�㒽@c��FO4�0h��gW?)r΋�?X��k�2QX����9�jnq��U�(Vm��V��a��@�$Z�Wd�Ųf&�
	 �R:X��lqKe�X�(��ˇ�y��k��U��W̤�[֣���Zh\+��$���f���4�d73����jb$�q��`4���w�/��z"��fQ�M���5�AEV�?���C:a��F�7�灧+wppo��.N�}zh t��z+�+J�]�I̅��R+_�����~�cB�����n5�=��Y '����R/g�.s��ZC�����Q�',i��ř_N����~�w�H5<�f�yu�)hօ�)K��O�i����:q%��z��+�~@�RF�r����3֙��e���'"���;�G�q<��X|s��l_`b�\ӕ`&�Li�o0�'!t�����e�9]yF� f5����4�"��`TR��@(���3M��;@�.�"*a������0j�<c�鎮i�&7>�p�?����8��:6�SF�_�����B��F?�mp���	M��i3%��!�T��@¨a�t�\���{c�[j@F~z���EIYʙ����~'+��ɻ��qA~�����O/�2vN�$��w�Q�͇�`5?_Em|?�x���)[*��'bZ������9�c��Bs�H�c�AO�ɽ�WF[^�y��e�L��S�� 墦p8��,L�gy�|���ī���c^6����R.���{8L������QL>�+s;���@�L&�R�)�jV�P=�uV�2�PX�E����T����XEؐ������S��ux�X���6L���Zg��"˘ٶ[�	uh�Nm����߿�Έ���{���Uƌ���q܁�iZ*��4|��8/�7/�~��R�������| ���
�gG�B�n��?vEz�(�[�H��9�/;M��ӄ|����cM�2�f?*��ò�v�"��`ݥ����g���jz3s5���k����#o�Q<T�Z/�sl�ǽ���[�6���<�+�X�}<?��pG^����������9���r�}����|07� �A9�| L�@(��	ױ��������fr�iP��9�/�cAN��'��T9>�~-�g)ԅ��'� �][�2n���,JY�
	�m^�b�����IPw���J$���4aL���|B����1iZX�+M�#�˪�VY���u�h
��xK���;rN�s��υ@�=4®U0���&~��,]����W$`_�~��Ѵ��g�.��An�2a"f�y� 6�2{��a�#Z Z=^�>�B��B�ycnLbjTDK���r�&B�-96
�p4�V�S8��I`l��ˍf@��,��7�lECIz	2���tѽ�W�K7�_z2��2���H�w߷�p'JI)4U���8b���8f�J6��*�(i�4�[z	R+�6�@G�O5d�O���Q��X񣱆)#L�^�OA�����(��)�t2:ql�w(�IQ�P�ɚ�G胃�\o��a⻻��Ũu��	S�Yæ��
a���h���m"���"���D�M�lt4N���"��,�C͍hm�iw'>�5(�*_�+n۫\p^��ph��e�5]h6��s��<v<8}o��X�f��Mr��w�E=l}~�<��S�y�����ۦrZj<;�a����~�̟��O��<1�=�w���}������Α�h���}~�h,j��#ܞ�-�dD:/�CfC#�#���s��X=��2���ad_/@ �aMZ�x�����%�Z.��gF���a��xpZ�F:d�B��p�
5���g*�����q�%K��:��E�~������y.Ce(�E�Ρkf)q]��m����?��7k�Å��L�����0%P<�$+�W�_*/�>sj/&�m���{9|_�C��k|ȯ�csA*���H-������]��>��+�F�����|8zӷ�b!�Ù1K�(U/��ϝ �[�?�|~)���/P���]�9SW�&���+�#��yVo6Hp�&�2�"�Q.�K����Ѷhp�APONJ�f�~5�ƫ@ٻp�3��Є%�iMDK�q����tS7�ICb\������QV�['�W y2�8��;ϐ5�,i'�sg�.x%)Ep#��x�_Bp�N�������"`"p�e(��,/�x:��A�mV�smįY��j�o�bx���L���k����S8�O2z��tf8kr��/��ޓX��b�����_�[�-�4�nK`�T��R@�E���µ�g��17�Y��tǍ���3����,����|)��㗡Ǡ�*c��|���ȚŸ(ݘa��hg����Fm?c>GA���]h��X����2F����+z��rzٓ�\�4�5�90��6j��T���"6����%�,�a�R�E�6�LC{���e,������E���o�Qr�`��Vq�c�]��U�����O�p�j�q;h��e�8��T�%j�O����v22�h��C���R�,�%���羰&/y�]��.y�<�f�Z�T灔����k�oi�Y��6��R�7�&�)�`^ۈ��u�ip�A��O�:e��K�"&�g��48��T���TR�S��2�|E�:���'�$2~����	�*#q�v�7�Jt�cj�Ю�9����YUw���'pY�-�3��]"	�L���>�	�en���S��H�x��aaM��ъ,Yr�QF�pv����V�@�N�Kj��.6c�>�͠i���̤D����V��Q�M.�ר�x�/7<���U[���K�e�S���i���\�Ȫ����F���M�مF��u?�����q�������4�
�Z���:���[!+O��Cs'?#�uPL�
�����,\b�B�%��-�,�Я:�e�?��#���|��\f�w��>X�܊xu��~�ޥ��u!#���E�1���H��x�n�D�@�t˥\|�]8��8�l&_{����`4�	�z��~.���c{�f��.hU�ix��Wؖ��Is��v�W�ES�7���=I=웭���kT�M7b߲r���������������62�_���U��T�זD~���+�iMT>VX��q�����\CW;U��|t�!���$E��>�w��'3�4�8P����z�N���z���f�$l�U��7'���8l<�7�F,Oa�x�sR`�F�*�!KD�>i�`~�h�DNݿtI�E��2 ��8�<RH.����PrOi����\���|������t�Ƌ��6@"�Px�f���p�Ve)���m;��6�2�w�WE��1���q�"�CptuF����9�nG��c�49U�͋�2�-�@X�-����R��k�����B��=~N�Y�K=e~7���_?�D�Y��H�"���F/HZ\y*���J�U�Y<&5Sp.X��+�E�t���>�K8�z�4�)n�>�=�5i�V)�А�|��I(������^�@%ڂu4Ӕ�O���)MBle�ەR}|�$���O/�D(x�Ftp:^�]Up?�*�J����|6b �J3:��.�&W���{CfIQTfI�<g*��rf�C1���Ce�+{ʎ��b���먞��sϣt:���#y1��͏�(�b�C�p"ɽeG�eaG$�)���Az0�c6Σ�.����aaU�C�!Ѝ@�po�8���]nz��%l��z܌@��Ҽ�&�s勛l���+����X�W�΢�r`lz������pV�۬���b�_I}��5IhGP6�F�Ceu���Eqr6?L>M���^��mO�P�F�!�G>`*�0 �CGR��T2�X`�D}��E�>��YJ>�13TYLU���ny8�p,7M3�-�ң�8,�c�+Ss���ⱞ��`WŮ~~~���F�˵|�/Dϑ-�q�Y�bR��jRN�P�7��P�b�u����l���s|���r^�>��o�w�E�#��1f&�d$z�!�V`��1�^�>ۉT?�Τ���X�^ _X���pj��g�S������$,k��)�=t�R`�����db5�����x��e8�J�9h��
$�zu?Q��#Y��%V������(���z�.��G;�Ekig��T
��#��o��^�M8Ҹ'L�v�(��n8MU�@,;����X���|���xօ�F*�W��ȩ'��Dj���*�'2��<w��L*�WuTWD��۬��ل�(�������8:�b����K��ĭC��jP�M�K�5oL�Xw"9��W��cI2G�=I6��~�#���"�����d^y�~�|sK͆�:Kͨ�FKM��/?�R�i��h��sb(r�"o3�v+���v��Kx5ي��3J	�~�9�Lc��#]%�&RƉ)thp	�7�gV8 䧭]��@ɋ��#����sX^	�(��tBMs�tBML��ȷ?Mք� L���d�������e���JQN���z�C�|��ª8�E�A?��Q�w
�Cͼ�~ֵ�w��1�d��O�u;���T�4sۊ��$��^�dT�FN���;6�AC��x{�Uz���׸_���S������]x�1n�2�d�rq�@+�:��J���yk'"�srH3���q�/~y�K�b�\Uƅ�~�,.d� 8�_�[Z�T+��5"6�������T2��-�:)ne���_L�����~��4�;D:l�|n5*��Eҹ�G�;މm��!���m	��۾�ܐ�N�n�� 	��I�J㛒T����B�G?�l��hy�-˱Z����hÛaƮ��vit��:���xl�&7*�IwD8�&_u�X�y�?J⢓�j�&?51�F��X��3趒8�-&��(���D�,���)>���b�-l)�N�;�t~��a��ep��_ǔ%o��cy㋢Yޑ��ڨ�6߃�d�Û�y(&O��KL�]��w�8�R�c���{���Y4��hj�-�~6iD�a��I���c5�f��Q�	�s���$	�Tx�.ǫO�땄�K��1�[Yt��
���o��5�%�#��[ñ��$=���G�E��;�S��O�����}�n=^��gKG�4A���Kҗ�Y��I$�����]�BK6����tY����,Vs�]{l>�d������.�Ȥ ��l�ࠂ��Gm�E�W�֣=(?�t�6�$����^"�ZY~�tfx�w����n��2���w���<�����ؐ��g�DOЏ��వ��I��odޅ��rR�������{��j����w�x�Ih���Eh�m|�![*�#v�Z����>�ѕ����F�Ԍf.��b�:e�V��se��S����*л�MS�v�?��("�u6z"h�v��_f� ��f�J0j�VN ����$�g0P�J����/n�*,T ���䠩�k}9w�s��8���
�>�M�v��j?n�"���|���WF��72��
�%K�,T��d�ӛp��mML�N%x�<���1�^Dl^ꦀ���w[�3�Ԏ��δ����������h�1�KjgP����J�PF.�T�4yƴ���C[f*!�{�&�d�e�����_��,�b��!���d�*9<N�$�f��8�N�O�*� M2����X~6�s7�#�n���1�L�t�_�"��-�05؂�������m�U��>Q�J����tD���Q���@��kWMMj��ܥq�f�۝���q/�ӣq���I����78�פ����iG� o��!V[�5J�ӈ5s�_F3������S���<�w��^�����T��f��V<P�U*^^�h{|�?1c�����`0���%♲O����aߥM��6�?r[w�w�	�.Dc��ړY��Y� �Z�P�����n=�ޙ�pR��:׿i���>�����C�}�j?')��@��I?=���$���ҵwV,�:������SA��G)*��k�荰���`9WR{Ʋ�-�6+�ܾ�_�cke�D'�(�]�Eu�m>~�>��	)a{�z�����5;�r��8��3F�7E�q1A(]�2F\��;�f#m�|i����n\�E�8���y�@2�����!����[$�|V!4��7Nv�3-O~�1M<l��ݩ߬���5��;x��}`T����f6*j� ��(Q�DA�dwa���lH $1��QQ���q�V|���mm�կ��ZĄW _���P�]��!�����̽��������w�7���̙3g�̝{�٥H�F����G�t���LI�O�d/�,��g�f찬�3�2v�L��s%;�\٥Xn��@J�������&���K�x��H��4H?��<�'�p���?.���iH�4�Ti���'"E�_��E�l�#͒��5l���_��p̮W\��[�%ْ"y>�<;u�âD$u��^�g����5C�rUA�bm���z����b�9Em%��7}Gl��/D+.T��ޤf��Iw�>cUB��2���K�q�_"����S��>1Apn`���k��aj�M�2�&OM�<�p��&Q��	��i����Uf���9{~J�C�;$�p�P���[��4�c�� ��u�T��Lq�%4���M?4T�l1!�̯�#μ��}��*]x�?��Rbx|\x�+���ќ���e_x�����G7#ˮy�� �,N+�?��U�:ѻ��V�ռ�D��pY���U�ú-t�y�e��v��ٛ����� �/�,>�(�u�zI�;8����䟦���nP�?=�CPYz�ֿ��i6Y�L�N-��=��6�K��IR���%RC*o�$?a~�J2:P���lɻ�Xe
"}����Ɨ�'6���\o^/�72/3�(�Q8.=kA"3��C)b�a�����`�5�|�M��b|�Qz\ҵ�|��%߽�כ%\��$"p�J�WDѸ�ɶ6d�e4�p^ӈ�Y$U�-r��tW3K]c&f�_���fpo6�&(+�ɇ�~��	�M�1F���-a]��F���ɰ.7^A��y!�̽	-�-�ђ�{F���@�3��@�0�@i��6eǑcG��7`��Ө��Y�(�܈"����R=�{y������@�g����Oy�5��/����k�K����S�3>����\�� c���u.�zhD� ��Mg� ���o@"�k���xQ �c�n�K_A�7pbu/�CP�S�A�j��F�&Y�����%_jN��Ůc$3� i*"�P��褆���P�$Cu�<�\�K�0j��_�Q�e�Y�-0H�M:��~
�Ɉ�寝!5�2��>��ߠ��������2���M�,�;�83��G���K��O9}��Z%O�a�������.����a��<�/�4�wۥ�����l�Aj����X�֘+�[��1��A{F�e�����9SGr�!�͌���v�cE	sx��F�]�D�&��
u�}:��'<���JB�y%�G�"@�+4��V$*Ch�yk�g��I��㗆�\}�-W���%�%O�A2>߆������:J��W8�����KM��1��^MJ����D-V_ɮİޣ
���~q42; Q��Ѓ�DN������ZQKr.U3�l�B��|�>G)녘��E�|z��uq�!V�ѳ��t���a��V,��)%A��B
����Z<m�ƕ��\�5N,�z�]�W���n<�	��V��ֆ�̣8��S�U�bR�gS�,�����	��:13@��X.�QX�ԥ�^	KT�޶��Գİ�X?P߀U-5��:��:p�T�E�޸��:v�N��T��U�%�ꛦ���dHx1�/u�S�6�H����K���1x�#خ9!:g�7�$YmmxN�����.$O� �KW#��˸ћ�~�0G�(]�~I�f�O���e�B)\�u(�ڡ$N)JF��U�M��V|j�V�J5/Z
��I���R yT�u^௘޹d��d����(B?N��57	��Ů�6�6��I�n���7�j�:��.�_j�h7@���{�1KMYEZ�!~J�P�*��:7뷎��h��,����%�O��`��~�X��ô����_�9N���d�<9'�GǪ�i�+���U������z�n�{����U��{��a�9��3�9�P\��e��̡���}��$5��+�e�Q^ފ��d�皳� b��f8���=���Hې�BL�5�X��m�ǧ����n�1�r����P\��f��*�`�_��1��sW/6�#��o;�'�+��R,�l�YG&s�4�BX��W|8OWa.[��K���``���۲u��Z�H��+��1���j_���[L�c�kS3V�'Jwc���]����V�����%��@�S�BE-j��8-������$�˻�@���o����Q�����l����֦X��rfz��90�=�,�v.�L����J"�y+eٟR�| �4�O�u�gk��5�K��:�~�lR�����(_�K��I�^�Vd�ԅG>�K�fS�Q|Rx�*5>%�7<�,T8�����f�e�_�����\�h����ɡ�>��-�.e��/,�ikEJ��N��z��R��=
�Yn�,3'�j[u9�AF�\�̽��W�,,姓�޷����&��t�	F���髾�/t�o߅��{I�G�SF�3?�|����Hd\�L�c�u�V��No�6�\)�HT��Nl��\X�~��]
�6)7� ��Ըo�Ұ:�k���X?w(-��""5c�	�F���(QK�Ɨ�ƛ8�)�����5�gF��i�Os�0ָ��
*O�\&n1:;.c|����h�|u#�_��>�(ֆ���+Ө<1��BZ�i���-,(Y#-�_4��\��-���M���^9�u;,��K�*o����/Ă��Y|�:��	s�R%ciay����?flp�$F��#~"��Q��Yt�X���$����5xĂ.� dU1zH>����^ǹjf���n4<a�v�1G��$5�w�*���]��t.$�>B{T�d	)O�O���6>�Z��g�^��DhO���А=�pfĘ�,e���uF��_�v�x��fw�(D��XыD!�j��
��{� si�b��� ?LL�)���Sj�=�i�6y\؞Ҵd�lI�q&l*]���q߀M��4�՗�n|�)�#�����c��ٜ��wn���57�D޳b3]�տ���E�%Q!oS;�g���ƌ����=l�cFD��"����|Y�^�-\����A����Hܮ�D�7��j��滳�OC�)zQ���c?.�{��J�.�5��eЇ�>C���b�"���	����5g�j�H�Rs��Ƈ���⥺�d?W�?��Hd�$�e9��ư��)3�P��e�=۲�4�Y�oh���9�`|p� n�y�&�e�l��kqo�@���
�yrsK�D�EwByd�J��K�e�Qv�Ÿ6��6�FE֬ ,�
�zl�6O��Z�|���oa<#)�6Z)5�2�k�2�/��T�"
,��η��u��eB�����5���])�j�r�Jz��U6?��3oɥY�o����w��U�X��Hŭ�ݴt0ֿz�v�
�$_����S�QZw�푌�OO�$�/�<�9�޸ΐ��/-�1���H+�{�a� 5m��>�gKb���H���R�"Rؑ".�����B�P`@���!ȏ���)};�J>�ʆ�\Ζ����IŌ
���fC`,�c�}�~�o�]�_��9o�Ŧ���F�w�P˫��_�x�+�"��C`ig�A��zN�c|����l2mr�$R����9�Ydի+����"��X0k����8�-.��O���v�g�w���� ����!߸.�.v�����vֵo�A��Oqѡ1���|�G;h�v��h���k4�%�̀leI���b$��Z�`�'S�g8�*?e~�_�q#�e��'w�Z�4��*�ӕ'�֙��=���e��h�o1
?jO�Gݘ��=\��ȴ�_��u���\)�πW�$#���x*򛖧ѝ@�v�lmn)r�9�vR��3a��JQ|�+�6�)��ʋ�n&�<�"���av��K/f|��� �`{��U��lؘN[7�p6�t#ϫ��f��f��́����� 7�|ci��&���6_��m��^T�bQl��~%nW�[��k[x߲�ǣ��Yc�D+�DuKM�$cI���PD��yH)��MhW.p����a���Z�Z�ǈĪ��@LUQCE�*��n*�mVm��ő���xUUuT�^�!=�Fb��*������Ou+������u����l�Z�_����w��8>�Y�6�U���]Iۘ��ա��VHi��ͽ��,n��%��ߠ��B��L#����ܸ>����]
X��O.��˒����2���#�˪��z� �@,�ܩdL��F�ac��`�>#J麘6)�.�k���*aa���Ӻ|L�1����c��T;�#�G�ݖ�[�W�ҢD�%����q=$�G�2x8��O_3�E�>o�ћ�����G�&r��'�k��T�~������@�7zUtM�qo�ۄ,,���O�"��}L�}aټI�O���a�22l�mjh�Lܶ4�.��dK��S��C�>���`�%Z1�d9��߶+��I�h=?�a�5R�>X�~�5�~�D	��38��9E����	�A�|y`�A�m�If/u@ԩƐ�o|�J�opKq�I �/�̉�U[�iW"�����˺��M�H=�
UU�B�r}�'�<vJ�+�잗�����t�#�("�
J�"��xZIIn�$9]�)�3aItݒ\HIF~�(��a�^����Ғ�nV�e�=�<�W�����������·=�b�^m��x����µ˅��bQ/j{(O]!�g�qb�e����0��=`���0u-�D���\D�6LO����rl�w��#VL�)��؀�M�yQ)-"�灸2?�K���AV�{p5�7�W#��F���I�ձ��z5�2��te���i��{"9LL"���s1��ܕ1*��x��ڮS]�#�KC)R��\C�*f�m���r�Qtkp�F�=~�G��2���N���z�Ȁ0��G�彉�c%G��!���vZ��.!+"�VQ�ʫ��8d����x	�F�b,u�`�46l�4%Y�63�p�i��c��0˥�({<��NIN
S�ӓ%uK*�������i���h��A��.>M���y��X?��g��>7����uːc!p�M�+��
��V�������.�U!���=�c5�U|5��G�+�obN^G��#Ş�5x�A���j��j�����	j|�,Z���ʧ������>rІ6�Ə�=W�o��]�/V��z ❙0%6�#z?c==�n��v!t�|6?)RMh�	�4��!���!��465]%vR�ˉ��>G,���4�:_�7�u�4�� �����4�'Hg��J�bnfE�YK\7m��&���W#�&��uW�#i˷P������m��W��ZB�dP�����4Rq*m?'r��h�O�y��RC�1k�����^����(""��{fu��#���h"
�6�t����x��뗺�Sy���E���,<4�uj�+E=�,�[��NG��a���M��m�7�ɟ�[�=z���(�a�Y��9boҥ���\�LE�����d��>��=�DBȇf����T�ᰝ�n�8R�=THSZ�4]��3;[y���@�Ϯ�A^ڙɃ��$���Q�+TJ3��'����K�h�n0g�
�Pۆ�
�#+^����Ok�C߈�%�mV�N4٩V ��yRm����������xR��0Sĩ	2v�F�\���琽�d\�y�/����:�G�Z|(�n��{����Bng�T��C�E��/��e�Z�o}=<T��QN�`�j��T]��B^Q�Jmc���dcPQ�A#�����=�������#�����鶣��"^�T�f�ZM�?$Oj�;���	��Z��F���x(���A寽D�_��ϏH�J$϶j���EE�bl�Z6���L��p1H�Q��Co����`3��m�������=��e�â��e�������e�c�N�z�e�黗P*^���|�Vu!A'��xU�.�~��_�ɽ/�����$�<w��T�c��h̠?M��*��2���'S�#j���j���I�
~4�o
-�&�/�P�D��א��� ��,w��)��{����R+��Wő/?�.B�b:��3l���M�l荀���w�0#id�5sĿ3x��4��bhϟQ��h�x0Y�ؕ����m��X���5��\v�<~��Ēj���u���;h�T��;%ɣ#v�z����
��d{����H;+.�Κ:Y[mS�@�=/�&�P�
Ԑ�]ŴN"�p�*�5[[fe���Ď:kq\&uh�A��V<4IIT�@^4����u�򃃥�bՊ�k!+�akKV�0D�׫�Y�և���I����J	j������;f�;&D���pJ��pù!;Mט??�?�&� ��`�j:�<�L/���������/����y�>R����w_<��:'t�o����o�C}E�����C}\7��L/�-�h����gr,�屳���2%Obv��C�m�)���\c�G���^��[��.�݉K˭�(�M[����� �3�A��x�ųEg1�50Ocf�~t���A��xK�q���$�3�$���$wT���?ɽO}�k��k/��ݸ��%|CiֶR�E��j�����R�\�<�7�O0z��+�;���Ļ�vy��i.$/����5�<R�Iq���4�:UWf�O���6�uU��|.s�Mn��|�w�A�����n��ˌ�=�Q=���I;��xz�W�)�'o�����m��hB�������c��3���G-�|�͸��Һ.�ɣ�ƕ����w'J='�[�kS�1�|�֬T��~�!z82�����7V�zw����&m`��ʧ�,qa^��[&���f� �v�F�0�����/���Mޤ��.8$��i��4{҇Aa��?mZM}�Og��z�	�C$?�,,v*~��v�X�t��c.�����}@{n�_�
>P�P�5���c𘛡V9��_i#�&��G�H�y�绖tn#���Ba���"�����D��;�6a(��`(�%����O�qצF���c��T��=�,^~@Q���Etc���"|��/ǫe��a�(�δl��5�t蓎$�C����;��UtT{�}�>p+=ʁ��GG�|C�����������]��
N,�.> ��Es`���:���Y��c��zn��W��g=�Y�32^��>8����F�E<�F��e'/e�ٕү{)�v�5r�M��H=�7{�f�7MI/^��+�e��90� �e6_�^�����Hc=|r/�ȅ�ȅV��A=J��R�i�췧�!�٤����v�%RHK�{�pC����IQ��iFﳈn��Ө�2��X��E�.q��Z������zh��RmT����2:2K�6p��#R=�WȆTR�i��������%z�:��j�=f��7��?����,�C������-���u}`g��T3���u��S�&��9���t��壥M�^�)�Hu�Aߴ���I>�ٷ\���Sx�u�J���'�%n�.C��SJpt�_r�ϧ�qz1໋g�U�1��џ�0p��W�ׄU����n���,Ni�Ǉ���ٯ���t��w�����zԟ��!�v�`��D���I���{~Ny���A�/�-b.��ޅ∻��q��yǍq���M����?��yؑ\�Pl�ٿۃKO�9�-��t�Q�V��Ȱ������������-z�;�ޣ�?��y릯Υ�������v+J��T��cU���@� L��{5�����ϻ�Jd��nJ�/۸�� |lh#��CU_k������)/k��v
N�8���B��RYXOt������ŏx,y�����EW�XӒ����ޑ���iZ�����f6UDf8�`����f��ڭ�on�hզ�T*�b�BoItZ��>�֔ӿ�~�뾶y�%�?@�F|�~;�+�����{�Jrg��94��05�Dj0���Z�d꟠�0� {�v����*76�����y>�<(�<����4#w�+��?�I�&0Z�0M�oԭx�qֺIo�2���Y��pVSm"V���٨ǎ�	�������D�Ƀ���Om����V�ߊ�����Fϧ0}�!����\^f��.��6N�:uj�2��W�|ISt;��M'��K��0���0V��k���]r-�5� _��WM3�U���-�;�,냗��n�7��2�+	�)��܇d��D�V��,y�̡�}7��b�)��JP�ß8��|T�V�^m�?�Wo�TZ��ИJ�/���ݮ���Z�)��ibQ��kZ>C9hox�w_�xy��M�?�D=�^���.|��0`[m��o^q#u*Y�|���n�:!F��'�NE�&�c�N�nc#:u{x�n�4D���j��Ԇ�N"�Y֫�j9��Vx�_�(]*�.�(���u.�u�D׍Eוͼ}3�O�Ē���E��~������_�������6�4�T�oq
ƝM�޸)i(+��6:# ���������{~��pEa�lI���ƽs&�5����Oj�)ō	do��+��!�0�Y�P<���[�aѬ��8��n�2�������n+y��O�>'/�ǳZ����Գj[8I׭�{x'E;�[j��!�O^J�4���Y�X����v2Y�/m}���vE�)�9���V�J�m~� LL�lP*)�b�^B[�	�*J_2P�]%a�(o#2��A ,��H͛���
̆�䐎���g(�*S�gf4R�!}��H���^�R�r��)Rz����E�	���[�a���g���v��{�I"&<��?.�c̏���L^И
�Wq[�
��{�%I�����d�a�a�I�A��TJ�n��!�m�s9)�ʷ�dɳ-ٿ�M�
���3Qa���&	 �t���=(W��C!��f�F�̃"�bNp�a��%*N�k��ն�<F&vC���^5A���$d�/�?F����-W���o��If����ׅ7뤺v�u���Vk�N����L�Z��|�?r�{�ޝ�h�����'ߦ�fƉ[���w�䯥��uM�'��20���ڜGy�[�]C�]��V����8��^�d���xbj�k\g�=m�NEdvK�w�wy>�4�vg<�y�S��SI�FA�">5���d�ʧ�>�-�[]��6�d�
Ocv��)��nѹLdx焥!"�"}t"���DO'�F���P�%�p �_���n1Q��2H���Yx�[�$w��͠Rȏ,CAF���べ�G���j��X�5�����N��*o.mj�'��T|3�F�`���`��M�� 7O'�o�x�f���ͦ5��+��W0�fq�cW=q}!����uQ�����%�͞��-�2[�Z�{�"�/�>�������XJ��(��u�q��t�]�x���nXt�/=nI�<"��?~���f]�>�x��Զ@�������%ϗz񕁬�j�aQ�Y��c\���N�i�P�x�e
Zд�