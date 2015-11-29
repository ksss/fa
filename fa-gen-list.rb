#! /usr/bin/env ruby

require 'yaml'

icons = YAML.load(File.read("fa-icons.yml"))
id2unicode = icons["icons"].map{|i| i.values_at("id", "unicode")}

puts <<-CODE
struct icon {
  const char *id, *unicode, *code;
};
const struct icon icon_list[] = {
#{id2unicode.map { |key, value|
  %(  {"#{key}", "#{value.to_i(16).chr(Encoding::UTF_8)}", "#{value}"},)
}.join("\n")}
};
CODE
