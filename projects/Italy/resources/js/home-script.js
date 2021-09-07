$(document).ready(function() {
    $('.main-slides').slippry({
        // general elements & wrapper
        elements: 'li', // elments cointaining slide content
      
        // options
        adaptiveHeight: false, // height of the sliders adapts to current 
        captions: false,
      
        // transitions
        transition: 'horizontal', // fade, horizontal, kenburns, false
        speed: 1200,
        pause: 8000,
      
        // slideshow
        autoDirection: 'next'
    });

    $('.flexslider').flexslider({
        animation: "slide",
        animationLoop: true,
        itemWidth: 210,
        itemMargin: 5,
        minItems: 2,
        maxItems: 3
    });

    $('#logo-section').mouseenter(function() {
        $('#home-logo').attr('src', 'resources/images/logo-f.png');
    });

    $('#logo-section').mouseleave(function() {
        $('#home-logo').attr('src', 'resources/images/logo.png');
    });
});