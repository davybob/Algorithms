
//Function for creating the MarkovChain 
function nGram(sentence, n){
	//Split the input text into individual elements 
	var words = sentence.split(" ");
	//calculate the length of the sentence
	var total = words.length - n;
	//array to be filled with the individual elements 
	var grams = [];
	//Fill the empty array with the elements from the sentence.
	for (var i = 0; i <= total; i++) {
		var seq = '';
		for (var j = i; j < i + n; j++) 
			seq += words[j] + ' ';
		grams.push(seq);
	}
	return grams;
}

function MarkovChain(){
//Input sentence
var text = 'Hello my name is David and today is a nice day';
//Array to be filled with random sentence 
var tex = [];

var	x = nGram(text, 2);
//Create a random sentence from the elements in the MarkovChain.
	for (var i = 0; i < 5; i++) {
		var seq = '';
		var r = x[Math.floor(Math.random() * x.length)];
		seq += r + ' ';
		tex.push(seq);
	}
	//display the sentence.
	document.getElementById("demo").innerHTML = tex;
}
