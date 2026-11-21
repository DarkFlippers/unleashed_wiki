// Known sources/authors, referenced from page frontmatter:
//   author: gromovyna            → highlighted credit card at the bottom
//   original: https://telegra.ph/...  (link to the original article)
//   sources: [flipper-docs, unleashed-docs, how2flipper]
export const SOURCES: Record<string, { name: string; url: string; avatar?: string; telegram?: boolean }> = {
  'gromovyna':      { name: '@gromovyna', url: 'https://t.me/gromovyna', telegram: true },
  'how2flipper':    { name: '@how2flipper_rus', url: 'https://t.me/how2flipper_rus', telegram: true },
  'flipper-docs':   { name: 'Flipper Zero Docs', url: 'https://docs.flipper.net/zero' },
  'unleashed-docs': { name: 'Unleashed Firmware docs', url: 'https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation' },
  'unleashed-readme': { name: 'Unleashed ReadMe', url: 'https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md' },
  'unleashed-src':  { name: 'Unleashed Firmware source', url: 'https://github.com/DarkFlippers/unleashed-firmware/tree/dev' },
  'li0ard':         { name: 'li0ard blog', url: 'https://blog.li0ard.rest/wtfiskeeloq' },
  'all-the-plugins': { name: 'xMasterX/all-the-plugins', url: 'https://github.com/xMasterX/all-the-plugins/tree/dev' }
}
