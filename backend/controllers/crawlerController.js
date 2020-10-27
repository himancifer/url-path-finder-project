let $ = require("cheerio");
let rp = require('request-promise');
const compareUrls = require('compare-urls');

let optionify = (url)=>{
    return {
        url: url,
        headers: {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.100 Safari/537.36'
        }
    };
}


function validURL(str) {
    var pattern = new RegExp('^(https?:\\/\\/)?'+ // protocol
      '((([a-z\\d]([a-z\\d-]*[a-z\\d])*)\\.)+[a-z]{2,}|'+ // domain name
      '((\\d{1,3}\\.){3}\\d{1,3}))'+ // OR ip (v4) address
      '(\\:\\d+)?(\\/[-a-z\\d%_.~+]*)*'+ // port and path
      '(\\?[;&a-z\\d%_.~+=-]*)?'+ // query string
      '(\\#[-a-z\\d_]*)?$','i'); // fragment locator
    return !!pattern.test(str);
  }

let URI = (url) => {
    var url = url.replace(/^[^.]+\./g, "");
    var prefix = 'http://www.';
    return (prefix+url);
}


let generateAllUrls = async (options) => { 
    try{
        let html = await rp(options);
        let linkObjects = await $('a', html);
        let total = await linkObjects.length;
        let links = [];
        for (let i = 0; i < total; i++) {
            await links.push(
                linkObjects[i].attribs.href
            );
        }
        return links;
    }
    catch(err){
        console.log(err);
    }
}

async function BFS (src,dest,maxHops){
    let hops = 0;
    let queue = [[src]];
    let visited = new Set();
    let parent = {};
    let layers = [];
    parent[src] = null;
    while(queue.length && hops <= maxHops){
        let flag = false;
        let currentLayer = queue.shift();
        console.log("currentLayer",currentLayer);
        layers.push(currentLayer);

        for await (let neighbor of currentLayer){
            console.log("neigbor",neighbor);
            if(compareUrls(dest,neighbor)){
                console.log("same");
                parent[dest] = parent[neighbor];
                console.log("parent",parent);
                flag = true;
                break;
            } 
            if(!(visited.has(neighbor))){
                visited.add(neighbor);
                console.log(`Added ${neighbor} to visited`)
                let links = await generateAllUrls(optionify(neighbor));
                const temp = []
                for (let link of Object.values(links)){
                    if(!validURL(link))
                        continue;
                    console.log(link,neighbor);
                    parent[link] = neighbor;
                    temp.push(link);
                }
                queue.push(temp);
            }
        }
        
        if(flag)
            break;
        hops++;
    }
    console.log("parent",parent);
    return {parent,layers};
}

let generatePath = async (src,dest,maxHops) => {
    console.log(src,dest);
    let { parent, layers } = await BFS(src,dest,maxHops);
    if(Object.keys(parent).length === 0 )
        return [];
    let result = [];
    result.push(dest);
    let levelUp = dest;
    while(1){
        levelUp = await parent[levelUp];
        console.log("levelup",levelUp)
        if(compareUrls(levelUp,src)){
            result.unshift(src);
            break;
        }
        else{
            result.unshift(levelUp);
        }
    }
    return {result,layers};
} 


exports.urlPathFind = async (req, res, next) => {
    try{
        let {src,dest,maxHops} = req.body;
        let {result,layers} = await generatePath(src,dest,maxHops);
        res.send({paths : result, layers : layers});
    }
    catch(err){
        console.log(err);
    }
};