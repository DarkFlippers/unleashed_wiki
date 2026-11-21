// Lists pages that exist in English (root) but are missing in other locales.
import fs from 'node:fs'; import path from 'node:path'
const DOCS = path.resolve('docs')
const locs = fs.readFileSync('docs/.vitepress/i18n/index.ts','utf8').match(/import \w+ from '\.\/(\w+)'/g).map(s=>s.match(/'\.\/(\w+)'/)[1]).filter(c=>c!=='en')
const walk = (d, rel='') => fs.readdirSync(d,{withFileTypes:true}).flatMap(e => e.name.startsWith('.')||e.name==='public'||(rel===''&&locs.includes(e.name)) ? [] : e.isDirectory() ? walk(path.join(d,e.name), path.join(rel,e.name)) : e.name.endsWith('.md') ? [path.join(rel,e.name)] : [])
const en = walk(DOCS); let missing = 0
for (const l of locs) { const miss = en.filter(f => !fs.existsSync(path.join(DOCS,l,f))); missing += miss.length
  console.log(`${l}: ${en.length-miss.length}/${en.length} pages`); miss.forEach(f=>console.log('  missing', f)) }
process.exit(missing ? 1 : 0)
