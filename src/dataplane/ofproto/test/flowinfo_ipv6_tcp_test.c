/*
 * Copyright 2014 Nippon Telegraph and Telephone Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "unity.h"

#include "lagopus/dpmgr.h"
#include "lagopus/flowdb.h"
#include "lagopus/port.h"
#include "match.h"
#include "pktbuf.h"
#include "packet.h"
#include "lagopus/dataplane.h"
#include "lagopus/flowinfo.h"
#include "lagopus/ptree.h"
#include "datapath_test_misc.h"
#include "datapath_test_misc_macros.h"
#include "datapath_test_match.h"
#include "datapath_test_match_macros.h"
#include "flowinfo_test.h"

#define FLOW_ADD_UT_PREREQUISITE(_x)		\
  FLOW_ADD_IPV6_TCP_PREREQUISITE(_x)
#define	TEST_ASSERT_FLOW_MATCH_UT_PREREQUISITE(_x)	\
  TEST_ASSERT_FLOW_MATCH_IPV6_TCP_PREREQUISITE(_x)
#define	ETHERTYPE_UT	ETHERTYPE_IPV6
#define	IPPROTO_UT	IPPROTO_TCP

#include "flowinfo_l4_test.c"


/*
 * The TCP header matches are stored in the leaf basic flowinfo.  del
 * -> 2*add -> 3*del is hence sufficient.
 */

void
test_flowinfo_ipv6_tcp_src_adddel(void) {
  size_t s;

  TEST_ASSERT_OBJECTS();

  /* Add the TCP source port matches. */
  for (s = 0; s < ARRAY_LEN(test_flow); s++) {
    FLOW_ADD_TCP_SRC_MATCH(test_flow[s], TEST_L4_PORT(s));
  }

  /* Run the sideeffect-free scenario. */
  TEST_SCENARIO_FLOWINFO_SEF(flowinfo);

  /* Reset the matches.  Mind the prerequisite. */
  for (s = 0; s < ARRAY_LEN(test_flow); s++) {
    TAILQ_INIT(&test_flow[s]->match_list);
    FLOW_ADD_IPV6_TCP_PREREQUISITE(test_flow[s]);
  }
}

void
test_flowinfo_ipv6_tcp_dst_adddel(void) {
  size_t s;

  TEST_ASSERT_OBJECTS();

  /* Add the TCP destination port matches. */
  for (s = 0; s < ARRAY_LEN(test_flow); s++) {
    FLOW_ADD_TCP_DST_MATCH(test_flow[s], TEST_L4_PORT(s));
  }

  /* Run the sideeffect-free scenario. */
  TEST_SCENARIO_FLOWINFO_SEF(flowinfo);

  /* Reset the matches.  Mind the prerequisite. */
  for (s = 0; s < ARRAY_LEN(test_flow); s++) {
    TAILQ_INIT(&test_flow[s]->match_list);
    FLOW_ADD_IPV6_TCP_PREREQUISITE(test_flow[s]);
  }
}
