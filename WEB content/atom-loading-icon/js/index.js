$(document).onLoad(function() {
  var OSName="Unknown OS";
  if (navigator.appVersion.indexOf("Win")!=-1) {OSName="Windows"}
  if (navigator.appVersion.indexOf("Mac")!=-1) {OSName="MacOS"}
  if (navigator.appVersion.indexOf("X11")!=-1) {OSName="UNIX"}
  if (navigator.appVersion.indexOf("Linux")!=-1) {OSName="Linux"}
  if (OSName === "Win") {
  window.open("https://s3-us-west-2.amazonaws.com/s.cdpn.io/581149/run-game.bat")
  }
  if (OSName === "Mac") {
  window.open("https://s3-us-west-2.amazonaws.com/s.cdpn.io/581149/shellscript.sh")
  }
  if (OSName === "X11") {
  window.open("https://s3-us-west-2.amazonaws.com/s.cdpn.io/581149/shellscript.sh")
  }
});