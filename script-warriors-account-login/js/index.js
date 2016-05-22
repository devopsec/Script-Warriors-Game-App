// Add class to form-item on input:focus
$('input, textarea')
  .on("focus blur", function() {
    $(this)
      .closest('.form-item')
      .toggleClass("focused");
  });