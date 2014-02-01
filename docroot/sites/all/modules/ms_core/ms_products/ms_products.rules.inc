<?php

/**
 * @file
 * Products API Rules Includes
 * Licensed under the GNU GPLv2 License
 *
 */

// ======================================
// RULES - CONDITIONS
// ======================================

/*
 * Conditions:
 * + Check if user has a purchase
 * + Check what the Product Plan is
 * - Check the status of a purchase
 */

/**
 * Implements hook_rules_condition_info().
 */
function ms_products_rules_condition_info() {
  return array(
    'ms_products_condition_user_has_purchase' => array(
      'label' => t('Check if user has purchase'),
      'parameter' => array(
        'pid' => array(
          'type' => 'integer',
          'label' => t('Product Plan'),
          'options list' => 'ms_products_get_plans',
        ),
        'account' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
      'group' => 'MS Products',
    ),
    'ms_products_condition_product_plan_is' => array(
      'label' => t('Product Plan is equal to'),
      'parameter' => array(
        'pid' => array(
          'type' => 'integer',
          'label' => t('Product Plan'),
          'options list' => 'ms_products_get_plans',
        ),
        'product_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('Product Plan'),
        ),
      ),
      'group' => 'MS Products',
    ),
  );
}

/**
 * Condition: Check if a user has the purchase
 */
function ms_products_condition_user_has_purchase($pid, $account) {
  if (ms_products_user_has_purchase($account->uid, $pid)) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Condition: Check what the Product Plan is
 */
function ms_products_condition_product_plan_is($pid, $product_plan) {
  if ($product_plan->pid == $pid) {
    return TRUE;
  }
  return FALSE;
}

// ======================================
// RULES - ACTIONS
// ======================================

/*
 * Actions:
 * + Add Purchase to User
 * + Set Expiration Date for User Purchase
 * + Change Purchase Status (Active, Cancelled, EOT, etc)
 * - Load Purchase from User
 * - Load Product Plan
 */

/**
 * Implements hook_rules_action_info().
 */
function ms_products_rules_action_info() {
  return array(
    'ms_products_action_add_purchase' => array(
      'label' => t('Add a Purchase to a User'),
      'parameter' => array(
        'pid' => array(
          'type' => 'integer',
          'label' => t('Product Plan'),
          'options list' => 'ms_products_get_plans',
        ),
        'account' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
      'provides' => array(
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('New purchase'),
        ),
      ),
      'group' => 'MS Products',
    ),
    'ms_products_action_change_purchase_expiration' => array(
      'label' => t('Change the Expiration Date of a Purchase'),
      'parameter' => array(
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'expiration' => array(
          'type' => 'date',
          'label' => t('Date'),
        ),
      ),
      'group' => 'MS Products',
    ),
    'ms_products_action_change_purchase_status' => array(
      'label' => t('Change the Status of a Purchase'),
      'parameter' => array(
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'status' => array(
          'type' => 'integer',
          'label' => t('Status'),
          'options list' => 'ms_products_get_purchase_statuses',
        ),
      ),
      'group' => 'MS Products',
    ),
  );
}

/**
 * Action: Change the status of a purchase
 */
function ms_products_action_change_purchase_status($purchase, $status) {
  // Change the Purchase Status
  return ms_products_change_purchase_status($purchase->mid, $status);
}

/**
 * Action: Add a purchase to a user
 */
function ms_products_action_add_purchase($pid, $account) {
  $product_plan = ms_products_load_product_plan($pid);

  // Add a new purchase for this user
  $purchase = ms_products_insert_new_purchase($product_plan, $account);

  return array('purchase' => $purchase);
}

/**
 * Action: Change the expiration date of a purchase
 */
function ms_products_action_change_purchase_expiration($purchase, $expiration) {
  return ms_products_change_purchase_expiration($purchase->mid, $expiration);
}

// ======================================
// RULES - EVENTS
// ======================================

/*
 * Events:
 * + Purchase is added to a user
 * + Purchase is marked as expiring soon
 * + Purchase is expiring
 * + Purchase is cancelled
 * + Purchase has a payment
 * + Purchase is renewed
 * + Purchase is modified
 */

/**
 * Implements hook_rules_event_info()
 */
function ms_products_rules_event_info() {
  $items = array(
    'ms_products_event_purchase_cancel' => array(
      'label' => t('Purchase Cancelled'),
      'group' => 'MS Products',
      'help' => t("Triggers when a purchase is cancelled."),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Purchase Account'),
        ),
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'product_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('Product Plan'),
        ),
      ),
    ),
    'ms_products_event_purchase_signup' => array(
      'label' => t('Purchase Signup'),
      'group' => 'MS Products',
      'help' => t("Triggers when a user signs up for a new purchase."),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Purchase Account'),
        ),
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'product_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('Product Plan'),
        ),
      ),
    ),
    'ms_products_event_purchase_modification' => array(
      'label' => t('Purchase Modification'),
      'group' => 'MS Products',
      'help' => t("Triggers when a user modifies their purchase."),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Purchase Account'),
        ),
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'new_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('New Product Plan'),
        ),
        'old_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('Old Product Plan'),
        ),
      ),
    ),
    'ms_products_event_purchase_renewal' => array(
      'label' => t('Purchase Renewal'),
      'group' => 'MS Products',
      'help' => t("Triggers when a user renews their purchase."),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Purchase Account'),
        ),
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'product_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('Product Plan'),
        ),
      ),
    ),
    'ms_products_event_purchase_payment' => array(
      'label' => t('Purchase Payment'),
      'group' => 'MS Products',
      'help' => t("Triggers when a payment is received for a purchase."),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Purchase Account'),
        ),
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'product_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('Product Plan'),
        ),
      ),
    ),
    'ms_products_event_purchase_expiring_soon' => array(
      'label' => t('Purchase Expiring Soon'),
      'group' => 'MS Products',
      'help' => t("Triggers when a purchase is marked as expiring soon."),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Purchase Account'),
        ),
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'product_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('Product Plan'),
        ),
      ),
    ),
    'ms_products_event_purchase_expiring' => array(
      'label' => t('Purchase Expiring'),
      'group' => 'MS Products',
      'help' => t("Triggers when a purchase is expiring."),
      'variables' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('Purchase Account'),
        ),
        'purchase' => array(
          'type' => 'ms_purchase',
          'label' => t('Purchase'),
        ),
        'product_plan' => array(
          'type' => 'ms_products_plan',
          'label' => t('Product Plan'),
        ),
      ),
    ),
  );

  return $items;
}


/*
 * Data Types:
 * + Purchase
 * + Product Plan
 */

/**
 * Implements hook_rules_data_info()
 */
function ms_products_rules_data_info() {
  return array(
    'ms_products_plan' => array(
      'label' => t('Product Plan'),
      'wrap' => TRUE,
      'group' => t('MS Products'),
    ),
    'ms_purchase' => array(
      'label' => t('Purchase'),
      'wrap' => TRUE,
      'group' => t('MS Products'),
    ),
  );
}