WRAP_CLASS("itk::Index")
  foreach(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE(${d} ${d})
  endforeach(d)
END_WRAP_CLASS()
