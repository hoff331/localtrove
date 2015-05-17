(function ($) {
  $(document).ready(function() {
    if ($('#edit-should-expire').attr('checked'))
      {
        $('.form-item-expiration-date').show();
      }
      else
      {
        $('.form-item-expiration-date').hide();
      }
    $('.form-item-should-expire').click(function(){
      if ($('#edit-should-expire').attr('checked'))
      {
        $('.form-item-expiration-date').slideDown();
      }
      else
      {
        $('.form-item-expiration-date').slideUp();
      }
    });
  });
})(jQuery);