<?php
/**
 * @file
 */
/**
 * Show a list of the MoneyScripts pages
 */
function ms_core_main_page() {
  $message = t('Various MoneyScripts modules can be found here. Click the links below to view and change the settings.');

  return $message . theme('admin_block_content', array('content' => system_admin_menu_block(menu_get_item())));
}

/**
 * Show a list of the installed Gateways
 */
function ms_core_gateways_page() {
  $message = t('Various MoneyScripts Payment Gateway modules can be found here. Click the links below to view and change the settings. To enable more MoneyScripts Payment Gateways, go to the <a href="!url">module administration page</a>', array('!url' => url('admin/modules')));

  return $message . theme('admin_block_content', array('content' => system_admin_menu_block(menu_get_item())));
}

/**
 * Show a list of the Reports available
 */
function ms_core_reports_page() {
  $message = (module_exists('ms_reports')) ? t('Various reports generated by MoneyScripts modules can be found here. Click the links below to view the reports.') : t('Various reports generated by MoneyScripts modules can be found here. Click the links below to view the reports. To view core MoneyScripts statistics enable the <strong>MS Reports</strong> module on the <a href="!url">module administration page</a>', array('!url' => url('admin/modules')));

  return $message . theme('admin_block_content', array('content' => system_admin_menu_block(menu_get_item())));
}