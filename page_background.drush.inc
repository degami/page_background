<?php

/**
 * @file
 * Drush commands for page_background.
 */

/**
 * Implements hook_drush_command().
 */
function page_background_drush_command() {
  $items['page_background-list'] = array(
    'callback' => 'drush_page_background_list',
    'description' => dt('List defined Backgrounds'),
    'arguments' => array(),
    'options' => array(),
    'aliases' => array('pbl'),
  );
  $items['page_background-add'] = array(
    'callback' => 'drush_page_background_add',
    'description' => dt('Add a new page background'),
    'examples' => array(
      'drush page_background-add <front> /path/to/file.png' => 'Add file.png as background for frontpage',
    ),
    'arguments' => array(
      'path' => 'path for this background ("null" in case of "default")',
      'image' => 'image to be used',
    ),
    'options' => array(
      'image_alt'   => dt('Image Alt (only if background set as Image tag)'),
      'image_title'   => dt('Image Title (only if background set as Image tag)'),
      'bglinkurl'   => dt('Link Url'),
      'bgtext' => t('Background Slogan Text'),
      'bgtextlang' => t('Background Slogan Language'),
    ),
    'aliases' => array('pba'),
  );
  $items['page_background-delete'] = array(
    'callback' => 'drush_page_background_delete',
    'description' => dt('Delete a page background'),
    'examples' => array(
      'drush page_background-delete 1' => 'Delete page background identified by bid:1',
    ),
    'arguments' => array(
      'bid' => 'Bid',
    ),
    'options' => array(),
    'aliases' => array('pbd'),
  );
  $items['page_background-clone'] = array(
    'callback' => 'drush_page_background_clone',
    'description' => dt('Clone a page background image with a new path'),
    'examples' => array(
      'drush page_background-clone 1 <front>' => 'Clone page background identified by bid:1 to be also in frontpage',
    ),
    'arguments' => array(
      'bid' => 'Bid',
      'path' => 'path for this background ("null" in case of "default")',
    ),
    'options' => array(
      'image_alt'   => dt('Image Alt (only if background set as Image tag)'),
      'image_title'   => dt('Image Title (only if background set as Image tag)'),
      'bglinkurl'   => dt('Link Url'),
      'bgtext' => t('Background Slogan Text'),
      'bgtextlang' => t('Background Slogan Language'),
    ),
    'aliases' => array('pbc'),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function page_background_drush_help($section) {
  switch ($section) {
    case 'drush:page_background-list':
      return dt('List defined Backgrounds');

    case 'drush:page_background-add':
      return dt('Add a new page background');

    case 'drush:page_background-delete':
      return dt('Delete a page background');

    case 'drush:page_background-clone':
      return dt('Clone a page background image with a new path');
  }
}

/**
 * Add new page background.
 */
function drush_page_background_add($path, $image) {
  if (strtolower($path) == "null") {
    $path = NULL;
  }
  if ($path != NULL) {
    $path = drupal_get_normal_path($path);
  }

  $imagecontents = file_get_contents($image);
  $file = file_save_data($imagecontents, 'public://page_backgrounds/' . basename($image));

  $values = array(
    'file' => $file,
    'path' => $path,
    'weight' => 0,
  );
  if ($image_alt = drush_get_option('image_alt')) {
    $values['image_alt'] = $image_alt;
  }
  if ($image_title = drush_get_option('image_title')) {
    $values['image_title'] = $image_title;
  }
  if ($bglinkurl = drush_get_option('bglinkurl')) {
    $values['bglinkurl'] = $bglinkurl;
  }
  if ($bgtext = drush_get_option('bgtext')) {
    $values['bgtext'] = $bgtext;
  }
  if ($bgtextlang = drush_get_option('bgtextlang')) {
    $values['bgtextlang'] = $bgtextlang;
  }

  $fake_form_state = array('values' => array());
  _page_background_save($values, $fake_form_state);

  drupal_set_message(t('Background saved succesfully'));
}

/**
 * Delete page background.
 */
function drush_page_background_delete($bid) {
  if (($background_row = page_background_load($bid)) !== FALSE) {
    $numdeleted = _page_background_delete($background_row);
    drupal_set_message(t(':numelements elements deleted', array(':numelements' => $numdeleted)));
  }
}

/**
 * Clone page background.
 */
function drush_page_background_clone($bid, $path) {
  if (strtolower($path) == "null") {
    $path = NULL;
  }
  if ($path != NULL) {
    $path = drupal_get_normal_path($path);
  }
  if (($background_row_orig = page_background_load($bid)) !== FALSE) {

    $values = array(
      'fid' => $background_row_orig->fid,
      'path' => $path,
      'weight' => 0,
      'bglinkurl' => $background_row_orig->bglinkurl,
      'bgtextlang' => $background_row_orig->bgtextlang,
      'bgtext' => $background_row_orig->bgtext,
      'image_alt' => $background_row_orig->image_alt,
      'image_title' => $background_row_orig->image_title,
    );

    if ($image_alt = drush_get_option('image_alt')) {
      $values['image_alt'] = $image_alt;
    }
    if ($image_title = drush_get_option('image_title')) {
      $values['image_title'] = $image_title;
    }
    if ($bglinkurl = drush_get_option('bglinkurl')) {
      $values['bglinkurl'] = $bglinkurl;
    }
    if ($bgtext = drush_get_option('bgtext')) {
      $values['bgtext'] = $bgtext;
    }
    if ($bgtextlang = drush_get_option('bgtextlang')) {
      $values['bgtextlang'] = $bgtextlang;
    }

    $fake_form_state = array('values' => array());
    _page_background_save($values, $fake_form_state);

    drupal_set_message(t('Background cloned succesfully'));
  }
}

/**
 * Lists page backgrounds.
 */
function drush_page_background_list() {
  $query = db_select('url_background_images', 'bg');
  $query->fields('bg');
  $query->orderBy('weight');
  $query->orderBy('created');
  $result = $query->execute()->fetchAll();

  $rows = array();
  $rows[] = array(
    dt('Bid'),
    dt('Path'),
    dt('File uri'),
  );
  foreach ($result as $bkg) {
    $file = file_load($bkg->fid);
    $rows[] = array(
      0 => $bkg->bid,
      1 => ($bkg->path == NULL) ? dt('Default') : $bkg->path,
      2 => $file->uri,
    );
  }

  drush_print_table($rows, $header = TRUE);
}
