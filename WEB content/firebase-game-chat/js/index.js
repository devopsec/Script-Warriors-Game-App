var fireBaseRef = new Firebase("https://boiling-fire-5700.firebaseio.com");
 
        $("#submit-btn").bind("click", function() {
            var comment = $("#comments");
            var commentValue = $.trim(comment.val());
 
            if (commentValue.length === 0) {
                alert('Comments are required to continue!');
            } else {
                fireBaseRef.push({comment: commentValue}, function(error) {
                    if (error !== null) {
                        alert('Unable to push comments to Firebase!');
                    }
                });
 
                comment.val("");
            }
 
            return false;
        });
 
        fireBaseRef.on('child_added', function(snapshot) {
            var uniqName = snapshot.name();
            var comment = snapshot.val().comment;
            var commentsContainer = $('#comments-container');
 
            $('<div/>', {class: 'comment-container'})
                .html('<span class="label label-default">Comment '
                    + uniqName + '</span>' + comment).appendTo(commentsContainer);
 
            commentsContainer.scrollTop(commentsContainer.prop('scrollHeight'));
        });