document.addEventListener('DOMContentLoaded', function() {

    let correct = document.querySelector('.correct');
    correct.addEventListener('click', function() {
        correct.style.backgroundColor = 'green';
        document.querySelector('#q1f').innerHTML = 'Correct!';
    });

    let incorrects = document.querySelectorAll('.incorrect');
    for (let i = 0; i < incorrects.length; i++) {
        incorrects[i].addEventListener('click', function() {
            incorrects[i].style.backgroundColor = 'red';
            document.querySelector('#q1f').innerHTML = 'Incorrect!';
        });
    }

    document.querySelector('form').addEventListener('submit', function(e) {
        let object = document.getElementById("q2f");
        let text = document.getElementById("q2");
        if ((document.querySelector('#q2').value) == 'United States of America') {
            object.innerHTML = "Correct!";
            text.style.backgroundColor = "green";
        } else {
            object.innerHTML = "Incorrect!";
            text.style.backgroundColor = "red";
        }
        e.preventDefault();
    });
});