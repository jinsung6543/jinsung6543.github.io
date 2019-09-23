$(document).ready(function(){
/*
GAME RULES:

- In each turn, a player chooses odd/even.
- When both players choose, roll dice.
- If player is correct, earn points (2 * sum of all dice)
-           if wrong, lose points
- Reach 100 points to win.
*/

let score;
let choices;
let dice;
let sumOfDice;
let oddOrEven;
let ready;
let playing;
const winPoints = 100;

init();

$('#btn-new').click(init);

$("#btn-roll").click(function() {

    playersReady();
    checkScore();

    if (playing && ready) {
        var dice1 = Math.floor(Math.random() * 6) + 1;
        var dice2 = Math.floor(Math.random() * 6) + 1;
        var dice3 = Math.floor(Math.random() * 6) + 1;
    
        dice.push(dice1, dice2, dice3);
    
        sumOfDice = dice1 + dice2 + dice3;
    
        document.getElementById('dice-1').src = 'images/d-' + dice1 + '.png';
        document.getElementById('dice-2').src = 'images/d-' + dice2 + '.png';
        document.getElementById('dice-3').src = 'images/d-' + dice3 + '.png';

        $('.dice').addClass('animate');
    
        if (sumOfDice % 2 === 0) {
            oddOrEven = 0;
        } else {
            oddOrEven = 1;
        }
    
        $('#sum').text(sumOfDice);
        
        if (oddOrEven === 0) {
            $('#odd-or-even').text('EVEN!');
        } else {
            $('#odd-or-even').text('ODD!');
        }
    
        calculateScore(0);
        calculateScore(1);
        
        $('#point-0').text(score[0]);
        $('#point-1').text(score[1]);
    
        dice = [];
        sumOfDice = 0;
    }

    winner();
    choices = [-1,-1];
    ready = false;
    $('#btn-roll').removeClass('roll-enabled');
    $('#btn-roll').addClass('roll-disabled');
    $('.btn-even').removeClass('selected');
    $('.btn-odd').removeClass('selected');
    setTimeout(
        function() 
        {
            $('.dice').addClass('animate-over');
            $('.dice').removeClass('animate');
        }, 200);
    });

$('.btn-odd').click(function() {
    if ($(this).hasClass('p1')) {
        choices[0] = 1;
    } else {
        choices[1] = 1;
    }

    $(this).addClass("selected");
    $(this).next().removeClass("selected");
    playersReady();
    checkScore();
});

$('.btn-even').click(function() {
    if ($(this).hasClass('p1')) {
        choices[0] = 0;
    } else {
        choices[1] = 0;
    }

    $(this).addClass("selected");
    $(this).prev().removeClass('selected');
    playersReady();
    checkScore();
});

function calculateScore(player) {
    if (choices[player] === oddOrEven) {
        score[player] += 2 * sumOfDice;
        $(`#player-${player + 1}`).addClass('animate');
        setTimeout(
            function() 
            {
                $(`#player-${player + 1}`).addClass('animate-over');
                $(`#player-${player + 1}`).removeClass('animate');
            }, 200);
    } else if (score[player] >= 18) {
        score[player] -= sumOfDice;
    } else {
        score[player] = 0;
    }
}

function playersReady() {
    if (choices[0] !== -1 && choices[1] !== -1 && playing) {
        ready = true;
        $('#btn-roll').removeClass('roll-disabled');
        $('#btn-roll').addClass('roll-enabled');
        $('.dice').removeClass('animate-over');
        $('#player-1').removeClass('animate-over');
        $('#player-2').removeClass('animate-over');
    }
}

function checkScore() {
    if (score[0] >= winPoints || score[1] >= winPoints) {
        playing = false;
    }
}

function winner() {
    if (score[0] >= winPoints && score[1] >= winPoints) {
        if (score[0] > score[1]) {
            $('#player-1').addClass('winner');
            $('#name-1').text('WINNER!');
        } else if (score[0] < score[1]) {
            $('#player-2').addClass('winner');
            $('#name-2').text('WINNER!');
        } else {
            $('#player-1').addClass('draw');
            $('#name-1').text('DRAW');
            $('#player-2').addClass('draw');
            $('#name-2').text('DRAW');
        }
    } else if (score[0] >= winPoints) {
        $('#player-1').addClass('winner');
        $('#name-1').text('WINNER!');
    } else if (score[1] >= winPoints) {
        $('#player-2').addClass('winner');
        $('#name-2').text('WINNER!');
    }
}

function init() {
    score = [0,0];
    choices = [-1,-1];
    dice = [];
    playing = true;
    ready = false;

    $('#point-0').text(0);
    $('#point-1').text(0);
    $('#odd-or-even').text('Odd/Even');
    $('#sum').text('Ready');
    $('#btn-roll').removeClass('roll-enabled');
    $('#btn-roll').addClass('roll-disabled');
    $('#player-1').removeClass('winner');
    $('#player-2').removeClass('winner');
    $('#player-1').removeClass('draw');
    $('#player-2').removeClass('draw');
    $('.btn-even').removeClass('selected');
    $('.btn-odd').removeClass('selected');
    $('#name-1').text('Player 1');
    $('#name-2').text('Player 2');

    document.getElementById('dice-1').src = 'images/d-1.png';
    document.getElementById('dice-2').src = 'images/d-2.png';
    document.getElementById('dice-3').src = 'images/d-3.png';
}

});