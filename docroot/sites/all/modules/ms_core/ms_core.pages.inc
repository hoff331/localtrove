<?php
/**
 * @file
 * MS Core Pages Includes
 * Licensed under the GNU GPLv2 License
 *
 */

/**
 * List the Order Details
 */
function ms_core_view_order_details($order_key) {
  global $user;
  $output = '';
  if ($order = ms_core_order_load_by_key($order_key)) {
    // Add the CSS
    drupal_add_css(drupal_get_path('module', 'ms_core') . '/ms_core.css');
    $account = user_load($order->uid);
    $headers = array();
    $attr = array('id' => 'ms-core-order-details-table');
    $actions = array();
    if ($cancel_url = ms_core_get_cancel_url($order)) {
      $actions[] = l(t('Cancel Recurring Payments'), $cancel_url,
        array('attributes' => array('target' => '_blank'), 'query' => drupal_get_destination()));
    }
    if ($billing_url = ms_core_get_billing_url($order)) {
      $actions[] = l(t('Change Billing'), $billing_url,
        array('query' => drupal_get_destination()));
    }
    if ($order->status == 'checkout' AND $user->uid == $order->uid) {
      $actions[] = l(t('Checkout'), 'ms/resume-checkout/' . $order->order_key);
      $actions[] = l(t('Delete'), 'user/' . $user->uid . '/order-history/delete/' . $order->order_key);
    }
    $rows = array(
      array(
        'data' => array(t('Order') . ' #', $order->order_number),
        'class' => array('ms_order_oid'),
      ),
      array(
        'data' => array(t('User'), isset($account->name) ? l($account->name, 'user/' . $account->uid) : t('N/A')),
        'class' => array('ms_order_user'),
      ),
      array(
        'data' => array(t('Created'), format_date($order->created)),
        'class' => array('ms_order_created'),
      ),
      array(
        'data' => array(t('Total'), ms_core_format_money($order->total, $order->currency, 'order_total')),
        'class' => array('ms_order_total'),
      ),
      array(
        'data' => array(t('Status'), ms_core_get_order_status($order->status)),
        'class' => array('ms_order_status'),
      ),
      array(
        'data' => array(t('Actions'), implode($actions, ' | ')),
        'class' => array('ms_order_actions'),
      ),
      array(
        'data' => array(array(
            'data' => ms_core_get_order_details_table($order),
            'colspan' => 2,
          )),
        'class' => array('ms_order_details'),
      ),
      array(
        'data' => array(t('Order Type'), ms_core_get_order_type($order)),
        'class' => array('ms_order_type'),
      ),
      array(
        'data' => array(array(
            'data' => ms_core_get_order_payments_table($order),
            'colspan' => 2,
          )),
        'class' => array('ms_order_payments_row'),
      ),
      array(
        'data' => array(array(
            'data' => ms_core_get_order_customer_information_table($order),
            'colspan' => 2,
          )),
        'class' => array('ms_order_address_row'),
      ),
      array(
        'data' => array(array(
            'data' => ms_core_get_order_history_table($order),
            'colspan' => 2,
          )),
        'class' => array('ms_order_history_row'),
      ),
    );

    // Output the table
    $output .= theme('table', array('header' => $headers, 'rows' => $rows, 'attributes' => $attr));
    return $output;
  }
  else {
    drupal_not_found();
  }
}

/**
 * Generates the invoice header html with token support
 */
function ms_core_get_invoice_header($order) {
  $account = user_load($order->uid);
  $template = variable_get('ms_core_invoice_header', variable_get('ms_core_invoice_header', "<h2>[site:name]</h2><h4>[site:slogan]</h4>"));
  $template = token_replace($template, array(
    'ms_core_order' => $order,
    'user' => $account,
  ));
  return $template;
}

/**
 * Displays the invoice for an order
 */
function ms_core_view_order_invoice($order_key) {
  if ($order = ms_core_order_load_by_key($order_key)) {
    $vars = array(
      'order' => $order,
      'op' => 'view',
      'invoice_header' => ms_core_get_invoice_header($order),
    );
    return theme('ms_core_invoice', $vars);
  }
  else {
    drupal_not_found();
  }
}

/**
 * Displays the print invoice for an order
 */
function ms_core_view_order_print($order_key) {
  if ($order = ms_core_order_load_by_key($order_key)) {
    $op = 'print';
    if (ip_address() == '69.164.218.62') {
      $op = 'pdf';
    }
    $vars = array(
      'order' => $order,
      'op' => $op,
      'invoice_header' => ms_core_get_invoice_header($order),
    );
    print theme('ms_core_invoice', $vars);
    exit;
  }
  else {
    drupal_not_found();
  }
}

/**
 * Show the Billing Information for a user
 *
 * @param $user
 */
function ms_core_user_billing_info_page($user) {
  $html = array();

  drupal_alter('ms_core_billing_info', $html, $user);

  if (empty($html)) {
    return t('No Billing Information is Available.');
  }

  return drupal_render($html);
}

/**
 * Show the Choose Gateway Page
 */
function ms_core_checkout_page($order_key = '') {
  // Stop the caching
  $GLOBALS['conf']['cache'] = FALSE;

  $is_cart = TRUE;
  if ($order = ms_core_order_load_by_key($order_key)) {
    $cart = $order;
    $is_cart = FALSE;
  }
  else {
    $cart = ms_core_get_cart();
  }

  // Trigger the rule
  if (module_exists('rules')) {
    rules_invoke_event('ms_core_event_cart_checkout', $cart);
  }

  // Set some defaults:
  if (!isset($cart->data['skip_registration'])) {
    $cart->data['skip_registration'] = FALSE;
  }
  if (!isset($cart->data['blocked_gateways'])) {
    $cart->data['blocked_gateways'] = array();
  }

  if (count($cart->products) > 0) {
    // Give other modules a chance to add steps to the checkout form
    // Invoke hook_ms_checkout_steps to get the steps
    $steps = module_invoke_all('ms_checkout_steps', $cart);

    if (!is_array($steps)) {
      $steps = array();
    }

    // Perform each step until they have all been done
    foreach ($steps as $step) {
      // Perform the step
      return drupal_get_form($step['form_id'], $cart);
    }

    // Once all of the steps are done, show the final checkout form to let the user choose the gateway
    $gateways = ms_core_get_payment_gateways($cart->order_type, $cart->data['blocked_gateways']);

    // Allow other modules to alter the gateways
    drupal_alter('ms_payment_gateway', $gateways, $cart);

    $fields = ms_core_get_checkout_fields($cart);

    // Bypass the Checkout Form?
    global $user;
    if (!count($fields) AND count($gateways) == 1 AND ($user->uid OR $cart->data['skip_registration']) AND variable_get('ms_core_skip_checkout', FALSE)) {
      // Save the order
      ms_core_cart_to_order();
      foreach ($gateways as $gateway) {
        drupal_goto($gateway['path']);
        break;
      }
    }

    // Add the Order Info Field
    $fields[] = array(
      'id' => 'ms_core_order_info',
      'type' => 'plain',
      'title' => t('Order items'),
      'html' => ms_core_get_order_details_table($cart, $is_cart),
      'weight' => 0,
    );
    module_load_include('inc', 'ms_core', 'ms_core.forms');

    $build = array();
    $build_fields = array();

    // Order the fields by weight
    usort($fields, "ms_core_sort_fields");

    foreach ($fields as $field) {
      $build_fields[$field['id']] = array(
        '#type' => 'fieldset',
        '#title' => check_plain($field['title']),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      if ($field['type'] == 'form') {
        $field_form = drupal_get_form($field['html']);
        $build_fields[$field['id']][$field['id'] .'_html'] = array(
          '#type' => 'item',
          '#markup' => drupal_render($field_form),
        );
      }
      else {
        $build_fields[$field['id']][$field['id'] . '_html'] = array(
          '#type' => 'item',
          '#markup' => $field['html'],
        );
      }
    }

    $build['content'] = array(
      'ms_checkout_fields' => array(
        '#markup' => drupal_render($build_fields),
      ),
      'ms_checkout_form' => drupal_get_form('ms_checkout_form', $cart),
    );
    return $build;
  }
  else {
    return t('There are no products in your cart. Please add one or more products before checking out.');
  }
}

/**
 * Allow for resuming orders in checkout
 */
function ms_core_resume_checkout_page($order_key) {
  global $user;
  $order = ms_core_order_load_by_key($order_key);
  if ($user->uid AND $user->uid == $order->uid) {
    return ms_core_checkout_page($order->order_key);
  }
  else {
    drupal_access_denied();
  }
}

// ======================================
// CART
// ======================================

/**
 * Show the Shopping Cart Page
 */
function ms_core_cart_page() {
  $build = array();
  $content = '';

  // Add the CSS
  drupal_add_css(drupal_get_path('module', 'ms_core') . '/ms_core.css');

  // Stop the caching
  $GLOBALS['conf']['cache'] = FALSE;

  if ($cart = ms_core_get_cart()) {
    $content = ms_core_get_order_details_table($cart, TRUE);
    $fields = ms_core_get_cart_fields($cart);

    foreach ($fields as $field) {
      $content .= "<div class='ms_cart_field_div'>" . drupal_render($field['html']) . "</div>";
    }

    $redirect = variable_get('ms_core_continue_shopping_path', '');

    if (isset($_GET['ref'])) {
      $redirect = $_GET['ref'];
    }

    $content .= "<div class='ms_cart_field_div'>";
    $continue_shopping_button = drupal_get_form('ms_core_get_continue_shopping_button', $redirect);
    $content .= "<div class='ms_cart_left'>" . drupal_render($continue_shopping_button) . "</div>";

    if (count($cart->products)) {
      $checkout_button = drupal_get_form('ms_core_get_checkout_button');
      $content .= "<div class='ms_cart_right'>" . drupal_render($checkout_button) . "</div>";
    }
    $content .= "<div style='clear:both;'></div>";
    $content .= "</div>";
  }
  else {
    $content = t('There are currently no products in your shopping cart.');
  }

  $build['content']['ms_core_cart_contents']['#markup'] = $content;

  return $build;
}

/**
 * Removes a product from the cart, then redirects
 */
function ms_core_cart_remove_page($pid) {
  $cart = ms_core_get_cart();

  $product = $cart->products[$pid];

  if ($product->cart_product_id) {
    ms_core_remove_cart_product($product, $cart);
    // Redirect to the page it came from
    $redirect = (isset($_GET['destination'])) ? $_GET['destination'] : 'ms/cart';

    drupal_goto($redirect);
  }
  else {
    drupal_not_found();
  }
}

// ======================================
// ORDERS
// ======================================

/**
 * View Orders Page
 */
function ms_core_view_orders_page() {
  // this will be filled with an array of our content
  $build = array();

  $headers = array(
    array(
      'data' => t('#'),
      'field' => 'o.oid',
      'sort' => 'desc',
      'class' => array('ms_orders_oid_header'),
    ),
    array(
      'data' => t('User'),
      'field' => 'u.name',
      'class' => array('ms_orders_user_header'),
    ),
    array(
      'data' => t('Gateway'),
      'field' => 'o.gateway',
      'class' => array('ms_orders_gateway_header'),
    ),
    array(
      'data' => t('Status'),
      'field' => 'o.status',
      'class' => array('ms_orders_status_header'),
    ),
    array(
      'data' => t('Products'),
      'class' => array('ms_orders_products_header'),
    ),
    array(
      'data' => t('Total'),
      'field' => 'o.amount',
      'class' => array('ms_orders_total_header'),
    ),
    array(
      'data' => t('Created'),
      'field' => 'o.created',
      'class' => array('ms_orders_created_header'),
      'sort' => 'desc',
    ),
    array(
      'data' => t('Actions'),
      'class' => array('ms_orders_actions_header'),
    ),
  );

  $query = db_select('ms_orders', 'o');
  $query->leftjoin('users', 'u', 'o.uid = u.uid');
  $query->fields('o', array('oid', 'gateway', 'uid', 'status', 'order_type', 'amount', 'created', 'currency'));
  $query->fields('u', array('name'));
  $query = $query->extend('TableSort')->orderByHeader($headers);

  // Add the pager if requested
  $pager_amount = 20;
  if (!isset($_GET['pager_amount']) OR $pager_amount = $_GET['pager_amount']) {
    $query = $query->extend('PagerDefault')->limit($pager_amount);
  }

  // Act on the filters
  $name = '';
  if (isset($_GET['name']) AND $_GET['name']) {
    $name = $_GET['name'];
    $query->condition('u.name', '%' . $name . '%', 'LIKE');
  }
  $order_status = 'All';
  if (isset($_GET['order_status']) AND $_GET['order_status'] != 'All') {
    $order_status = $_GET['order_status'];
    $query->condition('o.status', $order_status);
  }
  $oid_key = '';
  if (isset($_GET['oid_key']) AND $_GET['oid_key']) {
    $oid_key = $_GET['oid_key'];
    $oid_key_condition = db_or()->condition('o.oid', $oid_key)->condition('o.order_key', $oid_key);
    $query->condition($oid_key_condition);
  }

  // execute the query
  $result = $query->execute();

  $rows = array();
  $attr = array('id' => 'ms-core-orders-table');
  foreach ($result as $row) {
    $order = ms_core_order_load($row->oid);
    $actions = array();
    $actions[] = l(t('View'), 'admin/moneyscripts/orders/view/' . $order->order_key);
    $actions[] = l(t('Edit'), 'admin/moneyscripts/orders/edit/' . $order->order_key);
    $actions[] = l(t('Delete'), 'admin/moneyscripts/orders/delete/' . $order->order_key);
    $rows[] = array('data' => array(
        array(
          'data' => $order->order_number,
          'class' => array('ms_orders_oid'),
        ),
        array(
          'data' => l($row->name, 'user/' . $order->uid),
          'class' => array('ms_orders_user'),
        ),
        array(
          'data' => ms_core_get_gateway_name($order->gateway),
          'class' => array('ms_orders_gateway'),
        ),
        array(
          'data' => ms_core_get_order_status($order->status),
          'class' => array('ms_orders_status'),
        ),
        array(
          'data' => ms_core_list_products($order),
          'class' => array('ms_orders_products'),
        ),
        array(
          'data' => ms_core_format_money($order->total, $order->currency, 'order_total'),
          'class' => array('ms_orders_total'),
        ),
        array(
          'data' => format_date($order->created, 'small'),
          'class' => array('ms_orders_created'),
        ),
        array(
          'data' => implode($actions, ' | '),
          'class' => array('ms_orders_actions'),
        ),
      ));
  }

  // Add Export CSV link to output
  $content = "<div class='ms_payments_header'>" . l(t('Export CSV'), 'admin/moneyscripts/ms_core/export_csv/ms_orders') . "</div>";

  // Store the data for csv export
  ms_core_store_csv($headers, $rows, 'ms_orders');

  // Add the filters form
  $filters = array(
    'name' => $name,
    'oid_key' => $oid_key,
    'order_status' => $order_status,
    'pager_amount' => $pager_amount,
  );

  // Add the filters form
  $filters_form = drupal_get_form('ms_core_get_filter_form', $filters);
  $content .= drupal_render($filters_form);

  $table_vars = array(
    'header' => $headers,
    'rows' => $rows,
    'attributes' => $attr,
  );
  $content .= theme('table', $table_vars);

  // add the content
  $build['content'] = array('#markup' => $content);

  // Add the pager
  $build['pager'] = array(
    '#theme' => 'pager',
    '#weight' => 5,
  );

  return $build;
}

/**
 * Show the default thankyou page
 */
function ms_core_thankyou_page() {
  // Stop the caching
  $GLOBALS['conf']['cache'] = FALSE;

  // Load some variables
  global $user;

  if (!isset($_SESSION['ms_oid']) OR !$order = ms_core_order_load($_SESSION['ms_oid'])) {
    return t('There was an error loading the order. Please contact a site administrator.');
  }

  $account = user_load($order->uid);

  ms_core_log('ms_core', 'New Thank You Page has been received. Here are the details for it: Order: !data User: !vars',
    array('!data' => ms_core_print_r($order), '!vars' => ms_core_print_r($user)));

  // Log the User In?
  if (!$user->uid) {
    if (variable_get('ms_core_auto_login', FALSE)) {
      if ($order->uid) {
        // Make sure the user isn't blocked or pending admin approval
        if ($account->status == 1) {
          ms_core_log('ms_core', 'Logging in a user on thank-you page: !account',
            array('!account' => ms_core_print_r($account)));
          $user = $account;
          user_login_finalize();
        }
        else {
          ms_core_log_error('ms_core', 'The user @user could not be automatically logged in because their account is not yet active.
            You will need to change the !user_settings so that admin approval is not required.',
            array('@user' => $account->name, '!user_settings' => l(t('User Settings'), 'admin/config/people/accounts')));
        }
      }
    }
  }

  // Set the messages in the order
  ms_core_show_order_messages($order);

  // Invoke the thankyou page hook
  module_invoke_all('ms_thankyou', $order);

  // Redirect to the order specific thank-you page if set
  foreach ($order->products as $product) {
    if (!empty($product->data['thankyou_path'])) {
      drupal_goto($product->data['thankyou_path']);
    }
  }

  // Redirect to the Thankyou Page if set
  if ($path = ms_core_variable_get('ms_core_thankyou_path', '', $order)) {
    // Redirect to the thank-you page specified in the settings for MS Core
    drupal_goto($path);
  }

  // Otherwise, print the default thank-you page content
  $content = variable_get('ms_core_thankyou_page_template',
"<p>Thank you for your purchase, [user:name]! Your payment has been received and your order details are below:</p>
<br />
<p>Order # [ms_core_order:orderId]</p>
<p>Order Status: [ms_core_order:orderStatus]</p>
<p>Payment: [ms_core_payment:paymentAmount] - [ms_core_payment:paymentDate]</p>
<p>Payment Method: [ms_core_payment:gatewayName]</p>
<br />
<p>Please print a copy of this page for your records.</p>
");
  $payment = ms_core_get_last_payment($order);

  // Replace the Tokens
  $content = token_replace($content,
    array(
    'ms_core_order' => $order,
    'ms_core_payment' => $payment,
    'user' => $account,
  ));

  return $content;
}

/**
 * Autocomplete a User Name
 */
function ms_core_autocomplete_user($name = '') {
  $matches = array();
  if ($name) {
    $result = db_query("SELECT name FROM {users}");
    foreach ($result as $account) {
      $possible_values[] = $account->name;
    }
    foreach ($possible_values as $value) {
      if (preg_match("/$name/i", $value)) {
        $matches[$value] = $value;
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * Autocomplete a Node
 */
function ms_core_autocomplete_node($title = '') {
  $matches = array();
  if ($title) {
    $result = db_query("SELECT title, nid FROM {node} WHERE LOWER(title) LIKE LOWER(:title)", array(':title' => '%' . $title . '%'));
    foreach ($result as $node) {
      $matches[ms_core_create_autocomplete_key($node->nid)] = $node->title;
    }
  }
  drupal_json_output($matches);
}

/**
 * Autocomplete a Product Name
 */
function ms_core_autocomplete_product($name = '') {
  $matches = array();
  if ($name) {
    $products = ms_core_get_module_products();
    foreach ($products as $key => $product) {
      if (preg_match("/$name/i", $product->module_title . ' - ' . $product->name)) {
        $matches[$key] = $product->module_title . ' - ' . $product->name;
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * Autocomplete callback for the role
 */
function ms_core_autocomplete_role($string) {
  $matches = array();
  // Please convert this statement to the D7 database API syntax.
  $result = db_query("SELECT name FROM {role} WHERE name LIKE :string",
    array(':string' => '%' . $string . '%'));
  foreach ($result as $row) {
    $matches[$row->name] = $row->name;
  }
  print drupal_json_encode($matches);
  exit;
}

/**
 * Page callback to download the csv
 */
function ms_core_csv_page($id) {
  $csv_data = cache_get('ms_core_csv_' . $id, 'cache');

  if (!$csv_data) {
    drupal_set_message(t("The CSV data could not be retreived.
      It's possible the data might have expired.
      Refresh the report page and try to retrieve the CSV file again."), 'error');
    drupal_not_found();
    exit();
  }
  else {
    ob_end_clean();
    $http_headers = array(
      'Pragma' => 'no-cache',
      'Expires' => '0',
      'Cache-Control' => 'no-cache, must-revalidate',
      'Cache-Control' => 'private',
      'Content-Transfer-Encoding' => 'binary',
      'Content-Length' => strlen($csv_data->data),
      'Content-Disposition' => 'attachment; filename="' . $id . '-' . REQUEST_TIME . '.csv"',
      'Content-type' => 'text/csv',
    );
    foreach ($http_headers as $name => $value) {
      $value = preg_replace('/\r?\n(?!\t| )/', '', $value);
      drupal_add_http_header($name, $value);
    }

    print $csv_data->data;
    exit();
  }
}

// ======================================
// Payments
// ======================================

/**
 * View Payments Page
 */
function ms_core_view_payments_page() {
  $build = array();
  $content = '';

  $headers = array(
    array(
      'data' => t('Date'),
      'field' => 'p.created',
      'class' => array('ms_payments_created_header'),
      'sort' => 'desc',
    ),
    array(
      'data' => t('User'),
      'field' => 'u.name',
      'class' => array('ms_payments_user_header'),
    ),
    array(
      'data' => t('Order #'),
      'field' => 'o.oid',
      'class' => array('ms_payments_oid_header'),
    ),
    array(
      'data' => t('Title'),
      'class' => array('ms_payments_order_title_header'),
    ),
    array(
      'data' => t('Gateway'),
      'field' => 'p.gateway',
      'class' => array('ms_payments_gateway_header'),
    ),
    array(
      'data' => t('Transaction #'),
      'field' => 'p.transaction',
      'class' => array('ms_payments_transaction_header'),
    ),
    array(
      'data' => t('Type'),
      'field' => 'p.type',
      'class' => array('ms_payments_type_header'),
    ),
    array(
      'data' => t('Amount'),
      'field' => 'p.amount',
      'class' => array('ms_payments_amount_header'),
    ),
  );

  $query = db_select('ms_payments', 'p');
  $query->leftjoin('ms_orders', 'o', 'o.oid = p.oid');
  $query->leftjoin('users', 'u', 'o.uid = u.uid');
  $query->fields('p', array('pid', 'oid', 'type', 'transaction', 'recurring_id', 'gateway', 'amount', 'currency', 'created'));
  $query->fields('o', array('oid', 'uid', 'status', 'order_type', 'order_key'));
  $query->fields('u', array('name'));
  $query = $query->extend('TableSort')->orderByHeader($headers);

  // Add the pager if requested
  $pager_amount = 20;
  if (!isset($_GET['pager_amount']) OR $pager_amount = $_GET['pager_amount']) {
    $query = $query->extend('PagerDefault')->limit($pager_amount);
  }

  // Act on the filters
  $name = '';
  if (isset($_GET['name']) AND $_GET['name']) {
    $name = $_GET['name'];
    $query->condition('u.name', '%' . $name . '%', 'LIKE');
  }
  $oid_key = '';
  if (isset($_GET['oid_key']) AND $_GET['oid_key']) {
    $oid_key = $_GET['oid_key'];
    $oid_key_condition = db_or()->condition('o.oid', $oid_key)->condition('o.order_key', $oid_key);
    $query->condition($oid_key_condition);
  }

  // execute the query
  $result = $query->execute();

  $rows = array();
  $attr = array('id' => 'ms-core-payments-table');
  foreach ($result as $row) {
    if ($order = ms_core_order_load($row->oid)) {
      $rows[] = array('data' => array(
          array(
            'data' => format_date($row->created, 'small'),
            'class' => array('ms_payments_created'),
          ),
          array(
            'data' => l($row->name, 'user/' . $order->uid),
            'class' => array('ms_payments_user'),
          ),
          array(
            'data' => l($order->order_number, 'admin/moneyscripts/orders/view/' . $order->order_key),
            'class' => array('ms_payments_oid'),
          ),
          array(
            'data' => ms_core_get_order_title($order),
            'class' => array('ms_payments_order_title'),
          ),
          array(
            'data' => ms_core_get_gateway_name($order->gateway),
            'class' => array('ms_payments_gateway'),
          ),
          array(
            'data' => $row->transaction,
            'class' => array('ms_payments_transaction'),
          ),
          array(
            'data' => ms_core_get_payment_type($row->type),
            'class' => array('ms_payments_type'),
          ),
          array(
            'data' => ms_core_format_money($row->amount, $row->currency),
            'class' => array('ms_payments_amount'),
          ),
        ));
    }
  }

  // Add the filters form
  $filters = array(
    'name' => $name,
    'oid_key' => $oid_key,
    'pager_amount' => $pager_amount,
  );
  $filters_form = drupal_get_form('ms_core_get_filter_form', $filters);
  $content .= drupal_render($filters_form);

  // Store the data for csv export
  ms_core_store_csv($headers, $rows, 'ms_payments');

  $content .= theme('table', array('header' => $headers, 'rows' => $rows, 'attributes' => $attr));

  // add the content
  $build['content'] = array('#markup' => $content);

  // Add the pager
  $build['pager'] = array(
    '#theme' => 'pager',
    '#weight' => 5,
  );

  return $build;
}
