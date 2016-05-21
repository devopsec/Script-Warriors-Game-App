$(document).ready(function() {
  $("#playbutton").click(function() {
    var name = prompt("What is your name?");
    alert("Hello " + name + ".");
    
    var ask = confirm("Are you ready to play?"); 
    
    if (ask == true) {
      alert("Great! Let's begin.");
      location.assign("http://codepen.io/gabobsd/full/PZzMNp/");
    }
    
    else {
      alert("Oh. Well, hurry up then!")
    }

});
});