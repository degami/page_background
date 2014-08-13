/**
 * @file
 * Page Background Admin JS.
 */

(function($){
  $(document).ready(function(){
    $('#edit-default').change(function(){
      var $this = $(this);
      $form = $this.closest('form');
      if($this.attr('checked')){
        $form.find('#edit-path').parent().hide();
      }else{
        $form.find('#edit-path').parent().show();
      }
    }).trigger('change');
  });
})(jQuery);
