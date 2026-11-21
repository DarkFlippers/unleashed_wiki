<script setup lang="ts">
import { computed } from 'vue'
import { useData } from 'vitepress'
import { LOCALES } from '../../i18n'

const { localeIndex, page } = useData()
const loc = computed(() => LOCALES.find((l) => (l.prefix || 'root') === localeIndex.value))
const show = computed(() => !!loc.value?.machineTranslated && !!loc.value?.mtNotice)
// Link to the same page in English: strip the locale prefix.
const enLink = computed(() => '/' + page.value.relativePath.replace(/^[a-z]{2}\//, '').replace(/(index)?\.md$/, ''))
</script>

<template>
  <div v-if="show" class="ul-mt">
    <span class="ul-mt-icon">⚠</span>
    <div>
      <strong>{{ loc!.mtNotice!.title }}</strong>
      <p>{{ loc!.mtNotice!.text }} <a :href="enLink">English</a> · <a :href="'/ru' + enLink">Русский</a></p>
      <p class="ul-mt-help">{{ loc!.mtNotice!.help }}</p>
    </div>
  </div>
</template>
