const input = document.querySelector('input');
const preview = document.querySelector('.preview');
const itemsList = document.getElementById('items-hook');
const submitBtn = document.querySelector('#submit-btn');

let urlUpload = 'http://localhost:8081/input.php';
let url = '';

const submitHandler = (e) => {
	e.preventDefault();
	console.log(e.target.value);
}



submitBtn.addEventListener('click', submitHandler);
