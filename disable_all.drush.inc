<?php

/**
* @file
* Drush integration for the disable_all module.
*/

/**
* Implements hook_drush_command().
*/
function disable_all_drush_command() {
  $items['kill-all-modules'] = array(
    'description' => dt('Disables all non-required Drupal modules.'),
    'aliases' => array('dam'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );
  $items['necro-all-modules'] = array(
    'description' => dt('Reenables all previously disabled modules.'),
    'aliases' => array('eam'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );

  return $items;
}

function drush_disable_all_kill_all_modules() {
  if (variable_get('disable_all_modules_disabled', FALSE)) {
    return drush_set_error(dt('Cannot disable all modules as they are already disabled.'));
  }
  module_load_include('admin.inc', 'disable_all');
  disable_all_disable_all();
}

function drush_disable_all_necro_all_modules() {
  if (!variable_get('disable_all_modules_disabled', FALSE)) {
    drush_set_error(dt('Cannot re-enable all modules as they have not been disabled.'));
  }
  module_load_include('admin.inc', 'disable_all');
  disable_all_enable_all();
}
