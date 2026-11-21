<script setup lang="ts">
import { computed } from 'vue'
import { useData } from 'vitepress'
import { LOCALES } from '../../i18n'
import { SOURCES } from '../../sources'

const { frontmatter, localeIndex } = useData()
const t = computed(() => (LOCALES.find((l) => (l.prefix || 'root') === localeIndex.value) || LOCALES[0]).credits)
const authors = computed<string[]>(() => {
  const a = frontmatter.value.author
  return (Array.isArray(a) ? a : a ? [a] : []).filter((k) => SOURCES[k])
})
const sources = computed<string[]>(() => (frontmatter.value.sources || []).filter((k: string) => SOURCES[k]))
const originals = computed<string[]>(() => {
  const o = frontmatter.value.original
  return Array.isArray(o) ? o : o ? [o] : []
})
const label = (u: string) => {
  try { const x = new URL(u); const p = decodeURIComponent(x.pathname).replace(/\/$/, '').split('/').pop() || ''
    return `${x.hostname.replace(/^www\./, '')} › ${p.replace(/-\d\d-\d\d$/, '').replace(/-/g, ' ').slice(0, 60)}` } catch { return u }
}
</script>

<template>
  <div v-if="authors.length || sources.length || originals.length" class="ul-credits">
    <div v-for="a in authors" :key="a" class="ul-author">
      <div class="ul-author-badge">✦</div>
      <div>
        <div class="ul-author-title">{{ t.authorTitle }}</div>
        <a class="ul-author-name" :href="SOURCES[a].url" target="_blank" rel="noopener">{{ SOURCES[a].name }}</a>
        <span v-if="SOURCES[a].telegram" class="ul-author-tag">{{ t.channel }}</span>
        <p class="ul-author-thanks">{{ t.thanks.replace('{name}', SOURCES[a].name) }}</p>
      </div>
    </div>
    <div v-if="originals.length" class="ul-sources">
      <span>{{ t.original }}:</span>
      <a v-for="o in originals" :key="o" :href="o" target="_blank" rel="noopener">{{ label(o) }}</a>
    </div>
    <div v-if="sources.length" class="ul-sources">
      <span>{{ t.basedOn }}:</span>
      <a v-for="s in sources" :key="s" :href="SOURCES[s].url" target="_blank" rel="noopener">{{ SOURCES[s].name }}</a>
    </div>
  </div>
</template>
