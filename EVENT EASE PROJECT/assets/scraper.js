const axios = require('axios');
const fs = require("fs");
const { JSDOM } = require("jsdom");
const ProgressBar = require('progress'); // Import the progress module

const months = ["Baisakh", "Jestha", "Asadh", "Shrawan", "Bhadra", "Ashwin", "Kartik", "Mangshir", "Poush", "Magh", "Falgun", "Chaitra"];

const parseEnglishDate = (en) => {
    const [monthYear, year] = en.split(" ");
    const [startMonth, endMonth] = monthYear.split("/");
    const enBeginning = [startMonth];
    const enEnding = [endMonth];

    if (year.length === 4) {
        enBeginning.push(year);
        enEnding.push(year);
    } else {
        const [yearBeginning, yearEnding] = year.split("/");
        enBeginning.push(yearBeginning);
        enEnding.push(yearEnding);
    }

    return { enBeginning, enEnding };
};

const fetchData = async (year, month, bar) => { // Add a bar parameter to update the progress bar
    try {
        console.log("Fetching", year, month);

        const monthName = months[month - 1];
        const directoryPath = `./data/${year}/${monthName}`;

        // Check if the file already exists
        if (fs.existsSync(`${directoryPath}.json`)) {
            console.log("Data already exists for", monthName);
            bar.tick(); // Increment the progress bar by one
            return;
        }

        const url = `https://nepalicalendar.rat32.com/${year}/${month}`;
        const { data } = await axios.get(url);

        let dom = new JSDOM(data);

        // Metadata
        let metadata = {
            nepaliDate: dom.window.document.querySelector("#yren").textContent.trim().split(' '),
        };

        const englishDate = dom.window.document.querySelector("#entarikYr").textContent.trim();
        Object.assign(metadata, parseEnglishDate(englishDate));

        // Days
        let days = [];

        let dayCount = 1;
        let cells = Array.from(dom.window.document.querySelectorAll('.cells'));
        cells.forEach(cell => {
            dom = new JSDOM(cell.innerHTML);
            days.push({
                nepaliDay: dom.window.document.querySelector('#nday').textContent.trim(),
                englishDay: dom.window.document.querySelector('#eday').textContent.trim(),
                isHoliday: dom.window.document.querySelector('#nday font').getAttribute('color').trim() == "red",
                dayCount
            });

            dayCount++;
            if (dayCount > 7) dayCount = 1;
        });

        // Write to file with indentation for better readability
        if (!fs.existsSync(`./data/${year}`)) fs.mkdirSync(`./data/${year}`);

        fs.writeFileSync(`${directoryPath}.json`, JSON.stringify({ metadata, days }, null, 2));
        console.log("Done", monthName);
        bar.tick(); // Increment the progress bar by one
    } catch (error) {
        console.log(error);
    }
}

const scrapeData = async (year, month) => {
    const bar = new ProgressBar('[:bar] :percent', { total: 1 }); // Create a progress bar with one total tick
    await fetchData(year, month, bar);
    console.log("Data fetch completed");
}

const scrapeAllData = async () => {
    const missingDataLog = [];

    const total = 12 * (2099 - 1992 + 1); // Calculate the total number of months to scrape
    const bar = new ProgressBar('[:bar] :percent', { total }); // Create a progress bar with the total number of ticks

    for (let y = 1992; y <= 2099; y++) {
        for (let m = 1; m <= 12; m++) {
            if (!fs.existsSync(`./data/${y}/${months[m - 1]}.json`)) {
                missingDataLog.push({ month: months[m - 1] });
                await fetchData(y, m, bar); // Pass the progress bar to the fetchData function
            } else {
                bar.tick(); // Increment the progress bar by one if the data already exists
            }
        }
    }

    // Write missing data log to a file with indentation
    const logFilePath = './data/missing_data_log.json';
    fs.writeFileSync(logFilePath, JSON.stringify(missingDataLog, null, 2));
    console.log("All data fetch completed");
    console.log(`Missing data log has been saved to ${logFilePath}`);
}

// Example usage: node code.js 2081 1
const argument = process.argv[2];

if (argument && argument.toLowerCase() === 'all') {
    scrapeAllData();
} else {
    // Example usage: node code.js 2081 1
    const year = parseInt(process.argv[2]);
    const month = parseInt(process.argv[3]);
    scrapeData(year, month);
}
