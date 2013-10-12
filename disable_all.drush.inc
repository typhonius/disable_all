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
  );
  $items['necro-all-modules'] = array(
    'description' => dt('Reenables all previously disabled modules.'),
    'aliases' => array('eam'),
  );

  return $items;
}

function drush_disable_all_kill_all_modules() {
  module_load_include('admin.inc', 'disable_all');
  disable_all_disable_all();
}

function drush_disable_all_necro_all_modules() {
  module_load_include('admin.inc', 'disable_all');
  disable_all_enable_all();
}
