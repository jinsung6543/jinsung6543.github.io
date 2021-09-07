$(document).ready(function() {
    $(".project").hover3d({
        selector: ".project__card",
        sensitivity: 15
    });

    setTimeout(() => {
        $('.hello-1').css('color', '#f9e89f');
    }, 1000);

    setTimeout(() => {
        $('.hello-2').css('color', '#ed8c72');
    }, 2000);

    setTimeout(() => {
        $('.hello-3').css('color', '#2988bc');
    }, 3000);

    $('.js--nav-icon').click(function() {
        var nav = $('.js--main-nav');
        var icon = $('.js--nav-icon i');

        nav.slideToggle(200);

        if (icon.hasClass('ion-navicon-round')) {
            icon.addClass('ion-close-round');
            icon.removeClass('ion-navicon-round');
        } else {
            icon.addClass('ion-navicon-round');
            icon.removeClass('ion-close-round');
        }
        
    });

    $('.js--section-about').waypoint(function(direction) {
        if (direction == "down") {
            $('nav').addClass('sticky');
        } else {
            $('nav').removeClass('sticky');
        }
    }, {
        offset: '80px'
    });

    $('.profile-img').waypoint(function(direction) {
        $('.profile-img').addClass('animated rollIn');
    }, {
        offset: '50%'
    });
});