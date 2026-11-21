// Downloads every remote image referenced in docs/**/*.md into docs/public/img/remote/
// and rewrites the markdown to the local path, so the built site has no hotlinks.
import fs from 'node:fs'; import path from 'node:path'; import crypto from 'node:crypto'
const DOCS = path.resolve('docs'), OUT = path.join(DOCS, 'public/img/remote')
fs.mkdirSync(OUT, { recursive: true })
const walk = (d) => fs.readdirSync(d, { withFileTypes: true }).flatMap((e) =>
  e.name.startsWith('.') || e.name === 'public' ? [] : e.isDirectory() ? walk(path.join(d, e.name)) : e.name.endsWith('.md') ? [path.join(d, e.name)] : [])
const RE = /!\[([^\]]*)\]\((https?:\/\/[^)\s]+)(\s+"[^"]*")?\)/g
const cache = new Map(); let n = 0, fail = 0
for (const file of walk(DOCS)) {
  let src = fs.readFileSync(file, 'utf8'); const urls = [...src.matchAll(RE)].map((m) => m[2])
  if (!urls.length) continue
  for (const url of urls) {
    if (!cache.has(url)) {
      try {
        const r = await fetch(url); if (!r.ok) throw new Error(r.status)
        const ct = r.headers.get('content-type') || ''
        const ext = (ct.match(/image\/(png|jpeg|gif|webp|svg)/) || [])[1]?.replace('jpeg', 'jpg').replace('svg', 'svg') || path.extname(new URL(url).pathname).slice(1) || 'png'
        const name = crypto.createHash('sha1').update(url).digest('hex').slice(0, 16) + '.' + ext
        fs.writeFileSync(path.join(OUT, name), Buffer.from(await r.arrayBuffer())); cache.set(url, `/img/remote/${name}`); n++
      } catch (e) { console.warn('FAIL', url, e.message); cache.set(url, null); fail++ }
    }
    const local = cache.get(url); if (local) src = src.split(url).join(local)
  }
  fs.writeFileSync(file, src)
}
console.log(`downloaded ${n}, failed ${fail}`)
