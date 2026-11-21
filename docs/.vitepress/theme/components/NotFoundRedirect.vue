<script setup lang="ts">
import { onMounted } from 'vue'
import { LOCALES } from '../../i18n'

const PREFIXES = LOCALES.map((l) => l.prefix).filter(Boolean) as string[]

// A page that isn't translated yet would 404 in that language. Send the visitor
// to the English version of the same path instead; the loop guard set by the
// language redirect in config.mts keeps them there.
onMounted(() => {
  const seg = location.pathname.split('/')[1]
  if (!PREFIXES.includes(seg)) return
  const english = location.pathname.slice(seg.length + 1) || '/'
  location.replace(english + location.search + location.hash)
})
</script>

<template><span /></template>
