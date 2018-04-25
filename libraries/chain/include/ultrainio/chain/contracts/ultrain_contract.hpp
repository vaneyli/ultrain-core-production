/**
 *  @file
 *  @copyright defined in ultrain/LICENSE.txt
 */
#pragma once

#include <ultrainio/chain/apply_context.hpp>

#include <ultrainio/chain/types.hpp>

namespace ultrainio { namespace chain { namespace contracts {

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_ultrainio_newaccount(apply_context&);
   void apply_ultrainio_updateauth(apply_context&);
   void apply_ultrainio_deleteauth(apply_context&);
   void apply_ultrainio_linkauth(apply_context&);
   void apply_ultrainio_unlinkauth(apply_context&);

   void apply_ultrainio_postrecovery(apply_context&);
   void apply_ultrainio_passrecovery(apply_context&);
   void apply_ultrainio_vetorecovery(apply_context&);

   void apply_ultrainio_setcode(apply_context&);
   void apply_ultrainio_setabi(apply_context&);

   void apply_ultrainio_onerror(apply_context&);

   void apply_ultrainio_canceldelay(apply_context&);
   ///@}  end action handlers

} } } /// namespace ultrainio::contracts
