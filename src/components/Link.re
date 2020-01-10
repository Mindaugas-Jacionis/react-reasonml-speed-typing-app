let component = ReasonReact.statelessComponent("Link");

let renderWords = wordsArray =>
  Array.map(
    word => <span> {ReasonReact.string(word ++ " ")} </span>,
    wordsArray,
  );

let make = (~href, ~text, _children) => {
  ...component,

  render: _self =>
    <a onClick={_event => ReasonReactRouter.push(href)}>
      {ReasonReact.string(text)}
    </a>,
};