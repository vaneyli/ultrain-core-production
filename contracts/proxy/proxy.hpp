/**
 *  @file
 *  @copyright defined in ultrain/LICENSE.txt
 */
#include <ultrainiolib/ultrainio.hpp>

namespace proxy {
   
   //@abi action
   struct PACKED( set_owner ) {
      account_name owner;
      uint32_t     delay;
   };

   //@abi table
   struct config {
      config(){}
      constexpr static uint64_t key = N(config);
      account_name        owner = 0;
      uint32_t            delay = 0;
      uint32_t            next_id = 0;
   };

} /// namespace proxy
