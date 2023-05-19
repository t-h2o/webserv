const headBtn = document.querySelector('#head-btn');

const headHandler = (e) => {
	e.preventDefault();
  fetch('http://localhost:8081', {
  method: 'HEAD'
})
  .then(response => {
    console.log('Status:', response.status);
    console.log('Headers:', response.headers);
  })
  .catch(error => {
    console.error('Error:', error);
  });
}

headBtn.addEventListener('click', headHandler);
