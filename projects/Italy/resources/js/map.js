$(document).ready(function() {
    mapboxgl.accessToken = 'pk.eyJ1IjoiYm9vemFhOTQiLCJhIjoiY2prOG80bDE3MXM5ZDNwcGFodXI0Nno3OSJ9.gJkjK5lqid4X_GYiDzxKMg';
    var map = new mapboxgl.Map({
    container: 'map',
    style: 'mapbox://styles/boozaa94/cjkc6dfoe0az72ro6m274qwog'
    });

    map.addControl(new mapboxgl.NavigationControl());
});