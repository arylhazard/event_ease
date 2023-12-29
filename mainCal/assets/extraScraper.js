const axios = require('axios');
const fs = require("fs");
const { JSDOM } = require("jsdom");
const path = require('path');
const months = ["Baisakh", "Jestha", "Asadh", "Shrawan", "Bhadra", "Ashwin", "Kartik", "Mangshir", "Poush", "Magh", "Falgun", "Chaitra"];

// Initialize an empty object to store the year's data
let yearData = {};

const fetchData = async (year, month) => {
    try {
        console.log("Fetching", year, month);

        const monthName = months[month - 1];

        const url = `https://nepalicalendar.rat32.com/${year}/${month}`;
        const { data } = await axios.get(url);

        let dom = new JSDOM(data);

        // Select the #holiC element
        let holiC = dom.window.document.querySelector("#holiC");

        // Remove the style block from the #holiC div
        let style = holiC.querySelector("style");
        if (style) style.remove();

        let holiFest;
        if (holiC.querySelector("table")) {
            // If a table is found within #holiC, process it as the new format
            holiFest = Array.from(holiC.querySelectorAll("tr.bigFont.red, tr.bigFont.blue"))
                .map(node => {
                    let text = node.textContent.trim();
                    let match = text.match(/^(\d{1,2})(.+)/);
                    if (match) {
                        return { [match[1].trim()]: match[2].trim() };
                    } else {
                        return { "unspecified": text };
                    }
                })
                .reduce((obj, item) => ({ ...obj, ...item }), {});
        } else {
            // If no table is found within #holiC, process it as the old format
            holiC.querySelector("b")?.remove();
            holiC.querySelector("a")?.remove();
            holiFest = holiC.textContent.trim().split('\n')
                .map(text => {
                    let match = text.trim().match(/(\d{1,2})(.+)/);
                    if (match) {
                        return { [match[1].trim()]: match[2].trim() };
                    } else {
                        return { "unspecified": text.trim() };
                    }
                })
                .reduce((obj, item) => ({ ...obj, ...item }), {});
        }
            dom.window.document.querySelector("#bibah b").remove();
            let marriage = dom.window.document.querySelector("#bibah").textContent.trim().replace(' and ', ',').split(',');
            marriage = marriage.map(s => Number(s.trim()));
            
            // Bratabandha Date
            dom.window.document.querySelector("#bratabandha b").remove();

            let bratabandha = dom.window.document.querySelector("#bratabandha").textContent.trim().replace(' and ', ',').split(',');
            bratabandha = bratabandha.map(s => Number(s.trim()));

    
        let tithiObject = {};
        let cells = Array.from(dom.window.document.querySelectorAll('.cells'));
        cells.forEach(cell => {
            dom = new JSDOM(cell.innerHTML);
            let nepaliDay = dom.window.document.querySelector('#nday').textContent.trim();
            let tithi = dom.window.document.querySelector('#dashi').textContent.trim();
            tithiObject[nepaliDay] = tithi;
        });

        // Store the month's data in the yearData object
        yearData[monthName] = {
            holidays: holiFest,
            marriage: marriage,
            bratabandha: bratabandha,
            tithi: tithiObject
        };
    } catch (error) {
        console.log(error);
    }
}
const scrapeData = async (year) => {
    // Check if the file already exists
    const dir = `./data/${year}`;
    const filePath = path.join(dir, `${year}.json`);
    if (fs.existsSync(filePath)) {
        console.log(`Data for year ${year} already exists. Skipping...`);
        return;
    }

    for (let m = 1; m <= 12; m++) {
        await fetchData(year, m);
    }

    // Check if the directory exists, if not, create it
    if (!fs.existsSync(dir)){
        fs.mkdirSync(dir, { recursive: true });
    }

    // Convert the yearData object to a JSON string
    const dataString = JSON.stringify(yearData, null, 2);

    // Print the data string to the console
    console.log(dataString);

    // Write the data string to a file
    fs.writeFileSync(filePath, dataString);
    console.log("Data fetch completed for year", year);
}
const scrapeAllData = async () => {
    for (let y = 1992; y <= 2099; y++) {
        await scrapeData(y);
    }
    console.log("All data fetch completed");
}

// Example usage: node extraScraper.js 2081
// or: node extraScraper.js all
const argument = process.argv[2];

if (argument && argument.toLowerCase() === 'all') {
    scrapeAllData();
} else {
    // Example usage: node extraScraper.js 2081
    const year = parseInt(argument);
    scrapeData(year);
}