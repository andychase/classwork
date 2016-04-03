var image = 1;

function nextImage() {
    image++;
    if (image > 5)
        image = 1;
    var imagePath = "../assignment3/images/" + image + ".jpg";
    document.getElementById("image").src = imagePath;
}

document.addEventListener("DOMContentLoaded", function (event) {
    document.getElementById("next-icon").addEventListener("click", function () {
        nextImage();
    });
});