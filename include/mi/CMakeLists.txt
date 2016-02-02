SET ( INCLUDE_FILES base.hpp
      Argument.hpp
      Attribute.hpp
      AttributeSet.hpp
      BooleanAttribute.hpp
      Clamp.hpp
      CommandTemplate.hpp
      DoubleNumericAttribute.hpp
      Exporter.hpp
      FileLister.hpp
      FileNameConverter.hpp
      Importer.hpp
      Limits.hpp
      NumericAttribute.hpp
      ParallelFor.hpp
      Parse.hpp
      PriorityQueue.hpp
      Progress.hpp
      Routine.hpp
      SvgRenderer.hpp
      StringAttribute.hpp
      SystemInfo.hpp
      TestSuite.hpp
      TestCase.hpp
      Thread.hpp
      Timer.hpp
      Tokenizer.hpp
      TripleNumericAttribute.hpp
      XmlDocument.hpp
      XmlDocumentExporter.hpp
      XmlNode.hpp
      XmlText.hpp
      XmlElement.hpp
      xml.hpp
    )
INSTALL ( FILES ${INCLUDE_FILES}
          DESTINATION include/mi
          PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )
