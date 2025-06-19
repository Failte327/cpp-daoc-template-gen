const puppeteer = require('puppeteer');
const Database = require("better-sqlite3");
const fs = require("fs");
(async () => {
  const conn = new Database("daoc-eden-item-db.sqlite3");
  const bonusesMap = {
    1: "Strength",
    2: "Dexterity",
    3: "Constitution",
    4: "Quickness",
    5: "Intelligence",
    6: "Piety",
    7: "Empathy",
    8: "Charisma",
    9: "Power",
    10: "Hits",
    11: "Body",
    12: "Cold",
    13: "Crush",
    14: "Energy",
    15: "Heat",
    16: "Matter",
    17: "Slash",
    18: "Spirit",
    19: "Thrust",
    40: "Parry",
    43: "Shield",
    148: "Armor Factor",
    153: "Spell Range",
    155: "Melee Speed",
    156: "Acuity",
    163: "All Magic Skills",
    164: "All Melee Skills",
    165: "All Focus Levels",
    173: "Melee Damage",
    190: "Buff Effectiveness",
    191: "Casting Speed",
    194: "Fatigue",
    195: "Healing Effectiveness",
    196: "Power Pool (TOA)",
    197: "Resist Pierce",
    198: "Spell Damage",
    199: "Spell Duration",
    200: "Style Damage",
    201: "Strength Cap Bonus",
    202: "Dexterity Cap Bonus",
    203: "Constitution Cap Bonus",
    204: "Quickness Cap Bonus",
    209: "Acuity Cap Bonus",
    210: "Max Health Cap Bonus",
    211: "Power Pool Cap Bonus",
    254: "Arcane Siphon",
  }
  const browser = await puppeteer.launch({ "headless": false })
  const page = await browser.newPage()
  await page.goto('https://discord.com/oauth2/authorize?client_id=1000531741456470137&grant_type=authorization_code&response_type=code&redirect_uri=https%3A%2F%2Feden-daoc.net%2Fucp.php%3Fmode%3Dlogin%26login%3Dexternal%26oauth_service%3Dstudio_discord&scope=identify+email&prompt=consent&state=9476ba4e9c14aaf94255f27fb70c8e22')
  page.setViewport({ width: 1920, height: 1080 });
  await page.waitForSelector("#uid_34", { visible: true, timeout: 0 });
  await page.type("#uid_34", "timothy.twelker@gmail.com")
  await page.type("#uid_36", "Shealyn15")
  await page.click("[type='submit']")
  await page.waitForSelector('.action__3d3b0', { visible: true, timeout: 0 })
  await page.click('.action__3d3b0')
  await page.waitForNavigation()
  for (i = 600; i < 881; i++) {
    console.log("PAGE " + i + "/881");
    var pageIdentifierForResponse = i - 1;
    await page.goto(`https://eden-daoc.net/items?p=${i}`)
    try {
      var data = await page.waitForResponse(response => response.url() === `https://eden-daoc.net/itm/search.php?p=${pageIdentifierForResponse}`).then((response) => {
        return response.json()
      })
    } catch (error) {
      // Log, retry
      console.error(error);
      await page.goto(`https://eden-daoc.net/items?p=${i}`)
      var data = await page.waitForResponse(response => response.url() === `https://eden-daoc.net/itm/search.php?p=${pageIdentifierForResponse}`).then((response) => {
        return response.json()
      })
    }
    var itemIds = [];
    for (var item in data["items"]) {
      itemIds.push(data["items"][item]["id"])
    }
    for (var id in itemIds) {
      await page.goto(`https://eden-daoc.net/items?id=${itemIds[id]}`)
      var itemData = await page.waitForResponse(response => response.url() === `https://eden-daoc.net/itm/item.php?id=${itemIds[id]}`).then((response) => {
        return response.json()
      });
      await page.waitForSelector("#table_result", { visible: true, timeout: 0 });
      const options = await page.$$eval('.item_line_right', options => {
        return options.map(option => option.textContent);
      });
      var armorTypes = ["Studded", "Reinforced", "Cloth", "Leather", "Chain", "Scale", "Plate"]
      var itemType = options[0];
      var slot = options[1];
      if (armorTypes.includes(itemType)) {
        var realm = options[6];
      } else if (itemType === "Magical") {
        var realm = options[5];
      } else {
        var realm = options[8];
      }
      var name = itemData["name"].replace(/'/g, "");
      var levelRequirement = itemData["required_level"];
      var utility = itemData["utility"];
      var utilitySingle = itemData["utility_single"];
      var allowedClasses = itemData["allowed_classes"];
      var bonusTypes = itemData["bonus_types"];
      var bonusValues = itemData["bonus_values"];
      var proc1Json = itemData["proc1_json"];
      var proc2Json = itemData["proc2_json"];
      var use1Json = itemData["use1_json"];
      var use2Json = itemData["use2_json"];
      var passiveJson = itemData["passive_json"];
      var react1Json = itemData["react1_json"];
      var react2Json = itemData["react2_json"];
      try {
        conn.exec(`INSERT INTO Items (name, item_type, slot, level_requirement, realm, utility, utility_single, allowed_classes, bonus_types, bonus_values, proc1_json, proc2_json, use1_json, use2_json, passive_json, react1_json, react2_json) VALUES ('${name}', '${itemType}', '${slot}', ${levelRequirement}, '${realm}', ${utility}, ${utilitySingle}, '${allowedClasses}', '${bonusTypes}', '${bonusValues}', '${proc1Json}', '${proc2Json}', '${use1Json}', '${use2Json}', '${passiveJson}', '${react1Json}', '${react2Json}');`);
      } catch (error) {
        conn.exec(`INSERT INTO Items (name, item_type, slot, level_requirement, realm, utility, utility_single, allowed_classes, bonus_types, bonus_values) VALUES ('${name}', '${itemType}', '${slot}', ${levelRequirement}, '${realm}', ${utility}, ${utilitySingle}, '${allowedClasses}', '${bonusTypes}', '${bonusValues}');`);
        console.log("failed to get proc info for " + name);
      }
    }
  }
})()

