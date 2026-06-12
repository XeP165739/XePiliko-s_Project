async function fetchData(data) {
  // Simulate fetching data with a timeout.
    return new Promise((resolve) => {
        setTimeout(() => resolve(`data ${data} fetched succesfully!`), 1000);
    });
}

async function sequential() {
    console.time('s');

    const data1 = await fetchData(1);
    const data2 = await fetchData(2);
    const data3 = await fetchData(3);
    
    console.timeEnd('s');

    console.log('data: ', data1, data2, data3);
}

async function parallel() {
    console.time('p');

    const result = await Promise.all([
        fetchData(1),
        fetchData(2),
        fetchData(3)
    ]);

    console.timeEnd('p');

    console.log('data:', result);
}

sequential();
parallel();