#ifndef FONT_CHEF_UNICODE_BLOCK_H
#define FONT_CHEF_UNICODE_BLOCK_H

/**
 * @file unicode-block.h
 * This file provides the fc_unicode_block structure that specifies the first and last unicode point in a range.
 * It also provides, for convenience, many pre-made unicode blocks corresponding to the common blocks in unicode.
 */

#include <stdint.h>
#include "font-chef/font-chef-export.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides information about a specific unicode block, as specified in
 * ftp://ftp.unicode.org/Public/UNIDATA/Blocks.txt
 */
struct fc_unicode_block {
  /** @brief The first unicode point in this range */
  uint32_t first;

  /** @brief The last unicode point in this range (inclusive) */
  uint32_t last;

  /** @brief Same as `last - first` */
  uint32_t count;
};

/* All the blocks, minus a few in the bottom */
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_control;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_basic_latin;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_latin_1_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_latin_extended_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_latin_extended_b;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ipa_extensions;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_spacing_modifier_letters;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_combining_diacritical_marks;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_greek_and_coptic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cyrillic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cyrillic_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_armenian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hebrew;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_arabic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_syriac;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_arabic_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_thaana;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_nko;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_samaritan;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mandaic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_syriac_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_arabic_extended_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_devanagari;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_bengali;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_gurmukhi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_gujarati;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_oriya;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tamil;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_telugu;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_kannada;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_malayalam;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_sinhala;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_thai;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_lao;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tibetan;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_myanmar;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_georgian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hangul_jamo;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ethiopic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ethiopic_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cherokee;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_unified_canadian_aboriginal_syllabics;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ogham;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_runic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tagalog;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hanunoo;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_buhid;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tagbanwa;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_khmer;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mongolian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_unified_canadian_aboriginal_syllabics_extended;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_limbu;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tai_le;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_new_tai_lue;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_khmer_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_buginese;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tai_tham;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_combining_diacritical_marks_extended;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_balinese;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_sundanese;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_batak;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_lepcha;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ol_chiki;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cyrillic_extended_c;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_georgian_extended;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_sundanese_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_vedic_extensions;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_phonetic_extensions;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_phonetic_extensions_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_combining_diacritical_marks_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_latin_extended_additional;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_greek_extended;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_general_punctuation;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_superscripts_and_subscripts;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_currency_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_combining_diacritical_marks_for_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_letterlike_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_number_forms;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_arrows;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mathematical_operators;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_miscellaneous_technical;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_control_pictures;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_optical_character_recognition;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_enclosed_alphanumerics;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_box_drawing;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_block_elements;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_geometric_shapes;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_miscellaneous_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_dingbats;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_miscellaneous_mathematical_symbols_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_supplemental_arrows_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_braille_patterns;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_supplemental_arrows_b;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_miscellaneous_mathematical_symbols_b;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_supplemental_mathematical_operators;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_miscellaneous_symbols_and_arrows;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_glagolitic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_latin_extended_c;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_coptic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_georgian_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tifinagh;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ethiopic_extended;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cyrillic_extended_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_supplemental_punctuation;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_radicals_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_kangxi_radicals;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ideographic_description_characters;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_symbols_and_punctuation;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hiragana;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_katakana;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_bopomofo;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hangul_compatibility_jamo;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_kanbun;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_bopomofo_extended;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_strokes;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_katakana_phonetic_extensions;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_enclosed_cjk_letters_and_months;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_compatibility;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_unified_ideographs_extension_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_yijing_hexagram_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_unified_ideographs;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_yi_syllables;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_yi_radicals;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_lisu;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_vai;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cyrillic_extended_b;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_bamum;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_modifier_tone_letters;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_latin_extended_d;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_syloti_nagri;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_common_indic_number_forms;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_phags_pa;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_saurashtra;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_devanagari_extended;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_kayah_li;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_rejang;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hangul_jamo_extended_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_javanese;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_myanmar_extended_b;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cham;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_myanmar_extended_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tai_viet;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_meetei_mayek_extensions;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ethiopic_extended_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_latin_extended_e;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cherokee_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_meetei_mayek;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hangul_syllables;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hangul_jamo_extended_b;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_high_surrogates;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_high_private_use_surrogates;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_low_surrogates;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_private_use_area;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_compatibility_ideographs;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_alphabetic_presentation_forms;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_arabic_presentation_forms_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_variation_selectors;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_vertical_forms;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_combining_half_marks;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_compatibility_forms;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_small_form_variants;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_arabic_presentation_forms_b;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_halfwidth_and_fullwidth_forms;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_specials;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_linear_b_syllabary;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_linear_b_ideograms;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_aegean_numbers;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ancient_greek_numbers;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ancient_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_phaistos_disc;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_lycian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_carian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_coptic_epact_numbers;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_old_italic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_gothic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_old_permic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ugaritic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_old_persian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_deseret;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_shavian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_osmanya;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_osage;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_elbasan;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_caucasian_albanian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_linear_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cypriot_syllabary;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_imperial_aramaic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_palmyrene;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_nabataean;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hatran;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_phoenician;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_lydian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_meroitic_hieroglyphs;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_meroitic_cursive;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_kharoshthi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_old_south_arabian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_old_north_arabian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_manichaean;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_avestan;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_inscriptional_parthian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_inscriptional_pahlavi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_psalter_pahlavi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_old_turkic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_old_hungarian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_hanifi_rohingya;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_rumi_numeral_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_old_sogdian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_sogdian;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_elymaic;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_brahmi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_kaithi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_sora_sompeng;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_chakma;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mahajani;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_sharada;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_sinhala_archaic_numbers;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_khojki;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_multani;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_khudawadi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_grantha;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_newa;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tirhuta;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_siddham;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_modi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mongolian_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_takri;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ahom;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_dogra;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_warang_citi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_nandinagari;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_zanabazar_square;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_soyombo;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_pau_cin_hau;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_bhaiksuki;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_marchen;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_masaram_gondi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_gunjala_gondi;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_makasar;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tamil_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cuneiform;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cuneiform_numbers_and_punctuation;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_early_dynastic_cuneiform;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_egyptian_hieroglyphs;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_egyptian_hieroglyph_format_controls;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_anatolian_hieroglyphs;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_bamum_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mro;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_bassa_vah;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_pahawh_hmong;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_medefaidrin;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_miao;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ideographic_symbols_and_punctuation;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tangut;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tangut_components;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_kana_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_kana_extended_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_small_kana_extension;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_nushu;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_duployan;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_shorthand_format_controls;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_byzantine_musical_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_musical_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ancient_greek_musical_notation;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mayan_numerals;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tai_xuan_jing_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_counting_rod_numerals;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mathematical_alphanumeric_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_sutton_signwriting;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_glagolitic_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_nyiakeng_puachue_hmong;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_wancho;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mende_kikakui;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_adlam;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_indic_siyaq_numbers;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ottoman_siyaq_numbers;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_arabic_mathematical_alphabetic_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_mahjong_tiles;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_domino_tiles;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_playing_cards;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_enclosed_alphanumeric_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_enclosed_ideographic_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_miscellaneous_symbols_and_pictographs;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_emoticons;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_ornamental_dingbats;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_transport_and_map_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_alchemical_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_geometric_shapes_extended;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_supplemental_arrows_c;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_supplemental_symbols_and_pictographs;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_chess_symbols;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_symbols_and_pictographs_extended_a;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_unified_ideographs_extension_b;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_unified_ideographs_extension_c;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_unified_ideographs_extension_d;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_unified_ideographs_extension_e;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_unified_ideographs_extension_f;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_cjk_compatibility_ideographs_supplement;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_tags;
FONT_CHEF_EXPORT extern struct fc_unicode_block const fc_variation_selectors_supplement;

#ifdef __cplusplus
}
#endif

#endif /* FONT_CHEF_UNICODE_BLOCK_H */
