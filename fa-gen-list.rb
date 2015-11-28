#! /usr/bin/env ruby

require 'yaml'

icons = YAML.load(File.read("fa-icons.yml"))
id2unicode = icons["icons"].map{|i| i.values_at("id", "unicode")}.to_h
id2unicode.each do |key, value|
  id2unicode[key] = value.to_i(16).chr(Encoding::UTF_8)
end
File.open('fa-icon-list.go', 'w+') do |f|
  f.puts "package fa"
  f.puts ""
  f.puts "type Icon struct {"
  f.puts "  Id string"
  f.puts "  Unicode string"
  f.puts "}"
  f.puts "var List = []Icon{"
  id2unicode.each do |key, value|
    f.puts %(  {"#{key}", "#{value}"},)
  end
  f.puts "}"
end
