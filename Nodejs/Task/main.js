const fs = require('fs');
const path = require('path');
const { stringify } = require('querystring');

const FILE = "Users";
const EXTENTION = ".json";

const user = "XeP";
const filename = `${user}${EXTENTION}`;

const filepath = path.join(__dirname, FILE, filename);

const DEAFULT = {
    user: (user === null || user === undefined) ? 'User' : user,
    tasks: []
}

async function jasonReader(){ //returning the data, not a promise
    try {
        const rawData = await fs.promises.readFile(filepath, 'utf8');
        return JSON.parse(rawData);
    } catch (err) {
        console.error("Error reading file:", err);
        return null;
    }
}

async function addTask(readline, data){
    const task = await new Promise ((resolve) => readline.question('Enter Task:', resolve));
    
    data.tasks.push(task);
}

async function viewTask(data){
    const tasks = data.tasks;
    const size = tasks.length;

    if (size > 0) for (let i = 0; i < size; ++i) console.log(`${i + 1}: ${tasks[i]}`);
    else console.log(`Your task is currently empty.`);
}

function save(rawdata){
    try {
        const data = JSON.stringify(rawdata, null, 2);
        fs.writeFileSync(filepath, data);
    } catch (err) {
        console.error(`Error Occured in Saving: ${err}`);
    }
}

function test(){
    console.log("Testing...");
    try {
        const data = JSON.stringify(DEAFULT, null, 2);
        fs.writeFileSync(filepath, data);
    } catch (err) {
        console.error(`Writing JSON Error: ${err}`);
    }
}

async function main(){
    const readline = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });

    const data = await jasonReader();

    let isUsing = true;

    while(isUsing){
    console.log(`Task Manager | User: ${user} \n 1. Add Task \n 2. View Tasks \n 3. Exit`);
        const command = await new Promise(resolve => readline.question('> ', resolve));

        switch(command.trim().toLowerCase()){
            case '1' : {
                await addTask(readline, data);
                break;
            }
            case '2': {
                viewTask(data);
                break;
            }
            case '3': {
                await save(data);
                isUsing = false;
            }
            default : {
                console.error(`Input Invaid: ${command}`);
            }
        }
    }

    readline.close();
}

main();