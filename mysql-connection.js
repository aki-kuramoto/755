// to get to mysql package to npm install mysql -g
const mysql = require('mysql');
let connection = mysql.createConnection({
	host     : '127.0.0.1',
	user     : 'root',
	// password : 'secret'
});

connection.connect(err => {
	if (err) {
		console.error('error connecting: ' + err.stack);
		return;
	}
	
	console.log('connected as id ' + connection.threadId);
});
