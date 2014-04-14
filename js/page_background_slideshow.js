(function($) {
  $(document).ready(function() {
    var page_background_cycle_options = {
      fx: Drupal.settings.page_background.fx,
      timeout: Drupal.settings.page_background.timeout,
      speed: Drupal.settings.page_background.speed,
      fit: Drupal.settings.page_background.fit,
      delay: Drupal.settings.page_background.delay,
      sync: Drupal.settings.page_background.sync,
      pager:  '#page_background_pager'
    };
    if( Drupal.settings.page_background.page_background_pager_generator == 'module' ){
     page_background_cycle_options['pagerAnchorBuilder'] = function() {};
    }
    $('#page_background_container')
      .not('.processed')
      .cycle(page_background_cycle_options)
      .addClass('processed');
  });
})(jQuery);
