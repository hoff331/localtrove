<?php

// ======================================
// CONDITIONS
// ======================================
/*
 * Conditions:
 * + Check the status of a pay to publish node
 */

/**
 * Implements hook_rules_condition_info().
 * @ingroup rules
 */
function ms_paypublish_rules_condition_info() {
  return array(
    'ms_paypublish_condition_pp_node_status' => array(
      'label' => t('Check the status of the Pay to Publish Node Record'),
      'parameter' => array(
        'pp_node' => array('type' => 'ms_paypublish', 'label' => t('Pay to Publish Node Record')),
        'status' => array('type' => 'text', 'label' => t('Status'), 'options list' => 'ms_paypublish_get_statuses'),
      ),
      'group' => 'Pay to Publish',
    ),
    'ms_paypublish_condition_pp_plan_is' => array(
      'label' => t('Pay to Publish Plan is equal to'),
      'parameter' => array(
        'plan' => array('type' => 'ms_paypublish_plan', 'label' => t('Pay to Publish Plan')),
        'pid' => array('type' => 'text', 'label' => t('Pay to Publish Plan'), 'options list' => 'ms_paypublish_get_plans'),
      ),
      'group' => 'Pay to Publish',
    ),
  );
}

/**
 * Condition: Check the status of a pay to publish node
 */
function ms_paypublish_condition_pp_node_status($pp_node, $status) {
  return $pp_node->status == $status;
}

/**
 * Condition: Check what the plan is
 */
function ms_paypublish_condition_pp_plan_is($plan, $pid) {
  return $plan->pid == $pid;
}
// ======================================
// ACTIONS
// ======================================

/*
 * Actions:
 * + Set Expiration Date for User Pay to Publish Node Record
 * + Change Pay to Publish Node Status
 * + Load Node from PTP Node Record
 * + Load PTP Node Record from Node
 */

/**
 * Implements hook_rules_action_info().
 * @ingroup rules
 */
function ms_paypublish_rules_action_info() {
  return array(
    'ms_paypublish_action_load_node' => array(
      'label' => t('Load the node for a Pay to Publish Node Record'),
      'parameter' => array(
        'pp_node' => array('type' => 'ms_paypublish_node', 'label' => t('Pay to Publish Node Record')),
      ),
      'provides' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
        ),
      ),
      'group' => 'Pay to Publish',
    ),
    'ms_paypublish_action_load_pp_node' => array(
      'label' => t('Load the Pay to Publish Node Record from a node'),
      'parameter' => array(
        'node' => array('type' => 'node', 'label' => t('Node')),
      ),
      'provides' => array(
        'pp_node' => array(
          'type' => 'ms_paypublish_node',
          'label' => t('Pay to Publish Node Record'),
        ),
      ),
      'group' => 'Pay to Publish',
    ),
    'ms_paypublish_action_change_pp_node_expiration' => array(
      'label' => t('Change the Expiration Date of a Pay to Publish Node'),
      'parameter' => array(
        'pp_node' => array('type' => 'ms_paypublish_node', 'label' => t('Pay to Publish Node')),
        'expiration' => array('type' => 'date', 'label' => t('Date')),
      ),
      'group' => 'Pay to Publish',
    ),
    'ms_paypublish_action_change_pp_node_status' => array(
      'label' => t('Change the Status of a Pay to Publish Node'),
      'parameter' => array(
        'pp_node' => array('type' => 'ms_paypublish_node', 'label' => t('Pay to Publish Node')),
        'status' => array('type' => 'text', 'label' => t('Status'), 'options list' => 'ms_paypublish_get_statuses'),
      ),
      'group' => 'Pay to Publish',
    ),
  );
}

/**
 * Action: Change the status of a paypublish
 */
function ms_paypublish_action_change_pp_node_status($pp_node, $status) {
  // Change the pay to publish node Status
  return ms_paypublish_change_node_status($pp_node->id, $status);
}

/**
 * Action: Load a node from a Pay to Publish Node
 */
function ms_paypublish_action_load_node($pp_node) {
  $node = node_load($pp_node->nid);
  return array('node' => $node);
}

/**
 * Action: Load a Pay to Publish Node from a Node
 */
function ms_paypublish_action_load_pp_node($node) {
  $pp_node = ms_paypublish_load_node_nid($node->nid);
  return array('pp_node' => $pp_node);
}

/**
 * Action: Change the expiration date of a pay to publish node
 */
function ms_paypublish_action_change_pp_node_expiration($pp_node, $expiration) {
  return ms_paypublish_change_node_expiration($pp_node->id, $expiration);
}

// ======================================
// TRIGGERS
// ======================================

/*
 * Triggers:
 * + Pay to Publish Node is purchased
 * + Pay to Publish Node is expiring
 * + Pay to Publish Node is cancelled
 * + Pay to Publish Node has a payment
 */

/**
 * Implements hook_rules_event_info()
 */
function ms_paypublish_rules_event_info() {
  $items = array(
    'ms_paypublish_event_paypublish_cancel' => array(
      'label' => t('Pay to Publish Node Cancelled'),
      'group' => 'Pay to Publish',
      'help' => t("Triggers when a Pay to Publish Node is cancelled."),
      'variables' => array(
        'account' => array('type' => 'user', 'label' => t('User Account')),
        'node' => array('type' => 'node', 'label' => t('Pay to Publish Node')),
        'pp_node' => array('type' => 'ms_paypublish_node', 'label' => t('Pay to Publish Node Record')),
        'plan' => array('type' => 'ms_paypublish_plan', 'label' => t('Pay to Publish Plan')),
      ),
    ),
    'ms_paypublish_event_paypublish_purchase' => array(
      'label' => t('Pay to Publish Node Purchase'),
      'group' => 'Pay to Publish',
      'help' => t("Triggers when a user pays to publish a new node."),
      'variables' => array(
        'account' => array('type' => 'user', 'label' => t('User Account')),
        'node' => array('type' => 'node', 'label' => t('Pay to Publish Node')),
        'pp_node' => array('type' => 'ms_paypublish_node', 'label' => t('Pay to Publish Node Record')),
        'plan' => array('type' => 'ms_paypublish_plan', 'label' => t('Pay to Publish Plan')),
      ),
    ),
    'ms_paypublish_event_paypublish_payment' => array(
      'label' => t('Pay to Publish Node Payment Received'),
      'group' => 'Pay to Publish',
      'help' => t("Triggers when a payment is received for a paypublish."),
      'variables' => array(
        'account' => array('type' => 'user', 'label' => t('User Account')),
        'node' => array('type' => 'node', 'label' => t('Pay to Publish Node')),
        'pp_node' => array('type' => 'ms_paypublish_node', 'label' => t('Pay to Publish Node Record')),
        'plan' => array('type' => 'ms_paypublish_plan', 'label' => t('Pay to Publish Plan')),
      ),
    ),
    'ms_paypublish_event_paypublish_expiring' => array(
      'label' => t('Pay to Publish Node Expiring'),
      'group' => 'Pay to Publish',
      'help' => t("Triggers when a Pay to Publish Node is expiring."),
      'variables' => array(
        'account' => array('type' => 'user', 'label' => t('User Account')),
        'node' => array('type' => 'node', 'label' => t('Pay to Publish Node')),
        'pp_node' => array('type' => 'ms_paypublish_node', 'label' => t('Pay to Publish Node Record')),
        'plan' => array('type' => 'ms_paypublish_plan', 'label' => t('Pay to Publish Plan')),
      ),
    ),
  );

  return $items;
}


// ======================================
// DATA TYPES
// ======================================

/**
 * Implements hook_rules_data_type_info().
 */
function ms_paypublish_rules_data_info() {
  return array(
    'ms_paypublish_plan' => array(
      'label' => t('Pay to Publish Plan'),
      'class' => 'rules_data_type_ms_paypublish_plan',
      'wrap' => TRUE,
      'group' => 'Pay to Publish',
    ),
    'ms_paypublish' => array(
      'label' => t('Pay to Publish Node Record'),
      'wrap' => TRUE,
      'group' => 'Pay to Publish',
    ),
  );
}
