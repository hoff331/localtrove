<?php

/**
 * @file
 * MS Core Forms Includes
 * Licensed under the GNU GPLv2 License
 *
 */

/**
 * Order Form
 */
function ms_core_order_form($form, &$form_state, $action = 'add', $order_key = NULL) {
  drupal_add_library('system','ui.datepicker');
  drupal_add_js('jQuery(document).ready(function(){jQuery( ".pickadate" ).datepicker({
      dateFormat: "mm/dd/yy",
      autoSize: true
    });});', 'inline');
  $is_edit = FALSE;
  $form['order'] = array(
    '#type' => 'fieldset',
    '#title' => t('Order'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  if ($action == 'edit') {
    $is_edit = TRUE;
    $order = ms_core_order_load_by_key($order_key);
    $account = user_load($order->uid);

    // Show the products for the order
    $form['products'] = array(
      '#type' => 'fieldset',
      '#title' => t('Products'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

    // Show an add product link
    $form['products']['add_product_link'] = array(
      '#type' => 'item',
      '#markup' => l(t('Add Product'), 'admin/moneyscripts/products/add/' . $order->order_key, array('attributes' => array('class' => array('ms_core_edit_order_add_product_link')))),
    );

    foreach ($order->products as $prod_num => $product) {
      $form['products']['product_' . $prod_num . '_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => check_plain($product->name),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      // Show the Actions available for this payment
      $product_actions = array();
      $product_actions[] = l(t('Remove'), 'admin/moneyscripts/products/remove/' . $product->order_product_id);

      // Display details about the payment
      $headers = array(array(
          'data' => t('Product Details'),
          'colspan' => 2,
        ));
      $rows = array();
      $rows[] = array(t('Actions'), implode(' | ', $product_actions));
      $rows[] = array(t('Module'), $product->module);
      $rows[] = array(t('Amount'), ms_core_get_recurring_string($product->recurring_schedule, ($product->type == 'recurring')));
      $rows[] = array(t('Type'), $product->type);

      $form['products']['product_' . $prod_num . '_fieldset']['product_' . $prod_num . '_details'] = array(
        '#type' => 'item',
        '#markup' => theme('table', array('header' => $headers, 'rows' => $rows, 'attributes' => array())),
      );
    }

    // Show the payments for the order
    $form['payments'] = array(
      '#type' => 'fieldset',
      '#title' => t('Payments'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

    // Show an add payment link
    $form['payments']['add_payment_link'] = array(
      '#type' => 'item',
      '#markup' => l(t('Add Payment'), 'admin/moneyscripts/payments/add/' . $order->order_key, array('attributes' => array('class' => array('ms_core_edit_order_add_payment_link')))),
    );

    foreach ($order->payments as $pid => $payment) {
      $form['payments']['payment_' . $pid . '_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => check_plain(ms_core_get_payment_type($payment->type) . ' - ' . format_date($payment->created)),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      // Show the Actions available for this payment
      $payment_actions = array();
      $payment_actions[] = l(t('Edit'), 'admin/moneyscripts/payments/edit/' . $payment->pid);
      $payment_actions[] = l(t('Delete'), 'admin/moneyscripts/payments/delete/' . $payment->pid);
      $payment_actions[] = l(t('Resubmit'), 'admin/moneyscripts/payments/resubmit/' . $payment->pid);

      // Display details about the payment
      $headers = array(array(
          'data' => t('Payment Details'),
          'colspan' => 2,
        ));
      $rows = array();
      $rows[] = array(t('Actions'), implode(' | ', $payment_actions));
      $rows[] = array(t('Amount'), ms_core_format_money($payment->amount, $payment->currency, 'payment_amount'));
      $rows[] = array(t('Type'), ms_core_get_payment_type($payment->type));
      $rows[] = array(t('Date'), format_date($payment->created));
      $rows[] = array(t('Gateway'), ms_core_get_gateway_name($payment->gateway));
      if ($payment->transaction) {
        $rows[] = array(t('Transaction ID'), $payment->transaction);
      }
      if ($payment->recurring_id) {
        $rows[] = array(t('Recurring ID'), $payment->recurring_id);
      }

      $form['payments']['payment_' . $pid . '_fieldset']['payment_' . $pid . '_details'] = array(
        '#type' => 'item',
        '#markup' => theme('table', array('header' => $headers, 'rows' => $rows, 'attributes' => array())),
      );
    }

    $form['order']['oid'] = array(
      '#type' => 'value',
      '#value' => $order->oid,
    );
    $form['order']['orderid'] = array(
      '#type' => 'textfield',
      '#title' => t('Order ID'),
      '#size' => 32,
      '#maxlength' => 64,
      '#disabled' => TRUE,
      '#description' => t("The ID of this Order"),
      '#value' => $order->order_number,
    );
  }

  $today = REQUEST_TIME;
  $form['order']['created'] = array(
    '#type' => 'textfield',
    '#title' => t('Date Created'),
    '#default_value' => ($is_edit) ? date('m/d/Y', $order->created) : 0,
    '#description' => t("Enter any date in the MM/DD/YYYY format (or any other format supported by strtotime())."),
    '#attributes' => array('class' => array('pickadate')),
  );
  $form['order']['username'] = array(
    '#type' => 'textfield',
    '#title' => t('User'),
    '#size' => 32,
    '#maxlength' => 64,
    '#description' => t("The User for this Order"),
    '#autocomplete_path' => 'admin/structure/ms_core/autocomplete',
    '#required' => TRUE,
    '#default_value' => ($is_edit) ? $account->name : '',
  );
  $form['order']['order_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => array(
      'recurring' => t('Recurring'),
      'cart' => t('Cart'),
    ),
    '#description' => t("The type of order"),
    '#required' => TRUE,
    '#default_value' => ($is_edit) ? $order->order_type : 'cart',
  );
  $form['order']['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#options' => ms_core_get_order_statuses(),
    '#description' => t("The status of this order"),
    '#required' => TRUE,
    '#default_value' => ($is_edit) ? $order->status : '',
  );
  $form['order']['gateway'] = array(
    '#type' => 'select',
    '#title' => t('Gateway'),
    '#options' => ms_core_get_payment_gateways_list(),
    '#description' => t("The gateway for this order"),
    '#required' => TRUE,
    '#default_value' => ($is_edit) ? $order->gateway : '',
  );
  $form['order']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#size' => 32,
    '#maxlength' => 64,
    '#description' => t("The first name of the Customer"),
    '#default_value' => ($is_edit) ? $order->first_name : '',
  );
  $form['order']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#size' => 32,
    '#maxlength' => 64,
    '#description' => t("The last name of the Customer"),
    '#default_value' => ($is_edit) ? $order->last_name : '',
  );
  $form['order']['email_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#size' => 64,
    '#maxlength' => 255,
    '#default_value' => ($is_edit) ? $order->email_address : '',
  );
  $form['order']['currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#options' => ms_core_get_currencies(),
    '#description' => t("The currency for this order"),
    '#required' => TRUE,
    '#default_value' => ($is_edit) ? $order->currency : '',
  );

  // Billing Address
  $form['order']['billing_address'] = array(
    '#type' => 'fieldset',
    '#title' => t('Billing Address'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['order']['billing_address']['billing_street'] = array(
    '#type' => 'textfield',
    '#title' => t('Street'),
    '#size' => 32,
    '#maxlength' => 64,
    '#default_value' => ($is_edit) ? $order->billing_address['street'] : '',
  );
  $form['order']['billing_address']['billing_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 32,
    '#maxlength' => 64,
    '#default_value' => ($is_edit) ? $order->billing_address['city'] : '',
  );
  $form['order']['billing_address']['billing_state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
    '#maxlength' => 15,
    '#default_value' => ($is_edit) ? $order->billing_address['state'] : '',
  );
  $form['order']['billing_address']['billing_zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip Code'),
    '#size' => 32,
    '#maxlength' => 15,
    '#default_value' => ($is_edit) ? $order->billing_address['zip'] : '',
  );
  $form['order']['billing_address']['billing_country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#options' => ms_core_get_countries('iso'),
    '#default_value' => ($is_edit) ? $order->billing_address['country'] : '',
  );
  $form['order']['billing_address']['billing_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone Number'),
    '#size' => 32,
    '#maxlength' => 32,
    '#default_value' => ($is_edit) ? $order->billing_address['phone'] : '',
  );

  // Shipping Address
  $form['order']['shipping_address'] = array(
    '#type' => 'fieldset',
    '#title' => t('Shipping Address'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['order']['shipping_address']['shipping_street'] = array(
    '#type' => 'textfield',
    '#title' => t('Street'),
    '#size' => 32,
    '#maxlength' => 64,
    '#default_value' => ($is_edit) ? $order->shipping_address['street'] : '',
  );
  $form['order']['shipping_address']['shipping_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 32,
    '#maxlength' => 64,
    '#default_value' => ($is_edit) ? $order->shipping_address['city'] : '',
  );
  $form['order']['shipping_address']['shipping_state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 32,
    '#maxlength' => 15,
    '#default_value' => ($is_edit) ? $order->shipping_address['state'] : '',
  );
  $form['order']['shipping_address']['shipping_zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip Code'),
    '#size' => 32,
    '#maxlength' => 15,
    '#default_value' => ($is_edit) ? $order->shipping_address['zip'] : '',
  );
  $form['order']['shipping_address']['shipping_country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#options' => ms_core_get_countries('iso'),
    '#default_value' => ($is_edit) ? $order->shipping_address['country'] : '',
  );
  $form['order']['shipping_address']['shipping_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone Number'),
    '#size' => 32,
    '#maxlength' => 32,
    '#default_value' => ($is_edit) ? $order->shipping_address['phone'] : '',
  );

  // Show the recurring schedule edit fprm if applicable
  if ($is_edit AND $order->order_type == 'recurring' AND $gateway = ms_core_get_gateway($order->gateway) AND !empty($gateway['recurring_schedule_support']) AND $recurring_schedule = ms_core_load_recurring_schedule($order->oid)) {
    $form['order']['recurring_schedule'] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Recurring Schedule'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t("Here you can view and edit the recurring schedule for
        this order. Changing these values will change when the user is billed
        next, and for how much and how long. Be very careful about changing these
        values!")
    );
    $form['order']['recurring_schedule']['change_recurring_schedule'] = array(
      '#type' => 'checkbox',
      '#title' => t("Change the Recurring Schedule?"),
      '#description' => t("Click this in order to change the recurring schedule
        values below. Note that there is generally no reason to change the values
        in the recurring schedule."),
    );
    $form['order']['recurring_schedule']['status'] = array(
      '#type' => 'select',
      '#title' => t('Status'),
      '#options' => array(
        'active' => t('Active'),
        'cancelled' => t('Cancelled'),
        'expiring' => t('Expiring'),
      ),
      '#default_value' => $recurring_schedule->status,
    );
    $form['order']['recurring_schedule']['main_amount'] = array(
      '#type' => 'textfield',
      '#title' => t('Main Amount'),
      '#default_value' => $recurring_schedule->main_amount,
    );
    $form['order']['recurring_schedule']['main_length'] = array(
      '#type' => 'textfield',
      '#title' => t('Main Length'),
      '#default_value' => $recurring_schedule->main_length,
    );
    $form['order']['recurring_schedule']['main_unit'] = array(
      '#type' => 'select',
      '#title' => t('Main Unit'),
      '#options' => array(
        'H' => t('Hours'),
        'D' => t('Days'),
        'W' => t('Weeks'),
        'M' => t('Months'),
        'Y' => t('Years'),
      ),
      '#default_value' => $recurring_schedule->main_unit,
    );
    $form['order']['recurring_schedule']['trial_amount'] = array(
      '#type' => 'textfield',
      '#title' => t('Trial Amount'),
      '#default_value' => $recurring_schedule->trial_amount,
    );
    $form['order']['recurring_schedule']['trial_length'] = array(
      '#type' => 'textfield',
      '#title' => t('Trial Length'),
      '#default_value' => $recurring_schedule->trial_length,
    );
    $form['order']['recurring_schedule']['trial_unit'] = array(
      '#type' => 'select',
      '#title' => t('Trial Unit'),
      '#options' => array(
        'H' => t('Hours'),
        'D' => t('Days'),
        'W' => t('Weeks'),
        'M' => t('Months'),
        'Y' => t('Years'),
      ),
      '#default_value' => $recurring_schedule->trial_unit,
    );
    $form['order']['recurring_schedule']['total_occurrences'] = array(
      '#type' => 'textfield',
      '#title' => t('Total Occurrences'),
      '#default_value' => $recurring_schedule->total_occurrences,
    );
    $form['order']['recurring_schedule']['next_payment'] = array(
      '#type' => 'textfield',
      '#title' => t('Next Payment'),
      '#default_value' => date('m/d/Y', $recurring_schedule->next_payment),
      '#description' => t("Enter any date in the MM/DD/YYYY format (or any other format supported by strtotime())."),
      '#attributes' => array('class' => array('pickadate')),
    );
    $form['order']['recurring_schedule']['current_payments'] = array(
      '#type' => 'textfield',
      '#title' => t('Current Payments'),
      '#default_value' => $recurring_schedule->current_payments,
    );
    $form['order']['recurring_schedule']['created'] = array(
      '#type' => 'textfield',
      '#title' => t('Created'),
      '#default_value' => date('m/d/Y', $recurring_schedule->created),
      '#description' => t("Enter any date in the MM/DD/YYYY format (or any other format supported by strtotime())."),
      '#attributes' => array('class' => array('pickadate')),
    );
    $form['order']['recurring_schedule']['expiration'] = array(
      '#type' => 'textfield',
      '#title' => t('Expiration'),
      '#default_value' => $recurring_schedule->expiration ? date('m/d/Y', $recurring_schedule->expiration) : 0,
      '#description' => t("Enter any date in the MM/DD/YYYY format (or any other
        format supported by strtotime()). Enter 0 for no expiration."),
      '#attributes' => array('class' => array('pickadate')),
    );
    $form['order']['recurring_schedule']['failed_payments'] = array(
      '#type' => 'textfield',
      '#title' => t('Failed Payments'),
      '#default_value' => $recurring_schedule->failed_payments,
    );
    $form['order']['recurring_schedule']['notified'] = array(
      '#type' => 'checkbox',
      '#title' => t('Notified'),
      '#default_value' => $recurring_schedule->notified,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form_state['redirect'] = 'admin/moneyscripts/orders';
  return $form;
}

/**
 * Validate Function for the Order Form
 */
function ms_core_order_form_validate($form, &$form_state) {
  $v = $form_state['values'];
  $account = user_load_by_name($v['username']);
  if (!$account->uid) {
    form_set_error('username', t('You must enter a valid user'));
  }
}

/**
 * Submit Function for the Order Form
 */
function ms_core_order_form_submit($form, &$form_state) {
  // Handle the Updating or Inserting of an order
  $v = $form_state['values'];

  if (isset($v['oid']) AND $order = ms_core_order_load($v['oid'])) {
    $account = user_load_by_name($v['username']);

    // Update the values
    $order->created = strtotime($v['created']);
    $order->gateway = $v['gateway'];
    $order->order_type = $v['order_type'];
    $order->status = $v['status'];
    $order->currency = $v['currency'];
    $order->first_name = $v['first_name'];
    $order->last_name = $v['last_name'];
    $order->email_address = $v['email_address'];
    $order->uid = ($account) ? $account->uid : 0;
    $order->billing_address = array(
      'street' => trim($v['billing_street']),
      'city' => trim($v['billing_city']),
      'state' => trim($v['billing_state']),
      'zip' => trim($v['billing_zip']),
      'country' => trim($v['billing_country']),
      'phone' => trim($v['billing_phone']),
    );
    $order->shipping_address = array(
      'street' => trim($v['shipping_street']),
      'city' => trim($v['shipping_city']),
      'state' => trim($v['shipping_state']),
      'zip' => trim($v['shipping_zip']),
      'country' => trim($v['shipping_country']),
      'phone' => trim($v['shipping_phone']),
    );

    // Save the recurring schedule
    if (!empty($v['recurring_schedule']['change_recurring_schedule']) AND $recurring_schedule = ms_core_load_recurring_schedule($order->oid)) {
      // Merge in the values
      $recurring_schedule = (object) array_merge((array) $recurring_schedule, $v['recurring_schedule']);
      $recurring_schedule->next_payment = strtotime($recurring_schedule->next_payment);
      $recurring_schedule->created = strtotime($recurring_schedule->created);
      $recurring_schedule->expiration = strtotime($recurring_schedule->expiration);
      ms_core_update_recurring_schedule($recurring_schedule);
    }

    // Save the order

    if (ms_core_order_save($order)) {
      // Display a message
      drupal_set_message(t('Order @num saved.', array('@num' => $order->order_number)));
    }
  }
  else {
    // Create a new order
    $account = user_load_by_name($v['username']);
    $order = ms_core_order_new($v['order_type'], ($account) ? $account->uid : 0);

    // Set the values
    $order->created = strtotime($v['created']);
    $order->gateway = $v['gateway'];
    $order->order_type = $v['order_type'];
    $order->status = $v['status'];
    $order->currency = $v['currency'];
    $order->first_name = $v['first_name'];
    $order->last_name = $v['last_name'];
    $order->email_address = $v['email_address'];
    $order->billing_address = array(
      'street' => trim($v['billing_street']),
      'city' => trim($v['billing_city']),
      'state' => trim($v['billing_state']),
      'zip' => trim($v['billing_zip']),
      'country' => trim($v['billing_country']),
      'phone' => trim($v['billing_phone']),
    );
    $order->shipping_address = array(
      'street' => trim($v['shipping_street']),
      'city' => trim($v['shipping_city']),
      'state' => trim($v['shipping_state']),
      'zip' => trim($v['shipping_zip']),
      'country' => trim($v['shipping_country']),
      'phone' => trim($v['shipping_phone']),
    );

    // Save the order
    ms_core_order_save($order);

    // Display a message
    drupal_set_message(t('Order @num saved.', array('@num' => $order->order_number)));
  }

  $form_state['redirect'] = 'admin/moneyscripts/orders';
}

/**
 * Delete Checkout Order Confirmation
 */
function ms_core_delete_checkout_order_confirm($form, &$form_state, $order_key) {
  $order = ms_core_order_load_by_key($order_key);
  $form['#ms_core_oid'] = $order->oid;
  return confirm_form($form, t('Are you sure you want to delete this order?'), 'user', t('This action cannot be undone.'), t('Delete'));
}

/**
 * Deletes an order
 */
function ms_core_delete_checkout_order_confirm_submit($form, &$form_state) {
  $order = ms_core_order_load($form['#ms_core_oid']);

  ms_core_order_delete($order->oid);

  drupal_set_message(t('Order %number has been deleted.', array('%number' => $order->order_number)));
  $form_state['redirect'] = 'user';
}

// ======================================
// CHECKOUT
// ======================================

/**
 * The Checkout Form
 */
function ms_checkout_form($form, &$form_state, $order) {
  global $user;

  // Stop the caching
  $GLOBALS['conf']['cache'] = FALSE;

  // Set a default setting if not set
  if (!isset($order->data['skip_registration'])) {
    $order->data['skip_registration'] = FALSE;
  }

  // Add the User Registration form
  if (!$user->uid AND !$order->data['skip_registration']) {
    ms_core_create_account_form($form);
    if (variable_get('ms_core_mimic_register_form', FALSE)) {
      $form_state = NULL;
      drupal_prepare_form('user_register', $form, $form_state);
    }
  }
  if (!(variable_get('ms_core_terms_service_hide_for_authenticated', FALSE) AND $user->uid)
    AND variable_get('ms_core_terms_service_nid', '') AND $node = node_load(variable_get('ms_core_terms_service_nid', ''))) {
    $form['terms_of_service'] = array(
      '#type' => 'fieldset',
    );
    $node_view = node_view($node);
    $form['terms_of_service']['terms'] = array(
      '#type' => 'fieldset',
      '#collapsible' => variable_get('ms_core_terms_service_collapsed', FALSE),
      '#collapsed' => variable_get('ms_core_terms_service_collapsed', FALSE),
      '#title' => variable_get('ms_core_terms_service_collapsed', FALSE) ? $node->title : '',
    );
    $form['terms_of_service']['terms']['terms_of_service_text'] = array(
      '#type' => 'item',
      '#markup' => drupal_render($node_view),
    );
    $form['terms_of_service']['terms_of_service_agree'] = array(
      '#type' => 'checkbox',
      '#title' => variable_get('ms_core_terms_service_text', ''),
      '#return_value' => 1,
      '#required' => TRUE,
    );
  }
  if ($order->amount == 0 AND !$order->recurring_schedule['has_trial']) {
    // Put the Free Button here
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Complete Order'),
      '#validate' => array('ms_core_checkout_form_validate'),
      '#submit' => array('ms_core_checkout_form_free_submit'),
      '#weight' => 999,
    );
  }
  else {
    // Get the Payment Gateways
    $gateways = ms_core_get_payment_gateways($order->order_type, $order->data['blocked_gateways']);
    if ($gateways) {
      // Show a form to let the user select which gateway
      ms_core_choose_gateway_form($form, $gateways);

      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Continue'),
        '#validate' => array('ms_core_checkout_form_validate'),
        '#submit' => array('ms_core_checkout_form_submit'),
        '#weight' => 999,
      );
    }
    else {
      // There are no gateways installed
      $form['gateways'] = array(
        '#type' => 'fieldset',
        '#title' => t('Choose Payment Method'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      $form['gateways']['gateways_html'] = array(
        '#type' => 'item',
        '#markup' => t('There are no payment gateways enabled which are compatible with this order.'),
      );
    }
  }

  if (isset($order->oid)) {
    $form['oid'] = array(
      '#type' => 'value',
      '#value' => $order->oid,
    );
  }

  return $form;
}

/*
 * The Choose Gateway Form
 */
function ms_core_choose_gateway_form(&$form, $gateways) {
  $gateway_options = array();
  foreach ($gateways as $gateway) {
    $gateway_options[$gateway['module']] = $gateway['description'];
  }
  if (!empty($gateway_options)) {
    if (count($gateway_options) > 1) {
      $form['gateways'] = array(
        '#type' => 'fieldset',
        '#title' => t('Choose Payment Method'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      $form['gateways']['gateway'] = array(
        '#type' => 'radios',
        '#title' => t('Payment Method'),
        '#options' => $gateway_options,
        '#description' => t("Choose your Payment Method."),
        '#default_value' => key($gateway_options),
        '#required' => TRUE,
      );
    }
    else {
      $form['gateway'] = array(
        '#type' => 'value',
        '#value' => key($gateway_options),
        '#required' => TRUE,
      );
    }
  }
  else {
    $form['gateway'] = array(
      '#type' => 'item',
      '#markup' => t('No Payment Gateways are enabled which are compatible with this order. Please check your settings.'),
    );
  }
}

/**
 * Delete Order Confirmation
 */
function ms_core_delete_order_confirm($form, &$form_state, $order_key) {
  $order = ms_core_order_load_by_key($order_key);
  $form['#ms_core_oid'] = $order->oid;
  return confirm_form($form, t('Are you sure you want to delete this order?'), 'admin/moneyscripts/orders', t('This action cannot be undone. Deleting this order will remove all records of payments received for this order as well.'), t('Delete'));
}

/**
 * Deletes an order
 */
function ms_core_delete_order_confirm_submit($form, &$form_state) {
  $order = ms_core_order_load($form['#ms_core_oid']);

  ms_core_order_delete($order->oid);

  drupal_set_message(t('Order %number has been deleted.', array('%number' => $order->order_number)));
  $form_state['redirect'] = 'admin/moneyscripts/orders';
}

/**
 * Delete Payment Confirmation
 */
function ms_core_delete_payment_confirm($form, &$form_state, $pid) {
  $payment = ms_core_load_payment($pid);
  $form['#ms_core_pid'] = $payment->pid;
  return confirm_form($form, t('Are you sure you want to delete this payment?'), 'admin/moneyscripts/orders', t('This action cannot be undone. Deleting this payment will remove all records of it from the database.'), t('Delete'));
}

/**
 * Deletes a payment from an order
 */
function ms_core_delete_payment_confirm_submit($form, &$form_state) {
  $payment = ms_core_load_payment($form['#ms_core_pid']);

  db_delete('ms_payments')
    ->condition('pid', $payment->pid)
    ->execute();

  drupal_set_message(t('Payment %number has been deleted.', array('%number' => $payment->pid)));
  $form_state['redirect'] = 'admin/moneyscripts/orders';
}

/**
 * Remove Product Confirmation
 */
function ms_core_remove_product_confirm($form, &$form_state, $order_product_id) {
  $product = ms_core_load_order_product($order_product_id);
  $form['#ms_core_order_product_id'] = $product->order_product_id;
  return confirm_form($form, t('Are you sure you want to remove this product?'), 'admin/moneyscripts/orders', t('This action cannot be undone.'), t('Remove'));
}

/**
 * Removes a product from an order
 */
function ms_core_remove_product_confirm_submit($form, &$form_state) {
  $product = ms_core_load_order_product($form['#ms_core_order_product_id']);

  db_delete('ms_order_products')
    ->condition('order_product_id', $product->order_product_id)
    ->execute();

  drupal_set_message(t('Product %name has been removed.', array('%name' => $product->name)));
  $form_state['redirect'] = 'admin/moneyscripts/orders';
}

/**
 * Resubmit Payment Confirmation
 */
function ms_core_resubmit_payment_confirm($form, &$form_state, $pid) {
  $payment = ms_core_load_payment($pid);
  $form['#ms_core_pid'] = $payment->pid;
  return confirm_form($form, t('Are you sure you want to resubmit this payment?'), 'admin/moneyscripts/orders', t('This action cannot be undone. Resubmitting a payment will cause other modules to act on the payment as if it were a real payment.'), t('Resubmit'));
}

/**
 * Resubmits a payment for an order
 */
function ms_core_resubmit_payment_confirm_submit($form, &$form_state) {
  $payment = ms_core_load_payment($form['#ms_core_pid']);

  // Enter the payment, without inserting a new record or validating it
  ms_core_enter_payment($payment, FALSE, TRUE, FALSE);

  drupal_set_message(t('Payment %number has been resubmitted.', array('%number' => $payment->pid)));
  $form_state['redirect'] = 'admin/moneyscripts/orders';
}

/**
 * Build the add payment form
 */
function ms_core_edit_payment_form($form, &$form_state, $action = 'add', $id = 0) {
  ms_core_add_timeentry_js('edit-created-time');
  $form['payment'] = array(
    '#type' => 'fieldset',
    '#title' => t('Payment'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  if ($action == 'edit') {
    $is_edit = TRUE;
    $payment = ms_core_load_payment($id);
    $order = ms_core_order_load($payment->oid);
    $form['payment']['pid'] = array(
      '#type' => 'value',
      '#value' => $payment->pid,
    );
    $form['payment']['paymentid'] = array(
      '#type' => 'textfield',
      '#title' => t('Payment ID'),
      '#size' => 32,
      '#maxlength' => 64,
      '#disabled' => TRUE,
      '#description' => t("The ID of this Payment"),
      '#value' => $payment->pid,
    );
    $form['payment']['oid'] = array(
      '#type' => 'value',
      '#value' => ($order) ? $order->oid : 0,
    );
    $form['payment']['orderid'] = array(
      '#type' => 'textfield',
      '#title' => t('Order ID'),
      '#size' => 32,
      '#maxlength' => 64,
      '#disabled' => TRUE,
      '#description' => t("The ID of the Order"),
      '#default_value' => ($order) ? $order->order_number : '',
    );
  }
  elseif (arg(3) == 'add' AND $oid = arg(4)) {
    $is_edit = FALSE;
    $order = ms_core_order_load_by_key($oid);
    $form['payment']['oid'] = array(
      '#type' => 'value',
      '#value' => ($order) ? $order->oid : 0,
    );
    $form['payment']['orderid'] = array(
      '#type' => 'textfield',
      '#title' => t('Order ID'),
      '#size' => 32,
      '#maxlength' => 64,
      '#disabled' => TRUE,
      '#description' => t("The ID of the Order"),
      '#default_value' => ($order) ? $order->order_number : '',
    );
  }
  else {
    $is_edit = FALSE;
    $order = ms_core_order_load_by_key($id);
    $form['payment']['oid'] = array(
      '#type' => 'textfield',
      '#title' => t('Order ID'),
      '#size' => 32,
      '#required' => TRUE,
    );
  }

  $today = REQUEST_TIME;
  $form['payment']['created'] = array(
    '#type' => 'date',
    '#title' => t('Date'),
    '#description' => t("Date the order was created"),
    '#default_value' => array(
      'year' => ($is_edit) ? date('Y', $payment->created) : date('Y', $today),
      'month' => ($is_edit) ? date('n', $payment->created) : date('n', $today),
      'day' => ($is_edit) ? date('j', $payment->created) : date('j', $today),
    ),
  );
  $form['payment']['created_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Time'),
    '#size' => 12,
    '#description' => t("Time the payment was created"),
    '#default_value' => ($is_edit) ? date('H:i:s', $payment->created) : date('H:i:s', $today),
  );
  $form['payment']['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => ($order) ? ms_core_get_payment_types($order->order_type) : ms_core_get_payment_types(),
    '#description' => t("The type of payment"),
    '#required' => TRUE,
    '#default_value' => ($is_edit) ? $payment->type : 'cart',
  );
  $form['payment']['gateway'] = array(
    '#type' => 'select',
    '#title' => t('Gateway'),
    '#options' => ms_core_get_payment_gateways_list(),
    '#description' => t("The gateway for this payment"),
    '#required' => TRUE,
    '#default_value' => ($is_edit) ? $payment->gateway : '',
  );
  $form['payment']['transaction'] = array(
    '#type' => 'textfield',
    '#title' => t('Transaction ID'),
    '#size' => 32,
    '#maxlength' => 64,
    '#description' => t("The transaction id"),
    '#default_value' => ($is_edit) ? $payment->transaction : '',
  );
  $form['payment']['recurring_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Recurring ID'),
    '#size' => 32,
    '#maxlength' => 64,
    '#description' => t("The recurring id"),
    '#default_value' => ($is_edit) ? $payment->recurring_id : '',
  );
  $form['payment']['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount'),
    '#size' => 32,
    '#maxlength' => 64,
    '#description' => t("The amount for this payment"),
    '#default_value' => ($is_edit) ? $payment->amount : '',
  );
  $form['payment']['currency'] = array(
    '#type' => 'select',
    '#title' => t('Currency'),
    '#options' => ms_core_get_currencies(),
    '#description' => t("The currency for this payment"),
    '#required' => TRUE,
    '#default_value' => ($is_edit) ? $payment->currency : ($order) ? $order->currency : variable_get('ms_core_default_currency', 'USD'),
  );
  $form['payment']['notify'] = array(
    '#type' => 'checkbox',
    '#title' => t('Process the Payment?'),
    '#description' => t("Check this to have modules act on the payment as if it were live."),
    '#default_value' => ($is_edit) ? 0 : 1,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form_state['redirect'] = 'admin/moneyscripts/orders';
  return $form;
}

/**
 * Submit Function for the edit payment form
 */
function ms_core_edit_payment_form_submit($form, &$form_state) {
  $v = $form_state['values'];

  if (isset($v['orderid']) AND $order = ms_core_order_load($v['oid'])) {
    if (isset($v['pid']) AND $payment = ms_core_load_payment($v['pid'])) {
      $payment->oid = $order->oid;
      $payment->type = $v['type'];
      $payment->created = strtotime($v['created']['year'] . '-' . $v['created']['month'] . '-' . $v['created']['day'] . ' ' . $v['created_time']);
      $payment->gateway = $v['gateway'];
      $payment->transaction = $v['transaction'];
      $payment->amount = $v['amount'];
      $payment->currency = $v['currency'];
      $payment->recurring_id = $v['recurring_id'];

      $payment->save();
      drupal_set_message(t('Payment %number has been saved.', array('%number' => $payment->pid)));

      if ($v['notify']) {
        ms_core_enter_payment($payment, FALSE, TRUE, FALSE);
      }
    }
    else {
      // Create a new payment
      $payment = ms_core_new_payment($order->oid, $v['gateway'], $v['type']);
      $payment->created = strtotime($v['created']['year'] . '-' . $v['created']['month'] . '-' . $v['created']['day'] . ' ' . $v['created_time']);
      $payment->transaction = $v['transaction'];
      $payment->amount = $v['amount'];
      $payment->currency = $v['currency'];
      $payment->data = array('manual' => TRUE);
      $payment->recurring_id = $v['recurring_id'];
      $payment->billing_address = $order->billing_address;
      $payment->shipping_address = $order->shipping_address;

      // Add the Payment to the Order
      ms_core_enter_payment($payment, FALSE, $v['notify']);

      drupal_set_message(t('Added a new payment for Order %number.', array('%number' => $order->order_number)));
    }
  }
  else {
    drupal_set_message(t('Error loading the order.'));
  }

  $form_state['redirect'] = 'admin/moneyscripts/orders';
}

/**
 * Build the add product form
 */
function ms_core_add_product_form($form, &$form_state, $order_key) {
  $order = ms_core_order_load_by_key($order_key);

  $form['oid'] = array(
    '#type' => 'value',
    '#value' => $order->oid,
  );
  $form['orderid'] = array(
    '#type' => 'textfield',
    '#title' => t('Order ID'),
    '#size' => 32,
    '#maxlength' => 64,
    '#disabled' => TRUE,
    '#description' => t("The ID of the Order"),
    '#value' => $order->order_number,
  );
  $form['productid'] = array(
    '#type' => 'select',
    '#title' => t('Select Product'),
    '#options' => ms_core_get_module_products_list(),
    '#description' => t("Select a product from this list"),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add Product'),
  );
  $form_state['redirect'] = 'admin/moneyscripts/orders';

  return $form;
}

/**
 * Submit Function for the Add Product form
 */
function ms_core_add_product_form_submit($form, &$form_state) {
  $v = $form_state['values'];
  $order = ms_core_order_load($v['oid']);
  $product = ms_core_get_module_product($v['productid']);

  if ($product->id) {
    // Add the product to the order
    ms_core_add_order_product($order, $product);

    drupal_set_message(t('Added product %product to Order %number.',
      array('%product' => $product->name, '%number' => $order->order_number)));
  }

  $form_state['redirect'] = 'admin/moneyscripts/orders';
}

/**
 * Confirms the rebuild orders action
 */
function ms_core_rebuild_orders_confirm($form, &$form_state) {
  return confirm_form($form, t('Are you sure you want to rebuild the orders?'), 'admin/moneyscripts/orders',
    t('This will refresh the order data object to use the latest override settings from the product(s) in the order. This action cannot be undone.'),
    t('Rebuild Orders'));
}

/**
 * Rebuilds the orders
 */
function ms_core_rebuild_orders_confirm_submit($form, &$form_state) {
  // Load all of the orders from the database
  $result = db_query("SELECT * FROM {ms_orders}");
  foreach ($result as $row) {
    // For each order, load the products and get the override settings and data into the order object
    $order = ms_core_order_load($row->oid);
    $data = $order->data;
    foreach ($order->products as $item) {
      $product = ms_core_load_module_product($item->module, $item->id);
      $data = array_merge($data, $product->data);
    }

    ms_core_add_data($order, $data);
  }

  drupal_set_message(t('Successfully rebuilt the orders.'));

  $form_state['redirect'] = 'admin/moneyscripts/orders';
}
