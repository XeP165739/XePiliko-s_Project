function jasonWriter(userData){
    const fs = require('fs'); // file system module
    const path = require('path'); // path module
    const filePath = path.join(__dirname, 'userData.json');  // creating file path

    const jasonData = JSON.stringify(userData, null, 2); // translating data to jason format
    try{
        fs.writeFileSync(filePath, jasonData); // writing data to file synchronously
    } catch (err) {
        console.error("Error writing file:", err); // handling error if any occurs during file writing
    }

    /*
    the whole block can be written as 
    fs.writeFileSync(filepath, jasonData, (err) => if(err) throw err);
    */
}

async function jasonReader(){
    const fs = require('fs');
    const path = require('path');

    try{
        const filePath = path.join(__dirname, 'userData.json');
        const data = await fs.promises.readFile(filePath, 'utf8');
        return JSON.parse(data);
    } catch (err) {
        console.error("Error reading file:", err);
        return null;
    }
}

async function addTask(data ,task){
    data.tasks.push(task)
}

async function main(){
    const fs = require('fs');

    const userData = await jasonReader();

    addTask(userData, "Complete Node.js project");
    jasonWriter(userData);
}

main();