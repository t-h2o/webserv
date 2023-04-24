const input = document.querySelector('input');
const preview = document.querySelector('.preview');
const itemsList = document.getElementById('items-hook');
const submitBtn = document.querySelector('#submit-btn');

let urlUpload = 'http://localhost:8080/website/upload-file';
let urlDelete = 'http://localhost:8080/'
let url = '';

let submitedFiles = [];

// Handle the front when a file is selected, preview.
const updateImageDisplay = () => {
	// remove image from preview div if have any
	while (preview.firstChild)
	{
		preview.removeChild(preview.firstChild);
	}
	const curFiles = input.files;
	// display text if there is no files in preview
	const para = document.createElement('p');
	if (curFiles.length === 0)
	{
		para.textContent = 'No files currently selected for upload';
		preview.appendChild(para);
	}
	else
	{
		// display the image preview
		const list = document.createElement('ul');
		list.style.listStyleType = 'none';
		preview.appendChild(list);
		for (const file of curFiles)
		{
			const listItem = document.createElement('li');
			if (validFileType(file))
			{
				const image = document.createElement('img');
				image.style.width = '250px';
				image.style.height = '150px';
				image.src = URL.createObjectURL(file);
				listItem.appendChild(image);
			}
			else
			{
				para.textContent = `File name ${file.name}: Not a valid file type. Update your selection.`;
				listItem.appendChild(para);
			}
			list.appendChild(listItem);
		}
	}
};

const validFileType = (file) => { return fileTypes.includes(file.type); };

// list of accepted image
const fileTypes = [ 'image/gif', 'image/jpeg', 'image/png', 'image/svg+xml' ];

const renderImages = () => {
	while (itemsList.firstChild)
	{
		itemsList.removeChild(itemsList.firstChild);
	}
	if (submitedFiles.length === 0)
		return;
	for (const images of submitedFiles)
	{
		itemsList.appendChild(images);
	}
	while (preview.firstChild)
	{
		preview.removeChild(preview.firstChild);
	}
	input.value = null;
};

const createIdNumber = () => { return Math.random().toString(); };

// Function that is called when we click on a existing file to delete it
const deleteExistingFile = (e) => {
	e.preventDefault();
	const id = e.target.parentElement.id
	submitedFiles = submitedFiles.filter((el) => el.id !== e.target.parentElement.id);
	/**
	 * TODO => send http DELETE methode to delete the file.
	 */
	fetch(`${ urlDelete }${id}`, { method : 'DELETE' })
		.then(response => {
			if (!response.ok)
			{
				throw new Error('Network response was not ok');
			}
			console.log('Item deleted successfully');
		})
		.catch(error => { console.error('There was a problem deleting the item:', error); });
	renderImages();
};

const submitHandler = (e) => {
	e.preventDefault();
	/**
	 * * Backend part
	 * * send http POST methode to send the file to the server.
	 */
	const curFiles = input.files;
	const data = new FormData();

	const files = curFiles[0].name;
	data.append(files, curFiles[0]);
	fetch(urlUpload, { method : 'POST', mode : 'no-cors', body : data })
		.then((response) => response)
		.then((data) => { console.log(data); })
		.catch((error) => { console.error(error); });
	console.log(data);

	/**
	 * * Frontend part
	 */
	console.log(files);
	if (curFiles.length === 0)
		return;
	const li = document.createElement('li');
	li.setAttribute('id', files);
	const image = document.createElement('img');
	image.style.width = '250px';
	image.style.height = '150px';
	image.src = URL.createObjectURL(curFiles[0]);
	li.appendChild(image);
	li.addEventListener('click', deleteExistingFile);
	submitedFiles.push(li);
	renderImages();
};

input.addEventListener('change', updateImageDisplay);
submitBtn.addEventListener('click', submitHandler);
