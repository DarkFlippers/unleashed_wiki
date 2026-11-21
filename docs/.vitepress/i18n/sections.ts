// Section folder slugs, in sidebar order. Shared by every language.
// To add a section: add the slug here + a label in every locale file.
export const SECTIONS = [
  'start', 'subghz', 'nfc', 'rfid', 'infrared', 'ibutton',
  'badusb', 'gpio', 'apps', 'mobile', 'dev', 'community'
] as const
export type Section = typeof SECTIONS[number]
